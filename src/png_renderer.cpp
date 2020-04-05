#include "png_renderer.hpp"
#include <lodepng.h>
#include <iomanip> 


PNGRenderer::PNGRenderer(unsigned char *image, int width, int height) :
_image(image),
_width(width),
_height(height) {

}

PNGRenderer::~PNGRenderer() {
	delete _image;
}

PNGRenderer PNGRenderer::create(const Camera &camera) {
	int width = camera.getScreenWidth();
	int height = camera.getScreenHeight();
	unsigned char *image = new unsigned char[4 * width * height];
	return PNGRenderer(image, width, height);
}

void PNGRenderer::setPixel(int x, int y, const glm::dvec4 &color) {
	int index = 4 * ((_height - y - 1) * _width + x);
	_image[index]     = (unsigned char)(color.r * 255.0);
	_image[index + 1] = (unsigned char)(color.g * 255.0);
	_image[index + 2] = (unsigned char)(color.b * 255.0);
	_image[index + 3] = (unsigned char)(color.a * 255.0);
}

void PNGRenderer::save(const std::string &fname) {
	unsigned error = lodepng::encode(fname, _image, _width, _height, LCT_RGBA);
	if (error) {
		throw std::runtime_error("Error loadpng::decode: " + std::string(lodepng_error_text(error)));
	}
}
