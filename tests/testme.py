#!env /usr/bin/python2

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
import os
import re
import ConfigParser
import filecmp
import argparse

testme_version = "0.1"
testme_config_name = "testme.conf"
testme_args = {}
testme_to_run = {}
testme_env = {}

def parse_string(string):
    m = re.search('\$\{(.*)\}', string)

    if m == None:
        return string

    if testme_env.get(m.group(1), None) == None:
        return string

    return re.sub('\$\{(.*)\}', testme_env[m.group(1)], string)

def update_env(cat):
    global testme_env

    testme_env['TESTME_TESTDIR'] = testme_args['dir']
    testme_env['TESTME_CATEGORY'] = cat
    testme_env['TESTME_CATEGORY_DIR'] = os.path.join(testme_args['dir'], cat)

def change_extension(change_file, ext):
    path = os.path.splitext(change_file)
    return path[0] + "." + ext

def print_verbose(msg):
    if testme_args.get('verbose', None):
        print msg

def run(category, test_file):
    global testme_env

    command = ""
    ret_value = True

    if testme_to_run[category]['input']:
        full_path = os.path.join(testme_to_run[category]['input_dir'], test_file)
        testme_env['TESTME_RUNNING_INPUT'] = full_path

    if testme_to_run[category]['stdin'] and testme_to_run[category]['input']:
        stdin = change_extension(full_path, testme_to_run[category]['stdin_ext'])
        command = "cat " + stdin + " | "
    elif testme_to_run[category]['stdin']:
        full_path = os.path.join(testme_to_run[category]['stdin_dir'], test_file)
        command = "cat " + full_path + " | "

    command += parse_string(testme_to_run[category]['cmd_line'])

    if testme_to_run[category]['stdout']:
        command += " > /tmp/testme.stdout"
        stdout = change_extension(test_file, testme_to_run[category]['stdout_ext'])
        stdout = os.path.join(testme_to_run[category]['stdout_dir'], stdout)
    if testme_to_run[category]['stderr']:
        command += " > /tmp/testme.stderr"
        stderr = change_extension(test_file, testme_to_run[category]['stderr_ext'])
        stderr = os.path.join(testme_to_run[category]['stderr_dir'], stderr)

    command_exit = os.WEXITSTATUS(os.system(command))

    if testme_to_run[category]['stdout']:
        if os.path.exists(stdout):
            ret_value &= filecmp.cmp("/tmp/testme.stdout", stdout)
        else:
            print_verbose("\033[33m[TESTME] " + stdout + " not present stdout ignored\033[0m")
    if testme_to_run[category]['stderr']:
        if os.path.exists(stderr):
            ret_value &= filecmp.cmp("/tmp/testme.stdout", stderr)
        else:
            print_verbose("\033[33m[TESTME] " + stderr + " not present stderr ignored\033[0m")

    if testme_to_run[category]['check_code']:
        ret_value &= testme_to_run[category]['error_code'] == command_exit

    return ret_value

def print_result(test_result, category, file_name):
    if (test_result and (testme_to_run[category]['display_ok_tests']
                        or testme_args.get('full_display', False))
                   and not testme_args.get('extra_light_display', False)):
        print "\033[32m[TESTME] Test :", file_name, "passed\033[0m"
    elif (not test_result and (testme_to_run[category]['display_ko_tests']
                               or testme_args.get('full_display', False)
                               or testme_args.get('light_display', False))
                          and not testme_args.get('extra_light_display', False)):
        print "\033[91m[TESTME] Test :", file_name, "failed\033[0m"

def is_runnable_category(cat_name):
    if testme_args.get('category', None) != None:
        return testme_args['category'].count(cat_name) > 0

    return True

