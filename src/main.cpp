#include "Wordly.hpp"
#include <iostream>


auto main() -> int {
	wordly::Dictionary dict{"dict"};
	wordly::Wordly wordly{std::move(dict)};
	wordly.newGame();
	std::cout << wordly.check("abcdefg") << std::endl;
  return 0;
}
