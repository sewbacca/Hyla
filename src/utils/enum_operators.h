
#pragma once

#define ENABLE_BITWISE_OPERATORS(E) \
constexpr E operator&(E a, E b) { return E(int(a) & int(b)); } \
constexpr E operator|(E a, E b) { return E(int(a) | int(b)); } \
constexpr E operator^(E a, E b) { return E(int(a) ^ int(b)); } \
constexpr E& operator&=(E& container, E other) { return container = E(container & other); } \
constexpr E& operator|=(E& container, E other) { return container = E(container | other); } \
constexpr E& operator^=(E& container, E other) { return container = E(container ^ other); }

#define ENABLE_CREMENT_OPERATORS(E) \
constexpr E& operator++(E& value) { return value = E(int(value) + 1); } \
constexpr E& operator--(E& value) { return value = E(int(value) - 1); } \
constexpr E operator++(E& value, int) { E container(value); ++value; return container; } \
constexpr E operator--(E& value, int) { E container(value); --value; return container; }

#define ENABLE_BASIC_OPERATORS(E) \
constexpr E operator+(E a, int b) { return E(int(a) + int(b)); } \
constexpr E operator+(int a, E b) { return E(int(a) + int(b)); } \
constexpr E operator-(E a, int b) { return E(int(a) - int(b)); } \
constexpr E operator-(int a, E b) { return E(int(a) - int(b)); } \
constexpr E& operator+=(E& container, int other) { return container = E(int(container) + other); } \
constexpr E& operator-=(E& container, int other) { return container = E(int(container) - other); }
