#ifndef scope_member_hh_INCLUDED
#define scope_member_hh_INCLUDED

#include "safe_ptr.hh"
#include "vector.hh"
#include "ranges.hh"

namespace Kakoune
{

template<typename Derived>
class ScopeMember
{
protected:
    ScopeMember() = default;
    ScopeMember(Derived& parent) : m_parent(&parent) {}
    ScopeMember(const ScopeMember&) = delete;

    void add_shared(Derived& derived)
    {
        m_shared.emplace_back(&derived);
    }

    void remove_shared(Derived& derived)
    {
        auto it = find_if(m_shared, [&](const SafePtr<Derived>& ptr) { return ptr.get() == &derived; });
        m_shared.erase(it);
    }

    SafePtr<Derived> m_parent;
    Vector<SafePtr<Derived>> m_shared;
};

}

#endif // scope_member_hh_INCLUDED
