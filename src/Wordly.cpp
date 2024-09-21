#include "Wordly.hpp"

namespace wordly {

Wordly::Wordly(Dictionary dict)
    : m_Dict{ std::move(dict) } {
}

void Wordly::newGame() {
  m_TriesCount = 0;
  m_TargetWord = m_Dict.getRandomWord();
  for (char ch : m_TargetWord) {
    m_TargetWordMap[ch]++;
  }
}

auto Wordly::check(const std::string& attempt) -> std::string {
  std::string result(attempt.size(), '*');
  auto mapCopy{ m_TargetWordMap };

  for (auto [i, ch] : std::views::enumerate(attempt)) {
    if (i < m_TargetWord.size() && ch == m_TargetWord[i]) {
      result[i] = 'X';
      mapCopy[ch]--;
    }
  }

  for (auto [i, ch] : std::views::enumerate(attempt)) {
    if (result[i] != 'X' && mapCopy[ch] > 0) {
      result[i] = '+';
      mapCopy[ch]--;
    }
  }
  return result;
}

} // namespace wordly
