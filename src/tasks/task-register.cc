#include <tasks/task-register.hh>

namespace tasks
{
    TaskRegister& TaskRegister::instance()
    {
        static TaskRegister inst;

        return inst;
    }

    TaskRegister::TaskRegister()
    {}

    TaskRegister::~TaskRegister()
    {}
} // namespace tasks
