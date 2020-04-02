#include "ray.hpp"

Ray::Ray(const glm::dvec3 &origin, const glm::dvec3 &vector) :
_origin(origin),
_vector(glm::normalize(vector)) {
	
}

Ray Ray::betweenPoints(const glm::dvec3 &origin, const glm::dvec3 &target) {
	return Ray(origin, target - origin);
}

Ray Ray::reflect(const glm::dvec3 &point, const glm::dvec3 &normal) const {
	double scale = 2*glm::dot(normal, _vector);
	return Ray(point, _vector - scale*normal);
}

glm::dvec3 Ray::getOrigin() const {
	return glm::dvec3(_origin);
}
	
glm::dvec3 Ray::getVector() const {
	return glm::dvec3(_vector);
}
