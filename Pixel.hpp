#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <GL/glew.h>

class Pixel
{
	public:
		GLint x;
		GLint y;
		Pixel(GLint x_value, GLint y_value);
		Pixel(const Pixel& p);
	
		Pixel operator+(const Pixel& p);
		Pixel operator-(const Pixel& p);
		Pixel operator*(const GLint& c);
//	friend Pixel operator*(const Pixel& p, const GLint& c)
//		{
//			return p * c;
//		}
};

#endif
