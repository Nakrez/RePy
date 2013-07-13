#include <misc/error.hh>

#include <tasks/task-invoker.hh>
#include <repy.hh>

char* repy::input_name = nullptr;

int main(int argc, char *argv[])
{
    repy::input_name = tasks::TaskInvoker::instance().parse_argv(argc, argv);

    try {
        tasks::TaskInvoker::instance().run();
    }
    catch (misc::Error& error)
    {
        std::cerr << error.msg_get();

        return error.error_type_get();
    }

    return 0;
}
