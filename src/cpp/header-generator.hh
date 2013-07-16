#ifndef CPP_HEADER_GENERATOR_HH
# define CPP_HEADER_GENERATOR_HH

# include <misc/indent.hh>

# include <ast/default-visitor.hh>

namespace cpp
{
    class HeaderGenerator : public ast::DefaultVisitor
    {
        public:
            using ast::DefaultVisitor::operator();

            HeaderGenerator(std::ostream& o);
            virtual ~HeaderGenerator();

            virtual void operator()(ast::ModuleStmt& ast);

            virtual void operator()(ast::FunctionDec& ast);

        protected:
            std::ostream& o_;
    };
} // namespace cpp

#endif /* !CPP_HEADER_GENERATOR_HH */