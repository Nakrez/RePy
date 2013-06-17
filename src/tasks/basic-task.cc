#include <tasks/basic-task.hh>
#include <tasks/task-register.hh>

namespace tasks
{
    BasicTask::BasicTask(const std::string& description,
                         const std::string& opt,
                         const std::string& dependancy)
        : description_(description)
        , dep_(dependancy)
    {
        static int key = -1;

        if (opt.length() >= 2 && opt[1] == '|')
        {
            key_ = opt[0];
            long_opt_ = opt.substr(2, opt.length() - 2);
        }
        else
        {
            long_opt_ = opt;
            key_ = key--;
        }

        TaskRegister::instance().register_task(*this);
    }

    BasicTask::~BasicTask()
    {}

    const std::string& BasicTask::dep_get() const
    {
        return dep_;
    }

    const std::string& BasicTask::description_get() const
    {
        return description_;
    }

    int BasicTask::key_get() const
    {
        return key_;
    }

    const std::string& BasicTask::long_opt_get() const
    {
        return long_opt_;
    }
} // namespace tasks
