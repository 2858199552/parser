#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>
#include <complex>

namespace client{
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  struct employee{
    int age;
    std::string surname;
    std::string forename;
    double salary;
  };
  
}

// We need to tell fusion about our employee struct
// to make it a first-class fusion citizen. This has to
// be in global scope.

BOOST_FUSION_ADAPT_STRUCT(
    client::employee,
    (int, age)
    (std::string, surname)
    (std::string, forename)
    (double, salary)
)

namespace client{
  template <typename Iterator>
    struct employee_parser : qi::grammar<Iterator, employee(), ascii::space_type>{
      employee_parser() : employee_parser::base_type(start){
        using qi::int_;
        using qi::lit;
        using qi::double_;
        using qi::lexeme;
        using ascii::char_;

        quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];

        start %= 
          lit("employee")
          >> '{'
          >> int_ >> ','
          >> quoted_string >> ','
          >> quoted_string >> ','
          >> double_
          >> '}'
          ;
      }

    qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
    qi::rule<Iterator, employee(), ascii::space_type> start;
  };

}

int main(){
  using boost::spirit::ascii::space;
  typedef std::string::const_iterator iterator_type;
  typedef client::employee_parser<iterator_type> employee_parser;

  employee_parser g;
  std::string str;
  while(getline(std::cin, str)){
    if(str.empty() || str[0] == 'q' || str[0] == 'Q')
      break;

    client::employee emp;
    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();
    bool r = phrase_parse(iter, end, g, space, emp);

    if(r && iter == end){
      std::cout << boost::fusion::tuple_open('[');
      std::cout << boost::fusion::tuple_close(']');
      std::cout << boost::fusion::tuple_delimiter(',');

      std::cout << "Parsing succeeded\n";
      std::cout << "got: " << boost::fusion::as_vector(emp) << std::endl;
    }
    else{
      std::cout << "Parsing failed\n";
    }
  }

  return 0;
}
