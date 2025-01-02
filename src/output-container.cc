#include <iostream>
#include <string>
#include <functional>
#include <vector>

template <typename Container>
using UnaryOp = std::function<std::string(typename Container::value_type const &)>; 

template<typename Container>
class MyClass{
 public: 
  typedef UnaryOp<Container> UnaryOp;
 private:
  typedef typename Container::const_iterator IteratorType;
  std::string m_startSequence;
  std::string m_endSequence;
  std::string m_delimiter;
  const UnaryOp m_selector;
  IteratorType m_begin;
  IteratorType m_current;
  IteratorType m_end;
  bool m_printedFirstOne;
public:
  MyClass(
    Container const & container
	 ,std::string const & delimiter
   ,const UnaryOp & selector
	 ,std::string const & startSeq
	 ,std::string const & endSeq) 
	  : m_delimiter(delimiter)
     ,m_selector(selector)
	   ,m_begin(container.cbegin())
	   ,m_current(container.cbegin())
	   ,m_end(container.cend())
	   ,m_printedFirstOne(false)
	   ,m_startSequence(startSeq)
	   ,m_endSequence(endSeq) {}

  MyClass(
    IteratorType begin
	 ,IteratorType end
	 ,std::string const & delimiter
   ,const UnaryOp & selector)
	  : m_delimiter(delimiter)
     ,m_selector(selector)
	   ,m_begin(begin)
	   ,m_current(begin)
	   ,m_end(end)
	   ,m_printedFirstOne(false) {}

  MyClass(
    IteratorType begin
	 ,IteratorType end
	 ,std::string const & delimiter
   ,const UnaryOp & selector
	 ,std::string const & startSeq
	 ,std::string const & endSeq) 
	  : m_delimiter(delimiter)
     ,m_selector(selector)
	   ,m_begin(begin), m_current(begin), m_end(end)
	   ,m_printedFirstOne(false), m_startSequence(startSeq)
     ,m_endSequence(endSeq) {}

  void printNextItem(std::ostream & target) {
    if (m_printedFirstOne) {
      target << m_delimiter;
    } else {
      m_printedFirstOne = true;
    }
    //target << std::to_string(*m_current);  // what if current is a string?
    if (nullptr != m_selector) {
      target << m_selector(*m_current);
    } else {
      target << *m_current;
    }
    ++m_current;
  }
  
  bool hasNext() const {
     return m_current != m_end;
  }

  void printStartSequence(std::ostream & target) const {
    target << m_startSequence;
  }
  void printEndSequence(std::ostream & target) const {
    target << m_endSequence;
  }
};

template<typename Container>
MyClass<Container> printContainerContents(
    Container const & container
  , std::string const & delimiter = ", "
  , const UnaryOp<Container> selector = nullptr
  , std::string const & startSeq = "("
  , std::string const & endSeq = ")")
{
  return MyClass<Container>{container, delimiter, selector, startSeq, endSeq};
}

template<typename Container> 
std::ostream& operator<< (std::ostream& target, MyClass<Container> && obj) {
  obj.printStartSequence(target);
  while(obj.hasNext()) {
    obj.printNextItem(target);
  }
  obj.printEndSequence(target);
  return target;
}

int main(int argc, char ** argv) {
  std::vector<int> items = { 10, 20, 30 };
  std::cout << printContainerContents(items, ", ", nullptr) << "\n"; // template argument deduction does work for functions
  //std::cout << printContainerContents<std::vector<int>>(items, ", ", "(", ")") << "\n"; // template argument deduction does work for functions
  //operator<< <std::vector<int>>(std::cout, printContainerContents<std::vector<int>>(items, ", ", "(", ")" ));

                                                                  
  // std::cout << MyClass(items, ", ", "(", ")") << "\n"; // error: does not work for class constructors: 'MyClass': use of class template requires template argument list
//  std::cout << MyClass<std::vector<int>>(items, ", ", "(", ")") << "\n"; // this obviously works, but looks ugly
  return 0;
}
