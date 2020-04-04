/**
 * \file light.hpp
 * \brief Representation of light
 *
 * Module for manipulation of lights.
 *
 */
 
#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glm/glm.hpp>

/** 
 * \class Light
 * \brief Class representing a light in the scene
 */
class Light {

public:

	/**
	 * Construct a light
     * \param position : Position of the light
     * \param color : Color of the light
     */
	explicit Light(const glm::dvec3 &position, const glm::dvec4 &color);

	/**
     * Get the position of the light
     * \return the position of the light
     */
	glm::dvec3 getPosition() const;

	/**
     * Get the color of the light
     * \return the color of the light
     */
	glm::dvec4 getColor() const;


private:

	glm::dvec3 _position;
	glm::dvec4 _color;

};

#endif
