#pragma once

#include <vector>


class Color  {
public:
	Color(float r, float g, float b, float alpha) :
			r(r), g(g), b(b), alph(alpha), size(4){};
	Color(float r, float g, float b) :
			r(r), g(g), b(b), alph(1), size(3) {};

	std::vector<float> getData()const {
		if (size == 4) return { r, g, b, alph };
		else if (size == 3) return { r, g, b };
		else return {};
	}
private:
	float r{}, g{}, b{}, alph{};
	int size{};
};
