#include <tasks/basic-task.hh>

namespace tasks
{
    BasicTask::BasicTask(const std::string& name,
                         const std::string& description,
                         const std::string& opt)
        : name_(name)
        , description_(description)
    {
        if (opt.length() >= 2 && opt[1] == '|')
        {
            short_opt_ = '-' + opt.substr(0, 1);
            long_opt_ = "--" + opt.substr(2, opt.length() - 2);
        }
        else
            long_opt_ = opt;
    }

    BasicTask::~BasicTask()
    {}

    const std::string& BasicTask::name_get() const
    {
        return name_;
    }

    const std::string& BasicTask::description_get() const
    {
        return description_;
    }

    const std::string& BasicTask::short_opt_get() const
    {
        return short_opt_;
    }

    const std::string& BasicTask::long_opt_get() const
    {
        return long_opt_;
    }
} // namespace tasks
