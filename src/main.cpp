#include "Wordly.hpp"
#include <iostream>


auto main() -> int {
	wordly::Dictionary dict{"dict"};
	wordly::Wordly wordly{std::move(dict)};
  return 0;
}
