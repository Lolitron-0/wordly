#pragma once
#include "Dictionary.hpp"
#include <iostream>
#include <ranges>
#include <unordered_map>

namespace wordly {

enum class LetterResult {
	Undefined=-1,
	NoSuch,
	Misplaced,
	Correct
};

class Wordly {
public:
	using CheckResult = std::vector<LetterResult>;

  explicit Wordly(Dictionary dict);

  void resetGameState();

  void startGameLoop();

private:
  auto check(const std::string& attempt) const -> CheckResult;

  Dictionary m_Dict;
  std::string m_TargetWord;
  std::unordered_map<char, int> m_TargetWordMap;
  int m_TriesCount{ 0 };
};

} // namespace wordly
