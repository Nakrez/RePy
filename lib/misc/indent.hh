#ifndef MISC_INDENT_HH
# define MISC_INDENT_HH

# include <iostream>
# include <iomanip>

namespace misc
{
    std::ostream& indent(std::ostream& o);
    std::ostream& dedent(std::ostream& o);
    std::ostream& indentendl(std::ostream& o);
    std::ostream& dedentendl(std::ostream& o);
    std::ostream& iendl(std::ostream& o);
} // namespace misc

#endif /* !MISC_INDENT_HH */
