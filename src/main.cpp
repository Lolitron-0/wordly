#include "SessionOptions.hpp"
#include "Wordly.hpp"
#include <cxxopts.hpp>
#include <iostream>

auto main(int argc, char* argv[]) -> int {
  wordly::SessionOptions opts;
  cxxopts::Options cliOpts{ "wordly", "Wordly game in your terminal" };
  // clang-format off
	cliOpts.add_options()
		("help,h", "display help") 
		("dictionary,d", "path to dict file",
		 cxxopts::value<std::string>(opts.dictPath)->default_value(opts.dictPath))
		("num-attempts,n", "number of allowed attempts (0 - infinite)",
		 cxxopts::value<std::size_t>(opts.numAttempts)
		 ->default_value(std::to_string(opts.numAttempts)));
  // clang-format on

  auto cliOptsMap{ cliOpts.parse(argc, argv) };

  if (cliOptsMap.count("help")) {
    std::cout << cliOpts.help() << std::endl;
    return 0;
  }

  try {
    opts.dictionary = std::make_shared<wordly::Dictionary>(opts.dictPath);
  } catch (const wordly::NoSuchDictFile& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  wordly::Wordly wordly{ opts };
  wordly.startGameLoop();
  return 0;
}
