#ifndef TYPE_TYPE_CHECKER_HXX
# define TYPE_TYPE_CHECKER_HXX

# include <type/type-checker.hh>

namespace type
{
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
