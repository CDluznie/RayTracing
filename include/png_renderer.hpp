#ifndef __PNG_RENDERER_H__
#define __PNG_RENDERER_H__

#include "camera.hpp"
#include <glm/glm.hpp>
#include <string>

class PNGRenderer {

public:

	static PNGRenderer create(const Camera & camera);
	
	~PNGRenderer();

	void setPixel(int x, int y, const glm::dvec4 &color);
	
	void save(const std::string &fname);

private:

	unsigned char *_image;
	int _width;
	int _height;
	
	explicit PNGRenderer(unsigned char *image, int width, int height);

};

#endif
