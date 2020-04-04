/**
 * \file sphere.hpp
 * \brief Representation of sphere
 *
 * Module for manipulation of spheres.
 *
 */

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "shape.hpp"
#include "ray.hpp"
#include <glm/glm.hpp>
#include <vector>

/** 
 * \class Sphere
 * \brief Class representing a sphere in the scene
 */
class Sphere : public Shape {

public:

	/**
	 * Construct a sphere
     * \param center : Center of the sphere
     * \param radius : Radius of the sphere
     * \param color : Color of the sphere
     * \param emissive : Emissive color of the sphere
     * \param reflect : Reflection coefficients of the sphere
     */
	explicit Sphere(const glm::dvec3 &center, double radius, const glm::dvec4 &color, const glm::dvec4 &emissive, const glm::dvec4 &reflect);
	
	/**
     * Get the parametric values on the ray where the sphere is intersected
     * 
     * A point on a ray can be written as <em>O + tD</em>, where \a O is the origin, \a D the direction and \a t a scalar.
     * This function will return all values \a t where the ray hit the sphere.
     * If the ray did not hit the sphere, the returned vector is empty.
     *
     * \param ray: Tested ray
     * \return a vector containing all values \a t where the sphere is intersected
     */
	std::vector<double> intersect(const Ray &ray) const override;
	
	/**
     * Get the normal of the sphere at a particular point
     * 
     * The point have to be on the surface of the sphere.
     *
     * \param point: Point where we want to retrieve the normal
     * \return the normal of the sphere
     */
	glm::dvec3 normal(const glm::dvec3 &point) const override;
	
private:

	glm::dvec3 _center;
	double _radius;

};

#endif