def run_tests():
    total_test = 0
    total_pass = 0
    for category in testme_to_run:
        cat_test = 0
        cat_pass = 0

        if not is_runnable_category(category):
            continue
        print "\n[TESTME] Running tests in", category
        dir_to_run = 'input_dir' if testme_to_run[category]['input'] else 'stdin_dir'
        ext = 'input_ext' if testme_to_run[category]['input'] else 'stdin_ext'

        try:
            for files in os.listdir(testme_to_run[category][dir_to_run]):
                if files.endswith(testme_to_run[category][ext]):
                    total_test += 1
                    cat_test += 1
                    test_result = run(category, files)
                    if test_result:
                        cat_pass += 1
                        total_pass += 1
                    print_result(test_result, category, files)

            if testme_to_run[category]['display_summary'] == 1:
                print "[TESTME] Category : '" + category + "' :", cat_pass, "/", cat_test

        except OSError:
            sys.stderr.write("[TESTME][ERROR] Fatal error with directory : " +
                             testme_to_run[category][dir_to_run] + "\n")


    print "\n[TESTME] Final result :", total_pass, "/", total_test

def die_on_error(msg):
    sys.stderr.write("[TESTME][ERROR] " + msg + "\n")
    sys.exit(1)

def default_category(cat_name):
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
            'error_code' : 0,
            'display_ok_tests' : 1,
            'display_ko_tests' : 1,
            'display_summary' : 1}

def get_bool(config, dico, section, value):
    try:
        dico[section][value] = config.getboolean(section, value)
    except ConfigParser.NoOptionError:
        return 0
    except:
        die_on_error(value + " in section '" + section + "' is not a boolean")

def get_string(config, dico, section, value):
    try:
        txt = config.get(section, value)
        dico[section][value] = parse_string(txt)
        return
    except ConfigParser.NoOptionError:
        return

def get_int(config, dico, section, value):
    try:
        dico[section][value] = config.getint(section, value)
    except ConfigParser.NoOptionError:
        return 0
    except:
        die_on_error(value + " in section '" + section + "' is not an integer")

def parse_config():
    global testme_to_run

    config_full_path = os.path.join(testme_args['dir'], testme_config_name)
    print_verbose("[TESTME] Parsing configuration file : " + config_full_path)

    config_file = ConfigParser.RawConfigParser()
    config_file.read(config_full_path)

    for section in config_file.sections():
        testme_to_run[section] = default_category(section)
        update_env(section)

        get_bool(config_file, testme_to_run, section, 'stdout')
        get_bool(config_file, testme_to_run, section, 'stdin')
        get_bool(config_file, testme_to_run, section, 'stderr')
        get_bool(config_file, testme_to_run, section, 'input')
        get_string(config_file, testme_to_run, section, 'stdout_dir')
        get_string(config_file, testme_to_run, section, 'stdin_dir')
        get_string(config_file, testme_to_run, section, 'stderr_dir')
        get_string(config_file, testme_to_run, section, 'input_dir')
        get_string(config_file, testme_to_run, section, 'cmd_line')
        get_string(config_file, testme_to_run, section, 'input_ext')
        get_string(config_file, testme_to_run, section, 'stdin_ext')
        get_string(config_file, testme_to_run, section, 'stdout_ext')
        get_string(config_file, testme_to_run, section, 'stderr_ext')
        get_string(config_file, testme_to_run, section, 'cmd_line')
        get_bool(config_file, testme_to_run, section, 'check_code')
        get_int(config_file, testme_to_run, section, 'error_code')
        get_bool(config_file, testme_to_run, section, 'display_ok_tests')
        get_bool(config_file, testme_to_run, section, 'diplay_ko_tests')
        get_bool(config_file, testme_to_run, section, 'display_summary')

def parse_argv():
    global testme_running_dir, testme_verbose, testme_args
    argc = 1

    if len (sys.argv) == 1:
        return # No option to parse

    parser = argparse.ArgumentParser(description='TestMe ' + testme_version
                                     + ' by Baptiste COVOLATO')

    parser.add_argument('--dir', action="store",
                        help='The directory where you want to run testme')
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
    parse_argv()

    if testme_args.get('dir', None) == None:
        testme_args['dir'] = os.getcwd()

    print_verbose("[TESTME] Running directory : " + testme_args['dir'])
    parse_config()
    run_tests()

main()
