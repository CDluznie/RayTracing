#include "camera.hpp"


Camera::Camera(const glm::dvec3 &position, const glm::dvec3 &sight, const glm::dvec3 &right, const glm::dvec3 &top, double heightFov, int screenWidth, int screenHeight) :
_position(position),
_sight(sight),
_right(right),
_top(top),
_heightFov(heightFov),
_screenWidth(screenWidth),
_screenHeight(screenHeight) {
	
}

Camera Camera::create(const glm::dvec3 &position, const glm::dvec3 &target, const glm::dvec3 &up, double heightFov, int screenWidth, int screenHeight) {
	glm::dvec3 sight = glm::normalize(target - position);
	glm::dvec3 top = glm::normalize(glm::cross(up, sight));
	glm::dvec3 right = glm::cross(sight, top);
	return Camera(position, sight, right, top, heightFov, screenWidth, screenHeight);
}

glm::dvec3 Camera::pixelPosition(int px, int py, double dz) const {
	double screenRatio = ((double) _screenWidth)/_screenHeight;
	double h = 2*tan(_heightFov/2)*dz;
	double w = h*screenRatio;
	glm::dvec3 centerPosition = _position + _sight*dz;
	glm::dvec3 bottomLeftPosition = centerPosition - _right*(w/2) - _top*(h/2);
	return bottomLeftPosition + _right*(px*(w/_screenWidth)) + _top*(py*(h/_screenHeight));
}

glm::dvec3 Camera::getPosition() const {
	return glm::dvec3(_position);
}

int Camera::getScreenWidth() const {
	return _screenWidth;
}

int Camera::getScreenHeight() const {
	return _screenHeight;
}


