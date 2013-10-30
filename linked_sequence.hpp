#ifndef LINKED_SEQUENCE_HPP
#define LINKED_SEQUENCE_HPP

#include <iostream>

#include "sequence.hpp"
#include "iterator.hpp"

//------------------------------------------------------------------------------
namespace cs603 {
//------------------------------------------------------------------------------

template < typename T >
class LinkedSequence;

template < typename T >
class LinkedSequenceIterator;

template < typename T >
class LinkedSequenceConstIterator;

template < typename T >
class LinkedSequenceReverseIterator;

template < typename T >
class LinkedSequenceConstReverseIterator;


template < typename T >
struct SequenceTraits< T, LinkedSequence<T> >
{
    typedef size_t                          size_type;
    typedef T                               value_type;
    typedef value_type*                     pointer;
    typedef const value_type*               const_pointer;
    typedef value_type&                     reference;
    typedef const value_type&               const_reference;
    typedef LinkedSequenceIterator<T>       iterator;
    typedef LinkedSequenceConstIterator<T>  const_iterator;
    typedef LinkedSequenceReverseIterator<T> reverse_iterator;
    typedef LinkedSequenceConstReverseIterator<T> const_reverse_iterator;
};

template < typename T >
struct IteratorTraits< T, LinkedSequenceIterator<T> >
{
    typedef T   value_type;
    typedef T*  pointer;
    typedef T&  reference;
};

template < typename T >
struct IteratorTraits< T, LinkedSequenceConstIterator<T> >
{
    typedef const T   value_type;
    typedef const T*  pointer;
    typedef const T&  reference;
};

template < typename T >
struct IteratorTraits< T, LinkedSequenceReverseIterator<T> >
{
    typedef const T   value_type;
    typedef const T*  pointer;
    typedef const T&  reference;
};

template < typename T >
struct IteratorTraits< T, LinkedSequenceConstReverseIterator<T> >
{
    typedef const T   value_type;
    typedef const T*  pointer;
    typedef const T&  reference;
};

template < typename T >
std::ostream& operator<<(std::ostream&, const LinkedSequence<T>&);

template < typename T >
class LinkedSequence
    : public Sequence< T, LinkedSequence<T> >
{
public:
    typedef SequenceTraits<T,LinkedSequence<T> > traits;

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
    ///@TODO                                                                    
    ///@TODO    QUESTION 7: What is the alternative to making                   
    ///@TODO        LinkedSequenceIterator<T> a friend class?                   
    ///@TODO                                                                    
    friend class LinkedSequenceIterator<T>;
    friend class LinkedSequenceConstIterator<T>;
    friend class LinkedSequenceReverseIterator<T>;
    friend class LinkedSequenceConstReverseIterator<T>;

    /**
     *  Constructors/Destructor
     */

    ///@brief   Creates an empty sequence without any elements.
    LinkedSequence();

    ///@brief   Creates a deep copy of another sequence
    LinkedSequence(const LinkedSequence&);

    ///@brief   Creates a sequence with n copies of data.
    ///@param   n
    ///@param   data  Optional.
    LinkedSequence(size_type, const_reference);

    ///@brief   Creates a sequence initialized with the elements.
    ///         of the range [beg,end)
    ///@param   beg
    ///@param   end
    template < typename InputIterator >
    explicit LinkedSequence(InputIterator, InputIterator);

    ///@brief   Destroys all elements.
    ///
    /// If the elements are pointers, the pointed-to memory
    /// is not touched in any way.  Managing the pointer is
    /// the user's responsibility.
    virtual ~LinkedSequence();

    /**
     *  Inherited member functions
     */
    size_type size() const;
    bool empty() const;

    bool operator==(const LinkedSequence&) const;
    bool operator!=(const LinkedSequence&) const;
    bool operator<(const LinkedSequence&) const;
    bool operator>(const LinkedSequence&) const;
    bool operator<=(const LinkedSequence&) const;
    bool operator>=(const LinkedSequence&) const;

    LinkedSequence& operator=(const LinkedSequence&);
    void swap(LinkedSequence&);

    reference operator[](size_type);                        // O(n)
    const_reference operator[](size_type) const;            // O(n)
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

    iterator insert(iterator, const_reference);             // O(1)
    void insert(iterator, size_type, const_reference);      // O(1)
    void push_back(const_reference);                        // O(1)
    iterator erase(iterator);                               // O(1)
    iterator erase(iterator, iterator);                     // O(1)
    void pop_back();
    void clear();                                           // O(n)

    /**
     *  Friend functions
     */
    friend std::ostream& operator<< <> (std::ostream&, const LinkedSequence&);

private:
    ///@TODO                                                                    
    ///@TODO    Add internal representation.                                    
    ///@TODO                                                                    
    struct Node {
      value_type * value;
      Node * prev;
      Node * next;
      Node(value_type*, Node*, Node*);
    };

    Node * head_;
    Node * tail_;
    size_type size_;
    
    void initList_();

	iterator insert_(iterator, const_reference);

	iterator remove_(iterator);

    template < typename Integer >
    void initialize_dispatch(Integer, Integer, std::__true_type);

    template < typename InputIterator >
    void initialize_dispatch(InputIterator, InputIterator, std::__false_type);

    // Copied from stl_algobase.h, referenced by stl_vector.h ... if this is
    // incorrect behavior then tell it to the STL.
    template < typename InputIterator >
	bool lex_compare(InputIterator f1, InputIterator l1, InputIterator f2, InputIterator l2) const;	

    
};


template < typename T >
class LinkedSequenceIterator
    : public Iterator< T, LinkedSequenceIterator<T> >
{
public:
    typedef IteratorTraits<T,LinkedSequenceIterator<T> > traits;

    typedef typename traits::value_type value_type;
    typedef typename traits::pointer    pointer;
    typedef typename traits::reference  reference;
    typedef struct LinkedSequence<T>::Node  Node; 

    /**
     *  Friend classes
     */
    ///@NOTE    Depending on your implementation, you may find the following
    ///@NOTE    friend declaration useful.
    friend class LinkedSequence<T>;
    friend class LinkedSequenceConstIterator<T>;

    /**
     *  Constructors/Destructor
     */
    LinkedSequenceIterator();
    LinkedSequenceIterator(const LinkedSequenceIterator&);

    virtual ~LinkedSequenceIterator();

    /**
     *  Inherited member functions
     */
    bool operator==(const LinkedSequenceIterator&) const;
    bool operator!=(const LinkedSequenceIterator&) const;
    LinkedSequenceIterator& operator=(const LinkedSequenceIterator&);
    pointer operator->() const;
    reference operator*() const;
    LinkedSequenceIterator& operator++();
    LinkedSequenceIterator operator++(int);
    LinkedSequenceIterator& operator--();
    LinkedSequenceIterator operator--(int);


private:
    ///@TODO                                                                    
    ///@TODO    Add internal representation.                                    
    ///@TODO                                                                    
    LinkedSequenceIterator(Node *);
    Node * pos_;
    inline Node * getPos() { return pos_; };
};

template < typename T >
class LinkedSequenceConstIterator
    : public Iterator< T, LinkedSequenceConstIterator<T> >
{
public:
    typedef IteratorTraits<T,LinkedSequenceConstIterator<T> > traits;

    typedef typename traits::value_type value_type;
    typedef typename traits::pointer    pointer;
    typedef typename traits::reference  reference;
    typedef struct LinkedSequence<T>::Node  Node; 

    friend class LinkedSequence<T>;
    friend class LinkedSequenceIterator<T>;
    /**
     *  Constructors/Destructor
     */
    LinkedSequenceConstIterator();
    LinkedSequenceConstIterator(const LinkedSequenceConstIterator&);
    
    ///@NOTE    Alternatively, you could provide a conversion operator in the
    ///@NOTE    LinkedSequenceIterator class.
    LinkedSequenceConstIterator(const LinkedSequenceIterator<T>&);

    virtual ~LinkedSequenceConstIterator();

    /**
     *  Inherited member functions
     */
    bool operator==(const LinkedSequenceConstIterator&) const;
    bool operator!=(const LinkedSequenceConstIterator&) const;
    LinkedSequenceConstIterator& operator=(const LinkedSequenceConstIterator&);
    pointer operator->() const;
    reference operator*() const;
    LinkedSequenceConstIterator& operator++();
    LinkedSequenceConstIterator operator++(int);
    LinkedSequenceConstIterator& operator--();
    LinkedSequenceConstIterator operator--(int);

private:
    ///@TODO                                                                    
    ///@TODO    Add internal representation.                                    
    ///@TODO                                                                    
    LinkedSequenceConstIterator(Node *);

    Node * pos_;
    inline Node * getPos() { return pos_; };
};


template < typename T >
class LinkedSequenceReverseIterator
    : public Iterator< T, LinkedSequenceReverseIterator<T> >
{
public:
    typedef IteratorTraits<T,LinkedSequenceReverseIterator<T> > traits;

    typedef typename traits::value_type value_type;
    typedef typename traits::pointer    pointer;
    typedef typename traits::reference  reference;
    typedef struct LinkedSequence<T>::Node  Node; 

    /**
     *  Friend classes
     */
    ///@NOTE    Depending on your implementation, you may find the following
    ///@NOTE    friend declaration useful.
    friend class LinkedSequence<T>;
    friend class LinkedSequenceConstReverseIterator<T>;

    /**
     *  Constructors/Destructor
     */
    LinkedSequenceReverseIterator();
    LinkedSequenceReverseIterator(const LinkedSequenceReverseIterator&);

    virtual ~LinkedSequenceReverseIterator();

    /**
     *  Inherited member functions
     */
    bool operator==(const LinkedSequenceReverseIterator&) const;
    bool operator!=(const LinkedSequenceReverseIterator&) const;
    LinkedSequenceReverseIterator& operator=(const LinkedSequenceReverseIterator&);
    pointer operator->() const;
    reference operator*() const;
    LinkedSequenceReverseIterator& operator++();
    LinkedSequenceReverseIterator operator++(int);
    LinkedSequenceReverseIterator& operator--();
    LinkedSequenceReverseIterator operator--(int);


private:
    ///@TODO                                                                    
    ///@TODO    Add internal representation.                                    
    ///@TODO                                                                    
    LinkedSequenceReverseIterator(Node *);
    Node * pos_;
    inline Node * getPos() { return pos_; };
};

template < typename T >
class LinkedSequenceConstReverseIterator
    : public Iterator< T, LinkedSequenceConstReverseIterator<T> >
{
public:
    typedef IteratorTraits<T,LinkedSequenceConstReverseIterator<T> > traits;

    typedef typename traits::value_type value_type;
    typedef typename traits::pointer    pointer;
    typedef typename traits::reference  reference;
    typedef struct LinkedSequence<T>::Node  Node; 

    friend class LinkedSequence<T>;
    friend class LinkedSequenceReverseIterator<T>;
    /**
     *  Constructors/Destructor
     */
    LinkedSequenceConstReverseIterator();
    LinkedSequenceConstReverseIterator(const LinkedSequenceConstReverseIterator&);
    
    ///@NOTE    Alternatively, you could provide a conversion operator in the
    ///@NOTE    LinkedSequenceReverseIterator class.
    LinkedSequenceConstReverseIterator(const LinkedSequenceReverseIterator<T>&);

    virtual ~LinkedSequenceConstReverseIterator();

    /**
     *  Inherited member functions
     */
    bool operator==(const LinkedSequenceConstReverseIterator&) const;
    bool operator!=(const LinkedSequenceConstReverseIterator&) const;
    LinkedSequenceConstReverseIterator& operator=(const LinkedSequenceConstReverseIterator&);
    pointer operator->() const;
    reference operator*() const;
    LinkedSequenceConstReverseIterator& operator++();
    LinkedSequenceConstReverseIterator operator++(int);
    LinkedSequenceConstReverseIterator& operator--();
    LinkedSequenceConstReverseIterator operator--(int);

private:
    ///@TODO                                                                    
    ///@TODO    Add internal representation.                                    
    ///@TODO                                                                    
    LinkedSequenceConstReverseIterator(Node *);

    Node * pos_;
    inline Node * getPos() { return pos_; };
};



/**
 *  Member function definitions (LinkedSequence)
 */

template < typename T >
LinkedSequence<T>::LinkedSequence()
  : Sequence< T, LinkedSequence<T> >(), size_(0) {
  initList_();
}


template < typename T >
LinkedSequence<T>::LinkedSequence(const LinkedSequence& rhs)
  : Sequence< T, LinkedSequence<T> >(), size_(0) {
    initList_();
    for(const_iterator x = rhs.begin(); x != rhs.end(); ++x) {
      insert_(iterator(tail_), *x);
    }
}

template < typename T >
LinkedSequence<T>::LinkedSequence(size_type sz, const_reference val)
  : Sequence< T, LinkedSequence<T> >(), size_(0) {
    initList_();
    for(size_type x = 0; x < sz; ++x) {
      insert_(iterator(tail_),val);
    }
}

template < typename T >
template < typename InputIterator >
LinkedSequence<T>::LinkedSequence(InputIterator left, InputIterator right)
  : size_(0) {
    // shamelessly borrowed from the vector stl, the names have been changed
    // slightly -- otherwise verbaitum.
    typedef typename std::__is_integer<InputIterator>::__type Integral;
    initialize_dispatch(left, right, Integral());
}

template < typename T >
template < typename Integer >
void LinkedSequence<T>::initialize_dispatch(Integer sz, Integer val, std::__true_type) {
  initList_();
  for(Integer x = 0; x < sz; ++x) {
    insert_(iterator(tail_),val);
  }
}

template < typename T >
template < typename InputIterator >
void LinkedSequence<T>::initialize_dispatch(InputIterator left, InputIterator right, std::__false_type) {
  initList_();
  for(const_iterator x = left; x != right; ++x) {
    insert_(iterator(tail_), *x);
  }
}

template < typename T >
LinkedSequence<T>::~LinkedSequence() {
    //delete end node
  while(size_ > 0) 
    remove_(tail_->prev);
  delete head_;
  delete tail_;
}

template < typename T >
typename LinkedSequence<T>::size_type
LinkedSequence<T>::size() const {
    return size_;
}

template < typename T >
bool
LinkedSequence<T>::empty() const {
	return (size_ == 0) ?  true : false;

}

template < typename T >
bool
LinkedSequence<T>::operator==(const LinkedSequence& rhs) const {
    if (size_ != rhs.size_) return false;
    for(const_iterator x(head_->next), y(rhs.head_->next); x != const_iterator(tail_); ++x, ++y) 
		if((*x) != (*y)) { return false;}
  	return true;
}

template < typename T >
bool
LinkedSequence<T>::operator!=(const LinkedSequence& rhs) const {
	return !(*this == rhs);
}

template < typename T >
bool
LinkedSequence<T>::operator<(const LinkedSequence& rhs) const {
    return lex_compare(const_iterator(head_->next), const_iterator(tail_), rhs.begin(), rhs.end());
}

template < typename T >
bool
LinkedSequence<T>::operator>(const LinkedSequence& rhs) const {
    return rhs < *this;
}

template < typename T >
bool
LinkedSequence<T>::operator<=(const LinkedSequence& rhs) const {
    return !(rhs < *this);
}

template < typename T >
bool
LinkedSequence<T>::operator>=(const LinkedSequence& rhs) const {
    return !(*this < rhs);
}

template < typename T >
LinkedSequence<T>&
LinkedSequence<T>::operator=(const LinkedSequence& rhs) {
  if(rhs == *this) return *this;

  while(size_ > 0) 
    remove_(tail_->prev);
  for(const_iterator x = rhs.begin(); x != rhs.end(); ++x) {
    insert_(iterator(tail_), *x);
  }
  return *this;
}

template < typename T >
void
LinkedSequence<T>::swap(LinkedSequence& rhs) {
  size_type temps = rhs.size_;
  Node * temp1 = rhs.head_;
  Node * temp2 = rhs.tail_;
  rhs.head_ = head_;
  rhs.tail_ = tail_;
  rhs.size_ = size_;
  size_ = temps;
  head_ = temp1;
  tail_ = temp2;
}

template < typename T >
typename LinkedSequence<T>::reference
LinkedSequence<T>::operator[](size_type index) {
    iterator iter = iterator(head_->next);
    for(size_type x = 0; x < index; x++, ++iter) ;
    return *iter;
}

template < typename T >
typename LinkedSequence<T>::const_reference
LinkedSequence<T>::operator[](size_type index) const {
    const_iterator iter = const_iterator(head_->next);
    for(size_type x = 0; x < index; ++x, ++iter) ;
    return *iter;
}

template < typename T >
typename LinkedSequence<T>::reference
LinkedSequence<T>::front() {
    return *(head_->next->value);
}

template < typename T >
typename LinkedSequence<T>::const_reference
LinkedSequence<T>::front() const {
    return *(head_->next->value);
}

template < typename T >
typename LinkedSequence<T>::reference
LinkedSequence<T>::back() {
    return *(tail_->prev->value);
}

template < typename T >
typename LinkedSequence<T>::const_reference
LinkedSequence<T>::back() const {
    return *(tail_->prev->value);
}

template < typename T >
typename LinkedSequence<T>::iterator
LinkedSequence<T>::begin() {
    return iterator(head_->next);
}

template < typename T >
typename LinkedSequence<T>::const_iterator
LinkedSequence<T>::begin() const {
    return const_iterator(head_->next);
}

template < typename T >
typename LinkedSequence<T>::iterator
LinkedSequence<T>::end() {
    return iterator(tail_);
}

template < typename T >
typename LinkedSequence<T>::const_iterator
LinkedSequence<T>::end() const {
    return const_iterator(tail_);
}

template < typename T >
typename LinkedSequence<T>::reverse_iterator
LinkedSequence<T>::rbegin() {
    return reverse_iterator(tail_->prev);
}

template < typename T >
typename LinkedSequence<T>::const_reverse_iterator
LinkedSequence<T>::rbegin() const {
    return const_reverse_iterator(tail_->prev);
}

template < typename T >
typename LinkedSequence<T>::reverse_iterator
LinkedSequence<T>::rend() {
    return reverse_iterator(head_);
}

template < typename T >
typename LinkedSequence<T>::const_reverse_iterator
LinkedSequence<T>::rend() const {
    return const_reverse_iterator(head_);
}

template < typename T >
typename LinkedSequence<T>::iterator
LinkedSequence<T>::insert(iterator iter, const_reference val) {
    return insert_(iter, val);
}

template < typename T >
void
LinkedSequence<T>::insert(iterator iter, size_type sz, const_reference val) {
    for(size_type x = 0; x < sz; ++x) {
      insert_(iter,val);
    }
}

template < typename T >
void
LinkedSequence<T>::push_back(const_reference val) {
  insert_(iterator(tail_), val);
}

template < typename T >
typename LinkedSequence<T>::iterator
LinkedSequence<T>::erase(iterator x) {
    return remove_(x);
}

template < typename T >
typename LinkedSequence<T>::iterator
LinkedSequence<T>::erase(iterator left, iterator right) {
  while(left != right) {
    left = remove_(left);
  }
  return left;
}

template < typename T >
void
LinkedSequence<T>::pop_back() {
  remove_(tail_->prev);
}

template < typename T >
void
LinkedSequence<T>::clear() {
  while(size_ > 0) 
    remove_(tail_->prev);
}

/**
 *  Member function definitions (LinkedSequenceIterator)
 */

template < typename T >
LinkedSequenceIterator<T>::LinkedSequenceIterator()
 : Iterator< T, LinkedSequenceIterator<T> >(), pos_(0) {
}

template < typename T >
LinkedSequenceIterator<T>::LinkedSequenceIterator(Node * n) 
 : Iterator< T, LinkedSequenceIterator<T> >(), pos_(n) {
}

template < typename T >
LinkedSequenceIterator<T>::LinkedSequenceIterator(const LinkedSequenceIterator& rhs) 
 : Iterator< T, LinkedSequenceIterator<T> >(), pos_(rhs.pos_) {
}

template < typename T >
LinkedSequenceIterator<T>::~LinkedSequenceIterator() {
}

template < typename T >
bool
LinkedSequenceIterator<T>::operator==(const LinkedSequenceIterator& rhs) const {
	return (pos_ == rhs.pos_);
}

template < typename T >
bool
LinkedSequenceIterator<T>::operator!=(const LinkedSequenceIterator& rhs) const {
	return (pos_ != rhs.pos_);
}

template < typename T >
LinkedSequenceIterator<T>&
LinkedSequenceIterator<T>::operator=(const LinkedSequenceIterator& rhs) {
	pos_ = rhs.pos_;
	return *this;
}

template < typename T >
typename LinkedSequenceIterator<T>::pointer
LinkedSequenceIterator<T>::operator->() const {
    return pos_->value;
}

template < typename T >
inline typename LinkedSequenceIterator<T>::reference
LinkedSequenceIterator<T>::operator*() const {
    return *(pos_->value);
}

template < typename T >
inline LinkedSequenceIterator<T>&
LinkedSequenceIterator<T>::operator++() {
	pos_ = pos_->next;
    return *this;
}

template < typename T >
inline LinkedSequenceIterator<T>
LinkedSequenceIterator<T>::operator++(int) {
    LinkedSequenceIterator<T> temp = *this;
    ++(*this);
    return temp;
}

template < typename T >
LinkedSequenceIterator<T>&
LinkedSequenceIterator<T>::operator--() {
	pos_ = pos_->prev;
    return *this;
}

template < typename T >
LinkedSequenceIterator<T>
LinkedSequenceIterator<T>::operator--(int) {
    LinkedSequenceIterator<T> temp = *this;
    --(*this);
    return temp;
}

/**
 *  Member function definitions (LinkedSequenceConstIterator)
 */

template < typename T >
LinkedSequenceConstIterator<T>::LinkedSequenceConstIterator()
 : Iterator< T, LinkedSequenceConstIterator<T> >(), pos_(0) {
}

template < typename T >
LinkedSequenceConstIterator<T>::LinkedSequenceConstIterator(Node * n) 
 : Iterator< T, LinkedSequenceConstIterator<T> >(), pos_(n) {
}

template < typename T >
LinkedSequenceConstIterator<T>::LinkedSequenceConstIterator(const LinkedSequenceConstIterator& rhs) 
 : Iterator< T, LinkedSequenceConstIterator<T> >(), pos_(rhs.pos_) {
}

template < typename T >
LinkedSequenceConstIterator<T>::LinkedSequenceConstIterator(const LinkedSequenceIterator<T>& rhs) 
 : Iterator< T, LinkedSequenceConstIterator<T> >(), pos_(rhs.pos_) {
}

template < typename T >
LinkedSequenceConstIterator<T>::~LinkedSequenceConstIterator() {
}

template < typename T >
bool
LinkedSequenceConstIterator<T>::operator==(const LinkedSequenceConstIterator& rhs) const {
	return (pos_ == rhs.pos_) ?  true : false;
}

template < typename T >
bool
LinkedSequenceConstIterator<T>::operator!=(const LinkedSequenceConstIterator& rhs) const {
	return (pos_ != rhs.pos_) ?  true : false;
}

template < typename T >
LinkedSequenceConstIterator<T>&
LinkedSequenceConstIterator<T>::operator=(const LinkedSequenceConstIterator& rhs) {
	pos_ = rhs.pos_;
	return *this;
}

template < typename T >
typename LinkedSequenceConstIterator<T>::pointer
LinkedSequenceConstIterator<T>::operator->() const {
    return pos_->value;
}

template < typename T >
typename LinkedSequenceConstIterator<T>::reference
LinkedSequenceConstIterator<T>::operator*() const {
    return *(pos_->value);
}

template < typename T >
LinkedSequenceConstIterator<T>&
LinkedSequenceConstIterator<T>::operator++() {
	pos_ = pos_->next;
    return *this;
}

template < typename T >
LinkedSequenceConstIterator<T>
LinkedSequenceConstIterator<T>::operator++(int) {
    LinkedSequenceConstIterator<T> temp = *this;
    ++(*this);
    return temp;
}

template < typename T >
LinkedSequenceConstIterator<T>&
LinkedSequenceConstIterator<T>::operator--() {
	pos_ = pos_->prev;
    return *this;
}

template < typename T >
LinkedSequenceConstIterator<T>
LinkedSequenceConstIterator<T>::operator--(int) {
    LinkedSequenceConstIterator<T> temp = *this;
    --(*this);
    return temp;
}


/**
 *  Member function definitions (LinkedSequenceReverseIterator)
 */

template < typename T >
LinkedSequenceReverseIterator<T>::LinkedSequenceReverseIterator()
 : Iterator< T, LinkedSequenceReverseIterator<T> >(), pos_(0) {
}

template < typename T >
LinkedSequenceReverseIterator<T>::LinkedSequenceReverseIterator(Node * n) 
 : Iterator< T, LinkedSequenceReverseIterator<T> >(), pos_(n) {
}

template < typename T >
LinkedSequenceReverseIterator<T>::LinkedSequenceReverseIterator(const LinkedSequenceReverseIterator& rhs) 
 : Iterator< T, LinkedSequenceReverseIterator<T> >(), pos_(rhs.pos_) {
}

template < typename T >
LinkedSequenceReverseIterator<T>::~LinkedSequenceReverseIterator() {
}

template < typename T >
bool
LinkedSequenceReverseIterator<T>::operator==(const LinkedSequenceReverseIterator& rhs) const {
	return (pos_ == rhs.pos_);
}

template < typename T >
bool
LinkedSequenceReverseIterator<T>::operator!=(const LinkedSequenceReverseIterator& rhs) const {
	return (pos_ != rhs.pos_);
}

template < typename T >
LinkedSequenceReverseIterator<T>&
LinkedSequenceReverseIterator<T>::operator=(const LinkedSequenceReverseIterator& rhs) {
	pos_ = rhs.pos_;
	return *this;
}

template < typename T >
typename LinkedSequenceReverseIterator<T>::pointer
LinkedSequenceReverseIterator<T>::operator->() const {
    return pos_->value;
}

template < typename T >
inline typename LinkedSequenceReverseIterator<T>::reference
LinkedSequenceReverseIterator<T>::operator*() const {
    return *(pos_->value);
}

template < typename T >
inline LinkedSequenceReverseIterator<T>&
LinkedSequenceReverseIterator<T>::operator++() {
	pos_ = pos_->prev;
    return *this;
}

template < typename T >
inline LinkedSequenceReverseIterator<T>
LinkedSequenceReverseIterator<T>::operator++(int) {
    LinkedSequenceReverseIterator<T> temp = *this;
    ++(*this);
    return temp;
}

template < typename T >
LinkedSequenceReverseIterator<T>&
LinkedSequenceReverseIterator<T>::operator--() {
	pos_ = pos_->next;
    return *this;
}

template < typename T >
LinkedSequenceReverseIterator<T>
LinkedSequenceReverseIterator<T>::operator--(int) {
    LinkedSequenceReverseIterator<T> temp = *this;
    --(*this);
    return temp;
}

/**
 *  Member function definitions (LinkedSequenceConstReverseIterator)
 */

template < typename T >
LinkedSequenceConstReverseIterator<T>::LinkedSequenceConstReverseIterator()
 : Iterator< T, LinkedSequenceConstReverseIterator<T> >() ,  pos_(0) {
}

template < typename T >
LinkedSequenceConstReverseIterator<T>::LinkedSequenceConstReverseIterator(Node * n) 
  : Iterator< T, LinkedSequenceConstReverseIterator<T> >() , pos_(n){
}

template < typename T >
LinkedSequenceConstReverseIterator<T>::LinkedSequenceConstReverseIterator(const LinkedSequenceConstReverseIterator& rhs) 
  : Iterator< T, LinkedSequenceConstReverseIterator<T> >() , pos_(rhs.pos_) {
}

template < typename T >
LinkedSequenceConstReverseIterator<T>::LinkedSequenceConstReverseIterator(const LinkedSequenceReverseIterator<T>& rhs) 
  : Iterator< T, LinkedSequenceConstReverseIterator<T> >() , pos_(rhs.pos_) {
}

template < typename T >
LinkedSequenceConstReverseIterator<T>::~LinkedSequenceConstReverseIterator() {
}

template < typename T >
bool
LinkedSequenceConstReverseIterator<T>::operator==(const LinkedSequenceConstReverseIterator& rhs) const {
	return (pos_ == rhs.pos_) ?  true : false;
}

template < typename T >
bool
LinkedSequenceConstReverseIterator<T>::operator!=(const LinkedSequenceConstReverseIterator& rhs) const {
	return (pos_ != rhs.pos_) ?  true : false;
}

template < typename T >
LinkedSequenceConstReverseIterator<T>&
LinkedSequenceConstReverseIterator<T>::operator=(const LinkedSequenceConstReverseIterator& rhs) {
	pos_ = rhs.pos_;
	return *this;
}

template < typename T >
typename LinkedSequenceConstReverseIterator<T>::pointer
LinkedSequenceConstReverseIterator<T>::operator->() const {
    return pos_->value;
}

template < typename T >
typename LinkedSequenceConstReverseIterator<T>::reference
LinkedSequenceConstReverseIterator<T>::operator*() const {
    return *(pos_->value);
}

template < typename T >
LinkedSequenceConstReverseIterator<T>&
LinkedSequenceConstReverseIterator<T>::operator++() {
	pos_ = pos_->prev;
    return *this;
}

template < typename T >
LinkedSequenceConstReverseIterator<T>
LinkedSequenceConstReverseIterator<T>::operator++(int) {
    LinkedSequenceConstReverseIterator<T> temp = *this;
    ++(*this);
    return temp;
}

template < typename T >
LinkedSequenceConstReverseIterator<T>&
LinkedSequenceConstReverseIterator<T>::operator--() {
 	pos_ = pos_->next;
    return *this;
}

template < typename T >
LinkedSequenceConstReverseIterator<T>
LinkedSequenceConstReverseIterator<T>::operator--(int) {
    LinkedSequenceConstReverseIterator<T> temp = *this;
    --(*this);
    return temp;
}

/**
 *  Friend function definitions
 */

template < typename T >
std::ostream& operator<< (std::ostream& os, const LinkedSequence<T>& seq) {
  os << "[ ";
  for(typename LinkedSequence<T>::const_iterator x = seq.begin(); x != seq.end(); ++x, os << " ") {
    os << *x;
  }
  os << "]";
  return os;
}

/**
 * Private Methods
 */

template < typename T >
LinkedSequence<T>::Node::Node(value_type* t, LinkedSequence<T>::Node* m, LinkedSequence<T>::Node* n) 
   : value(t), prev(m), next(n) {
}


template < typename T >
void LinkedSequence<T>::initList_() {
    head_ = new Node(0,0,0);
    tail_ = new Node(0,head_,0);
    head_->next = tail_;
}

template < typename T >
typename LinkedSequence<T>::iterator
LinkedSequence<T>::insert_(iterator iter, const_reference val) { 
  value_type * newval = new value_type(val);
  Node * ref = iter.pos_;
  Node * newnode = new Node(newval, ref->prev, ref);
  ref->prev->next = newnode;
  ref->prev = newnode;
  size_++;
  return iterator(newnode);
}

template < typename T >
typename LinkedSequence<T>::iterator
LinkedSequence<T>::remove_(iterator x) { 
  Node * iter = x.getPos();
  iterator returnval(iter->next);
  iter->prev->next = iter->next;
  iter->next->prev = iter->prev;
  delete iter->value;
  delete iter;
  size_--;
  return returnval;
}

template < typename T >
template < typename InputIterator >
bool LinkedSequence<T>::lex_compare(InputIterator f1, InputIterator l1, InputIterator f2, InputIterator l2) const {
  for(; f1 != l1 && f2 != l2; ++f1, ++f2) {
    if(*f1 < *f2) 
      return true;
    if(*f2 <  *f1)
      return false;
  }
  return f1 == l1 && f2 != l2;
}



//------------------------------------------------------------------------------
} // namespace cs603
//------------------------------------------------------------------------------

#endif
