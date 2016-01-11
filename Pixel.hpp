#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <GL/glew.h>

class Pixel
{
	public:
		GLint x;
		GLint y;
		Pixel(GLint x_value, GLint y_value):x(x_value), y(y_value){};
		Pixel(const Pixel& p): x(p.x), y(p.y){};
	
		Pixel operator+(const Pixel& p)
		{
			this->x += p.x;
			this->y += p.y;
			return *this;
		}

		Pixel operator-(const Pixel& p)
		{
			this->x -= p.x;
			this->y -= p.y;
			return *this;
		}
		
		Pixel operator*(const GLint& c)
		{
			this->x *= c;
			this->y *= c;
			return *this;
		} 
		
//	friend Pixel operator*(const Pixel& p, const GLint& c)
//		{
//			return p * c;
//		}
};

#endif
