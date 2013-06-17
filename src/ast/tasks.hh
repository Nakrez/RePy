#ifndef AST_TASKS_HH
# define AST_TASKS_HH

# include <typy.hh>

# include <ast/pretty-printer.hh>

# include <tasks/libtasks.hh>

namespace ast
{
    REGULAR_TASK("P|pretty-print", "Pretty print an input file", "parse",
                 pretty_input_file);
}

#endif /* !AST_TASKS_HH */
