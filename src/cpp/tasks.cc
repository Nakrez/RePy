#include <cpp/tasks.hh>

namespace cpp
{
    void cpp_generator()
    {
        assert(ast::program_ast && "No ast to transform to cpp");


        CodeGenerator cgen(std::cout);

        cgen.visit(ast::program_ast);
    }

    void header_generator()
    {
        assert(ast::program_ast && "No ast to transform to cpp header");

        HeaderGenerator hgen(std::cout);

        hgen.visit(ast::program_ast);
    }
} // namespace cpp
