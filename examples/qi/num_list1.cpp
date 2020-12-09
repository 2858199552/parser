#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client{
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  // number list parser
  template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last){
      using qi::double_;
      using qi::phrase_parse;
      using ascii::space;

      bool r = phrase_parse(
          first,
          last,
          double_ >> *(',' >> double_), /* the parser */
          space                         /* the skip-parser */
      );
      if(first != last) // fail if we did not get a full match
        return false;
      return r;
    }
}

int main(){
  std::string str;
  while(getline(std::cin, str)){
    if(str.empty() || str[0] == 'q' || str[0] == 'Q')
      break;

    if(client::parse_numbers(str.begin(), str.end())){
      std::cout << str << " Parses OK: " << std::endl;
    }
    else{
      std::cout << "Parsing failed\n";
    }
  }

  return 0;
}
