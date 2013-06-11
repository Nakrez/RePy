#ifndef TASKS_TASK_INVOKER_HH
# define TASKS_TASK_INVOKER_HH

# include <iostream>
# include <cstring>

# include <argp.h>

# include <tasks/task-register.hh>

namespace tasks
{
    class TaskInvoker
    {
        TaskInvoker(const TaskRegister&) = delete;
        TaskInvoker operator=(const TaskRegister&) = delete;

        public:
            static TaskInvoker& instance();

            char* parse_argv(int argc, char* argv[]);
            void run();
            void enable_task(BasicTask* task);

        private:
            TaskInvoker();
            ~TaskInvoker();

        private:
            std::list<BasicTask*> tasks_to_run_;
    };
} // namespace tasks

#endif /* !TASKS_TASK_INVOKER_HH */
