/**
 * \file png_renderer.hpp
 * \brief Methods to render the result
 *
 * Module that provide a method to save the result.
 * Here we choose to save as a \a .png file but we can imagine an other renderer
 * that for example display the result in a SDL window.
 *
 */

#ifndef __PNG_RENDERER_H__
#define __PNG_RENDERER_H__

#include "camera.hpp"
#include <glm/glm.hpp>
#include <string>

/** 
 * \class PNGRenderer
 * \brief Helper class to save the result as a \a .png file
 */
class PNGRenderer {

public:

	/**
	 * Create a PNG renderer
	 * \param camera : Camera used to render the scene
	 * \return the corresponding PNG renderer
	 */
	static PNGRenderer create(const Camera & camera);
	
	/**
	 * Destruct the PNG renderer
	 */
	~PNGRenderer();

	/**
	 * Get the position of a pixel in the space
	 * \param px : Coordinate value on the \a x axis of the pixel
	 * \param py : Coordinate value on the \a y axis of the pixel
	 * \param color : Color to set
	 */
	void setPixel(int x, int y, const glm::dvec4 &color);
	
	/**
	 * Save the rendering in a PNG file
	 * \param fname : Name of the output file
	 */
	void save(const std::string &fname);

private:

	unsigned char *_image;
	int _width;
	int _height;
	
	explicit PNGRenderer(unsigned char *image, int width, int height);

};

#endif
