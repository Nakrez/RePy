#include <cpp/tasks.hh>

namespace cpp
{
    void cpp_generator()
    {
        assert(ast::program_ast && "No ast to transform to cpp");

        CodeGenerator cgen(std::cout);

        cgen.visit(ast::program_ast);
        cgen.generate_main();
    }

    void header_generator()
    {
        assert(ast::program_ast && "No ast to transform to cpp header");

        std::cout << "#include <repy/repy.hh>" << std::endl;

        HeaderGenerator hgen(std::cout);

        hgen.visit(ast::program_ast);
    }
} // namespace cpp
