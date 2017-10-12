#ifndef COLOR_HPP
#define COLOR_HPP
#include <cmath>
#include <GL/glew.h>

class Color
{
	public:
		GLint red;
		GLint green;
		GLint blue;

		Color();
		Color(GLint r, GLint g, GLint b);
		Color(const Color& c);
		
		Color operator*(const GLint& c);
		Color operator*(const GLfloat& c);
		Color operator+(const Color& c);
		Color operator-(const Color& c);
		Color operator/(const GLint& c);
//	friend Color operator*(const Color& p, const GLint& c)
//		{
//			return p * c;
//		}
};

#endif
