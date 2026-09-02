#include "TestHarness.hpp"

#include <iostream>

int main() {
  const auto& test_cases = snake::testing::get_registered_tests();
  int passed = 0;
  int failed = 0;

  std::cout << "Running " << test_cases.size() << " test cases...\n";

  for (const auto& test : test_cases) {
    std::cout << "[ RUN      ] " << test.name << "\n";
    try {
      test.func();
      std::cout << "[       OK ] " << test.name << "\n";
      ++passed;
    } catch (const snake::testing::TestFailure& e) {
      std::cerr << "[  FAILED  ] " << test.name << "\n"
                << "  " << e.location().file_name() << ":"
                << e.location().line() << " - " << e.what() << "\n";
      ++failed;
    } catch (const std::exception& e) {
      std::cerr << "[  FAILED  ] " << test.name << "\n"
                << "  Unexpected exception: " << e.what() << "\n";
      ++failed;
    } catch (...) {
      std::cerr << "[  FAILED  ] " << test.name << "\n"
                << "  Unknown exception thrown\n";
      ++failed;
    }
  }

  std::cout << "\n========================================\n";
  std::cout << "Total: " << test_cases.size()
            << " | Passed: " << passed
            << " | Failed: " << failed << "\n";
  std::cout << "========================================\n";

  return failed == 0 ? 0 : 1;
}
