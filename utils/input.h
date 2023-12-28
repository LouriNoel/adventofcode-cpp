#pragma once

#include <string>
#include <vector>

namespace aoc {
	/// <summary>
	/// Wrapper around std::isdigit because it should not be used directly on a string,
	/// without first converting its elements to unsigned char.
	/// See https://en.cppreference.com/w/cpp/string/byte/isdigit#Notes
	/// </summary>
	inline bool isdigit(unsigned char c) {
		return std::isdigit(c);
	}

	void getlines(std::istream& src, std::vector<std::string>& dest);

	void digits(const std::string& src, std::vector<int>& dest);
}
