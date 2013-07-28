#ifndef TYPE_TYPE_CHECKER_HXX
# define TYPE_TYPE_CHECKER_HXX

# include <type/type-checker.hh>

namespace type
{
    template <class T>
    void TypeChecker::type_callable(T& e)
    {
        // FIXME : Dirty fix supposed to be set when an ambiguous call is made
        // This ambiguous call must only be made when checking function
        // declaration. Else it is a bug or something I did not think of.
        ast::ExprList* tmp = generate_prototype(e);

        if (e.params_get() != tmp)
        {
            delete e.params_get();
            e.params_set(tmp);
        }

        // If def get is null it is a builtin function (or a bug)
        if (!e.def_get())
        {
            builtin::BuiltinLibrary::instance().type_check(e, error_, *this);
            return;
        }

        bool ambigous = false;
        Function* prototype = new Function();

        if (e.params_get())
        {
            for (auto p : e.params_get()->list_get())
            {
                p->accept(*this);

                if (p->type_get() == &Polymorphic::instance())
                    ambigous = true;

                prototype->args_type_add(p->type_get());
            }
        }

        if (!ambigous)
        {
            e.type_set(type_call(e.def_get(), prototype));

            // If the result of the process is Polymorphic type then the code
            // is invalid or contains a part of unsupported stuff.
            // If you fine any example that is valid and fully supported
            // I would be glad to see it and review my algorithm
            if (e.type_get() == &Polymorphic::instance())
                error_ << misc::Error::TYPE
                       << e.location_get() << ": Function return type "
                       << "ambiguous or contains unsupported stuff."
                       << " If you believe your code works and is supported "
                       << "please report it as BUG. Thanks !"
                       << std::endl;
            else if (!e.type_get())
                e.type_set(&Polymorphic::instance());
        }
        else
            e.type_set(&Polymorphic::instance());
    }

    template <class T>
    ast::ExprList* TypeChecker::generate_prototype(T& dec)
    {
        const ast::ExprList* dec_get;

        if (!dec.def_get())
        {
            dec_get = builtin::BuiltinLibrary::instance().args_get(dec);

            if (!dec_get)
                return dec.params_get();
        }
        else
            dec_get = dec.def_get()->original_args_get();

        // Map all args with it expression, bool are to keep track of double
        // assignement of the same parameter which is wrong
        std::map<std::string, parameter> mapped_args;

        // Keep the order of insertion to the final recontruction
        std::vector<std::string> order_insertion;

        ast::ExprList* params = nullptr;

        if (dec_get)
        {
            if (dec.params_get() &&
                dec.params_get()->list_get().size() >
                dec_get->list_get().size())
                error_ << misc::Error::TYPE
                       << dec.params_get()->location_get()
                       << ": Too much parameters specified"
                       << std::endl;
            else
            {
                // Takes the function definition and build a mapping from it
                // for example def fun(a, b, c = 1)
                // will generate
                // a -> nullptr
                // b -> nullptr
                // c -> 1
                build_mapping(dec_get, mapped_args, order_insertion);

                if (dec.params_get())
                {
                    // Match the function call with the map built previously
                    // Let takes the same example. (def fun(a, b, c=1))
                    // Called it with fun(1, 2)
                    // The function will do
                    // a -> 1
                    // b -> 2
                    // c -> 1
                    build_call(dec.params_get(), mapped_args, order_insertion);
                }

                // Finally transform the map to a function call
                // So from or previous example we will build
                // fun(1, 2, 1)
                params = generate_list(dec.location_get(),
                                       mapped_args, order_insertion);
            }
        }
        else if (dec.params_get() && dec.params_get()->list_get().size() > 0)
                error_ << misc::Error::TYPE
                       << dec.params_get()->location_get()
                       << ": Too much parameters specified"
                       << std::endl;

        return params;
    }
}

#endif /* !TYPE_TYPE_CHECKER_HXX */
