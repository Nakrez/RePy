#include <cpp/code-generator.hh>
#include <ast/all.hh>

namespace cpp
{
    CodeGenerator::CodeGenerator(std::ostream& o)
        : o_(o)
        , params_(false)
    {}

    CodeGenerator::~CodeGenerator()
    {}

    void CodeGenerator::generate_main()
    {
        o_ << "int main()" << misc::iendl;
        o_ << "{" << misc::indentendl;

        for (auto mod : modules_)
            o_ << "__" << mod << "__::__init();" << misc::iendl;

        o_ << misc::dedentendl << "}" << misc::iendl;
    }

    void CodeGenerator::operator()(ast::ExprList& ast)
    {
        auto beg = ast.list_get().begin();
        auto end = ast.list_get().end();

        for (auto it = beg; it != end; ++it)
        {
            if (it != beg)
                code_ << ", ";

            (*it)->accept(*this);
        }
    }

    void CodeGenerator::operator()(ast::ModuleStmt& ast)
    {
        modules_.push_back(ast.name_get());

        o_ << "namespace __" << ast.name_get() << "__" << misc::iendl;
        o_ << "{" << misc::indentendl;

        code_ << misc::indent;

        ast.content_get()->accept(*this);

        o_ << code_.str();

        o_ << misc::dedentendl;
        o_ << "}" << misc::iendl;
    }

    void CodeGenerator::operator()(ast::FunctionDec& ast)
    {
        // Generating all functions prototypes
        for (auto proto : ast.to_generate_get())
        {
            ast.type_set(proto);

            code_ << ast.type_get()->return_type_get()->cpp_type() << " "
                << ast.name_get() << "(";

            params_ = true;
            if (ast.args_get())
                ast.args_get()->accept(*this);
            params_ = false;

            code_ << ")" << misc::iendl << "{" << misc::indentendl;

            ast.body_get()->accept(*this);

            code_ << misc::dedentendl << "}" << misc::iendl;
        }
    }

    void CodeGenerator::operator()(ast::IdVar& ast)
    {
        if (params_)
            code_ << ast.type_get()->cpp_type() << " ";

        code_ << ast.id_get();
    }
} // namespace cpp
