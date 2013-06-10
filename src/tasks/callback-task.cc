#include <tasks/callback-task.hh>

namespace tasks
{
    CallbackTask::CallbackTask(const std::string& name,
                               const std::string& description,
                               const std::string& opt,
                               task_callback callback)
        : BasicTask(name, description, opt)
        , callback_(callback)
    {}

    CallbackTask::~CallbackTask()
    {}

    task_callback CallbackTask::callback_get() const
    {
        return callback_;
    }

    void CallbackTask::run()
    {

    }
} // namespace tasks
