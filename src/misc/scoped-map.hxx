#ifndef MISC_SCOPED_MAP_HXX
# define MISC_SCOPED_MAP_HXX

# include <misc/scoped-map.hh>

namespace misc
{
    template<class Key, class Data>
    ScopedMap<Key, Data>::ScopedMap(const Data& default_value)
        : default_value_(default_value)
    {
        scope_begin();
    }

    template<class Key, class Data>
    ScopedMap<Key, Data>::~ScopedMap()
    {}

    template<class Key, class Data>
    void ScopedMap<Key, Data>::add(Key k, Data d)
    {
        map_.back()[k] = d;
    }

    template<class Key, class Data>
    const Data& ScopedMap<Key, Data>::get(Key k) const
    {
        try {
            return map_.back().at(k);
        }
        catch (...)
        {
            return default_value_;
        }
    }

    template<class Key, class Data>
    void ScopedMap<Key, Data>::scope_begin()
    {
        if (!map_.size())
            map_.push_back(std::map<Key, Data>());
        else
            map_.push_back(std::map<Key, Data>(map_.back()));
    }

    template<class Key, class Data>
    void ScopedMap<Key, Data>::scope_end()
    {
        map_.pop_back();
    }
} // namespace misc

#endif /* !MISC_SCOPED_MAP_HXX */
