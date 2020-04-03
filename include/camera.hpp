#ifndef __CAMERA_H__
#define __CAMERA_H__


#include <glm/glm.hpp>

class Camera {

public:

	/**
	 * Create a camera
     * \param position : Position of the camera
     * \param target : Targeted point of the camera
     * \param up : Up vector
     * \param heightFov : Field of view angle in height
     * \param screenWidth : Width of the screen
     * \param screenHeight : Height of the screen
     * \return The corresponding camera
     */
	static Camera create(const glm::dvec3 &position, const glm::dvec3 &target, const glm::dvec3 &up, double heightFov, int screenWidth, int screenHeight);

	/**
	 * Get the position of a pixel in the space
	 * \param px : Coordinate value on the \a x axis of the pixel
	 * \param py : Coordinate value on the \a y axis of the pixel
	 * \param dz : Distance on the \a z axis
	 * \return The position of the pixel
	 */
	glm::dvec3 pixelPosition(int px, int py, double dz) const;

	/**
	 * Get the position of the camera
	 * \return The position of the camera
	 */
	glm::dvec3 getPosition() const;

	/**
	 * Get the width of the screen
	 * \return The width of the screen
	 */
	int getScreenWidth() const;

	/**
	 * Get the height of the screen
	 * \return The height of the screen
	 */
	int getScreenHeight() const;

private:

	glm::dvec3 _position;
	glm::dvec3 _sight;
	glm::dvec3 _right;
	glm::dvec3 _top;
	double _heightFov;
	int _screenWidth;
	int _screenHeight;

	explicit Camera(const glm::dvec3 &position, const glm::dvec3 &sight, const glm::dvec3 &right, const glm::dvec3 &top, double heightFov, int screenWidth, int screenHeight);

};

#endif
