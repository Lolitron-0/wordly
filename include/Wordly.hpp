#pragma once
#include "Dictionary.hpp"
#include <iostream>
#include <ranges>
#include <unordered_map>

namespace wordly {

class Wordly {
public:
  explicit Wordly(Dictionary dict);

  void newGame();

  auto check(const std::string& attempt) -> std::string;

private:
  Dictionary m_Dict;
  std::string m_TargetWord;
  std::unordered_map<char, int> m_TargetWordMap;
  int m_TriesCount;
};

} // namespace wordly
