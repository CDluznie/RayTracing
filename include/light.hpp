#ifndef __LIGHT_H__
#define __LIGHT_H__


#include <glm/glm.hpp>

class Light {

public:

	explicit Light(const glm::dvec3 &position, const glm::dvec4 &color);

	glm::dvec3 getPosition() const;

	glm::dvec4 getColor() const;


private:

	glm::dvec3 _position;
	glm::dvec4 _color;

};

#endif
