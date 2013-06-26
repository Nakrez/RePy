#ifndef TASKS_LIBTASKS_HH
# define TASKS_LIBTASKS_HH

# include <tasks/callback-task.hh>
# include <tasks/boolean-task.hh>

# define REGULAR_TASK(Argv, Description, Dep, Callback)         \
    extern void (Callback)();                                   \
static tasks::CallbackTask task_##Callback(Description, Argv,   \
                                           Dep, Callback)

# define BOOLEAN_TASK(Argv, Description, Dep, Boolean)         \
    extern bool Boolean;                                       \
static tasks::BooleanTask task_##Callback(Description, Argv,   \
                                           Dep, Boolean)

#endif /* !TASKS_LIBTASKS_HH */
