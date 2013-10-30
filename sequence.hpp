#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

/**
 * DO NOT MODIFY THIS FILE.
 */

//------------------------------------------------------------------------------
namespace cs603 {
//------------------------------------------------------------------------------

template < typename T1, typename T2 >
struct SequenceTraits;

template < typename T, class Derived >
class Sequence
{
public:
    typedef SequenceTraits<T,Derived> traits;

    typedef typename traits::size_type                 size_type;
    typedef typename traits::value_type                value_type;
    typedef typename traits::reference                 reference;
    typedef typename traits::const_reference           const_reference;
    typedef typename traits::iterator                  iterator;
    typedef typename traits::const_iterator            const_iterator;
    typedef typename traits::reverse_iterator          reverse_iterator;
    typedef typename traits::const_reverse_iterator    const_reverse_iterator;

    ///@TODO                                                                    
    ///@TODO    QUESTION 1: Why must the destructor be virtual?                 
    ///@TODO                                                                    
    virtual ~Sequence() { }

    /**
     *  Queries
     */

    ///@brief   Returns the number of elements in the sequence.
    ///@note    O(1)
    virtual size_type size() const = 0;

    ///@brief   Returns true if the sequence is empty.
    ///@note    O(1)
    virtual bool empty() const = 0;

    /**
     *  Comparisons
     */

    ///@TODO    QUESTION 2: Consider the second template parameter (Derived).   
    ///@TODO        How does its presence affect the following operators?       
    ///@TODO        That is, how would their declarations (in Sequence)         
    ///@TODO        and their definitions (in ArraySequence and                 
    ///@TODO        LinkedSequence) be affected if Sequence had only the        
    ///@TODO        first template parameter (i.e., Sequence<T>)?               
    ///@TODO                                                                    
    ///@TODO    QUESTION 3: The second template parameter illustrates which     
    ///@TODO        C++ idiom?                                                  
    ///@TODO                                                                    
    ///@TODO    QUESTION 4: List three (meta-)programming techniques made       
    ///@TODO        possible/easier/better by the idiom?                        

    ///@brief   Sequence equality comparison.
    ///@param   rhs  A sequence.
    ///@return  True iff the sizes and elements of the sequences are equal.
    ///@note    O(n)
    virtual bool operator==(const Derived&) const = 0;

    ///@brief   Sequence non-equality comparison.
    ///@param   rhs  A sequence.
    ///@return  True iff the sizes or elements of the sequences are not equal.
    ///@note    O(n)
    virtual bool operator!=(const Derived&) const = 0;

    ///@brief   Sequence ordering relation.
    ///@param   rhs  A sequence.
    ///@return  True iff the sequence is lexicographically < rhs.
    ///@note    O(n)
    virtual bool operator<(const Derived&) const = 0;

    ///@brief   Sequence ordering relation.
    ///@param   rhs  A sequence.
    ///@return  True iff the sequence is lexicographically > rhs.
    ///@note    O(n)
    virtual bool operator>(const Derived&) const = 0;

    ///@brief   Sequence ordering relation.
    ///@param   rhs  A sequence.
    ///@return  True iff the sequence is lexicographically <= rhs.
    ///@note    O(n)
    virtual bool operator<=(const Derived&) const = 0;

    ///@brief   Sequence ordering relation.
    ///@param   rhs  A sequence.
    ///@return  True iff the sequence is lexicographically >= rhs.
    ///@note    O(n)
    virtual bool operator>=(const Derived&) const = 0;

    /**
     *  Assignments
     */

    ///@brief   Sequence assignment operator.
    ///@param   rhs  A sequence of the same element type.
    ///@note    O(n)
    ///
    /// All elements of rhs are copied, but any extra memory in rhs
    /// (e.g., unused capacity) is not copied.
    virtual Derived& operator=(const Derived&) = 0;

    ///@brief   Swaps data with another sequence.
    ///@param   rhs  A sequence of the same element type.
    ///@note    O(1)
    virtual void swap(Derived&) = 0;

    /**
     *  Accessors
     */

    ///@brief   Subscript access to the data in the sequence.
    ///@param   n  The index of the element for which data is accessed.
    ///@return  Read/write reference to data.
    ///
    /// Does not check for out-of-range errors.
    virtual reference operator[](size_type) = 0;

