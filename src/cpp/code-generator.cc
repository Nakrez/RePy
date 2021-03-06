#include <cpp/code-generator.hh>
#include <ast/all.hh>

namespace cpp
{
    CodeGenerator::CodeGenerator(std::ostream& o)
        : o_(o)
        , params_(false)
        , current_class_(nullptr)
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

    void CodeGenerator::operator()(ast::StmtList& ast)
    {
        auto beg = ast.list_get().begin();
        auto end = ast.list_get().end();

        for (auto it = beg; it != end; ++it)
        {
            if (it != beg)
                code_ << misc::iendl;

            (*it)->accept(*this);

            if (!dynamic_cast<ast::FunctionDec*> (*it)
                && !dynamic_cast<ast::WhileStmt*> (*it)
                && !dynamic_cast<ast::PassStmt*> (*it)
                && !dynamic_cast<ast::IfStmt*> (*it))
                code_ << ";";
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

    void CodeGenerator::operator()(ast::ReturnStmt& ast)
    {
        code_ << "return ";

        ast::DefaultVisitor::operator()(ast);
    }

    void CodeGenerator::operator()(ast::ContinueStmt&)
    {
        code_ << "continue";
    }

    void CodeGenerator::operator()(ast::BreakStmt&)
    {
        code_ << "break";
    }

    void CodeGenerator::operator()(ast::IfStmt& ast)
    {
        code_ << "if (";
        ast.cond_get()->accept(*this);
        code_ << ")" << misc::iendl << "{" << misc::indentendl;

        ast.true_stmt_get()->accept(*this);

        code_ << misc::dedentendl << "}";

        if (ast.else_stmt_get())
        {
            code_ << misc::iendl << "else" << misc::iendl << "{"
                  << misc::indentendl;

            ast.else_stmt_get()->accept(*this);

            code_ << misc::dedentendl << "}";
        }
    }

    void CodeGenerator::operator()(ast::WhileStmt& ast)
    {
        code_ << "while (";

        ast.cond_get()->accept(*this);

        code_ << ")" << misc::iendl << "{" << misc::indentendl;

        ast.loop_get()->accept(*this);

        code_ << misc::dedentendl << "}";
    }

    void CodeGenerator::operator()(ast::FunctionDec& ast)
    {
        // Generating all functions prototypes
        for (auto proto : ast.to_generate_get())
        {
            ast.type_set(proto);

            if (!(ast.name_get() == "__init__" && current_class_))
                code_ << ast.type_get()->return_type_get()->cpp_type() << " ";

            // If function is the method add the name of the class followed
            // by "::"
            if (current_class_)
                code_ << current_class_->name_get() << "::";

            if (ast.name_get() == "__init__" && current_class_)
                code_ << current_class_->name_get() << "(";
            else
                code_ << ast.name_get() << "(";

            params_ = true;
            if (ast.args_get())
                ast.args_get()->accept(*this);
            params_ = false;

            code_ << ")" << misc::iendl << "{" << misc::indentendl;

            ast.body_get()->accept(*this);

            code_ << misc::dedentendl << "}" << misc::iendl;
        }
    }

    void CodeGenerator::operator()(ast::ClassDec& ast)
    {
        type::Class* old = current_class_;

        current_class_ = ast.type_class_get();

        ast.def_get()->accept(*this);

        current_class_ = old;
    }

    void CodeGenerator::operator()(ast::IdVar& ast)
    {
        if (current_class_ && ast.id_get() == "self")
        {
            code_ << "this";
            return;
        }

        if (params_ || (!ast.def_get() && ast.type_get()))
            code_ << ast.type_get()->cpp_type() << " ";

        if (builtin::BuiltinLibrary::instance().is_builtin(ast.id_get()))
            code_ << builtin::BuiltinLibrary::instance().cpp_builtin(ast.id_get());
        else
            code_ << ast.id_get();
    }

    void CodeGenerator::operator()(ast::OpExpr& ast)
    {
        code_ << ast.to_cpp() << "(";

        ast.left_expr_get()->accept(*this);

        code_ << ", ";

        ast.right_expr_get()->accept(*this);

        code_ << ")";
    }

    void CodeGenerator::operator()(ast::AssignExpr& ast)
    {
        ast.lvalue_get()->accept(*this);

        code_ << " = ";

        ast.rvalue_get()->accept(*this);
    }

    void CodeGenerator::operator()(ast::StringExpr& ast)
    {
        code_ << "new __repy_string(\"" << ast.str_get() << "\")";
    }

    void CodeGenerator::operator()(ast::NumeralExpr& ast)
    {
        code_ << std::setprecision(10000) << ast.value_get();
    }

    void CodeGenerator::operator()(ast::FunctionVar& ast)
    {
        if (ast.constructor_get())
            code_ << "new ";

        ast.var_get()->accept(*this);

        code_ << "(";

        if (ast.params_get())
            ast.params_get()->accept(*this);

        code_ << ")";
    }

    void CodeGenerator::operator()(ast::FieldVar& ast)
    {
        ast.var_get()->accept(*this);

        code_ << "->" << ast.name_get();
    }

    void CodeGenerator::operator()(ast::MethodVar& ast)
    {
        ast.var_get()->accept(*this);

        code_ << "->" << ast.name_get() << "(";

        if (ast.params_get())
            ast.params_get()->accept(*this);

        code_ << ")";
    }
} // namespace cpp
