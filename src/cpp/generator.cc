#include <cpp/generator.hh>
#include <ast/all.hh>

namespace cpp
{
    Generator::Generator(std::ostream& o)
        : o_(o)
    {}

    Generator::~Generator()
    {}
} // namespace cpp
