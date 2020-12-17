#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <vector>
#include <cstdlib>
#include <ctime>

namespace karma = boost::spirit::karma;

namespace client{
  template <typename OutputIterator>
    struct matrix_grammar : karma::grammar<OutputIterator, std::vector<std::vector<int> >()>{
      matrix_grammar() : matrix_grammar::base_type(matrix){
        using karma::int_;
        using karma::right_align;
        using karma::eol;

        element = right_align(10)[int_];
        row = '|' << *element << '|';
        matrix = row % eol;
      }

      karma::rule<OutputIterator, std::vector<std::vector<int> >()> matrix;
      karma::rule<OutputIterator, std::vector<int>()> row;
      karma::rule<OutputIterator, int()> element;
    };

  template <typename OutputIterator>
    bool generate_matrix(OutputIterator& sink, std::vector<std::vector<int> > const& v){
      matrix_grammar<OutputIterator>matrix;
      return karma::generate(
          sink,
          matrix,
          v
      );
    }
}

int main(){
  std::vector<std::vector<int> > v;

  std::srand((unsigned int)std::time(NULL));
  std::size_t rows = std::rand() / (RAND_MAX / 10);
  std::size_t columns = std::rand() / (RAND_MAX / 10);

  v.resize(rows);
  for(std::size_t row = 0; row < rows; ++row){
    v[row].resize(columns);
    std::generate(v[row].begin(), v[row].end(), std::rand);
  }

  std::string generated;
  std::back_insert_iterator<std::string> sink(generated);
  if(!client::generate_matrix(sink, v)){
    std::cout << "Generating failed\n";
  }
  else{
    std::cout << "Generated:\n" << generated << std::endl;
  }

  return 0;
}
