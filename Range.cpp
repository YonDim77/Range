#include "Range.h"
#include <algorithm>


Range::Range() : rangeFirst(0), rangeLength(0), valueCounts(nullptr) {}

bool Range::empty() const {
	return valueCounts == nullptr;
}

void Range::clear() {
	if (!empty()) {
		delete[] valueCounts; 
		valueCounts = nullptr;
		rangeFirst = 0;
		rangeLength = 0;
	}
}

Range::~Range() {
	clear();
}

Range& Range::operator=(const Range& other) {
	clear();
	rangeFirst = other.rangeFirst;
	rangeLength = other.rangeLength;
	valueCounts = copyValues(other);
	return *this;
}

Range::Range(const Range& other) : rangeFirst(0), rangeLength(0), valueCounts(nullptr) {
	*this = other;

}

size_t Range::getCount(T value) const {
	if (rangeFirst <= value && value < (rangeLength + rangeFirst))
		return valueCounts[getIndex(value)];
	else
		return 0;
}

size_t Range::getIndex(T value) const {
	return value - rangeFirst;
}

void Range::add(T value) {
	T first = rangeFirst;
	T last = rangeFirst + rangeLength - 1;

	if (empty()) {
		resize(value, value);
	}
	else if (value < first) {
		resize(value, last);
	}
	else if (value > last) {
		resize(first, value);
	}

	valueCounts[getIndex(value)]++;
}


void Range::resize(T first, T last) {
	T newFirst = first;
	T newLength = last - first + 1;

	size_t* newCounts = new size_t[newLength] { 0 };

	if (!empty()) {
		std::copy(valueCounts, valueCounts + rangeLength, newCounts + (rangeFirst - first));
		clear();
	}

	rangeFirst = newFirst;
	rangeLength = newLength;
	valueCounts = newCounts;

}

/*
10 20 3 4 5 6
6 3 10 3 3 -2
3 4 5 6 1 3
1 5 6 7 2 4
end
3

1 2 3 4 5 6
1 2 3 3 3 6
1 3 3 4 5 6
1 2 4 5 6 7
end
3


*/

