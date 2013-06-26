#ifndef BIND_TASKS_HH
# define BIND_TASKS_HH

# include <typy.hh>

# include <tasks/libtasks.hh>

namespace bind
{
    bool print_bind = true;

    REGULAR_TASK("b|compute-binding", "Compute bind on ast", "parse",
                 compute_bind);

    BOOLEAN_TASK("B|print-binding-infos", "Print related binding infos",
                 "compute-binding", print_bind);

} // namespace bind

#endif /* !BIND_TASKS_HH */
