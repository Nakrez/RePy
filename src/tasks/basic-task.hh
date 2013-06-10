#ifndef TASKS_BASIC_TASK_HH
# define TASKS_BASIC_TASK_HH

# include <string>

namespace tasks
{
    class BasicTask
    {
        public:
            BasicTask(const std::string& name,
                      const std::string& description,
                      const std::string& opt);
            virtual ~BasicTask();

            virtual void run() = 0;

            const std::string& name_get() const;
            const std::string& description_get() const;
            const std::string& short_opt_get() const;
            const std::string& long_opt_get() const;

        private:
            std::string name_;
            std::string description_;
            std::string short_opt_;
            std::string long_opt_;
    };
} // namespace tasks

#endif /* !TASKS_BASIC_TASK_HH */
