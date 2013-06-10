#ifndef TASKS_CALLBACK_TASK_HH
# define TASKS_CALLBACK_TASK_HH

# include <tasks/basic-task.hh>

namespace tasks
{
    typedef void (*task_callback)();

    class CallbackTask : public BasicTask
    {
        public:
            CallbackTask(const std::string& name,
                         const std::string& description,
                         const std::string& opt,
                         task_callback callback);
            virtual ~CallbackTask();

            task_callback callback_get() const;

            virtual void run();

        private:
            task_callback callback_;
    };
} // namespace tasks

#endif /* !TASKS_CALLBACK_TASK_HH */
