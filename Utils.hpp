#ifndef UTILS_HPP
#define UTILS_HPP
//-------------------------------------------------------------------------
class Pixel;
class Image;
class Color;
//-------------------------------------------------------------------------
#include <algorithm>
#include <memory>
#include <iostream>
#include <GL/glew.h>
//-------------------------------------------------------------------------
#define _PI_  3.14159265359
#define _E_  2.16395341373

class Image;

/* for gaussian approximaton */
const GLint apxs[] {1, 4, 6, 4, 1};

GLint wrap(GLint toWrap, const GLint& limit);

GLfloat calc2DGaussKernel(const Pixel& p, const GLint& omega);

Color calc1DApproxGaussKernelX(const std::shared_ptr<Image>& image, const Pixel& p);

Color calc1DApproxGaussKernelY(const std::shared_ptr<Image>& image, const Pixel& p);

/* not actually a lerp, but somewhat satisfying for my results*/
Color lerp(const std::shared_ptr<Image>& image, const Pixel& p);

std::vector<GLint> boxesForGauss(GLfloat sigma, GLint boxes_count);
#endif
