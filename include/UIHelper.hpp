#pragma once
#include "CheckResult.hpp"
#include "SessionOptions.hpp"
#include <string>

namespace wordly {

class UIHelper {
public:
  explicit UIHelper(int maxHistory);

  void clearScreen() const;

  void pushCheckResult(const std::string& attempt,
                       const CheckResult& checkResult);
  void printAttemptHistory();
  auto inputString(std::size_t expectedSymbols) -> std::string;

  void printWin() const;
  void printLoss() const;

private:
  int m_MaxHistorySize;
  std::vector<std::string> m_AttemptsHistory;
};

} // namespace wordly
