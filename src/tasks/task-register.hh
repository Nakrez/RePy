#ifndef TASKS_TASK_REGISTER_HH
# define TASKS_TASK_REGISTER_HH

# include <list>

# include <tasks/basic-task.hh>

namespace tasks
{
    class TaskRegister
    {
        TaskRegister(const TaskRegister&) = delete;
        TaskRegister operator=(const TaskRegister&) = delete;

        public:
            static TaskRegister& instance();

            /// @brief  Register a new task
            void register_task(BasicTask& task);

            /// @brief  Get the list of all registered tasks
            const std::list<BasicTask*>& registered_tasks_get();

        private:
            TaskRegister();
            ~TaskRegister();

        private:
            std::list<BasicTask*> registered_tasks_;
    };
} // namespace tasks

#endif /* !TASKS_TASK_REGISTER_HH */
