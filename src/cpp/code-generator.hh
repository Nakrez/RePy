#ifndef CPP_CODE_GENERATOR_HH
# define CPP_CODE_GENERATOR_HH

# include <misc/indent.hh>

# include <ast/default-visitor.hh>

namespace cpp
{
    class CodeGenerator : public ast::DefaultVisitor
    {
        public:
            using ast::DefaultVisitor::operator();

            CodeGenerator(std::ostream& o);
            virtual ~CodeGenerator();

            virtual void operator()(ast::ModuleStmt& ast);

            virtual void operator()(ast::FunctionDec& ast);

        protected:
            std::ostream& o_;
    };
} // namespace cpp

#endif /* !CPP_CODE_GENERATOR_HH */
