#ifndef CPP_GENERATOR_HH
# define CPP_GENERATOR_HH

# include <ast/default-visitor.hh>

namespace cpp
{
    class Generator : public ast::DefaultVisitor
    {
        public:
            Generator(std::ostream& o);
            virtual ~Generator();

        protected:
            std::ostream& o_;
    };
} // namespace cpp

#endif /* !CPP_GENERATOR_HH */
