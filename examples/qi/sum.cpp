#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <iostream>
#include <string>

namespace client{
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;
  namespace phoenix = boost::phoenix;

  using qi::double_;
  using qi::_1;
  using ascii::space;
  using phoenix::ref;

  template <typename Iterator>
    bool adder(Iterator first, Iterator last, double& n){
      bool r = qi::phrase_parse(first, last,
          (
            double_[ref(n) = _1] >> *(',' >> double_[ref(n) += _1])
          ),
          space
          );

      if(first != last)
        return false;
      return r;
    }
}

int main(){
  std::string str;
  while(getline(std::cin, str)){
    if(str.empty() || str[0] == 'q' || str[0] == 'Q')
      break;

    double n;
    if(client::adder(str.begin(), str.end(), n)){
      std::cout << "Parsing succeeded\n";
      std::cout << "sum = " << n << std::endl;
    }
    else{
      std::cout << "Parsing failed\n";
    }
  }

  return 0;
}
