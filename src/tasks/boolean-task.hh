#ifndef TASKS_BOOLEAN_TASK_HH
# define TASKS_BOOLEAN_TASK_HH

# include <tasks/basic-task.hh>

namespace tasks
{
    class BooleanTask : public BasicTask
    {
        public:
            BooleanTask(const std::string& description,
                        const std::string& opt,
                        const std::string& dependancy,
                        bool& boolean);
            virtual ~BooleanTask();

            virtual void run();

        protected:
            bool& bool_;
    };
}

#endif /* !TASKS_BOOLEAN_TASK_HH */
