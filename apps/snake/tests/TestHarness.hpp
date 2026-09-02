#pragma once

#include <exception>
#include <functional>
#include <iostream>
#include <source_location>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace snake::testing {

class TestFailure : public std::exception {
public:
  TestFailure(std::string message, std::source_location loc)
      : message_(std::move(message)), loc_(loc) {}

  [[nodiscard]] const char* what() const noexcept override {
    return message_.c_str();
  }

  [[nodiscard]] const std::source_location& location() const noexcept {
    return loc_;
  }

private:
  std::string message_;
  std::source_location loc_;
};

struct TestCase {
  std::string_view name;
  std::function<void()> func;
};

inline std::vector<TestCase>& get_registered_tests() {
  static std::vector<TestCase> tests;
  return tests;
}

struct TestRegistrar {
  TestRegistrar(std::string_view name, std::function<void()> func) {
    get_registered_tests().push_back(TestCase{.name = name, .func = std::move(func)});
  }
};

inline void assert_true_impl(bool condition,
                            std::string_view expression,
                            std::source_location loc = std::source_location::current()) {
  if (!condition) {
    std::ostringstream oss;
    oss << "Assertion failed: (" << expression << ")";
    throw TestFailure(oss.str(), loc);
  }
}

template <typename T, typename U>
inline void assert_eq_impl(const T& actual,
                           const U& expected,
                           std::string_view actual_str,
                           std::string_view expected_str,
                           std::source_location loc = std::source_location::current()) {
  if (!(actual == expected)) {
    std::ostringstream oss;
    oss << "Assertion failed: " << actual_str << " == " << expected_str
        << "\n  Actual:   " << actual
        << "\n  Expected: " << expected;
    throw TestFailure(oss.str(), loc);
  }
}

}  // namespace snake::testing

#define SNAKE_TEST_CONCAT_INNER(a, b) a##b
#define SNAKE_TEST_CONCAT(a, b) SNAKE_TEST_CONCAT_INNER(a, b)

#define TEST_CASE(name)                                                        \
  static void SNAKE_TEST_CONCAT(test_func_, __LINE__)();                       \
  static const ::snake::testing::TestRegistrar SNAKE_TEST_CONCAT(             \
      test_reg_, __LINE__)(name, &SNAKE_TEST_CONCAT(test_func_, __LINE__));   \
  static void SNAKE_TEST_CONCAT(test_func_, __LINE__)()

#define ASSERT_TRUE(expr) ::snake::testing::assert_true_impl((expr), #expr)
#define ASSERT_FALSE(expr) ::snake::testing::assert_true_impl(!(expr), "!(" #expr ")")
#define ASSERT_EQ(actual, expected)                                            \
  ::snake::testing::assert_eq_impl((actual), (expected), #actual, #expected)
