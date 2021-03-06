#ifndef CPP_CODE_GENERATOR_HH
# define CPP_CODE_GENERATOR_HH

# include <list>
# include <sstream>
# include <iomanip>

# include <misc/indent.hh>

# include <ast/default-visitor.hh>
# include <builtin/builtin-library.hh>

# include <type/class.hh>

namespace cpp
{
    class CodeGenerator : public ast::DefaultVisitor
    {
        public:
            using ast::DefaultVisitor::operator();

            CodeGenerator(std::ostream& o);
            virtual ~CodeGenerator();

            void generate_main();

            virtual void operator()(ast::ExprList& ast);
            virtual void operator()(ast::StmtList& ast);

            virtual void operator()(ast::ModuleStmt& ast);
            virtual void operator()(ast::ReturnStmt& ast);
            virtual void operator()(ast::ContinueStmt& ast);
            virtual void operator()(ast::BreakStmt& ast);
            virtual void operator()(ast::IfStmt& ast);
            virtual void operator()(ast::WhileStmt& ast);
            virtual void operator()(ast::FunctionDec& ast);
            virtual void operator()(ast::ClassDec& ast);

            virtual void operator()(ast::OpExpr& ast);
            virtual void operator()(ast::AssignExpr& ast);
            virtual void operator()(ast::NumeralExpr& ast);
            virtual void operator()(ast::StringExpr& ast);
            virtual void operator()(ast::IdVar& ast);
            virtual void operator()(ast::FunctionVar& ast);
            virtual void operator()(ast::FieldVar& ast);
            virtual void operator()(ast::MethodVar& ast);

        protected:
            std::ostream& o_;
            std::stringstream code_;
            std::list<std::string> modules_;
            bool params_;
            type::Class* current_class_;
    };
} // namespace cpp

#endif /* !CPP_CODE_GENERATOR_HH */
