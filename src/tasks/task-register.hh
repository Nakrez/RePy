#ifndef TASKS_TASK_REGISTER_HH
# define TASKS_TASK_REGISTER_HH

# include <list>

namespace tasks
{
    class TaskRegister
    {
        TaskRegister(const TaskRegister&) = delete;
        TaskRegister operator=(const TaskRegister&) = delete;

        public:
            static TaskRegister& instance();

        private:
            TaskRegister();
            ~TaskRegister();
    };
} // namespace tasks

#endif /* !TASKS_TASK_REGISTER_HH */
