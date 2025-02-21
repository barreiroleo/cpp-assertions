#include <Assert.hpp>

#define EXIT_TESTS_FINISH 3

void inspect_args(int argc, char* argv[]) {
    std::cout << std::format("argc = {}", argc) << "\n";
    for (size_t i {}; i < argc; ++i) {
        std::cout << std::format("- argv[{}] = {}", i, argv[i]) << "\n";
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
        std::cout << std::format(R"( ASSERT_FATAL(true == true); )") << "\n";
        ASSERT_FATAL(true == true);
        break;

    case 1:
        std::cout << std::format(R"( ASSERT_FATAL(false == true); )") << "\n";
        ASSERT_FATAL(false == true);
        break;

    case 2:
        std::cout << std::format(R"( ASSERT_FATAL(false == true, "Always crash: No msg."); )") << "\n";
        ASSERT_FATAL(false == true, "Always crash: No msg.");
        break;

    case 3:
        std::cout << std::format(
            R"( ASSERT_FATAL(false == true, "Always crash: {{}} {{}}.", "Something", 10); )") << "\n";
        ASSERT_FATAL(false == true, "Always crash: {} {}.", "Something", 10);
        break;

    case 4:
        std::cout << std::format(R"( if (ASSERT(true == true, "This won't fail")) {{ )") << "\n";
        if (ASSERT(true == true, "This won't fail")) {
            auto loc { std::source_location::current() };
            std::cout << std::format("{}This is an expression-like assertion: {}:{}{}", Assert::Color::GREEN,
                         loc.file_name(), loc.line(), Assert::Color::RESET) << "\n";
        }
        break;

    case 5:
        std::cout << std::format(R"( if (!ASSERT(false == true, "This will fail: {{}}", 1)) {{ )") << "\n";
        if (!ASSERT(false == true, "This will fail: {}", 1)) {
            auto loc { std::source_location::current() };
            std::cout << std::format("{}This is an expression-like assertion: {}:{}{}", Assert::Color::GREEN,
                         loc.file_name(), loc.line(), Assert::Color::RESET) << "\n";
        }
        break;

    case 6:
        std::cout << std::format(R"( DEBUG_BREAK(); )") << "\n";
        DEBUG_BREAK();
        std::cout << std::format("Hey, I break the execution") << "\n";
        break;

    default:
        std::cout << std::format("{}All tests completed{}", Assert::Color::GREEN, Assert::Color::RESET) << "\n";
        return EXIT_TESTS_FINISH;
    }
}
