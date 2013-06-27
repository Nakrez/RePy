#ifndef TYPE_TASKS_HH
# define TYPE_TASKS_HH

# include <cassert>

# include <typy.hh>

# include <tasks/libtasks.hh>

# include <type/type-checker.hh>

namespace type
{
    bool print_type = false;

    REGULAR_TASK("t|type-check", "Compute type checking on ast",
                 "compute-binding", type_check);

    BOOLEAN_TASK("T|print-type-infos", "Print related type infos",
                 "type-check", print_type);
} // namespace type

#endif /* !TYPE_TASKS_HH */
