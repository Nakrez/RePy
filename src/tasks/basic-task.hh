#ifndef TASKS_BASIC_TASK_HH
# define TASKS_BASIC_TASK_HH

# include <string>

namespace tasks
{
    class BasicTask
    {
        public:
            BasicTask();
            virtual ~BasicTask();

            virtual void run() = 0;
    };
} // namespace tasks

#endif /* !TASKS_BASIC_TASK_HH */
