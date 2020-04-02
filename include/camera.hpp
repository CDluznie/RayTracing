#ifndef __CAMERA_H__
#define __CAMERA_H__


#include <glm/glm.hpp>

class Camera {

public:

	explicit Camera(const glm::dvec3 &position, const glm::dvec3 &sight, const glm::dvec3 &right, const glm::dvec3 &top, double heightFov, int screenWidth, int screenHeight);

	static Camera create(const glm::dvec3 &position, const glm::dvec3 &target, const glm::dvec3 &up, double heightFov, int screenWidth, int screenHeight);

	glm::dvec3 pixelPosition(int px, int py, double dz) const;

	glm::dvec3 getPosition() const;

	int getScreenWidth() const;

	int getScreenHeight() const;

private:

	glm::dvec3 _position;
	glm::dvec3 _sight;
	glm::dvec3 _right;
	glm::dvec3 _top;
	double _heightFov;
	int _screenWidth;
	int _screenHeight;

};

#endif
