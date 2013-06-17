#ifndef AST_DEFAULT_VISITOR_HH
# define AST_DEFAULT_VISITOR_HH

# include <ast/visitor.hh>

namespace ast
{
    template <template <typename> class Const>
    class GenDefaultVisitor : public virtual GenVisitor<Const>
    {
        public:
            using GenVisitor<Const>::operator();

            GenDefaultVisitor() = default;
            virtual ~GenDefaultVisitor();
    };

    typedef GenDefaultVisitor<misc::const_type> DefaultConstVisitor;
    typedef GenDefaultVisitor<misc::nonconst_type> DefaultVisitor;
} // namespace ast

# include <ast/default-visitor.hxx>

#endif /* !AST_DEFAULT_VISITOR_HH */