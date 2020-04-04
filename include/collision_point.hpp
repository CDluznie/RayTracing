/**
 * \file box.hpp
 * \brief Representation of collision point
 *
 * Module for manipulation of collision points.
 * The collision points are used to compute the intersection between a ray and a shape of the scene.
 *
 */
 
#ifndef __COLLISION_POINT_H__
#define __COLLISION_POINT_H__

#include "shape.hpp"
#include <glm/glm.hpp>

/** 
 * \class CollisionPoint
 * \brief Class representing a collision point
 * 
 * A collision point is represented by a point in the space and the shape to which it belongs.
 */
class CollisionPoint {

public:

	/**
	 * Construct a collision point
     * \param point : Point of the collision
     * \param shape : Collided shape
     */
	explicit CollisionPoint(const glm::dvec3 &point, const Shape *shape);
	
	/**
     * Get the point of the collision
     * \return the point of the collision
     */
	glm::dvec3 getPoint() const;
	
	/**
     * Get the collided shape
     * \return the collided shape
     */
	const Shape * getShape() const;
	
private:

	glm::dvec3 _point;
	const Shape *_shape;

};

#endif
