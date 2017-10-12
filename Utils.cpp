#include <cstdlib>
#include <cmath>
#include <vector>
//-------------------------------------------------------------------------
#include "Utils.hpp"
#include "Color.hpp"
#include "Image.hpp"
#include "Pixel.hpp"
//-------------------------------------------------------------------------

GLint wrap(GLint toWrap, const GLint& limit)
{
	if (toWrap >= limit)
	{
		toWrap %= limit;
		return toWrap;
	} 
	while (toWrap < 0)
		toWrap += limit;
	return toWrap;
}

GLfloat calc2DGaussKernel(const Pixel& p, const GLint& omega)
{
	return (1 / _PI_ * omega * omega) * pow(_E_, -1.0f * (p.x * p.x - p.y * p.y) / (2 * omega * omega));
}

/*naive*/
Color calc1DApproxGaussKernelX(const std::shared_ptr<Image>& image, const Pixel& p)
{
	Color result;
	GLint tiles = 0;
	GLint start = (p.x - 2) >= 0 ? -2 : (p.x - 1) >= 0 ? -1 : 0;
	GLint end = (image->getWidth() - p.x - 2) >= 0 ? 2 : (image->getWidth() - p.x - 1) >= 0 ? 1 : 0;
	for (int i = start; i <= end; i++)
	{
		tiles += apxs[i];
		result = result + image->getColor(Pixel(p.x + i, p.y)) * apxs[i];
	}
	return result / tiles;
}

/*naive*/
Color calc1DApproxGaussKernelY(const std::shared_ptr<Image>& image, const Pixel& p)
{
	Color result;
	GLint tiles = 0;
	GLint start = (p.y - 2) >= 0 ? -2 : (p.y - 1) >= 0 ? -1 : 0;
	GLint end = (image->getHeight() - p.y - 2) >= 0 ? 2 : (image->getHeight() - p.y - 1) >= 0 ? 1 : 0;
	for (int i = start; i <= end; i++)
	{
		tiles += apxs[i];
		result = result + image->getColor(Pixel(p.x, p.y + i)) * apxs[i];
	}
	return result / tiles;
}

Color lerp(const std::shared_ptr<Image>& image, const Pixel& p)
{
	Color result = image->getColor(p) + image->getColor(Pixel(p.x + 1, p.y)) + image->getColor(Pixel(p.x + 1, p.y + 1))
	 + image->getColor(Pixel(p.x, p.y + 1));
	return result / 4;
}

/* adopted from: http://blog.ivank.net/fastest-gaussian-blur.html */

std::vector<GLint> boxesForGauss(GLfloat sigma, GLint boxes_count)
{
	GLfloat wIdeal = sqrt((12.0f * sigma * sigma / (GLfloat)boxes_count) + 1.0f);
	GLint wl = (GLint)floor(wIdeal);
	if (wl % 2 == 0)
		wl--;
	GLint wu = wl + 2;
	GLfloat mIdeal = (12.0f * sigma * sigma - (GLfloat)(boxes_count * wl * wl) - 4.0f * (GLfloat)(boxes_count * wl) - 3.0f * (GLfloat)boxes_count) / (-4.0f * (GLfloat)wl - 4.0f);
	GLint m = (GLint)round(mIdeal);
	std::vector<GLint> vc;
	for (int i = 0; i < boxes_count; i++)
		vc.push_back(i < m ? wl : wu);
	return vc;
}




