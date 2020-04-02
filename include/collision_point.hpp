#ifndef __COLLISION_POINT_H__
#define __COLLISION_POINT_H__

#include "shape.hpp"
#include <glm/glm.hpp>

class CollisionPoint {

public:

	explicit CollisionPoint(const glm::dvec3 &point, const Shape *shape);
	
	glm::dvec3 getPoint() const;
	 
	const Shape * getShape() const;
	
private:

	glm::dvec3 _point;
	const Shape *_shape;

};

#endif
