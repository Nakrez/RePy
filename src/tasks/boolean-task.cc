#include <tasks/boolean-task.hh>

namespace tasks
{
    BooleanTask::BooleanTask(const std::string& description,
                             const std::string& opt,
                             const std::string& dependancy,
                             bool& boolean)
        : BasicTask(description, opt, dependancy)
        , bool_(boolean)
    {}

    BooleanTask::~BooleanTask()
    {}

    void BooleanTask::run()
    {
        bool_ = true;
    }
} // namespace tasks
