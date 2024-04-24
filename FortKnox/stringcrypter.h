#pragma once

#include <string>

template<typename T, size_t N>
struct encrypted {
    T data[N];
};

template<size_t N, char Key>
constexpr auto crypt(const char(&input)[N]) {
    encrypted<char, N> blob{};
    for (uint32_t index{ 0 }; index < N; index++) {
        blob.data[index] = input[index] ^ Key;
    }
    return blob;
}

#define make_string(STRING, KEY) ([&] {              \
    constexpr auto _{ crypt<sizeof(STRING), KEY>(STRING) };    \
    return std::string{ crypt<sizeof(STRING), KEY>(_.data).data }; \
}())
