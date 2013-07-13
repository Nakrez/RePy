#ifndef CPP_GENERATOR_HH
# define CPP_GENERATOR_HH

# include <misc/indent.hh>

# include <ast/default-visitor.hh>

namespace cpp
{
    class Generator : public ast::DefaultVisitor
    {
        public:
            using ast::DefaultVisitor::operator();

            Generator(std::ostream& o);
            virtual ~Generator();

            virtual void operator()(ast::ModuleStmt& ast);

            virtual void operator()(ast::FunctionDec& ast);

        protected:
            std::ostream& o_;
    };
} // namespace cpp

#endif /* !CPP_GENERATOR_HH */
