#include <SOIL/SOIL.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "Utils.hpp"
#include "Patch.hpp"

Image::Image(const Image& img)
{
	width = img.getWidth();
	height = img.getHeight();
	size_t size = width * height * 3;
	content = new unsigned char[size];
	memcpy(content, img.getContent(), size);
	initDistributions();
}

Image::Image(const GLsizei& w, const GLsizei& h): width(w), height(h)
{
	content = new unsigned char[width * height * 3];
	memset(content, 0, width * height * 3);
	initDistributions();
}

Image::Image(const char* path)
{
	/* width and height are adjusted with this function call aswell*/
	content = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	initDistributions();
}

Image::~Image() 
{
	/* Trusting to 3rd party library to free our resources. Should check if this is ok */
	std::cout<<"d";
	SOIL_free_image_data(content);
}

void Image::initDistributions() 
{
	color_dist = std::uniform_int_distribution<int>(0, 255);
	width_dist = std::uniform_int_distribution<int>(0, width - 1);
	height_dist = std::uniform_int_distribution<int>(0, height - 1);
}

std::shared_ptr<Image> Image::generateNoise()
{
	for (GLint i = 0; i < this->getHeight(); i++)
		for (GLint j = 0; j < this->getWidth(); j++) 
		{
			GLint r_value = color_dist(gen);
			this->setColor(Pixel(j, i), Color(r_value, r_value, r_value));	
		}
	return shared_from_this();
}

std::shared_ptr<Image> Image::noiseFrom(const std::shared_ptr<Image> &image)
{
	for (GLint i = 0; i < this->getHeight(); i++)
		for (GLint j = 0; j < this->getWidth(); j++) 
			this->setColor(Pixel(j, i), image->getRandomColor());
			
	return shared_from_this();
}

/*
	Synthesises the image with Wei and Levoy algorithmus.
*/
std::shared_ptr<Image> Image::synthesiseFromWeiLevoy(const std::shared_ptr<Image>& from)
{

	this->noiseFrom(from);
//	this->generateNoise();
	int count = width * height;
	/* Synthesise each pixel*/
	for (GLint i = 0; i < this->getHeight(); i++)
		for (GLint j = 0; j < this->getWidth(); j++)
		{
			this->setColor(Pixel(j, i), this->getColorMatchWeiLevoy(from, Pixel(j, i)));
			std::cout<<"Synthesized pixel n. "<<i * height + j + 1<<" out of " << count<<std::endl;
		}
	return shared_from_this();
}

/*
	Searches for the best match as Wei and Levoy did. For the patch w, that surrounds 
	pixel we want to generate, find patch w' in the source with argmin(d_perc(w, w')).
	Where d_perc calculates how much do the given patches differ. Here: d_perc is a 
	normalized sum of squared differences multiplied by 2d Gaussian kernel.
*/
Color Image::getColorMatchWeiLevoy(const std::shared_ptr<Image>& from, const Pixel& p) 
{
	std::shared_ptr<Patch> current_patch(new Patch(shared_from_this(), p));
	Color result(0, 0, 0);
	GLfloat argmin = FLT_MAX;
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			std::shared_ptr<Patch> check_patch(new Patch(from, Pixel(j, i)));
			GLfloat dif = current_patch->getDifference(check_patch);
			if (dif < argmin)
			{
				result = check_patch->getCenter();	
				argmin = dif;
			}
		}
	}
	return result;
}

Color Image::getRandomColor()
{
	GLint index = (width * height_dist(gen) + width_dist(gen)) * 3;
	return Color(content[index], content[index + 1], content[index + 2]);
}

//std::shared_ptr<Image> Image::gaussBlur()
//{
//	std::shared_ptr<Image> temp(new Image(*this));
//	for (int i = 0; i < height; i++)
//		for (int j = 0; j < width; j++)
//		{
//			Pixel current(j, i);
//			temp->setColor(current, calc1DApproxGaussKernelX(shared_from_this(), current)); 
//		}
//	std::shared_ptr<Image> temp2(new Image(*this));
//	for (int i = 0; i < height; i++)
//		for (int j = 0; j < width; j++)
//		{
//			Pixel current(j, i);
//			temp2->setColor(current, calc1DApproxGaussKernelY(temp, current)); 
//		}
//	size_t size = width * height * 3;
//	memcpy(content, temp2->getContent(), size);
//	return shared_from_this();
//}

std::shared_ptr<Image> Image::fastGaussBlur(GLfloat r)
{
	std::vector<GLint> boxes = boxesForGauss(r, 3);
	std::shared_ptr<Image> temp(new Image(*this));
	for (std::vector<int>::iterator it = boxes.begin(); it != boxes.end(); ++it)
		fastBoxBlur(temp, (*it - 1) / 2);
	return shared_from_this();
}

std::shared_ptr<Image> Image::gaussBlur(GLfloat r)
{
	std::vector<GLint> boxes = boxesForGauss(r, 3);
	std::shared_ptr<Image> temp(new Image(*this));
	for (std::vector<int>::iterator it = boxes.begin(); it != boxes.end(); ++it)
		boxBlur(temp, (*it - 1) / 2);
	return shared_from_this();
}

