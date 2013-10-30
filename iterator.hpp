#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/**
 * DO NOT MODIFY THIS FILE
 */

//------------------------------------------------------------------------------
namespace cs603 {
//------------------------------------------------------------------------------

template < typename T1, typename T2 >
struct IteratorTraits;

template < typename T, class Derived >
class Iterator
{
public:
    typedef IteratorTraits<T,Derived> traits;

    typedef typename traits::value_type         value_type;
    typedef typename traits::pointer            pointer;
    typedef typename traits::reference          reference;

    virtual ~Iterator() { }

    /**
     *  Comparisons
     */
    virtual bool operator==(const Derived&) const = 0;              // O(1)
    virtual bool operator!=(const Derived&) const = 0;              // O(1)

    /**
     *  Assignments
     */
    virtual Derived& operator=(const Derived&) = 0;                 // O(1)

    /**
     *  Accessors
     */
    virtual pointer operator->() const = 0;                         // O(1)
    virtual reference operator*() const = 0;                        // O(1)

    /**
     *  Modifiers
     */
    virtual Derived& operator++() = 0;                              // O(1)
    virtual Derived operator++(int) = 0;                           // O(1)
    virtual Derived& operator--() = 0;                              // O(1)
    virtual Derived operator--(int) = 0;                           // O(1)
};

//------------------------------------------------------------------------------
} // namespace cs603
//------------------------------------------------------------------------------

#endif
