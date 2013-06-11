#include <typy.hh>
#include <tasks/task-invoker.hh>

char* typy::input_name = nullptr;

int main(int argc, char *argv[])
{
    typy::input_name = tasks::TaskInvoker::instance().parse_argv(argc, argv);
    tasks::TaskInvoker::instance().run();

    return 0;
}
