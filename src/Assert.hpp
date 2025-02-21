// Define NDEBUG flag in compilation step: `clang++ -DNDEBUG`
#pragma once

#include <format>
#include <iostream>
#include <source_location>
#include <string_view>

#ifndef DEBUG
    #ifdef NDEBUG
        #define DEBUG false
    #else
        #define DEBUG true
    #endif
#endif

#ifndef DEBUG_BREAK
    #if DEBUG == true
        #if defined(_MSC_VER)
            #define DEBUG_BREAK() __debugbreak()
        #elif defined(__clang__)
            #define DEBUG_BREAK() __builtin_debugtrap()
        #elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
            #define DEBUG_BREAK() __asm__ volatile("int $0x03")
        #else
            #define DEBUG_BREAK() assert(false)
        #endif
    #else
        #define DEBUG_BREAK() ((void)0)
    #endif
#endif

#if DEBUG == true
    // Reports debug info and enter debug mode befor terminate the program.
    #define ASSERT_FATAL(expr, ...)                                                                \
        if (!(expr)) {                                                                             \
            ::Assert::handle_assert(#expr, std::source_location::current(), ::Assert::Color::RED,  \
                                    ##__VA_ARGS__);                                                \
            DEBUG_BREAK();                                                                         \
            std::abort();                                                                          \
        }

    // Reports debug info and enter debug mode. Returns the expresion result.
    #define ASSERT(expr, ...)                                                                      \
        ([&]() {                                                                                   \
            if (!(expr)) {                                                                         \
                ::Assert::handle_assert(#expr, std::source_location::current(),                    \
                                        ::Assert::Color::YELLOW, ##__VA_ARGS__);                   \
            }                                                                                      \
            return (expr);                                                                         \
        })()
#else
    #define ASSERT_FATAL(expr, ...) (!(expr)) ? std::abort() : ((void)0)
    #define ASSERT(expr, ...) ((bool)expr)
#endif

namespace Assert {
// Light color codes for terminal text formatting
namespace Color {
    inline static constexpr std::string_view RESET = "\033[0m";
    inline static constexpr std::string_view BOLD = "\033[1m";
    inline static constexpr std::string_view RED = "\033[31m";
    inline static constexpr std::string_view GREEN = "\033[32m";
    inline static constexpr std::string_view YELLOW = "\033[33m";
    inline static constexpr std::string_view BLUE = "\033[34m";
    inline static constexpr std::string_view MAGENTA = "\033[35m";
    inline static constexpr std::string_view CYAN = "\033[36m";
    inline static constexpr std::string_view WHITE = "\033[37m";
    inline static constexpr std::string_view BRIGHT_RED = "\033[91m";
    inline static constexpr std::string_view BRIGHT_GREEN = "\033[92m";
    inline static constexpr std::string_view BRIGHT_YELLOW = "\033[93m";
    inline static constexpr std::string_view BRIGHT_BLUE = "\033[94m";
    inline static constexpr std::string_view BRIGHT_MAGENTA = "\033[95m";
    inline static constexpr std::string_view BRIGHT_CYAN = "\033[96m";
    inline static constexpr std::string_view BRIGHT_WHITE = "\033[97m";
} // namespace Color

void handle_assert(std::string_view expr, std::source_location loc, std::string_view color = "",
                   std::string_view diagnostic_msg = "", auto&&... args) {
    // [file.cpp:99] Failed assertion -> `false == true`
    //     └-> some formated msg: 1
    static constexpr std::string_view msg { "{}[{}:{}] Failed assertion: `{}`" };
    std::cerr << std::format(msg, color, loc.file_name(), loc.line(), expr);

    if (!diagnostic_msg.empty()) {
        std::cerr << "\n    └-> ";
        if constexpr (sizeof...(args) > 0) {
            std::cerr << std::vformat(diagnostic_msg, std::make_format_args(args...));
        }
        else {
            std::cerr << diagnostic_msg;
        }
    }
    std::cerr << Assert::Color::RESET << "\n";
}

} // namespace Assert
