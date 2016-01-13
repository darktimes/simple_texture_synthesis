#include "Pixel.hpp"

Pixel::Pixel(GLint x_value, GLint y_value):x(x_value), y(y_value){}

Pixel::Pixel(const Pixel& p): x(p.x), y(p.y){}
	
Pixel Pixel::operator+(const Pixel& p)
{
	this->x += p.x;
	this->y += p.y;
	return *this;
}

Pixel Pixel::operator-(const Pixel& p)
{
	this->x -= p.x;
	this->y -= p.y;
	return *this;
}
		
Pixel Pixel::operator*(const GLint& c)
{
	this->x *= c;
	this->y *= c;
	return *this;
} 
		
