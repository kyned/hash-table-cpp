/* Produces an executable which tests ability of a hash_map 
 *   to handle insertion collisions. In order for it to definetely encounter
 *   a number of collisions set macro <ELEMENTS_TO_PASS> to be bigger than 
 *   a default size of a hash_map table.
 * If it fails, then a returned value is non-zero. But if you want it to 
 *   produce sort of verbose output to stdout pass "-v" or "--verbose" 
 *   as command line argument to executable.
 */

#include <iostream>
#include "../hash_map_implementation.cpp"

#define ELEMENTS_TO_PASS 128

#define RESULT_TO_STDOUT  true

/**@brief in current implementation returns 0 on a success and 1 if any pair was lost.
 */
int main(int argc, char** argv) {

  if (argc > 2) {
    std::cerr << "Too many input arguments. Check source file for additional info." << std::endl;
    return 0x7F;
  }

  if (argc == 2) {
    if (!((std::string(argv[1]) == "-v") || \
        (std::string(argv[1]) == "--verbose"))) {
      std::cerr << "Option is not supported. Try '-v' or '--verbose'." << std::endl;
      return 0x7F;
    }
  }

  std::string keys_to_pass_[ELEMENTS_TO_PASS];
  std::string vals_to_pass_[ELEMENTS_TO_PASS];

  for (int i = 0; i < ELEMENTS_TO_PASS; i++) {
    keys_to_pass_[i] = std::to_string(rand());
    vals_to_pass_[i] = std::to_string(rand());
  }

  hash_map<std::string, std::string> hash_table_;
  
  for (int i = 0; i < ELEMENTS_TO_PASS; i++) {
    hash_table_.insert(keys_to_pass_[i], vals_to_pass_[i]);
  }

  int retval = 0;
  for (int i = 0; i < ELEMENTS_TO_PASS; i++) {
    if (hash_table_[keys_to_pass_[i]] != vals_to_pass_[i]) {
      retval = 1;
      break;
    }
  }

  if (argc == 2) {
    if (retval) {
      std::cout << "Insertion test was failed. Some of the inserted pairs were lost/corrupted;" << std::endl;
    } else {
      std::cout << "Insertion test was executed with a success. None of the inserted pairs were lost/corrupted;" << std::endl;
    }
    std::cout << "Insertion test is completed;" << std::endl;
  }

  return retval;
}
