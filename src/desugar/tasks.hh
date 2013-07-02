#ifndef DESUGAR_TASKS_HH
# define DESUGAR_TASKS_HH

# include <cassert>

# include <typy.hh>

# include <tasks/libtasks.hh>

# include <bind/binder.hh>

# include <desugar/function-call-desugar.hh>
# include <desugar/function-dec-desugar.hh>

namespace desugar
{
    REGULAR_TASK("f|function-call-desugar", "Compute function call desugar",
                 "compute-binding", fun_call_desugar);

    REGULAR_TASK("d|function-dec-desugar",
                 "Compute function declaration desugar",
                 "function-call-desugar", fun_dec_desugar);
} // namespace desugar

#endif /* !DESUGAR_TASKS_HH */
