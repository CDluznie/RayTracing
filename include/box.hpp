#ifndef __BOX_H__
#define __BOX_H__

#include "shape.hpp"
#include "ray.hpp"
#include <glm/glm.hpp>
#include <vector>

class Box : public Shape {

public:

	explicit Box(const glm::dvec3 &boxMin, const glm::dvec3 &boxMax, const glm::dvec4 &color, const glm::dvec4 &emissive, const glm::dvec4 &reflect);
	
	std::vector<double> intersect(const Ray &ray) const override;
	
	glm::dvec3 normal(const glm::dvec3 &point) const override;
	
private:

	glm::dvec3 _boxMin;
	glm::dvec3 _boxMax;

};

#endif
