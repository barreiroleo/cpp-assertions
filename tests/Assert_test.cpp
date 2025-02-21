#include "Assert.hpp"
#include <iostream>
#include <print>

#define EXIT_TESTS_FINISH 3

void inspect_args(int argc, char* argv[]) {
    std::println("argc = {}", argc);
    for (size_t i {}; i < argc; ++i) {
        std::println("- argv[{}] = {}", i, argv[i]);
    }
}

int parse_test_case(int argc, char* argv[]) {
    int test_number {};
    if (std::string_view arg = argv[1]; arg == "--test") {
        try {
            test_number = std::atoi(argv[2]);
        }
        catch (const std::exception& e) {
            std::cerr << e.what();
            std::abort();
        }
    }
    return test_number;
}

int main(int argc, char* argv[]) {
    // inspect_args(argc, argv);
    int test_number = parse_test_case(argc, argv);

    switch (test_number) {
    case 0:
        std::println(R"( ASSERT_FATAL(true == true); )");
        ASSERT_FATAL(true == true);
        break;

    case 1:
        std::println(R"( ASSERT_FATAL(false == true); )");
        ASSERT_FATAL(false == true);
        break;

    case 2:
        std::println(R"( ASSERT_FATAL(false == true, "Always crash: No msg."); )");
        ASSERT_FATAL(false == true, "Always crash: No msg.");
        break;

    case 3:
        std::println(
            R"( ASSERT_FATAL(false == true, "Always crash: {{}} {{}}.", "Something", 10); )");
        ASSERT_FATAL(false == true, "Always crash: {} {}.", "Something", 10);
        break;

    case 4:
        std::println(R"( if (ASSERT(true == true, "This won't fail")) {{ )");
        if (ASSERT(true == true, "This won't fail")) {
            auto loc { std::source_location::current() };
            std::println("{}This is an expression-like assertion: {}:{}{}", Assert::Color::GREEN,
                         loc.file_name(), loc.line(), Assert::Color::RESET);
        }
        break;

    case 5:
        std::println(R"( if (!ASSERT(false == true, "This will fail: {{}}", 1)) {{ )");
        if (!ASSERT(false == true, "This will fail: {}", 1)) {
            auto loc { std::source_location::current() };
            std::println("{}This is an expression-like assertion: {}:{}{}", Assert::Color::GREEN,
                         loc.file_name(), loc.line(), Assert::Color::RESET);
        }
        break;

    case 6:
        std::println(R"( DEBUG_BREAK(); )");
        DEBUG_BREAK();
        std::println("Hey, I break the execution");
        break;

    default:
        std::println("{}All tests completed{}", Assert::Color::GREEN, Assert::Color::RESET);
        return EXIT_TESTS_FINISH;
    }
}
