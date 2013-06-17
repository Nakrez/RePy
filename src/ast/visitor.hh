#ifndef AST_VISITOR_HH
# define AST_VISITOR_HH

# include <functional>

# include <misc/constness.hh>

# include <ast/fwd.hh>

namespace ast
{
    template <template <typename> class Const>
    class GenVisitor : public std::unary_function<Ast, void>
    {
        public:
            GenVisitor() = default;
            virtual ~GenVisitor() = default;

            template <typename T> void visit(T* a);
            template <typename T> void visit(typename Const<T>::type& a);

            virtual void operator()(typename Const<Ast>::type& ast);
    };

    typedef GenVisitor<misc::const_type> ConstVisitor;
    typedef GenVisitor<misc::nonconst_type> Visitor;
} // namespace ast

# include <ast/visitor.hxx>

#endif /* !AST_VISITOR_HH */