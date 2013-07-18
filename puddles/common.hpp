#pragma once

template <typename T>
using Matrix = std::vector<std::vector<T> >;

template <typename T1, typename T2>
using Points = std::vector<std::tuple<T1, T2, T2> >;
