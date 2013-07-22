#!env /usr/bin/python3

#Copyright (C) 2013 Baptiste COVOLATO <b.covolato@gmail.com>
#
#Permission is hereby granted, free of charge, to any person obtaining a copy of
#this software and associated documentation files (the "Software"), to deal in
#the Software without restriction, including without limitation the rights to
#use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
#of the Software, and to permit persons to whom the Software is furnished to do
#so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.

import sys
import subprocess
import os
import re
import configparser
import filecmp
import argparse
import logging
import time
from threading import Thread
from queue import Queue

testme_version = "0.2"
testme_config_name = "testme.conf"
testme_args = {'threads' : 1}

class ThreadPool:
    class _ThreadQueue(Thread):
        def __init__(self, pool, *args, **kwargs):
            super(ThreadPool._ThreadQueue, self).__init__(*args, **kwargs)
            self.tasks = pool.tasks
            self.daemon = True
            self.start()

        def run(self):
            while True:
                task,args = self.tasks.get(True)
                task(*args)
                self.tasks.task_done()

    def __init__(self, num=10):
        self.tasks = Queue(num)
        for _ in range(num):
            self._ThreadQueue(self)

    def add_task(self, target, args):
        self.tasks.put((target, args))

    def wait_completion(self):
        self.tasks.join()


class TestPrinter:
    def __init__(self):
        self.verbose = False
        self.summary_on = True
        self.extra = True
        self.light = True
        self.full = True

    def print_summary(self, category, good, total):
        if self.summary_on:
            print("[TESTME] Category : '" + category + "' :", good, "/", total)

    def print_verbose(self, message):
        if self.verbose:
            print(message)

    def print_error(self, message):
        print("\033[91m" + message + "\033[0m")

    def print_result(self, test_result, file_name, opt):
        if (test_result and ((opt or self.full) and not self.extra and not self.light)):
            print("\033[32m[TESTME] Test :", file_name, "passed\033[0m")
        elif (not test_result and ((opt or self.full or self.light) and not self.extra)):
            print("\033[91m[TESTME] Test :", file_name, "failed\033[0m")

    def print_timeout(self, file_name, opt):
        if ((opt or self.full or self.light) and not self.extra):
            print("\033[34m[TESTME] Test :", file_name, "timeout\033[0m")

