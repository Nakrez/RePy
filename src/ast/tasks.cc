#include <ast/tasks.hh>
#include <ast/ast.hh>
#include <iostream>
#include <cassert>

namespace ast
{
    Ast* program_ast = nullptr;

    void pretty_input_file()
    {
        assert(program_ast);

        std::cout << "### Pretty printing AST ###" << std::endl;

        PrettyPrinter printer(std::cout);
        printer.visit(program_ast);
    }
}
