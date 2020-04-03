#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "ray.hpp"
#include <glm/glm.hpp>
#include <vector>

class Shape {

public:
	
	/**
	 * Construct a shape
     * \param color : Color of the shape
     * \param emissive : Emissive color of the shape
     * \param reflect : Reflection coefficients of the shape
     */
	Shape(const glm::dvec4 &color, const glm::dvec4 &emissive, const glm::dvec4 &reflect);

	/**
	 * Destruct the shape
	 */
	virtual ~Shape() {};

	/**
     * Get the parametric values on the ray where the shape is intersected
     * 
     * A point on a ray can be written as <em>O + tD</em>, where \a O is the origin, \a D the direction and \a t a scalar.
     * This function will return all values \a t where the ray hit the shape.
     * If the ray did not hit the shape, the returned vector is empty.
     *
     * \param ray: Tested ray
     * \return a vector containing all values \a t where the shape is intersected
     */
	virtual std::vector<double> intersect(const Ray &ray) const = 0;
	
	/**
     * Get the normal of the shape at a particular point
     * 
     * The point have to be on the surface of the shape.
     *
     * \param point: Point where we want to retrieve the normal
     * \return the normal of the shape
     */
	virtual glm::dvec3 normal(const glm::dvec3 &point) const = 0;
	
	/**
     * Get the color of the shape
     * \return the color of the shape
     */
	glm::dvec4 getColor() const;
	 
	/**
     * Get the emissive color of the shape
     * \return the emissive color of the shape
     */
	glm::dvec4 getEmissive() const;
	
	/**
     * Get the reflection coefficients of the shape
     * \return the reflection coefficients of the shape
     */
	glm::dvec4 getReflect() const;

	/**
     * Get the normal as a color of the shape at a particular point
     * 
     * This function is used for debugging purpose.
     * 
     * \return the normal of the shape as a color
     */
	glm::dvec4 normalColor(const glm::dvec3 &point) const;

private:

	glm::dvec4 _color;
	glm::dvec4 _emissive;
	glm::dvec4 _reflect;

};

#endif
