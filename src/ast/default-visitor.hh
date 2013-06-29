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
            virtual void operator()(typename Const<ExprList>::type& ast);

            virtual void operator()(typename Const<PassStmt>::type& ast);
            virtual void operator()(typename Const<BreakStmt>::type& ast);
            virtual void operator()(typename Const<ContinueStmt>::type& ast);
            virtual void operator()(typename Const<ExprStmt>::type& ast);
            virtual void operator()(typename Const<IfStmt>::type& ast);
            virtual void operator()(typename Const<WhileStmt>::type& ast);
            virtual void operator()(typename Const<ReturnStmt>::type& ast);
            virtual void operator()(typename Const<FunctionDec>::type& ast);

            virtual void operator()(typename Const<OpExpr>::type& ast);
            virtual void operator()(typename Const<UnaryExpr>::type& ast);
            virtual void operator()(typename Const<AssignExpr>::type& ast);
            virtual void operator()(typename Const<NumeralExpr>::type& ast);
            virtual void operator()(typename Const<StringExpr>::type& ast);
            virtual void operator()(typename Const<YieldExpr>::type& ast);
            virtual void operator()(typename Const<StarExpr>::type& ast);
            virtual void operator()(typename Const<DoubleStarExpr>::type& ast);

            virtual void operator()(typename Const<IdVar>::type& ast);
            virtual void operator()(typename Const<FunctionVar>::type& ast);
    };

    typedef GenDefaultVisitor<misc::const_type> DefaultConstVisitor;
    typedef GenDefaultVisitor<misc::nonconst_type> DefaultVisitor;
} // namespace ast

# include <ast/default-visitor.hxx>

#endif /* !AST_DEFAULT_VISITOR_HH */
