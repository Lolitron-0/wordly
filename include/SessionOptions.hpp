#pragma once
#include <memory>
#include <string>

namespace wordly {

class Dictionary;

struct SessionOptions {
  std::string dictPath{ "default.dict" };
  std::size_t numAttempts{ 0 };
	std::shared_ptr<Dictionary> dictionary;
};

} // namespace wordly
