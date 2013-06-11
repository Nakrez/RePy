#ifndef TASKS_LIBTASKS_HH
# define TASKS_LIBTASKS_HH

# include <tasks/callback-task.hh>

# define REGULAR_TASK(Argv, Description, Dep, Callback)         \
    extern void (Callback)();                                   \
static tasks::CallbackTask task_##Callback(Description, Argv,   \
                                           Dep, Callback)

#endif /* !TASKS_LIBTASKS_HH */
