#include <string>
#include <vector>
#include <iostream>

#include <assert.h>

#include "array_sequence.hpp"
#include "linked_sequence.hpp"

using std::cout;
using std::endl;

using cs603::LinkedSequence;
using cs603::ArraySequence;

class Test {
  friend std::ostream &operator<<(std::ostream &stream, const Test& ob);
public: 
  Test() : idx(0) {};
  Test(int x) : idx(x) {};
  int f() { return idx; };
private:
  int idx;
};

std::ostream &operator<<(std::ostream &stream, const Test& ob) {
  stream << ob.idx;
  return stream;
}

void testVector() {
    std::vector<int> s1; //default constructor
    std::vector<int> s2;
    assert(s1.empty()); // empty
    for(int x = 0; x < 10; ++x) {
      s1.push_back(x); //push_back
      s2.insert(s2.begin(),x); // insert iterator, val
    }
    //size
    assert(s1.size() == 10);

    //ostream, front, back
    cout << " " << s1.front()  << " " << s1.back() << endl;
    cout << " " << s2.front()  << " " << s2.back() << endl;

    //iterator test, begin, end, ++inc, *dereference, != comparison
    for(std::vector<int>::iterator x = s1.begin(); x != s1.end(); ++x) {
      cout << *x << " ";
      assert(x == x);
    }
    cout << endl;

    //reverse iterator test
    for(std::vector<int>::reverse_iterator x = s2.rbegin(); x != s2.rend(); ++x) {
      cout << *x << " ";
    }
    cout << endl;

    //copy constructor
    std::vector<int> s3 = s2;
    //== operator
    assert(s2 == s3);
    assert(s2 == s2); // just to make sure
    //!= operator
    assert(s2 != s1);
    //assignment operator
    s3 = s1;
    //verify assignment
    assert(s3 != s2);
    assert(s3 == s1);

    //< operator
    assert(s1 < s2);
    //> operator
    assert(s2 > s1);
    //<= operator
    assert(s1 <= s2);
    assert(s1 <= s1);
    //>= operator
    assert(s2 >= s1);
    assert(s2 >= s1);
    int temp = 10;
    int temp2 = 1;
    std::vector<int> s4(10,1); // constructor implicit
    std::vector<int> s5(temp,temp2); // constructor with ref

    assert(s4 == s5);

    //pop_back
    while(!s4.empty()) {
      s4.pop_back();
    }

    //clear
    s5.clear();
    assert(s4 == s5);
    assert(s5.empty());

    s3 = s1;
    std::vector<int>::iterator i1 = s3.begin();
    std::vector<int>::iterator i2 = s3.begin();
    //iterator comparisons, pre and post inc operator
    assert(i1 == i2++);
    assert(i1 != i2);
    assert(++i1 == i2);
    for(int x = 0; x < 4; ++x,++i2) ;


    std::vector<int> s6(i1,i2); // iterator constructor
    for(unsigned int x = 0; x < s6.size(); ++x) // [] operator
      cout << s6[x];
    cout << endl;
    //erase operations, range and individual
    i1 = i2 = s3.erase(i1,i2);
//    cout << s3 << endl;
    i1 = i2 = s3.erase(i1);

    //pre&post decrement
    assert(i2 == i1--);
    i1 = i2;
    assert(i2 != --i1);

	i1 = s3.begin();
	i1++;
//    cout << s3 << endl;
    s3.insert(i1,5,100);
//    cout << s3 << endl;
}


