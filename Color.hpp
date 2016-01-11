#ifndef COLOR_HPP
#define COLOR_HPP

#include <cmath>

class Color
{
	public:
		GLint red;
		GLint green;
		GLint blue;

		Color(): red(0), green(0), blue(0){};
		Color(GLint r, GLint g, GLint b):red(r), green(g), blue(b){};
		Color(const Color& c): red(c.red), green(c.green), blue(c.blue){};
		
		Color operator*(const GLint& c)
		{
			this->red *= c;
			this->green *= c;
			this->blue *= c;
			return *this;
		}
		
		Color operator*(const GLfloat& c)
		{
			this->red = (GLint)(round((GLfloat)red * c));
			this->green = (GLint)(round((GLfloat)green * c));
			this->blue = (GLint)(round((GLfloat)blue * c));
			return *this;
		}
		
		Color operator+(const Color& c)
		{
			this->red += c.red;
			this->green += c.green;
			this->blue += c.blue;
			return *this;
		}
		
		Color operator-(const Color& c)
		{
			this->red -= c.red;
			this->green -= c.green;
			this->blue -= c.blue;
			return *this;
		}

		
		Color operator/(const GLint& c)
		{
			this->red /= c;
			this->green /= c;
			this->blue /= c;
			return *this;
		}
		
//	friend Color operator*(const Color& p, const GLint& c)
//		{
//			return p * c;
//		}
};

#endif
