#ifndef DESUGAR_TASKS_HH
# define DESUGAR_TASKS_HH

# include <cassert>

# include <repy.hh>

# include <tasks/libtasks.hh>

# include <bind/binder.hh>

# include <desugar/declaration-generator.hh>
# include <desugar/global-desugar.hh>

# include <bind/binder.hh>

# include <type/type-checker.hh>


namespace desugar
{
    REGULAR_TASK("declaration-generator",
                 "Generates clean prototypes of function",
                 "parse", dec_generator);

    REGULAR_TASK("g|global-desugar",
                 "Compute global desugar",
                 "type-check", global_desugar);
} // namespace desugar

#endif /* !DESUGAR_TASKS_HH */
