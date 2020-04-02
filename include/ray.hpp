#ifndef __RAY_H__
#define __RAY_H__

#include <glm/glm.hpp>

class Ray {

public:

	explicit Ray(const glm::dvec3 &origin, const glm::dvec3 &vector);
	
	static Ray betweenPoints(const glm::dvec3 &origin, const glm::dvec3 &target);

	Ray reflect(const glm::dvec3 &point, const glm::dvec3 &normal) const;

	glm::dvec3 getOrigin() const;
	
	glm::dvec3 getVector() const;

private:

	glm::dvec3 _origin;
	glm::dvec3 _vector;
	glm::dvec3 _normalizedVector;


};

#endif
