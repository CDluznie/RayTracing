#include "raytracer.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


Ray Raytracer::initialRay(const Camera &camera, int px, int py, double distanceNear) {
	return Ray::betweenPoints(
		camera.getPosition(),
		camera.pixelPosition(px, py, distanceNear)
	);
}

glm::dvec4 Raytracer::throwRayForNormals(const Scene &scene, const Camera &camera, int px, int py) {
	Ray ray = initialRay(camera, px, py, scene.getDistanceNear());
	CollisionPoint *collisionPoint = scene.getIntersectedPoint(ray);
	if (collisionPoint == nullptr) {
		return scene.getBackgroundColor();
	}
	glm::dvec3 intersectedPoint = collisionPoint->getPoint();
	const Shape *intersectedObject = collisionPoint->getShape();
	delete collisionPoint;
	return intersectedObject->normalColor(intersectedPoint);
}

glm::dvec4 Raytracer::throwRayWithoutReflection(const Scene &scene, const Camera &camera, int px, int py) {
	Ray ray = initialRay(camera, px, py, scene.getDistanceNear());
	CollisionPoint *collisionPoint = scene.getIntersectedPoint(ray);
	if (collisionPoint == nullptr) {
		return scene.getBackgroundColor();
	}
	glm::dvec3 intersectedPoint = collisionPoint->getPoint();
	const Shape *intersectedObject = collisionPoint->getShape();
	delete collisionPoint;
	glm::dvec4 lightingColor = scene.getLightingColor(intersectedPoint, intersectedObject->normal(intersectedPoint), intersectedObject->getColor());
	return glm::clamp(lightingColor + intersectedObject->getEmissive(), 0.0, 1.0);
}

glm::dvec4 Raytracer::throwRayWithOneReflection(const Scene &scene, const Camera &camera, int px, int py) {
	Ray ray = initialRay(camera, px, py, scene.getDistanceNear());
	CollisionPoint *collisionPoint = scene.getIntersectedPoint(ray);
	if (collisionPoint == nullptr) {
		return scene.getBackgroundColor();
	}
	glm::dvec3 intersectedPoint = collisionPoint->getPoint();
	const Shape *intersectedObject = collisionPoint->getShape();
	delete collisionPoint;
	glm::dvec3 intersectedObjectNormal = intersectedObject->normal(intersectedPoint);
	Ray reflectRay = ray.reflect(intersectedPoint, intersectedObjectNormal);
	glm::dvec4 reflectColor;
	CollisionPoint *reflectCollisionPoint = scene.getIntersectedPoint(reflectRay);
	if (reflectCollisionPoint == nullptr || reflectCollisionPoint->getShape() == collisionPoint->getShape()) {
		reflectColor = scene.getBackgroundColor();
	} else {
		reflectColor = reflectCollisionPoint->getShape()->getColor();
	}
	delete reflectCollisionPoint;
	reflectColor = glm::clamp(intersectedObject->getReflect() * reflectColor, 0., 1.);
	glm::dvec4 lightingColor = scene.getLightingColor(intersectedPoint, intersectedObjectNormal, intersectedObject->getColor());
	lightingColor = glm::clamp(lightingColor + reflectColor, 0., 1.);
	return glm::clamp(intersectedObject->getEmissive() + lightingColor, 0.0, 1.0);
}

glm::dvec4 Raytracer::throwRay(const Scene &scene, const Camera &camera, int px, int py, int depth) {
	Ray ray = initialRay(camera, px, py, scene.getDistanceNear());
	CollisionPoint *collisionPoint = scene.getIntersectedPoint(ray);
	if (collisionPoint == nullptr) {
		return scene.getBackgroundColor();
	}
	glm::dvec3 intersectedPoint = collisionPoint->getPoint();
	const Shape *intersectedObject = collisionPoint->getShape();
	delete collisionPoint;
	glm::dvec4 lightingColor = followRay(scene, ray, intersectedObject, intersectedPoint, depth);
	return glm::clamp(intersectedObject->getEmissive() + lightingColor, 0.0, 1.0);
}

glm::dvec4 Raytracer::followRay(const Scene &scene, const Ray &ray, const Shape *shape, const glm::dvec3 &point, int depth) {
	if (depth == 0) {
		return scene.getLightingColor(point, shape->normal(point), shape->getColor());
	}
	glm::dvec3 normal = shape->normal(point);
	glm::dvec4 reflectColor;
	Ray reflectRay = ray.reflect(point, normal);
	CollisionPoint *reflectCollisionPoint = scene.getIntersectedPoint(reflectRay);
	if (reflectCollisionPoint == nullptr || reflectCollisionPoint->getShape() == shape) {
		reflectColor = scene.getBackgroundColor();
	} else {
		reflectColor = followRay(scene, reflectRay, reflectCollisionPoint->getShape(), reflectCollisionPoint->getPoint(), depth-1);
	}
	delete reflectCollisionPoint;
	reflectColor = glm::clamp(shape->getReflect() * reflectColor, 0., 1.);
	glm::dvec4 lightingColor = scene.getLightingColor(point, normal, shape->getColor());
	return glm::clamp(lightingColor + reflectColor, 0., 1.);
}

void Raytracer::renderNormals(const Scene &scene, const Camera &camera, PNGRenderer &renderer) {
	for(int j = 0; j < camera.getScreenHeight(); j++) {
		for(int i = 0; i < camera.getScreenWidth(); i++) {
			glm::dvec4 color = throwRayForNormals(scene, camera, i, j);
			renderer.setPixel(i, j, color);
		}
	}
}

void Raytracer::renderWithoutReflection(const Scene &scene, const Camera &camera, PNGRenderer &renderer) {
	for(int j = 0; j < camera.getScreenHeight(); j++) {
		for(int i = 0; i < camera.getScreenWidth(); i++) {
			glm::dvec4 color = throwRayWithoutReflection(scene, camera, i, j);
			renderer.setPixel(i, j, color);
		}
	}
}

void Raytracer::renderWithOneReflection(const Scene &scene, const Camera &camera, PNGRenderer &renderer) {
	for(int j = 0; j < camera.getScreenHeight(); j++) {
		for(int i = 0; i < camera.getScreenWidth(); i++) {
			glm::dvec4 color = throwRayWithOneReflection(scene, camera, i, j);
			renderer.setPixel(i, j, color);
		}
	}
}

void Raytracer::render(const Scene &scene, const Camera &camera, PNGRenderer &renderer, int depth) {
	for(int j = 0; j < camera.getScreenHeight(); j++) {
		for(int i = 0; i < camera.getScreenWidth(); i++) {
			glm::dvec4 color = throwRay(scene, camera, i, j, depth);
			renderer.setPixel(i, j, color);
		}
	}
}
