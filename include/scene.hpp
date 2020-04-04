/**
 * \file scene.hpp
 * \brief Representation of scene
 *
 * Module for manipulation of scene.
 *
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include "shape.hpp"
#include "light.hpp"
#include "ray.hpp"
#include "collision_point.hpp"
#include <vector>
#include <glm/glm.hpp>

/** 
 * \class Scene
 * \brief Class representing a scene
 */
class Scene {

public:

	/**
	 * Construct a scene
     * \param shapes : Shapes of the scene
     * \param lights : Lights of the scene
     * \param backgroundColor : Background color of the scene
     * \param distanceNear : Minimum rendering distance
     * \param distanceFar : Maximum rendering distance
     */
	explicit Scene(std::vector<Shape *> shapes, std::vector<Light *> lights, const glm::dvec4 &backgroundColor, double distanceNear, double distanceFar);
	
	/**
     * Get the collision point of the ray on the scene
     * 
     * The function return the value \a nullptr if the ray did not intersect any object of the scene.
     *
     * \param ray: Tested ray
     * \return a pointer on a collision point if the ray intersect a shape of the scene, \a nullptr otherwise
     */
	CollisionPoint * getIntersectedPoint(const Ray &ray) const;

	/**
     * Compute the rendering color of particular point on the scene
     * \param point : Point where we want to compute the color
     * \param normal : Normal of the point
     * \param color : Color of the point
     * \return the resulting color
     */
	glm::dvec4 getLightingColor(const glm::dvec3 &point, const glm::dvec3 &normal, const glm::dvec4 &color) const;

	/**
     * Get the background color of the scene
     * \return the background color of the scene
     */
	glm::dvec4 getBackgroundColor() const;

	/**
     * Get the minimum rendering distance of the scene
     * \return the minimum rendering distance of the scene
     */
	double getDistanceNear() const;

	/**
     * Get the maximum rendering distance of the scene
     * \return the maximum rendering distance of the scene
     */
	double getDistanceFar() const;

private:

	std::vector<Shape *> _shapes;
	std::vector<Light *> _lights;
	glm::dvec4 _backgroundColor;
	double _distanceNear;
	double _distanceFar;

	static glm::dvec4 lambertianLight(const Light &light, const glm::dvec3 &point, const glm::dvec3 &normal, const glm::dvec4 &color);

	bool pointOccludedByLight(const glm::dvec3 &point, const Light &light) const;

};

#endif
