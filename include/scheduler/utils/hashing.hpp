#pragma once

namespace specops {

template <typename T>
constexpr T cantorHashing(T a, T b) noexcept {
    return ((a+b)/2)*(a+b+1)+b;
}

template <typename T, typename... Args>
constexpr T cantorHashing(T a, T b, Args... args) noexcept {
    return cantorHashing(a, cantorHashing(b, args...));
}

}