//test push_back, insert, begin, size, empty
void testLinked() {
    LinkedSequence<int> s1; //default constructor
    LinkedSequence<int> s2;
    assert(s1.empty()); // empty
    for(int x = 0; x < 10; ++x) {
      s1.push_back(x); //push_back
      s2.insert(s2.begin(),x); // insert iterator, val
    }
    //size
    assert(s1.size() == 10);

    //ostream, front, back
    cout << s1 << " " << s1.front()  << " " << s1.back() << endl;
    cout << s2 << " " << s2.front()  << " " << s2.back() << endl;

    //iterator test, begin, end, ++inc, *dereference, != comparison
    for(LinkedSequence<int>::iterator x = s1.begin(); x != s1.end(); ++x) {
      cout << *x << " ";
      assert(x == x);
    }
    cout << endl;

    //reverse iterator test
    for(LinkedSequence<int>::reverse_iterator x = s2.rbegin(); x != s2.rend(); ++x) {
      cout << *x << " ";
    }
    cout << endl;

    //copy constructor
    LinkedSequence<int> s3 = s2;
    //== operator
    assert(s2 == s3);
    assert(s2 == s2); // just to make sure
    //!= operator
    assert(s2 != s1);
    //assignment operator
    s3 = s1;
    //verify assignment
    assert(s3 != s2);
    assert(s3 == s1);

    //< operator
    assert(s1 < s2);
    //> operator
    assert(s2 > s1);
    //<= operator
    assert(s1 <= s2);
    assert(s1 <= s1);
    //>= operator
    assert(s2 >= s1);
    assert(s2 >= s1);
    int temp = 10;
    int temp2 = 1;
    LinkedSequence<int> s4(10,1); // constructor implicit
    LinkedSequence<int> s5(temp,temp2); // constructor with ref

    assert(s4 == s5);

    //pop_back
    while(!s4.empty()) {
      s4.pop_back();
    }

    //clear
    s5.clear();
    assert(s4 == s5);
    assert(s5.empty());

    s3 = s1;
    LinkedSequence<int>::iterator i1 = s3.begin();
    LinkedSequence<int>::iterator i2 = s3.begin();
    //iterator comparisons, pre and post inc operator
    assert(i1 == i2++);
    assert(i1 != i2);
    assert(++i1 == i2);
    for(int x = 0; x < 4; ++x,++i2) ;


    LinkedSequence<int> s6(i1,i2); // iterator constructor
    for(unsigned int x = 0; x < s6.size(); ++x) // [] operator
      cout << s6[x];
    cout << endl;
    //erase operations, range and individual
    i1 = i2 = s3.erase(i1,i2);
    cout << s3 << endl;
    i1 = i2 = s3.erase(i1);

    //pre&post decrement
    assert(i2 == i1--);
    i1 = i2;
    assert(i2 != --i1);

	i1 = s3.begin();
	i1++;
	
    cout << s3 << endl;
    s3.insert(i1,5,100);
    cout << s3 << endl;
}


void testArray() {
    ArraySequence<int> s1; //default constructor
    ArraySequence<int> s2;
    assert(s1.empty()); // empty
    for(int x = 0; x < 10; ++x) {
      s1.push_back(x); //push_back
      s2.insert(s2.begin(),x); // insert iterator, val
    }
    //size
    assert(s1.size() == 10);

    //ostream, front, back
    cout << s1 << " " << s1.front()  << " " << s1.back() << endl;
    cout << s2 << " " << s2.front()  << " " << s2.back() << endl;

    //iterator test, begin, end, ++inc, *dereference, != comparison
    for(ArraySequence<int>::iterator x = s1.begin(); x != s1.end(); ++x) {
      cout << *x << " ";
      assert(x == x);
    }
    cout << endl;

    //reverse iterator test
    for(ArraySequence<int>::reverse_iterator x = s2.rbegin(); x != s2.rend(); ++x) {
      cout << *x << " ";
    }
    cout << endl;

    //copy constructor
    ArraySequence<int> s3 = s2;
    //== operator
    assert(s2 == s3);
    assert(s2 == s2); // just to make sure
    //!= operator
    assert(s2 != s1);
    //assignment operator
    s3 = s1;
    //verify assignment
    assert(s3 != s2);
    assert(s3 == s1);

    //< operator
    assert(s1 < s2);
    //> operator
    assert(s2 > s1);
    //<= operator
    assert(s1 <= s2);
    assert(s1 <= s1);
    //>= operator
    assert(s2 >= s1);
    assert(s2 >= s1);
    int temp = 10;
    int temp2 = 1;
    ArraySequence<int> s4(10,1); // constructor implicit
    ArraySequence<int> s5(temp,temp2); // constructor with ref

    assert(s4 == s5);

    //pop_back
    while(!s4.empty()) {
      s4.pop_back();
    }

    //clear
    s5.clear();
    assert(s4 == s5);
    assert(s5.empty());

    s3 = s1;
    ArraySequence<int>::iterator i1 = s3.begin();
    ArraySequence<int>::iterator i2 = s3.begin();
    //iterator comparisons, pre and post inc operator
    assert(i1 == i2++);
    assert(i1 != i2);
    assert(++i1 == i2);
    for(int x = 0; x < 4; ++x,++i2) ;


    ArraySequence<int> s6(i1,i2); // iterator constructor
    for(unsigned int x = 0; x < s6.size(); ++x) // [] operator
      cout << s6[x];
    cout << endl;
    //erase operations, range and individual
    i1 = i2 = s3.erase(i1,i2);
    cout << s3 << endl;
    i1 = i2 = s3.erase(i1);

    //pre&post decrement
    assert(i2 == i1--);
    i1 = i2;
    assert(i2 != --i1);
	
	i1 = s3.begin();
	i1++;
	
    cout << s3 << endl;
    s3.insert(i1,5,100);
    cout << s3 << endl;
}


int main()
{
  cout << "Vector test (for comparison -- lacks some prints, mostly there to verify correct asserts): " << endl;
  testVector();
  cout << "Array test: " << endl;
  testArray();
  cout << "Linked test: " << endl;
  testLinked();

  return 0;
}