class TestSuit:
    def __init__(self, printer):
        self.environement = {}
        self.test_list = {}
        self.running_cat = ""
        self.running_dir = ""
        self.ext = ""
        self.total_test = 0
        self.total_good = 0
        self.cat_test = 0
        self.cat_good = 0
        self.printer = printer

    def expand(self, string):
        while 1:
            m = re.search('\$\{(.*?)\}', string)

            if m == None or self.environement.get(m.group(1), None) == None:
                break

            string = re.sub('\$\{' + m.group(1) + '\}', self.environement[m.group(1)], string)

        return string

    def cat_field_get(self, field):
        if isinstance(self.test_list[self.running_cat][field], str):
            return self.expand(self.test_list[self.running_cat][field])
        else:
            return self.test_list[self.running_cat][field]

    def is_runnable(self):
        if testme_args.get('category', None) != None:
            return testme_args['category'].count(self.running_cat) > 0

        return True

    def change_extension(self, change_file, ext):
        path = os.path.splitext(change_file)
        return path[0] + "." + ext

    def stdin_input(self, test_name):
        stdin_val = ""

        if self.cat_field_get('stdin'):
            stdin_file = os.path.join(self.cat_field_get('stdin_dir'), test_name)
            stdin_file = self.change_extension(stdin_file, self.cat_field_get('stdin_ext'))
            stdin_val = ""
            if os.path.exists(stdin_file):
                stdin_fd = open(stdin_file, "r")
                stdin_val = stdin_fd.read()
                stdin_fd.close()

        return stdin_val

    def compare_out(self, output, value, ret, test_file):

        if self.cat_field_get(output):
            filename = self.change_extension(test_file, self.cat_field_get(output + '_ext'))
            filename = os.path.join(self.cat_field_get(output + '_dir'), filename)
            file_content = ""

            if os.path.exists(filename):
                fd = open(filename, "r")
                file_content = fd.read()
                fd.close()
            else:
                print_verbose("\033[33m[TESTME] " + filename + " not present " + output + " ignored\033[0m")

            ret = ret and (file_content == value)

        return ret

    def handle_timeout(self, process, test_file):
        timeout = self.cat_field_get('timeout')
        timeout = timeout + time.time()

        while time.time() < timeout and process.poll() == None:
            time.sleep(.001)

        if process.poll() == None:
            self.printer.print_timeout(test_file, self.cat_field_get('display_timeout_tests'))
            process.kill()
            return False

        return True

    def run_test(self, test_file):
        self.total_test += 1
        self.cat_test += 1

        ret_value = True

        if self.cat_field_get('input'):
            input_file = os.path.join(self.cat_field_get('input_dir'), test_file)
            self.environement['TESTME_RUNNING_INPUT'] = input_file

        self.environement['TESTME_TEMPFILE'] = self.change_extension(os.path.basename(test_file), 'tmp')
        stdinput = self.stdin_input(test_file)

        command = self.cat_field_get('cmd_line')

        process = subprocess.Popen(command, stdin=subprocess.PIPE,
                                   stdout=subprocess.PIPE,
                                   stderr=subprocess.PIPE,
                                   shell=True)

        process.stdin.write(stdinput.encode('utf-8'))
        process.stdin.close()

        if self.handle_timeout(process, test_file) == False:
            return

        stdout = process.stdout.read()
        stderr = process.stderr.read()

        stdout, stderr = stdout.decode('utf-8'), stderr.decode('utf-8')

        ret_value = self.compare_out('stdout', stdout, ret_value, test_file)
        ret_value = self.compare_out('stderr', stderr, ret_value, test_file)

        if self.cat_field_get('check_code'):
            ret_value &= str(process.returncode) in self.cat_field_get('error_code')

        if ret_value:
            self.cat_good += 1
            self.total_good += 1

        display_opt = ((ret_value and self.cat_field_get('display_ok_tests')) or
                      (not ret_value and self.cat_field_get('display_ko_tests')))

        self.printer.print_result(ret_value, test_file, display_opt)

        try:
            os.unlink(self.environement['TESTME_TEMPFILE'])
        except Exception:
            pass

    def thread_run(self, dir_file):
        if dir_file.endswith(self.cat_field_get(self.ext)):
            self.run_test(dir_file)

    def run_directory(self):
        global testme_args
        try:
            pool = ThreadPool(testme_args['threads'])
            for dir_file in os.listdir(self.cat_field_get(self.running_dir)):
                pool.add_task(target=self.run_test, args=(dir_file,))

            pool.wait_completion()

            if self.cat_field_get('display_summary') or self.printer.full:
                self.printer.print_summary(self.running_cat, self.cat_good,
                                           self.cat_test)

        except OSError:
           self.printer.print_error("[TESTME] Fatal error with " +
                                    "directory : " +
                                    self.cat_field_get(self.running_dir))

    def run(self):
        self.total_test = 0
        self.total_good = 0

        # Run every categories
        for cat in self.test_list:
            self.cat_test = 0
            self.cat_good = 0
            self.running_cat = cat
            self.environement['TESTME_CATEGORY'] = cat
            self.environement['TESTME_CATEGORY_DIR'] = os.path.join(self.environement['TESTME_TESTDIR'], cat)

            if not self.is_runnable():
                continue

            print("\n[TESTME] Running tests in", self.running_cat)
            self.running_dir = 'input_dir' if self.cat_field_get('input') else 'stdin_dir'
            self.ext = 'input_ext' if self.cat_field_get('input') else 'stdin_ext'

            self.run_directory()

        print("\n[TESTME] Final result :", self.total_good, "/", self.total_test)


