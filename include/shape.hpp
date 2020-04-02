#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "ray.hpp"
#include <glm/glm.hpp>
#include <vector>

class Shape {

public:
	
	Shape(const glm::dvec4 &color, const glm::dvec4 &emissive, const glm::dvec4 &reflect);

	virtual ~Shape() {};

	virtual std::vector<double> intersect(const Ray &ray) const = 0;
	
	virtual glm::dvec3 normal(const glm::dvec3 &point) const = 0;
	
	glm::dvec4 getColor() const;
	 
	glm::dvec4 getEmissive() const;
	
	glm::dvec4 getReflect() const;

	glm::dvec4 normalColor(const glm::dvec3 &point) const;

private:

	glm::dvec4 _color;
	glm::dvec4 _emissive;
	glm::dvec4 _reflect;

};

#endif
