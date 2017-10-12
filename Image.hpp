#ifndef IMAGE_HPP
#define IMAGE_HPP
//--------------------------------------------------------------------------------
class Pixel;
class Color;
//--------------------------------------------------------------------------------
#include <GL/glew.h>
#include <algorithm>
#include <memory>
#include <cfloat>
#include <random>
//--------------------------------------------------------------------------------
class Image
	 : public std::enable_shared_from_this<Image>
{
	private:
		GLsizei width;
		GLsizei height;
		unsigned char* content;
		std::uniform_int_distribution<int> color_dist;
		std::uniform_int_distribution<int> width_dist;
		std::uniform_int_distribution<int> height_dist;
		std::default_random_engine gen;
		
		void initDistributions();
		Color getColorMatchWeiLevoy(const std::shared_ptr<Image>& from, const Pixel& p);

		std::shared_ptr<Image> fastBoxBlur(std::shared_ptr<Image> temp, GLint r);
		std::shared_ptr<Image> fastBoxBlurH(std::shared_ptr<Image> temp, GLint r);
		std::shared_ptr<Image> fastBoxBlurV(std::shared_ptr<Image> temp, GLint r);
		
		std::shared_ptr<Image> boxBlur(std::shared_ptr<Image> temp, GLint r);
		std::shared_ptr<Image> boxBlurH(std::shared_ptr<Image> temp, GLint r);
		std::shared_ptr<Image> boxBlurV(std::shared_ptr<Image> temp, GLint r);
		
	public:
	
		/* Constructors */
		Image(const Image& img);
		Image(const char* path);
		Image(const GLsizei& width, const GLsizei& height); 
		~Image();
		
		/* Function members*/
		std::shared_ptr<Image> downscale();
		std::shared_ptr<Image> generateNoise();
		std::shared_ptr<Image> noiseFrom(const std::shared_ptr<Image>& image);
		std::shared_ptr<Image> synthesiseFromWeiLevoy(const std::shared_ptr<Image>& from);
		std::shared_ptr<Image> fastGaussBlur(GLfloat r);		
		std::shared_ptr<Image> gaussBlur(GLfloat r);
		Color getRandomColor();
		int save(const char* name);
		
				
		/* Setters */
		void setColor(const Pixel& p, const Color& color);
		void setColor(const GLint& where, const Color& c);
		void setContent(unsigned char* p);
		
		/* Getters */
		Color getColor(const Pixel& p) const;
		Color getColor(const GLint& where) const;
		unsigned char* getContent() const;
		GLsizei getWidth() const;
		GLsizei getHeight() const;
};

#endif
