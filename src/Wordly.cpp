#include "Wordly.hpp"
#include "UIHelper.hpp"

namespace wordly {

Wordly::Wordly(Dictionary dict)
    : m_Dict{ std::move(dict) } {
  resetGameState();
}

void Wordly::resetGameState() {
  m_TriesCount = 0;
  m_TargetWord = m_Dict.getRandomWord();
  for (char ch : m_TargetWord) {
    m_TargetWordMap[ch]++;
  }
}

void Wordly::startGameLoop() {
  UIHelper::printCheckResult("");
}

auto Wordly::check(const std::string& attempt) const -> CheckResult {
  CheckResult result(attempt.size(), LetterResult::Undefined);
  auto mapCopy{ m_TargetWordMap };

  for (auto [i, ch] : std::views::enumerate(attempt)) {
    if (i < m_TargetWord.size() && ch == m_TargetWord[i]) {
      result[i] = LetterResult::Correct;
      mapCopy[ch]--;
    }
  }

  for (auto [i, ch] : std::views::enumerate(attempt)) {
    if (result[i] != LetterResult::Correct && mapCopy[ch] > 0) {
      result[i] = LetterResult::Misplaced;
      mapCopy[ch]--;
    }
  }

  for (auto& el : result) {
    if (el == LetterResult::Undefined) {
      el = LetterResult::Misplaced;
    }
  }

  return result;
}

} // namespace wordly
