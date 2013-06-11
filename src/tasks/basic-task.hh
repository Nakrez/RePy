#ifndef TASKS_BASIC_TASK_HH
# define TASKS_BASIC_TASK_HH

# include <string>

namespace tasks
{
    class BasicTask
    {
        public:
            BasicTask(const std::string& description,
                      const std::string& opt,
                      const std::string& dependancy);
            virtual ~BasicTask();

            virtual void run() = 0;

            const std::string& description_get() const;
            int key_get() const;
            const std::string& long_opt_get() const;
            const std::string& dep_get() const;

        private:
            std::string description_;
            int key_;
            std::string long_opt_;
            std::string dep_;
    };
} // namespace tasks

#endif /* !TASKS_BASIC_TASK_HH */
