#include "scene.hpp"
#include <algorithm>


Scene::Scene(std::vector<Shape *> shapes, std::vector<Light *> lights, const glm::dvec4 &backgroundColor, double distanceNear, double distanceFar) :
_shapes(shapes),
_lights(lights),
_backgroundColor(backgroundColor),
_distanceNear(distanceNear),
_distanceFar(distanceFar) {

}

CollisionPoint * Scene::getIntersectedPoint(const Ray &ray) const {
	double mint = _distanceFar;
	const Shape *closestShape = nullptr;
	for (const Shape *shape : _shapes) {
		for (double t : shape->intersect(ray)) {
			if (t > _distanceNear && t < mint) {
				mint = t;
				closestShape = shape;
			}
		}
	}
	if (closestShape == nullptr) {
		return nullptr;
	}
	return new CollisionPoint(ray.getPoint(mint), closestShape);
}

bool Scene::pointOccludedByLight(const glm::dvec3 &point, const Light &light) const {
	Ray ray = Ray::betweenPoints(light.getPosition(), point);
	double distanceLightPoint = glm::length(light.getPosition() - point);
	double epsilon = 0.001;
	for (const Shape *shape : _shapes) {
		for (double t : shape->intersect(ray)) {
			if (epsilon < t && t < distanceLightPoint-epsilon) {
				return true;
			}
		}
	}
	return false;
}

glm::dvec4 Scene::lambertianLight(const Light &light, const glm::dvec3 &point, const glm::dvec3 &normal, const glm::dvec4 &color) {
	glm::dvec3 lightPos = light.getPosition();
	glm::dvec4 lightColor = light.getColor();
	glm::dvec3 lightVector =  glm::normalize(point - lightPos);
	double intensity = 1; // can add intensity based on the norm of light vector
	double coeff = intensity * glm::dot(normal, lightVector);
	return coeff * lightColor * color;
}

glm::dvec4 Scene::getLightingColor(const glm::dvec3 &point, const glm::dvec3 &normal, const glm::dvec4 &color) const {
	glm::dvec4 finalColor(0);
	glm::dvec4 receivedLightColor;
	for (Light *light : _lights) {
		if (pointOccludedByLight(point, *light)) {
			continue;
		}
		receivedLightColor = lambertianLight(*light, point, normal, color);
		finalColor = glm::clamp(finalColor + receivedLightColor, 0.0, 1.0);
	}
	return finalColor;
}

glm::dvec4 Scene::getBackgroundColor() const {
	return glm::dvec4(_backgroundColor);
}

double Scene::getDistanceNear() const {
	return _distanceNear;
}

double Scene::getDistanceFar() const {
	return _distanceFar;
}
