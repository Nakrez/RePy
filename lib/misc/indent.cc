#include <misc/indent.hh>

namespace misc
{
    static long int& indent_lvl(std::ostream& o)
    {
        static const long int lvl = std::ios::xalloc();

        return o.iword(lvl);
    }

    std::ostream& indent(std::ostream& o)
    {
        indent_lvl(o) += 2;

        return o;
    }

    std::ostream& dedent(std::ostream& o)
    {
        indent_lvl(o) -= 2;

        return o;
    }

    std::ostream& iendl(std::ostream& o)
    {
        o << std::endl;

        long int i = indent_lvl(o);

        o << std::setw(i) << "" << std::setfill(' ');

        return o;
    }

    std::ostream& indentendl(std::ostream& o)
    {
        indent_lvl(o) += 2;

        o << iendl;

        return o;
    }

    std::ostream& dedentendl(std::ostream& o)
    {
        indent_lvl(o) -= 2;

        o << iendl;

        return o;
    }
} // namespace misc