    ///@brief   Subscript access to the data in the sequence.
    ///@param   n  The index of the element for which data is accessed.
    ///@return  Read only reference to data.
    ///
    /// Does not check for out-of-range errors.
    virtual const_reference operator[](size_type) const = 0;

    ///@brief   Returns a read/write reference to the data at the first element.
    ///@note    O(1)
    virtual reference front() = 0;

    ///@brief   Returns a read only reference to the data at the first element.
    ///@note    O(1)
    virtual const_reference front() const = 0;

    ///@brief   Returns a read/write reference to the data at the last element.
    ///@note    O(1)
    virtual reference back() = 0;

    ///@brief   Returns a read only reference to the data at the last element.
    ///@note    O(1)
    virtual const_reference back() const = 0;

    /**
     *  Iterators
     */

    ///@brief   Returns a read/write iterator that points to the first
    ///         element in the sequence.
    ///@note    O(1)
    virtual iterator begin() = 0;

    ///@brief   Returns a read only iterator that points to the first
    ///         element in the sequence.
    ///@note    O(1)
    virtual const_iterator begin() const = 0;

    ///@brief   Returns a read/write iterator that points to one past the last
    ///         element in the sequence.
    ///@note    O(1)
    virtual iterator end() = 0;

    ///@brief   Returns a read only iterator that points to one past the last
    ///         element in the sequence.
    ///@note    O(1)
    virtual const_iterator end() const = 0;

    ///@brief   Returns a read/write reverse iterator that points to the last
    ///         element in the sequence.
    ///@note    O(1)
    virtual reverse_iterator rbegin() = 0;

    ///@brief   Returns a read only reverse iterator that points to the last
    ///         element in the sequence.
    ///@note    O(1)
    virtual const_reverse_iterator rbegin() const = 0;

    ///@brief   Returns a read/write reverse iterator that points to one before
    ///         the first element in the sequence.
    ///@note    O(1)
    virtual reverse_iterator rend() = 0;

    ///@brief   Returns a read only reverse iterator that points to one before
    ///         the first element in the sequence.
    ///@note    O(1)
    virtual const_reverse_iterator rend() const = 0;

    /**
     *  Modifiers
     */

    ///@brief   Inserts given value into sequence before specified iterator.
    ///@param   pos  An iterator into the sequence.
    ///@param   data  Data to be inserted.
    ///
    /// Inserts a copy of the given value before the specified location.
    virtual iterator insert(iterator, const_reference) = 0;

    ///@brief   Inserts a number of copies of given data into the sequence.
    ///@param   pos  An iterator into the sequence.
    ///@param   n  Number of elements to be inserted.
    ///@param   data  Data to be inserted.
    ///
    /// Inserts the specified number of copies of the given value before the
    /// specified location.
    virtual void insert(iterator, size_type, const_reference) = 0;

    ///@brief   Add data to the end of the sequence.
    ///@param   data  Data to be added.
    virtual void push_back(const_reference) = 0;

    ///@brief   Remove element at the given position.
    ///@param   pos  Iterator pointing to element to be erased.
    ///@return  An iterator pointing to the next element (or end()).
    ///
    /// If the elements are pointers, the pointed-to memory
    /// is not touched in any way.  Managing the pointer is
    /// the user's responsibility.
    virtual iterator erase(iterator) = 0;

    ///@brief   Removes the elements in the range [first,last).
    ///@param   first  Iterator pointing to the first element to be erased.
    ///@param   last  Iterator pointing to one past the last element to be erased.
    ///@return  An iterator pointing to the element pointed to by last prior to
    ///         erasing (or end()).
    ///
    /// If the elements are pointers, the pointed-to memory
    /// is not touched in any way.  Managing the pointer is
    /// the user's responsibility.
    virtual iterator erase(iterator, iterator) = 0;

    ///@brief   Removes the last element.
    ///@note    O(1)
    virtual void pop_back() = 0;

    ///@brief   Removes all elements.
    ///
    /// If the elements are pointers, the pointed-to memory
    /// is not touched in any way.  Managing the pointer is
    /// the user's responsibility.
    virtual void clear() = 0;
};

//------------------------------------------------------------------------------
} // namespace cs603
//------------------------------------------------------------------------------

#endif
