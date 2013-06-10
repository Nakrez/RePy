#include <tasks/task-invoker.hh>

int main(int argc, char *argv[])
{
    tasks::TaskInvoker program;

    if (argc == 1)
    {
        program.tpy_usage();
        return 0;
    }


    return 0;
}
