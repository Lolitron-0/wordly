#include "UIHelper.hpp"
#include <iostream>
#include <map>
#include <ranges>
#include <sstream>
#define OOF_IMPL
#include <oof/oof.h>

namespace wordly {

static constexpr oof::color inputColor{ 52, 55, 235 };
static constexpr oof::color historyColor{ 52, 235, 232 };
static constexpr oof::color errorColor{ 240, 20, 20 };
static constexpr oof::color neutralColor{ 120, 120, 120 };
static constexpr oof::color warnColor{ 252, 115, 3 };
static constexpr oof::color successColor{ 3, 252, 80 };

UIHelper::UIHelper(int maxHistory)
    : m_MaxHistorySize{ maxHistory } {
}

void UIHelper::clearScreen() const {
  std::cout << oof::clear_screen();
}

void UIHelper::pushCheckResult(const std::string& attempt,
                               const CheckResult& checkResult) {
  static const std::map<LetterResult, oof::color> resultColorMap{
    { LetterResult::Undefined, oof::color{ 255, 0, 0 } },
    { LetterResult::NoSuch, neutralColor },
    { LetterResult::Misplaced, warnColor },
    { LetterResult::Correct, successColor },
  };

  std::stringstream ss;
  for (auto [ch, result] :
       std::ranges::views::zip(attempt, checkResult)) {
    ss << oof::fg_color(oof::color{ 255, 255, 255 })
       << oof::bg_color(resultColorMap.at(result)) << ch
       << oof::reset_formatting();
  }

  std::string str{ ss.str() };
  std::cout << str << std::endl;

  m_AttemptsHistory.push_back(str);
}

void UIHelper::printAttemptHistory() {
  for (const auto& entry : m_AttemptsHistory) {
    std::cout << oof::fg_color(historyColor) << "] "
              << oof::reset_formatting() << entry << std::endl;
  }

  for (int i{ 0 };
       i < m_MaxHistorySize - static_cast<int>(m_AttemptsHistory.size());
       i++) {
    std::cout << oof::fg_color(historyColor) << "] "
              << oof::reset_formatting() << std::endl;
  }
}

void UIHelper::printWin() const {
  std::cout << oof::fg_color(successColor) << "YOU WON!"
            << oof::reset_sequence() << std::endl
            << "Thanks for playing!" << std::endl;
}

void UIHelper::printLoss() const {
  std::cout << oof::fg_color(errorColor) << "YOU LOST!"
            << oof::reset_sequence() << std::endl
            << "Better luck next time!" << std::endl;
}

auto UIHelper::inputString(std::size_t expectedSymbols) -> std::string {
  std::string inp;
  while (true) {
    std::cout << oof::fg_color(inputColor) << "> "
              << oof::reset_formatting()
              << std::string(expectedSymbols, '_') << '\r';
    std::cout << oof::fg_color(inputColor) << "> "
              << oof::reset_formatting();
    std::cin >> inp;
    std::cout << std::endl;

    if (inp.size() == expectedSymbols) {
      return inp;
    }

    std::cout << oof::fg_color(errorColor)
              << std::format("Expected {} character word",
                             expectedSymbols)
              << oof::reset_formatting() << std::endl;
  }
}
} // namespace wordly
