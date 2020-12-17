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

  struct complex{
    complex(double a, double b = 0.0) : a(a), b(b){}

    double a;
    double b;
  };

  std::ostream&
    operator<< (std::ostream& os, complex const& z){
      os << "{" << z.a << "," << z.b << "}";
      return os;
    }

  template <typename OutputIterator, typename Container>
    bool generate_numbers(OutputIterator& sink, Container const& v){
      using boost::spirit::karma::stream;
      using boost::spirit::karma::generate;
      using boost::spirit::karma::eol;

      bool r = generate(
          sink,
          stream % eol,
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
      std::vector<client::complex> vc;
      std::vector<double>::const_iterator end = v.end();
      for(std::vector<double>::const_iterator it = v.begin(); it != end; ++it){
        double real(*it);
        if(++it != end)
          vc.push_back(client::complex(real, *it));
        else{
          vc.push_back(client::complex(real));
          break;
        }
      }

      std::string generated;
      std::back_insert_iterator<std::string> sink(generated);
      if(!client::generate_numbers(sink, vc)){
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
