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

            virtual void operator()(typename Const<AstList>::type& ast);
            virtual void operator()(typename Const<StmtList>::type& ast);

            virtual void operator()(typename Const<PassStmt>::type& ast);
            virtual void operator()(typename Const<BreakStmt>::type& ast);
            virtual void operator()(typename Const<ContinueStmt>::type& ast);

            virtual void operator()(typename Const<NumeralExpr>::type& ast);
    };

    typedef GenDefaultVisitor<misc::const_type> DefaultConstVisitor;
    typedef GenDefaultVisitor<misc::nonconst_type> DefaultVisitor;
} // namespace ast

# include <ast/default-visitor.hxx>

#endif /* !AST_DEFAULT_VISITOR_HH */
