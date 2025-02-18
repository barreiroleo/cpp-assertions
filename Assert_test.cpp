#include "Assert.hpp"

int main(int argc, char* argv[]) {
    // RUN_TEST  ASSERT_FATAL(true == true);
    // RUN_TEST  ASSERT_FATAL(false == true);
    // RUN_TEST  ASSERT_FATAL(false == true, "Always crash: No msg.");
    // RUN_TEST  ASSERT_FATAL(false == true, "Always crash: {} {}.", "Something", 10);

    auto test_assert_ok = []() {
        if (ASSERT(true == true, "This won't fail")) {
            auto loc { std::source_location::current() };
            std::cout << std::format("{}This is an expression-like assertion: {}:{}{}\n",
                                     Assert::Color::GREEN, loc.file_name(), loc.line(),
                                     Assert::Color::RESET);
        }
    };
    // RUN_TEST test_assert_ok();

    auto test_assert_fail = []() {
        if (!ASSERT(false == true, "This will fail: {}", 1)) {
            auto loc { std::source_location::current() };
            std::cout << std::format("{}This is an expression-like assertion: {}:{}{}\n",
                                     Assert::Color::GREEN, loc.file_name(), loc.line(),
                                     Assert::Color::RESET);
        }
    };
    // RUN_TEST test_assert_fail();

    auto test_debug_break = []() {
        DEBUG_BREAK();
        std::cout << "Hey, I break the execution";
    };
    // RUN_TEST test_debug_break();

    return 0;
}
