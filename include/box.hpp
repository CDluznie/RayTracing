#ifndef __BOX_H__
#define __BOX_H__

#include "shape.hpp"
#include "ray.hpp"
#include <glm/glm.hpp>
#include <vector>

class Box : public Shape {

public:

	/**
	 * Construct a box
     * \param boxMin : Minimum point of the box
     * \param boxMax : Maximum point of the box
     * \param color : Color of the box
     * \param emissive : Emissive color of the box
     * \param reflect : Reflection coefficients of the box
     */
	explicit Box(const glm::dvec3 &boxMin, const glm::dvec3 &boxMax, const glm::dvec4 &color, const glm::dvec4 &emissive, const glm::dvec4 &reflect);
	
	/**
     * Get the parametric values on the ray where the box is intersected
     * 
     * A point on a ray can be written as <em>O + tD</em>, where \a O is the origin, \a D the direction and \a t a scalar.
     * This function will return all values \a t where the ray hit the box.
     * If the ray did not hit the box, the returned vector is empty.
     *
     * \param ray: Tested ray
     * \return a vector containing all values \a t where the box is intersected
     */
	std::vector<double> intersect(const Ray &ray) const override;
	
	/**
     * Get the normal of the box at a particular point
     * 
     * The point have to be on the surface of the box.
     *
     * \param point: Point where we want to retrieve the normal
     * \return the normal of the box
     */
	glm::dvec3 normal(const glm::dvec3 &point) const override;
	
private:

	glm::dvec3 _boxMin;
	glm::dvec3 _boxMax;

};

#endif
