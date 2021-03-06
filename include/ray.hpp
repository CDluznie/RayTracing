/**
 * \file ray.hpp
 * \brief Representation of ray
 *
 * Module for manipulation of rays.
 *
 */

#ifndef __RAY_H__
#define __RAY_H__

#include <glm/glm.hpp>

/** 
 * \class Ray
 * \brief Class representing a ray
 */
class Ray {

public:

	/**
	 * Construct a ray
     * \param origin : Origin point of the ray
     * \param vector : Direction of the ray
     */
	explicit Ray(const glm::dvec3 &origin, const glm::dvec3 &vector);
	
	/**
	 * Compute the ray between two points
     * \param origin : Origin point of the ray
     * \param target : Target point of the ray
     * \return the ray between the points \a origin and \a target
     */
	static Ray betweenPoints(const glm::dvec3 &origin, const glm::dvec3 &target);

	/**
	 * Compute the reflection ray at a particular point
	 * \param point : Point where we want to reflect the ray
	 * \param normal : Value of the normal at \a point
	 * \return the reflection ray
	 */
	Ray reflect(const glm::dvec3 &point, const glm::dvec3 &normal) const;
	
	/**
     * Get the point on a the ray at a particular distance from the origin
     * 
     * A point on a ray can be written as <em>O + tD</em>, where \a O is the origin, \a D the direction and \a t a scalar.
     * This function will return the point when the value \a t is given.
     *
     * \param t: Distance from the origin
     * \return the point on the ray
     */
	glm::dvec3 getPoint(double t) const;

	/**
     * Get the origin of the ray
     * \return the origin of the ray
     */
	glm::dvec3 getOrigin() const;
	
	/**
     * Get the direction of the ray
     * \return the direction of the ray
     */
	glm::dvec3 getVector() const;

private:

	glm::dvec3 _origin;
	glm::dvec3 _vector;
	glm::dvec3 _normalizedVector;


};

#endif
