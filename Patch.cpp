#include "Patch.hpp"

Patch::Patch(const std::shared_ptr<Image>& image, const Pixel& p)
{
	x = wrap(p.x, image->getWidth());
	y = wrap(p.y, image->getHeight());
	index = y * image->getWidth() + x + 1;
	content = new unsigned char[36];
		
	for (int i = 0; i < 12; i++)
	{
		Color c = image->getColor(Pixel(wrap(x - cOffSetX(i), image->getWidth()), wrap(y - cOffSetY(i), image->getHeight())));
		content[i * 3]		=	c.red;
		content[i * 3 + 1]	=	c.green;
		content[i * 3 + 2]	=	c.blue;
	}
	center = image->getColor(Pixel(x, y));
}

float Patch::getDifference(const std::shared_ptr<Patch>& other)
{
	GLfloat sum = 0.0f;
	for (int i = 0; i < 12; i++) 
	{
		GLfloat diff = 0.0f;
		diff+= abs(other->getContent()[i * 3] - this->content[i * 3]);
		diff+= abs(other->getContent()[i * 3 + 1] - this->content[i * 3 + 1]);
		diff+= abs(other->getContent()[i * 3 + 2] - this->content[i * 3 + 2]);
		diff *= diff;
//		diff *= calc2DGaussKernel(abs(cOffSetX(i)), abs(cOffSetY(i)), 2);
		sum += diff;
	}
	return sum;
}

Patch::~Patch()
{
	delete[] content;
}

Color Patch::getCenter()
{
	return center;
}

unsigned char* Patch::getContent()
{
	return content;
}

void Patch::setCenter(const Color& c)
{
	center = c;
}

GLint Patch::cOffSetX(const GLint& x)
{
	if (x % 5 == 0) return 2;
	if ((x + 1) % 5 == 0) return -2;
	if ((x - 1) % 5 == 0) return 1;
	if ((x - 3) % 5 == 0) return -1;
	return 0; 
}

GLint Patch::cOffSetY(const GLint& y)
{
	return (2 - y / 5);
}

