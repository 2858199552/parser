#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/bind/bind.hpp>
#include <boost/ref.hpp>

#include <iostream>
#include <string>

#include "example.hpp"

namespace lex = boost::spirit::lex;

enum token_ids{
  ID_WORD = 1000,
  ID_EOL,
  ID_CHAR
};

template <typename Lexer>
struct word_count_tokens : lex::lexer<Lexer>{
  word_count_tokens(){
    this->self.add
      ("[^ \t\n]+", ID_WORD)
      ("\n", ID_EOL)
      (".", ID_CHAR)
    ;
  }
};

struct counter{
  typedef bool result_type;
  
  template <typename Token>
    bool operator()(Token const& t, std::size_t& c, std::size_t& w, std::size_t& l) const{
      switch(t.id()){
        case ID_WORD:
          ++w; c += t.value().size();
          break;
        case ID_EOL:
          ++l; ++c;
          break;
        case ID_CHAR:
          ++c;
          break;
      }
      return true;
    }
};

int main(int argc, char* argv[]){
  std::size_t c = 0, w = 0, l = 0;
  std::string str(read_from_file(1 == argc ? "word_count.input" : argv[1]));
  word_count_tokens<lex::lexertl::lexer<> > word_count_functor;

  using boost::placeholders::_1;
  char const* first = str.c_str();
  char const* last = &first[str.size()];
  bool r = lex::tokenize(first, last, word_count_functor,
      boost::bind(counter(), _1, boost::ref(c), boost::ref(w), boost::ref(l)));

  if(r){
    std::cout << "lines: " << l << ", words:" << w
              << ", characters: " << c << "\n";
  }
  else{
    std::string rest(first, last);
    std::cout << "Lexical analysis failed\n" << "stopped at: \""
              << rest << "\"\n";
  }
  return 0;
}
