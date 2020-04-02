#include "collision_point.hpp"


CollisionPoint::CollisionPoint(const glm::dvec3 &point, const Shape *shape) :
_point(point),
_shape(shape) {

}

glm::dvec3 CollisionPoint::getPoint() const {
	return glm::dvec3(_point);
}
	 
const Shape * CollisionPoint::getShape() const {
	return _shape;
}
