#include "light.hpp"

Light::Light(const glm::dvec3 &position, const glm::dvec4 &color) : _position(position), _color(color) {
	
}

glm::dvec3 Light::getPosition() const {
	return glm::dvec3(_position);
}
	
glm::dvec4 Light::getColor() const {
	return glm::dvec4(_color);
}
