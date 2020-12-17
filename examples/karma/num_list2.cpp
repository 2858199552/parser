#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client{
  template <typename Iterator>
    bool parse_numbers(Iterator first, Iterator last, std::vector<double>& v){
      using boost::spirit::qi::double_;
      using boost::spirit::qi::phrase_parse;
      using boost::spirit::ascii::space;

      bool r = phrase_parse(first, last, double_ % ',', space, v);
      if(first != last)
        return false;
      return r;
    }

  template <typename OutputIterator>
    bool generate_numbers(OutputIterator& sink, std::vector<double> const& v){
      using boost::spirit::karma::double_;
      using boost::spirit::karma::generate_delimited;
      using boost::spirit::ascii::space;

      bool r = generate_delimited(
          sink,
          double_ % ',',
          space,
          v
      );
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
      std::string generated;
      std::back_insert_iterator<std::string> sink(generated);
      if(!client::generate_numbers(sink, v)){
        std::cout << "Generating failed!\n";
      }
      else{
        std::cout << "Generated: " << generated << "\n";
      }
    }
    else{
      std::cout << "Parsing failed\n";
    }
  }

  return 0;
}
