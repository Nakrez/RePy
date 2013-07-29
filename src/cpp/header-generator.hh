#ifndef CPP_HEADER_GENERATOR_HH
# define CPP_HEADER_GENERATOR_HH

# include <misc/indent.hh>

# include <ast/default-visitor.hh>

# include <type/class.hh>

namespace cpp
{
    class HeaderGenerator : public ast::DefaultVisitor
    {
        public:
            using ast::DefaultVisitor::operator();

            HeaderGenerator(std::ostream& o);
            virtual ~HeaderGenerator();

            virtual void operator()(ast::ExprList& ast);
            virtual void operator()(ast::ModuleStmt& ast);

            virtual void operator()(ast::ClassDec& ast);
            virtual void operator()(ast::FunctionDec& ast);
            virtual void operator()(ast::IdVar& ast);

        protected:
            std::ostream& o_;
            bool params_;
            type::Class* current_class_;
    };
} // namespace cpp

#endif /* !CPP_HEADER_GENERATOR_HH */
