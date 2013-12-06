#ifndef MPV2D_UTILS_H_
#define MPV2D_UTILS_H_

template <typename T>
std::string toString(T in)
{
	std::stringstream ss;

	ss << in;
	return ss.str();
}

template <typename T>
T charTo(char in)
{
	std::stringstream ss;
	T out;

	ss << in;
	ss >> out;

	return out;
}

#endif
