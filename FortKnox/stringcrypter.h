#pragma once

template<typename T, size_t N>
struct encrypted {
    T data[N];
};

template<size_t N>
constexpr auto crypt(const char(&input)[N]) {
    encrypted<char, N> blob{};
    for (uint32_t index{ 0 }; index < N; index++) {
        blob.data[index] = input[index] ^ 'A';
    }
    return blob;
}

template<size_t N>
constexpr auto crypt2(const char(&input)[N]) {
    encrypted<char, N> blob{};
    for (uint32_t index{ 0 }; index < N; index++) {
        blob.data[index] = input[index] ^ 'G';
    }
    return blob;
}

template<size_t N>
constexpr auto crypt3(const char(&input)[N]) {
    encrypted<char, N> blob{};
    for (uint32_t index{ 0 }; index < N; index++) {
        blob.data[index] = input[index] ^ 'X';
    }
    return blob;
}


#define make_string(STRING) ([&] {            \
    constexpr auto _{ crypt(STRING) };        \
    return std::string{ crypt(_.data).data }; \
}())

#define make_string2(STRING) ([&] {            \
    constexpr auto _{ crypt2(STRING) };        \
    return std::string{ crypt2(_.data).data }; \
}())

#define make_string3(STRING) ([&] {            \
    constexpr auto _{ crypt3(STRING) };        \
    return std::string{ crypt3(_.data).data }; \
}())
