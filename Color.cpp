#include "Color.hpp"

Color::Color(): red(0), green(0), blue(0){}

Color::Color(GLint r, GLint g, GLint b):red(r), green(g), blue(b){}

Color::Color(const Color& c): red(c.red), green(c.green), blue(c.blue){}
		
Color Color::operator*(const GLint& c)
{
	this->red *= c;
	this->green *= c;
	this->blue *= c;
	return *this;
}
	
Color Color::operator*(const GLfloat& c)
{
	this->red = (GLint)(round((GLfloat)red * c));
	this->green = (GLint)(round((GLfloat)green * c));
	this->blue = (GLint)(round((GLfloat)blue * c));
	return *this;
}

Color Color::operator+(const Color& c)
{
	this->red += c.red;
	this->green += c.green;
	this->blue += c.blue;
	return *this;
}

Color Color::operator-(const Color& c)
{
	this->red -= c.red;
	this->green -= c.green;
	this->blue -= c.blue;
	return *this;
}

		
Color Color::operator/(const GLint& c)
{
	this->red /= c;
	this->green /= c;
	this->blue /= c;
	return *this;
}
