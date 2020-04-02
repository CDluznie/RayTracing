#ifndef __SCENE_H__
#define __SCENE_H__

#include "shape.hpp"
#include "light.hpp"
#include "ray.hpp"
#include "collision_point.hpp"
#include <vector>
#include <glm/glm.hpp>

class Scene {

public:

	explicit Scene(std::vector<Shape *> shapes, std::vector<Light *> lights, const glm::dvec4 &backgroundColor, double distanceNear, double distanceFar);
	
	CollisionPoint * getIntersectedPoint(const Ray &ray) const;

	glm::dvec4 getLightingColor(const glm::dvec3 &point, const glm::dvec3 &normal, const glm::dvec4 &color) const;

	glm::dvec4 getBackgroundColor() const;

	double getDistanceNear() const;

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
