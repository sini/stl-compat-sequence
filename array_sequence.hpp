#ifndef ARRAY_SEQUENCE_HPP
#define ARRAY_SEQUENCE_HPP

#include <iostream>

#include "sequence.hpp"
#include "iterator.hpp"

//------------------------------------------------------------------------------
namespace cs603 {
//------------------------------------------------------------------------------

template < typename T >
class ArraySequence;

template < typename T >
class ArraySequenceReverseIterator;

template < typename T >
class ArraySequenceConstReverseIterator;

template < typename T >
struct SequenceTraits< T, ArraySequence<T> >
{
    typedef size_t                                  size_type;
    typedef T                                       value_type;
    typedef value_type*                             pointer;
    typedef const value_type*                       const_pointer;
    typedef value_type&                             reference;
    typedef const value_type&                       const_reference;
    typedef pointer                                 iterator;
    typedef const_pointer                           const_iterator;
    typedef ArraySequenceReverseIterator<T>         reverse_iterator;
    typedef ArraySequenceConstReverseIterator<T>    const_reverse_iterator;
};

template < typename T >
struct IteratorTraits< T, ArraySequenceReverseIterator<T> >
{
    typedef T   value_type;
    typedef T*  pointer;
    typedef T&  reference;
};

template < typename T >
struct IteratorTraits< T, ArraySequenceConstReverseIterator<T> >
{
    typedef const T   value_type;
    typedef const T*  pointer;
    typedef const T&  reference;
};

///@TODO                                                                        
///@TODO    QUESTION 5: Is this needed?  Why or why not?                        
///@TODO                                                                        
template < typename T >
std::ostream& operator<<(std::ostream&, const ArraySequence<T>&);

template < typename T >
class ArraySequence
    : public Sequence< T, ArraySequence<T> >
{
public:
    typedef SequenceTraits<T,ArraySequence<T> > traits;

    typedef typename traits::size_type              size_type;
    typedef typename traits::value_type             value_type;
    typedef typename traits::pointer                pointer;
    typedef typename traits::const_pointer          const_pointer;
    typedef typename traits::reference              reference;
    typedef typename traits::const_reference        const_reference;
    typedef typename traits::iterator               iterator;
    typedef typename traits::const_iterator         const_iterator;
    typedef typename traits::reverse_iterator       reverse_iterator;
    typedef typename traits::const_reverse_iterator const_reverse_iterator;

    /**
     *  Friend classes
     */
    friend class ArraySequenceReverseIterator<T>;
    friend class ArraySequenceConstReverseIterator<T>;

    /**
     *  Constructors/Destructor
     */

    ///@brief   Creates an empty sequence without any elements.
    ArraySequence();

    ///@brief   Creates a deep copy of another sequence
    ArraySequence(const ArraySequence&);

    ///@brief   Creates a sequence with n copies of data.
    ///@param   n
    ///@param   data  Optional.
    explicit ArraySequence(size_type, const_reference);

    ///@brief   Creates a sequence initialized with the elements.
    ///         of the range [beg,end)
    ///@param   beg
    ///@param   end
    template < typename InputIterator >
    ArraySequence(InputIterator, InputIterator);

    ///@brief   Destroys all elements.
    ///
    /// If the elements are pointers, the pointed-to memory
    /// is not touched in any way.  Managing the pointer is
    /// the user's responsibility.
    virtual ~ArraySequence();

    /**
     *  Inherited member functions
     */
    size_type size() const;
    bool empty() const;

    bool operator==(const ArraySequence&) const;
    bool operator!=(const ArraySequence&) const;
    bool operator<(const ArraySequence&) const;
    bool operator>(const ArraySequence&) const;
    bool operator<=(const ArraySequence&) const;
    bool operator>=(const ArraySequence&) const;

    ArraySequence& operator=(const ArraySequence&);
    void swap(ArraySequence&);

    reference operator[](size_type);                        // O(1)
    const_reference operator[](size_type) const;            // O(1)
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    iterator insert(iterator, const_reference);             // O(n)
    void insert(iterator, size_type, const_reference);      // O(n)

    ///@note    O(1) if preallocated space is available, O(n) otherwise.
    void push_back(const_reference);

    iterator erase(iterator);                               // O(n)
    iterator erase(iterator, iterator);                     // O(n)
    void pop_back();
    void clear();                                           // O(1)

    /**
     *  Additional member functions
     */

     ///@brief  Returns the capacity of the sequence.
     size_type capacity() const;

    /**
     *  Friend functions
     */
    ///@TODO                                                                    
    ///@TODO    QUESTION 6: Consider this method signature:                     
    ///@TODO        a. What is the effect of the `friend' keyword?              
    ///@TODO        b. Why is `<>' required after the function name?            
    ///@TODO                                                                    
    friend std::ostream& operator<< <> (std::ostream&, const ArraySequence&);

private:
    ///@TODO                                                                    
    ///@TODO    Add internal representation.                                    
    ///@TODO                                                                    
    size_type size_;
    size_type capacity_;
    value_type * data_;

    void resize_(size_type sz) {
      if(sz >= capacity_) {
        while(sz >= capacity_) { capacity_ = capacity_*2; }
      } else if((sz <= .25*capacity_) && (capacity_ > 10)) {
        while((sz <= .25*capacity_) && (capacity_ > 10)) { capacity_ = capacity_/2; }
      } else {
        size_ = sz;
        return;
      }
      value_type * newdata = new value_type[capacity_];
      for(size_type x = 0; (x < size_) && ((x < capacity_) && (x < sz)); ++x) {
        newdata[x] = data_[x];
      }
      delete [] data_;
      data_ = newdata;
      size_ = sz;
    };

    void remove_(size_type index) {
      for(size_type x = index; x < size_; ++x) {
        data_[x] = data_[x+1];
      }
      resize_(size_ - 1);
    };


    bool lex_compare(iterator f1, iterator l1, iterator f2, iterator l2) const {
      for(; f1 != l1 && f2 != l2; ++f1, ++f2) {
        if(*f1 < *f2) 
          return true;
        if(*f2 <  *f1)
          return false;
       }
       return f1 == l1 && f2 != l2;
    };
    
    template < typename Integer >
    void initialize_dispatch(Integer, Integer, std::__true_type);

    template < typename InputIterator >
    void initialize_dispatch(InputIterator, InputIterator, std::__false_type);
};

template < typename T >
class ArraySequenceReverseIterator
    : public Iterator< T, ArraySequenceReverseIterator<T> >
{
public:
    typedef IteratorTraits<T,ArraySequenceReverseIterator<T> > traits;

    typedef typename traits::value_type value_type;
    typedef typename traits::pointer    pointer;
    typedef typename traits::reference  reference;

    /**
     *  Friend classes
     */
    ///@NOTE    Depending on your implementation, you may find the following
    ///@NOTE    friend declaration useful.
    //friend class ArraySequenceConstReverseIterator<T>;

    /**
     *  Constructors/Destructor
     */
    ArraySequenceReverseIterator();
	ArraySequenceReverseIterator(value_type * val) : pos_(val) {};

    ArraySequenceReverseIterator(const ArraySequenceReverseIterator&);

    virtual ~ArraySequenceReverseIterator();

    /**
     *  Inherited member functions
     */
    bool operator==(const ArraySequenceReverseIterator&) const;
    bool operator!=(const ArraySequenceReverseIterator&) const;
    ArraySequenceReverseIterator& operator=(const ArraySequenceReverseIterator&);
    pointer operator->() const;
    reference operator*() const;
    ArraySequenceReverseIterator& operator++();
    ArraySequenceReverseIterator operator++(int);
    ArraySequenceReverseIterator& operator--();
    ArraySequenceReverseIterator operator--(int);

private:
	value_type * pos_;
    ///@TODO                                                                    
    ///@TODO    Add internal representation.                                    
    ///@TODO                                                                    
};

template < typename T >
class ArraySequenceConstReverseIterator
    : public Iterator< T, ArraySequenceConstReverseIterator<T> >
{
public:
    typedef IteratorTraits<T,ArraySequenceConstReverseIterator<T> > traits;

    typedef typename traits::value_type value_type;
    typedef typename traits::pointer    pointer;
    typedef typename traits::reference  reference;

    /**
     *  Constructors/Destructor
     */
    ArraySequenceConstReverseIterator();
    ArraySequenceConstReverseIterator(value_type * val) : pos_(val) {};

    ArraySequenceConstReverseIterator(const ArraySequenceConstReverseIterator&);
    
    ///@NOTE    Alternatively, you could provide a conversion operator in the
    ///@NOTE    ArraySequenceReverseIterator class.
    ArraySequenceConstReverseIterator(const ArraySequenceReverseIterator<T>&);

    virtual ~ArraySequenceConstReverseIterator();

    /**
     *  Inherited member functions
     */
    bool operator==(const ArraySequenceConstReverseIterator&) const;
    bool operator!=(const ArraySequenceConstReverseIterator&) const;
    ArraySequenceConstReverseIterator& operator=(const ArraySequenceConstReverseIterator&);
    pointer operator->() const;
    reference operator*() const;
    ArraySequenceConstReverseIterator& operator++();
    ArraySequenceConstReverseIterator operator++(int);
    ArraySequenceConstReverseIterator& operator--();
    ArraySequenceConstReverseIterator operator--(int);

private:
    ///@TODO                                                                    
    ///@TODO    Add internal representation.                                    
    ///@TODO                                                                    
	value_type * pos_;
};

/**
 *  Member function definitions
 */

template < typename T >
ArraySequence<T>::ArraySequence()
  : Sequence< T, ArraySequence<T> >(), size_(0), capacity_(10) {
    data_ = new value_type[10];
}

template < typename T >
ArraySequence<T>::ArraySequence(const ArraySequence& rhs)
  : Sequence< T, ArraySequence<T> >(), size_(rhs.size_), capacity_(rhs.capacity_) {
    data_ = new value_type[capacity_];
    for(size_type x = 0; x < rhs.size_; ++x) {
      data_[x] = rhs.data_[x];
    }
}

template < typename T >
ArraySequence<T>::ArraySequence(size_type sz, const_reference val)
  : Sequence< T, ArraySequence<T> >(), size_(0), capacity_(10) {
    data_ = new value_type[capacity_];
    resize_(sz);
    for(size_type x = 0; x < sz; ++x) {
      data_[x] = val;
    }
}

template < typename T >
template < typename InputIterator >
ArraySequence<T>::ArraySequence(InputIterator left, InputIterator right)
  : Sequence< T, ArraySequence<T> >(), size_(0),  capacity_(10) {
    data_ = new value_type[capacity_];
    typedef typename std::__is_integer<InputIterator>::__type Integral;
    initialize_dispatch(left, right, Integral());

// todo
}

template < typename T >
template < typename Integer >
void ArraySequence<T>::initialize_dispatch(Integer sz, Integer val, std::__true_type) {
    resize_(sz);
    for(Integer x = 0; x < sz; ++x) {
      data_[x] = val;
    }
}

template < typename T >
template < typename InputIterator >
void ArraySequence<T>::initialize_dispatch(InputIterator left, InputIterator right, std::__false_type) {
  size_type span = right - left;
  resize_(span);
  for(iterator x = left; x != right; ++x) {
    data_[span - (right-x)] = *x;
  }
}

template < typename T >
ArraySequence<T>::~ArraySequence() {
    delete [] data_;
}

template < typename T >
typename ArraySequence<T>::size_type
ArraySequence<T>::size() const {
    return size_;
}

template < typename T >
bool
ArraySequence<T>::empty() const {
    return (size_ == 0);
}

template < typename T >
bool
ArraySequence<T>::operator==(const ArraySequence& rhs) const {
    if(size_ != rhs.size_) return false;
    for(size_type x = 0; x < size_; ++x) 
      if(data_[x] != rhs.data_[x]) return false;
    return true;
}

template < typename T >
bool
ArraySequence<T>::operator!=(const ArraySequence& rhs) const {
    return !(*this == rhs);
}

template < typename T >
bool
ArraySequence<T>::operator<(const ArraySequence& rhs) const {
    return lex_compare(&data_[0], &data_[size_], &rhs.data_[0], &rhs.data_[rhs.size_]);
}

template < typename T >
bool
ArraySequence<T>::operator>(const ArraySequence& rhs) const {
    return rhs < *this;
}

template < typename T >
bool
ArraySequence<T>::operator<=(const ArraySequence& rhs) const {
    return !(rhs < *this);
}

template < typename T >
bool
ArraySequence<T>::operator>=(const ArraySequence& rhs) const {
    return !(*this < rhs);
}

template < typename T >
ArraySequence<T>&
ArraySequence<T>::operator=(const ArraySequence& rhs) {
  if(rhs == *this) return *this;
  
  delete[] data_;
    size_ = 0;
    capacity_ = 10;
    data_ = new value_type[capacity_];
    resize_(rhs.size_);
    for(size_type x = 0; x < size_; ++x) {
      data_[x] = rhs.data_[x];
    }
    return *this;
}

template < typename T >
void
ArraySequence<T>::swap(ArraySequence& rhs) {
  value_type * temp = rhs.data_;
  size_type tempc = rhs.capacity_;
  size_type temps = rhs.size_;
  rhs.data_ = data_;
  rhs.capacity_ = capacity_;
  rhs.size_ = size_;
  data_ = temp;
  capacity_ = tempc;
  size_ = temps;
}

template < typename T >
typename ArraySequence<T>::reference
ArraySequence<T>::operator[](size_type idx) {
    return data_[idx];
}

template < typename T >
typename ArraySequence<T>::const_reference
ArraySequence<T>::operator[](size_type idx) const {
    return data_[idx];
}

template < typename T >
typename ArraySequence<T>::reference
ArraySequence<T>::front() {
    return data_[0];
}

template < typename T >
typename ArraySequence<T>::const_reference
ArraySequence<T>::front() const {
    return data_[0];
}

template < typename T >
typename ArraySequence<T>::reference
ArraySequence<T>::back() {
    return data_[size_-1];
}

template < typename T >
typename ArraySequence<T>::const_reference
ArraySequence<T>::back() const {
    return data_[size_-1];
}

template < typename T >
typename ArraySequence<T>::iterator
ArraySequence<T>::begin() {
    return data_;
}

template < typename T >
typename ArraySequence<T>::const_iterator
ArraySequence<T>::begin() const {
    return data_;
}

template < typename T >
typename ArraySequence<T>::iterator
ArraySequence<T>::end() {
    return &data_[size_];
}

template < typename T >
typename ArraySequence<T>::const_iterator
ArraySequence<T>::end() const {
    return &data_[size_];
}

template < typename T >
typename ArraySequence<T>::reverse_iterator
ArraySequence<T>::rbegin() {
    return reverse_iterator(data_+(size_-1));
}

template < typename T >
typename ArraySequence<T>::const_reverse_iterator
ArraySequence<T>::rbegin() const {
    return const_reverse_iterator(data_+(size_-1));
}

template < typename T >
typename ArraySequence<T>::reverse_iterator
ArraySequence<T>::rend() {
    return reverse_iterator(data_-1);
}

template < typename T >
typename ArraySequence<T>::const_reverse_iterator
ArraySequence<T>::rend() const {
    return const_reverse_iterator(data_-1);
}

template < typename T >
typename ArraySequence<T>::iterator
ArraySequence<T>::insert(iterator iter, const_reference val) {
  size_type index = iter - data_;
  resize_(size_+1);
  for(size_type x = size_ - 1; x > index; --x) {
    data_[x] = data_[x-1];
  }
  data_[index] = val;
  return &data_[index];
}

template < typename T >
void
ArraySequence<T>::insert(iterator iter, size_type sz, const_reference val) {
  size_type index = iter - data_;
  resize_(size_+sz);
  for(size_type x = size_ - 1; x >= index+sz; --x) {
    data_[x] = data_[x-sz];
  }
  for(size_type x = 0; x < sz; ++x) {
    data_[index+x] = val;
  }
}

template < typename T >
void
ArraySequence<T>::push_back(const_reference val) {
  resize_(size_+1);
  data_[size_-1] = val;
}

template < typename T >
typename ArraySequence<T>::iterator
ArraySequence<T>::erase(iterator iter) {
  size_type index = iter - data_;
  remove_(index);
  return &data_[index];
//    return static_cast<iterator>(0);
}

template < typename T >
typename ArraySequence<T>::iterator
ArraySequence<T>::erase(iterator left, iterator right) {
  size_type leftindex = left - data_;
  size_type rightindex = right - data_;
  for(iterator x = right, y = left; x != &data_[size_]; ++x, ++y) {
    *y = *x; 
  }
  resize_(size_ - (rightindex - leftindex));
  return &data_[leftindex];
}

template < typename T >
void
ArraySequence<T>::pop_back() {
  remove_(size_-1);
}

template < typename T >
void
ArraySequence<T>::clear() {
  resize_(0);
}

template < typename T >
typename ArraySequence<T>::size_type
ArraySequence<T>::capacity() const {
    return capacity_;
}

/**
 *  Member function definitions (ArraySequenceReverseIterator)
 */

template < typename T >
ArraySequenceReverseIterator<T>::ArraySequenceReverseIterator() 
  : Iterator< T, ArraySequenceReverseIterator<T> >() , pos_(0) {

}

template < typename T >
ArraySequenceReverseIterator<T>::ArraySequenceReverseIterator(const ArraySequenceReverseIterator& rhs)
  : Iterator< T, ArraySequenceReverseIterator<T> >() , pos_(rhs.pos_) {
}

template < typename T >
ArraySequenceReverseIterator<T>::~ArraySequenceReverseIterator() {
}

template < typename T >
bool
ArraySequenceReverseIterator<T>::operator==(const ArraySequenceReverseIterator& rhs) const {
    return (pos_ == rhs.pos_);
}

template < typename T >
bool
ArraySequenceReverseIterator<T>::operator!=(const ArraySequenceReverseIterator& rhs) const {
    return (pos_ != rhs.pos_);
}

template < typename T >
ArraySequenceReverseIterator<T>&
ArraySequenceReverseIterator<T>::operator=(const ArraySequenceReverseIterator& rhs) {
	pos_ = rhs.pos_;
    return *this;
}

template < typename T >
typename ArraySequenceReverseIterator<T>::pointer
ArraySequenceReverseIterator<T>::operator->() const {
    return pos_;

}

template < typename T >
typename ArraySequenceReverseIterator<T>::reference
ArraySequenceReverseIterator<T>::operator*() const {
    return *pos_;
}

template < typename T >
ArraySequenceReverseIterator<T>&
ArraySequenceReverseIterator<T>::operator++() {
	--pos_;
    return *this;
}

template < typename T >
ArraySequenceReverseIterator<T>
ArraySequenceReverseIterator<T>::operator++(int) {
	ArraySequenceReverseIterator<T> temp = *this;
	++(*this);
    return temp;
}

template < typename T >
ArraySequenceReverseIterator<T>&
ArraySequenceReverseIterator<T>::operator--() {
	++pos_;
    return *this;
}

template < typename T >
ArraySequenceReverseIterator<T>
ArraySequenceReverseIterator<T>::operator--(int) {
	ArraySequenceReverseIterator<T> temp = *this;
	--(*this);
    return temp;
}

/**
 *  Member function definitions (ArraySequenceConstReverseIterator)
 */

template < typename T >
ArraySequenceConstReverseIterator<T>::ArraySequenceConstReverseIterator()
  : Iterator< T, ArraySequenceConstReverseIterator<T> >() , pos_(0) {
}

template < typename T >
ArraySequenceConstReverseIterator<T>::ArraySequenceConstReverseIterator(const ArraySequenceConstReverseIterator& rhs) 
  : Iterator< T, ArraySequenceConstReverseIterator<T> >() , pos_(rhs.pos_) {
}

template < typename T >
ArraySequenceConstReverseIterator<T>::ArraySequenceConstReverseIterator(const ArraySequenceReverseIterator<T>& rhs)
  : Iterator< T, ArraySequenceConstReverseIterator<T> >() , pos_(rhs.pos_) {
}

template < typename T >
ArraySequenceConstReverseIterator<T>::~ArraySequenceConstReverseIterator() {
}

template < typename T >
bool
ArraySequenceConstReverseIterator<T>::operator==(const ArraySequenceConstReverseIterator& rhs) const {
    return (pos_ == rhs.pos_);
}

template < typename T >
bool
ArraySequenceConstReverseIterator<T>::operator!=(const ArraySequenceConstReverseIterator& rhs) const {
    return (pos_ != rhs.pos_);
}

template < typename T >
ArraySequenceConstReverseIterator<T>&
ArraySequenceConstReverseIterator<T>::operator=(const ArraySequenceConstReverseIterator& rhs) {
	pos_ = rhs.pos_;
    return *this;
}

template < typename T >
typename ArraySequenceConstReverseIterator<T>::pointer
ArraySequenceConstReverseIterator<T>::operator->() const {
    return pos_;

}

template < typename T >
typename ArraySequenceConstReverseIterator<T>::reference
ArraySequenceConstReverseIterator<T>::operator*() const {
    return *pos_;
}

template < typename T >
ArraySequenceConstReverseIterator<T>&
ArraySequenceConstReverseIterator<T>::operator++() {
	--pos_;
    return *this;
}

template < typename T >
ArraySequenceConstReverseIterator<T>
ArraySequenceConstReverseIterator<T>::operator++(int) {
	ArraySequenceConstReverseIterator<T> temp = *this;
	++(*this);
    return temp;
}

template < typename T >
ArraySequenceConstReverseIterator<T>&
ArraySequenceConstReverseIterator<T>::operator--() {
	++pos_;
    return *this;
}

template < typename T >
ArraySequenceConstReverseIterator<T>
ArraySequenceConstReverseIterator<T>::operator--(int) {
	ArraySequenceConstReverseIterator<T> temp = *this;
	--(*this);
    return temp;
}

/**
 *  Friend function definitions
 */

template < typename T >
std::ostream& operator<< (std::ostream& os, const ArraySequence<T>& seq) {
  os << "[ ";
  for(typename ArraySequence<T>::const_iterator x = seq.begin(); x != seq.end(); ++x, os << " ") {
    os << *x;
  }
  os << "]";
  return os;
}

//------------------------------------------------------------------------------
} // namespace cs603
//------------------------------------------------------------------------------

#endif
