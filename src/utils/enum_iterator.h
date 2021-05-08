
#pragma once

#include <iterator>

template<class E>
struct EnumIterator : std::iterator <std::input_iterator_tag, E>
{
private:
	int value;
	int step;
	typedef EnumIterator<E> iterator;
public:
	explicit EnumIterator(E value, int step = 1) : value { value }, step { step } { }

	iterator& operator++() { ++value; return *this; }
	iterator operator++(int) { iterator copy = *this; ++(*this); return copy; }
	bool operator==(iterator other) { return value == other.value; }
	bool operator!=(iterator other) { return !(*this == other); }
	E operator*() const { return E(value); }
};

#define MAKE_ENUM_ITERATOR(T, E, START, END) \
struct T \
{ \
	typedef EnumIterator<E> iterator; \
	iterator begin() { return iterator(START); } \
	iterator end() { return iterator(END); } \
};
