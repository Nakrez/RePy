#include <tasks/callback-task.hh>

namespace tasks
{
    CallbackTask::CallbackTask(const std::string& description,
                               const std::string& opt,
                               const std::string& dependancy,
                               task_callback callback)
        : BasicTask(description, opt, dependancy)
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
        callback_();
    }
} // namespace tasks
