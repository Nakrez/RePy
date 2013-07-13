#include <cpp/header-generator.hh>
#include <ast/all.hh>

namespace cpp
{
    HeaderGenerator::HeaderGenerator(std::ostream& o)
        : o_(o)
    {}

    HeaderGenerator::~HeaderGenerator()
    {}

    void HeaderGenerator::operator()(ast::ModuleStmt& ast)
    {
        o_ << "namespace __" << ast.name_get() << "__" << misc::iendl;
        o_ << "{" << misc::indentendl;

        ast.content_get()->accept(*this);

        o_ << misc::dedentendl;
        o_ << "}" << misc::iendl;
    }

    void HeaderGenerator::operator()(ast::FunctionDec& ast)
    {
        // Generating all functions prototypes
        for (auto proto : ast.to_generate_get())
        {
            ast.type_set(proto);

            if (ast.args_get())
                ast.args_get()->accept(*this);

            ast.body_get()->accept(*this);
        }
    }
} // namespace cpp
