#pragma once
#include <cstdint>
#include <vector>

namespace wordly {

enum class LetterResult : int8_t {
  Undefined = -1,
  NoSuch,
  Misplaced,
  Correct
};

using CheckResult = std::vector<LetterResult>;

} // namespace wordly
