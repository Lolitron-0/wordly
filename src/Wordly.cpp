#include "Wordly.hpp"
#include "UIHelper.hpp"

namespace wordly {

Wordly::Wordly(const SessionOptions& opts)
    : m_UIHelper{ static_cast<int>(opts.numAttempts) },
      m_Dict{ opts.dictionary },
      m_AttemptsLeft{ opts.numAttempts },
      m_MaxAttempts{ opts.numAttempts } {
  resetGameState();
}

void Wordly::resetGameState() {
  m_AttemptsLeft = m_MaxAttempts;
  m_TargetWord   = m_Dict->getRandomWord();
  for (char ch : m_TargetWord) {
    m_TargetWordMap[ch]++;
  }
}

void Wordly::startGameLoop() {
  while (true) {
    m_UIHelper.clearScreen();

    m_UIHelper.printAttemptHistory();
    std::cout << "> " << m_TargetWord << std::endl;
    auto attempt{ m_UIHelper.inputString(m_TargetWord.size()) };
    auto checkResult{ check(attempt) };
    m_AttemptsLeft--;
    m_UIHelper.pushCheckResult(attempt, checkResult);

    if (checkWin(checkResult)) {
      m_UIHelper.clearScreen();
      m_UIHelper.pushCheckResult(attempt, checkResult);
      m_UIHelper.printWin();
      return;
    }

    if (m_AttemptsLeft <= 0) {
      m_UIHelper.clearScreen();
      std::cout << m_TargetWord << std::endl;
      m_UIHelper.printLoss();
      return;
    }
  }
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
      el = LetterResult::NoSuch;
    }
  }

  return result;
}

auto Wordly::checkWin(const CheckResult& res) -> bool {
  return std::all_of(res.begin(), res.end(), [](auto&& el) {
    return el == LetterResult::Correct;
  });
}

} // namespace wordly
