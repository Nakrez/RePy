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
            virtual void operator()(typename Const<AstList>::type& ast) = 0;
            virtual void operator()(typename Const<StmtList>::type& ast) = 0;
            virtual void operator()(typename Const<ExprList>::type& ast) = 0;

            virtual void operator()(typename Const<PassStmt>::type& ast) = 0;
            virtual void operator()(typename Const<BreakStmt>::type& ast) = 0;
            virtual void operator()(typename Const<ContinueStmt>::type& ast) = 0;
            virtual void operator()(typename Const<ExprStmt>::type& ast) = 0;
            virtual void operator()(typename Const<IfStmt>::type& ast) = 0;
            virtual void operator()(typename Const<WhileStmt>::type& ast) = 0;
            virtual void operator()(typename Const<ReturnStmt>::type& ast) = 0;
            virtual void operator()(typename Const<FunctionDec>::type& ast) = 0;
            virtual void operator()(typename Const<ClassDec>::type& ast) = 0;
            virtual void operator()(typename Const<ModuleStmt>::type& ast) = 0;

            virtual void operator()(typename Const<OpExpr>::type& ast) = 0;
            virtual void operator()(typename Const<UnaryExpr>::type& ast) = 0;
            virtual void operator()(typename Const<AssignExpr>::type& ast) = 0;
            virtual void operator()(typename Const<NumeralExpr>::type& ast) = 0;
            virtual void operator()(typename Const<StringExpr>::type& ast) = 0;
            virtual void operator()(typename Const<YieldExpr>::type& ast) = 0;
            virtual void operator()(typename Const<StarExpr>::type& ast) = 0;
            virtual void operator()(typename Const<DoubleStarExpr>::type& ast) = 0;

            virtual void operator()(typename Const<IdVar>::type& ast) = 0;
            virtual void operator()(typename Const<FunctionVar>::type& ast) = 0;
            virtual void operator()(typename Const<FieldVar>::type& ast) = 0;
            virtual void operator()(typename Const<MethodVar>::type& ast) = 0;
    };

    typedef GenVisitor<misc::const_type> ConstVisitor;
    typedef GenVisitor<misc::nonconst_type> Visitor;
} // namespace ast

# include <ast/visitor.hxx>

#endif /* !AST_VISITOR_HH */
