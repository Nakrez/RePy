#ifndef CLONER_AST_CLONER_HXX
# define CLONER_AST_CLONER_HXX

# include <cloner/ast-cloner.hh>

namespace cloner
{
    template <typename T>
    T* AstCloner::clone(T* t)
    {
        if (t)
        {
            t->accept(*this);
            T* res = dynamic_cast<T*> (cloned_ast_);

            assert(res && "Internal compiler error");

            return res;
        }

        return nullptr;
    }

    template <typename T>
    T* AstCloner::clone(T& t)
    {
        t.accept(*this);

        T* res = dynamic_cast<T*> (cloned_ast_);

        assert(res && "Internal compiler error");

        return res;
    }

    template <typename T>
    ast::AnyList<T>* AstCloner::clone_list(ast::AnyList<T>& l)
    {
        ast::AnyList<T>* ret = new ast::AnyList<T>(l.location_get());

        for (auto elem : l.list_get())
        {
            elem->accept(*this);

            T* res = dynamic_cast<T*> (cloned_ast_);

            assert(res && "Internal compiler error");

            ret->push_back(res);
        }

        return ret;
    }
} // namespace cloner

#endif /* !CLONER_AST_CLONER_HXX */
