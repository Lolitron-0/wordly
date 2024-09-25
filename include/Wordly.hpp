#pragma once
#include "CheckResult.hpp"
#include "Dictionary.hpp"
#include "SessionOptions.hpp"
#include "UIHelper.hpp"
#include <iostream>
#include <ranges>
#include <unordered_map>

namespace wordly {

class Wordly {
public:
  explicit Wordly(const SessionOptions& opts);

  void resetGameState();

  void startGameLoop();

private:
  auto check(const std::string& attempt) const -> CheckResult;
  auto checkWin(const CheckResult& res) -> bool;

  UIHelper m_UIHelper;
  std::shared_ptr<Dictionary> m_Dict;
  std::string m_TargetWord;
  std::unordered_map<char, int> m_TargetWordMap;
  std::size_t m_AttemptsLeft;
  std::size_t m_MaxAttempts;
};

} // namespace wordly
