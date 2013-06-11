#ifndef PARSER_TASKS_HH
# define PARSER_TASKS_HH

# include <tasks/libtasks.hh>

namespace parser
{
    REGULAR_TASK("p|parse", "Parse an input file", "", parse_input_file);
} // namespace parser

#endif /* !PARSER_TASKS_HH */
