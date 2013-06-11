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

    void TaskRegister::register_task(BasicTask& task)
    {
        // TODO : verify if tasks not already decalred
        registered_tasks_.push_back(&task);
    }

    const std::list<BasicTask*>& TaskRegister::registered_tasks_get()
    {
        return registered_tasks_;
    }
} // namespace tasks
