#ifndef DESUGAR_TASKS_HH
# define DESUGAR_TASKS_HH

# include <cassert>

# include <tasks/libtasks.hh>

# include <type/type-checker.hh>

namespace desugar
{
    REGULAR_TASK("f|function-call-desugar", "Compute function call desugar",
                 "compute-binding", fun_call_desugar);
} // namespace desugar

#endif /* !DESUGAR_TASKS_HH */
