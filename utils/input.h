#pragma once

#include <string>
#include <tuple>
#include <unordered_set>
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

	std::tuple<std::string::size_type, std::string> find_first_substr_of(const std::string_view& src, const std::unordered_set<std::string>& candidates);
	std::tuple<std::string::size_type, std::string> find_last_substr_of(const std::string_view& src, const std::unordered_set<std::string>& candidates);
}
