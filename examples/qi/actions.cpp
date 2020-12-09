#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind/bind.hpp>

#include <iostream>

// Presented are various ways to attach semantic actions

namespace client{
  namespace qi = boost::spirit::qi;

  // A plain function
  void print(int const& i){
    std::cout << i << std::endl;
  }

  // A member function
  struct writer{
    void print(int const& i) const{
      std::cout << i << std::endl;
    }
  };

  // A function object
  struct print_action{
    void operator()(int const& i, qi::unused_type, qi::unused_type) const{
      std::cout << i << std::endl;
    }
  };
}

int main(){
  using boost::spirit::qi::int_;
  using boost::spirit::qi::parse;
  using client::print;
  using client::writer;
  using client::print_action;

  { // example using plain function
    char const *first = "{42}", *last = first + std::strlen(first);
    parse(first, last, '{' >> int_[&print] >> '}');
  }

  { // example using simple function object
    char const *first = "{43}", *last = first + std::strlen(first);
    parse(first, last, '{' >> int_[print_action()] >> '}');
  }

  { // example using boost.bind with a plain function
    char const *first = "{44}", *last = first + std::strlen(first);
    using boost::placeholders::_1;
    parse(first, last, '{' >> int_[boost::bind(&print, _1)] >> '}');
  }
  
  { // example using boost::bind with a member function
    char const *first = "{44}", *last = first + std::strlen(first);
    using boost::placeholders::_1;
    writer w;
    parse(first, last, '{' >> int_[boost::bind(&writer::print, &w, _1)] >> '}');
  }
  
  { // example using boost.lambda
    namespace lambda = boost::lambda;
    char const *first = "{45}", *last = first + std::strlen(first);
    using lambda::_1;
    parse(first, last, '{' >> int_[std::cout << _1 << '\n'] >> '}');
  }

  return 0;
}
