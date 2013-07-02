#ifndef CLONER_TASKS_HH
# define CLONER_TASKS_HH

# include <cassert>

# include <typy.hh>

# include <tasks/libtasks.hh>

# include <cloner/ast-cloner.hh>

namespace cloner
{
    REGULAR_TASK("clone", "Clone the ast (used for debug purpose)",
                 "parse", clone_ast);
} // namespace cloner

#endif /* !CLONER_TASKS_HH */
