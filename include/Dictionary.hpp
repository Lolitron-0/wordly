#pragma once
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace wordly {

class NoSuchDictFile : public std::runtime_error {
public:
  NoSuchDictFile();
};

class Dictionary {
public:
  explicit Dictionary(const std::string& filePath);

  [[nodiscard]] auto getRandomWord() const -> std::string;

private:
  std::vector<std::string> m_Words;
  std::unique_ptr<std::mt19937_64> m_RandEngine;
};

} // namespace wordly
