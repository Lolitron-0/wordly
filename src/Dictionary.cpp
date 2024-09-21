#include "Dictionary.hpp"
#include <fstream>
#include <regex>
#include <sstream>

namespace wordly {

NoSuchDictFile::NoSuchDictFile()
    : std::runtime_error{ "No such dictionary file" } {
}

Dictionary::Dictionary(const std::string& filePath) {
  std::ifstream file{ filePath };
  if (!file.is_open()) {
    throw NoSuchDictFile{};
  }

  std::ostringstream stream;
  stream << file.rdbuf();
  std::string content{ stream.str() };

  std::regex separator{ "(\\w+)" };
  std::sregex_iterator wordsIt{ content.begin(), content.end(),
                                separator };
  std::sregex_iterator wordsEnd{};
  for (; wordsIt != wordsEnd; wordsIt++) {
    m_Words.push_back(wordsIt->str());
  }

  std::random_device rd;
  m_RandEngine = std::make_unique<std::mt19937_64>(rd());
}

auto Dictionary::getRandomWord() const -> std::string {
  std::uniform_int_distribution<size_t> dist{ 0, m_Words.size() - 1 };
  return m_Words.at(dist(*m_RandEngine));
}
} // namespace wordly
