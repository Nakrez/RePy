#ifndef TASKS_CALLBACK_TASK_HH
# define TASKS_CALLBACK_TASK_HH

# include <tasks/basic-task.hh>

namespace tasks
{
    class CallbackTask
    {
        public:
            CallbackTask();
            virtual ~CallbackTask();

            virtual void run();
    };
} // namespace tasks

#endif /* !TASKS_CALLBACK_TASK_HH */
