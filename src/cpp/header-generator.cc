#include <cpp/header-generator.hh>
#include <ast/all.hh>

namespace cpp
{
    HeaderGenerator::HeaderGenerator(std::ostream& o)
        : o_(o)
        , params_(false)
        , current_class_(nullptr)
    {}

    HeaderGenerator::~HeaderGenerator()
    {}

    void HeaderGenerator::operator()(ast::ExprList& ast)
    {
        auto beg = ast.list_get().begin();
        auto end = ast.list_get().end();

        for (auto it = beg; it != end; ++it)
        {
            if (it != beg && params_)
                o_ << ", ";

            (*it)->accept(*this);
        }
    }

    void HeaderGenerator::operator()(ast::ModuleStmt& ast)
    {
        o_ << "namespace __" << ast.name_get() << "__" << misc::iendl;
        o_ << "{" << misc::indentendl;

        ast.content_get()->accept(*this);

        o_ << misc::dedentendl;
        o_ << "}" << misc::iendl;
    }

    void HeaderGenerator::operator()(ast::ClassDec& ast)
    {
        type::Class* old = current_class_;

        current_class_ = ast.type_class_get();

        // Print all C++ stuff for class definition
        o_ << "class " << current_class_->name_get() << misc::iendl;
        o_ << "{" << misc::indentendl;
        o_ << "public:" << misc::indentendl;

        // Generates header for each field of the type (method + fields)
        for (auto field : current_class_->content_get())
        {
            if (field.second)
                field.second->accept(*this);
        }

        // Close the definition
        o_ << misc::dedent << misc::dedentendl << "};" << misc::iendl;

        current_class_ = old;
    }

    void HeaderGenerator::operator()(ast::FunctionDec& ast)
    {
        // Generating all functions prototypes
        for (auto proto : ast.to_generate_get())
        {
            ast.type_set(proto);

            // If the method name is __init__ export it as C++ constructor
            if (ast.name_get() == "__init__" && current_class_)
                o_ << current_class_->name_get();
            else
                o_ << ast.type_get()->return_type_get()->cpp_type() << " "
                << ast.name_get();

            o_ << "(";

            // Print parameters
            params_ = true;
            if (ast.args_get())
                ast.args_get()->accept(*this);
            params_ = false;

            o_ << ");" << misc::iendl;
        }
    }

    void HeaderGenerator::operator()(ast::IdVar& ast)
    {
        if (params_ && (!ast.def_get() && ast.type_get()))
            o_ << ast.type_get()->cpp_type() << " " << ast.id_get();
    }
} // namespace cpp
