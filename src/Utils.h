#ifndef MPV2D_UTILS_H_
#define MPV2D_UTILS_H_

#include <string>
#include <sstream>
#include <stdexcept>

namespace util
{
	template <typename T>
	std::string toString(T in)
	{
		std::stringstream ss;

		ss << in;
		return ss.str();
	}

	template <typename T>
	T hexCharTo(char in)
	{
		std::stringstream ss;
		T out;

		ss << std::hex << in;
		ss >> out;

		return out;
	}

	template <typename T>
	T hexStrTo(const std::string& in, unsigned int beginPos = 0, unsigned int endPos = in.size())
	{
		if (beginPos > endPos || beginPos > in.size() || endPos > in.size())
		{
			throw std::runtime_error("hexStrto begin/end invalid values");
		}

		std::stringstream ss;
		std::string input(in.substr(0 + beginPos, 0 + endPos));
		T out;

		ss << std::hex << input;
		ss >> out;

		return out;
	}
}

#endif
