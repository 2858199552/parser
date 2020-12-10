#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client{
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, std::vector<double>& v){
      using qi::double_;
      using qi::phrase_parse;
      using qi::_1;
      using ascii::space;

      bool r = phrase_parse(first, last,
          (
            double_ % ','
          ),
          space, v);

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

    std::vector<double> v;
    if(client::parse_numbers(str.begin(), str.end(), v)){
      std::cout << "Parsing succeeded\n";
      
      for(std::vector<double>::size_type i = 0; i < v.size(); ++i)
        std::cout << i << ": " << v[i] << std::endl;
    }
    else{
      std::cout << "Parsing failed\n";
    }
  }

  return 0;
}
