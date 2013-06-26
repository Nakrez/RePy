#include <misc/indent.hh>
#include <iostream>
#include <iomanip>

namespace misc
{
    long int& indent_lvl(std::ostream& o)
    {
        static const long int lvl = std::ios::xalloc();

        return o.iword(lvl);
    }

    std::ostream& indent(std::ostream& o)
    {
        indent_lvl(o) += 4;

        return o;
    }

    std::ostream& dedent(std::ostream& o)
    {
        indent_lvl(o) -= 4;

        return o;
    }

    std::ostream& iendl(std::ostream& o)
    {
        o << std::endl;

        char f = o.fill(' ');

        o << std::setw(indent_lvl(o)) << "" << std::setfill(f);

        return o;
    }

    std::ostream& indentendl(std::ostream& o)
    {
        o << indent << iendl;

        return o;
    }

    std::ostream& dedentendl(std::ostream& o)
    {
        o << dedent << iendl;

        return o;
    }
} // namespace misc
