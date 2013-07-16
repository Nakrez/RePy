#ifndef MISC_SCOPED_MAP_HH
# define MISC_SCOPED_MAP_HH

# include <list>
# include <map>

namespace misc
{
    template<class Key, class Data>
    class ScopedMap
    {
        public:
            ScopedMap(const Data& default_value);
            ~ScopedMap();

            void add(Key k, Data d);
            const Data& get(Key k) const;

            void scope_begin();
            void scope_end();

        private:
            std::list<std::map<Key, Data>> map_;
            Data default_value_;
    };
} // namespace misc

# include <misc/scoped-map.hxx>

#endif /* !MISC_SCOPED_MAP_HH */
