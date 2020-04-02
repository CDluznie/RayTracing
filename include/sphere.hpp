#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "shape.hpp"
#include "ray.hpp"
#include <glm/glm.hpp>
#include <vector>

class Sphere : public Shape {

public:

	explicit Sphere(const glm::dvec3 &center, double radius, const glm::dvec4 &color, const glm::dvec4 &emissive, const glm::dvec4 &reflect);
	
	std::vector<double> intersect(const Ray &ray) const override;
	
	glm::dvec3 normal(const glm::dvec3 &point) const override;
	
private:

	glm::dvec3 _center;
	double _radius;

};

#endif