class ConfigBuilder:
    def __init__(self, printer, filename):
        self.filename = filename
        self.configuration = {}
        self.printer = printer

    def default(self, cat_name):
        return {'stdout' : 0, # Stdout test
                'stdin' : 0, # Stdin test
                'stderr' : 0, # Stderr test
                'input' : 0, # Input test
                'input_dir' : os.path.join(testme_args['dir'], cat_name, "input"),
                'stdout_dir' : os.path.join(testme_args['dir'], cat_name, "stdout"),
                'stdin_dir' : os.path.join(testme_args['dir'], cat_name, "stdin"),
                'stderr_dir' : os.path.join(testme_args['dir'], cat_name, "stderr"),
                'input_ext' : 'inp',
                'stdout_ext' : 'out',
                'stdin_ext' : 'in',
                'stderr_ext' : 'err',
                'cmd_line' : '',
                'check_code' : 0,
                'timeout' : 5,
                'error_code' : ["0"],
                'display_ok_tests' : 1,
                'display_ko_tests' : 1,
                'display_timeout_tests' : 1,
                'display_summary' : 1}

    def get_bool(self, section, value):
        try:
            self.configuration[section][value] = self.parser.getboolean(section,
                                                                        value)
        except configparser.NoOptionError:
            return 0
        except:
            die_on_error(value + " in section '" + section + "' is not a boolean")

    def get_string(self, section, value):
        try:
            self.configuration[section][value] = self.parser.get(section, value)
            return
        except configparser.NoOptionError:
            return

    def get_int(self, section, value):
        try:
            self.configuration[section][value] = self.parser.getfloat(section, value)
        except configparser.NoOptionError:
            return 0
        except:
            die_on_error(value + " in section '" + section + "' is not an integer")

    def parse_config(self):
        self.parser = configparser.RawConfigParser()
        self.parser.read(self.filename)

        for section in self.parser.sections():
            self.configuration[section] = self.default(section)

            self.get_bool(section, 'stdout')
            self.get_bool(section, 'stdin')
            self.get_bool(section, 'stderr')
            self.get_bool(section, 'input')
            self.get_string(section, 'stdout_dir')
            self.get_string(section, 'stdin_dir')
            self.get_string(section, 'stderr_dir')
            self.get_string(section, 'input_dir')
            self.get_string(section, 'cmd_line')
            self.get_string(section, 'input_ext')
            self.get_string(section, 'stdin_ext')
            self.get_string(section, 'stdout_ext')
            self.get_string(section, 'stderr_ext')
            self.get_int(section, 'timeout')
            self.get_bool(section, 'check_code')
            self.get_string(section, 'error_code')
            self.get_bool(section, 'display_ok_tests')
            self.get_bool(section, 'diplay_ko_tests')
            self.get_bool(section, 'display_timeout_tests')
            self.get_bool(section, 'display_summary')

            if testme_args.get('timeout', None):
                self.configuration[section]['timeout'] = testme_args['timeout']
            if self.configuration[section]['error_code'] is str:
                self.configuration[section]['error_code'] = self.configuration[section]['error_code'].split("|")

def parse_argv():
    global testme_args
    argc = 1

    if len (sys.argv) == 1:
        return # No option to parse

    parser = argparse.ArgumentParser(description='TestMe ' + testme_version
                                     + ' by Baptiste COVOLATO')

    parser.add_argument('--dir', action="store",
                        help='The directory where you want to run testme')
    parser.add_argument('--threads', action="store", type=int,
                        help='Indicate the number of thread you want to use')
    parser.add_argument('--timeout', action="store", type=float,
                        help='Set a timeout for all tests')
    parser.add_argument('-v', '--verbose', action="store_true",
                        help='TestMe will display extra informations')
    parser.add_argument('-c', '--category', nargs='+', action="store",
                        help='Select specific categories to run')
    parser.add_argument('-x', '--extra-light-display', action="store_true",
                        help='Only print summary of each run category')
    parser.add_argument('-f', '--full-display', action="store_true",
                        help='Print all tests result')
    parser.add_argument('-l', '--light-display', action="store_true",
                        help='Print only failed tests')

    testme_args = vars(parser.parse_args())

def main():
    printer = TestPrinter()
    parse_argv()

    printer.verbose = testme_args.get('verbose', None)
    printer.extra = testme_args.get('extra_light_display', None)
    printer.light = testme_args.get('light_display', None)
    printer.full = testme_args.get('full_display', None)
    testme_args['threads'] = testme_args['threads'] if testme_args.get('threads', None) else 1

    if testme_args.get('dir', None) == None:
        testme_args['dir'] = os.getcwd()

    printer.print_verbose("[TESTME] Running directory : " + testme_args['dir'])
    config_full_path = os.path.join(testme_args['dir'], testme_config_name)

    config = ConfigBuilder(printer, config_full_path)
    config.parse_config()

    test_suit = TestSuit(printer)
    test_suit.environement['TESTME_TESTDIR'] = testme_args['dir']
    test_suit.test_list = config.configuration
    test_suit.run()

if __name__ == "__main__":
    main()
