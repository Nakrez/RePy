#include <cpp/tasks.hh>

namespace cpp
{
    void cpp_generator()
    {
        assert(ast::program_ast && "No ast to transform to cpp");

        // HeaderGenerator hgen(std::cout);

        // hgen.visit(ast::program_ast);

        CodeGenerator cgen(std::cout);

        cgen.visit(ast::program_ast);
    }
} // namespace cpp