std::shared_ptr<Image> Image::fastBoxBlur(std::shared_ptr<Image> temp, GLint r)
{
	return fastBoxBlurH(temp, r)->fastBoxBlurV(temp, r);
}

std::shared_ptr<Image> Image::boxBlur(std::shared_ptr<Image> temp, GLint r)
{
	return boxBlurH(temp, r)->boxBlurV(temp, r);
}


std::shared_ptr<Image> Image::boxBlurH(std::shared_ptr<Image> temp, GLint r) 
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Color val;
			for (int ix = j - r; ix < j + r + 1; ix++)
			{
				GLint x = std::min(width - 1, std::max(0, ix));
				val = val + temp->getColor(i * width + x);
			}
			setColor(i * width + j, val / (r + r + 1));
		}
	}
	return shared_from_this();
}

std::shared_ptr<Image> Image::boxBlurV(std::shared_ptr<Image> temp, GLint r)
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			Color val;
			for (int iy = i - r; iy < i + r + 1; iy++)
			{
				GLint y = std::min(height - 1, std::max(0, iy));
				val = val + temp->getColor(y * width + j);
			}
			setColor(i * width + j, val / (r + r + 1));
		}
	return shared_from_this();
}

std::shared_ptr<Image> Image::fastBoxBlurH(std::shared_ptr<Image> temp, GLint r) 
{

	GLfloat iarr = 1.0f / (r + r + 1.0f);
	for (int i = 0; i < height; i++)
	{
		GLint ti = i * width;
		GLint li = ti;
		GLint ri = ti + r;
		Color fv = temp->getColor(ti);
		Color lv = temp->getColor(ti + width - 1);
		Color val = fv * (r + 1);
		for (int j = 0; j < r; j++)
			val = val + temp->getColor(ti + j);
		for (int j = 0; j <= r; j++)
		{
			val = val + temp->getColor(ri++) - fv;
			setColor(ti++, Color(val) * iarr);
		}
		for (int j = r + 1; j < width - r; j++)
		{
			val = val + temp->getColor(ri++) - temp->getColor(li++);
			setColor(ti++, Color(val) * iarr);
		}
		for (int j = width - r; j < width; j++)
		{
			val = val + lv - temp->getColor(li++);
			setColor(ti++, Color(val) * iarr);
		}
	}
	return shared_from_this();
}

std::shared_ptr<Image> Image::fastBoxBlurV(std::shared_ptr<Image> temp, GLint r)
{
	GLfloat iarr = 1.0f / (r + r + 1.0f);
	for (int i = 0; i < width; i++)
	{
		GLint ti = i;
		GLint li = ti;
		GLint ri = ti + r * width;
		Color fv = temp->getColor(ti);
		Color lv = temp->getColor(ti + width * (height - 1));
		Color val = fv * (r + 1);
		for (int j = 0; j < r; j++)
			val = val + temp->getColor(ti + j * width);
		for (int j = 0; j <= r; j++)
		{
			val = val + temp->getColor(ri) - fv;
			setColor(ti, Color(val) * iarr);
			ri += width;
			ti += width;
		}
		for (int j = r + 1; j < height - r; j++)
		{
			val = val + temp->getColor(ri) - temp->getColor(li);
			setColor(ti, Color(val) * iarr);
			li += width;
			ri += width;
			ti += width;
		}
		
		for (int j = height - r; j < height; j++)
		{
			val = val + lv - temp->getColor(li);
			setColor(ti, Color(val) * iarr);
			li += width;
			ti += width;
		}
	}
	return shared_from_this();
}

std::shared_ptr<Image> Image::downscale()
{
	std::shared_ptr<Image> img(new Image(width / 2, height / 2));
	for (int i = 0; i < img->getHeight(); i++)
		for (int j = 0; j < img->getWidth(); j++)
		{
			Pixel current(j, i);
			img->setColor(current, lerp(shared_from_this(), Pixel(current) * 2));
		}

	std::cout<<"d";
	delete[] content;
	width /= 2;
	height /= 2;
	content = new unsigned char[width * height * 3];
	memcpy(content, img->getContent(), width * height * 3);
	return shared_from_this();
}

int Image::save(const char* name) 
{
	return SOIL_save_image(name, SOIL_SAVE_TYPE_TGA, width, height, 3, content);
}

//---------------------------------------------------------------------------------------

Color Image::getColor(const Pixel& p) const
{
	GLint index = (width * (wrap(p.y, height)) + (wrap(p.x, width))) * 3;
	return Color(content[index], content[index + 1], content[index + 2]);
}

void Image::setColor(const Pixel& p, const Color& c)
{
	GLint index = (width * p.y + p.x) * 3;
	content[index]		= c.red;
	content[index + 1]	= c.green;
	content[index + 2]	= c.blue;
}

GLint Image::getWidth() const
{
	return width;
} 

GLint Image::getHeight() const
{
	return height;
}

unsigned char* Image::getContent() const
{
	return content;
}

void Image::setContent(unsigned char* p)
{
	content = p;
}

void Image::setColor(const GLint& where, const Color& c)
{
	content[where * 3] = c.red;
	content[where * 3 + 1] = c.green;
	content[where * 3 + 2] = c.blue;
}

Color Image::getColor(const GLint& where) const
{
	return Color(content[where * 3], content[where * 3 + 1], content[where * 3 + 2]);
}
