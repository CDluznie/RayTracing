#include "shape.hpp"


Shape::Shape(const glm::dvec4 &color, const glm::dvec4 &emissive, const glm::dvec4 &reflect) :
_color(color),
_emissive(emissive),
_reflect(reflect) {

}

glm::dvec4 Shape::getColor() const {
	return glm::dvec4(_color);
}

glm::dvec4 Shape::getEmissive() const {
	return glm::dvec4(_emissive);
}

glm::dvec4 Shape::getReflect() const {
	return glm::dvec4(_reflect);
}


glm::dvec4 Shape::normalColor(const glm::dvec3 &point) const {
	glm::dvec3 pointNormal = normal(point);
	return glm::dvec4((pointNormal + 1.)/2., 1.);
}
