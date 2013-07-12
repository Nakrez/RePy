#include <cpp/tasks.hh>

namespace cpp
{
    void cpp_generator()
    {
        assert(ast::program_ast && "No ast to transform to cpp");

        Generator gen(std::cout);

        gen.visit(ast::program_ast);
    }
} // namespace cpp
