#ifndef PATCH_HPP
#define PATCH_HPP
//-------------------------------------------------------------------------
class Image;
class Pixel;
//-------------------------------------------------------------------------
#include <memory>
#include <GL/glew.h>
//-------------------------------------------------------------------------
#include "Color.hpp"
//-------------------------------------------------------------------------
class Patch
{
	private:
		GLint x;
		GLint y;
		Color center;
		unsigned char* content;
	public:
		Patch(const std::shared_ptr<Image>& image, const Pixel& p);
		~Patch();
		
		int index;
		
		float getDifference(const std::shared_ptr<Patch>& other);
		
		Color getCenter();
		unsigned char* getContent();
		void setCenter(const Color& c);
		
		static GLint cOffSetX(const GLint& x);
		static GLint cOffSetY(const GLint& y);
};
#endif
