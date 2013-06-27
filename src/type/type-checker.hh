#ifndef TYPE_TYPE_CHECKER_HH
# define TYPE_TYPE_CHECKER_HH

# include <misc/error.hh>

# include <ast/default-visitor.hh>

namespace type
{
    class TypeChecker : public ast::DefaultVisitor
    {
        public:
            using ast::DefaultVisitor::operator();

            TypeChecker();
            virtual ~TypeChecker();

            misc::Error& error_get();

            void operator()(ast::FunctionDec& ast);
            void operator()(ast::AssignExpr& ast);

        private:
            misc::Error error_;
    };
} // namespace type

#endif /* !TYPE_TYPE_CHECKER_HH */
