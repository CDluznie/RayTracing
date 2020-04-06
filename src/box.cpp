#include "box.hpp"
#include <vector>
#include <algorithm>
#include <glm/gtx/component_wise.hpp>

Box::Box(const glm::dvec3 &boxMin, const glm::dvec3 &boxMax, const glm::dvec4 &color, const glm::dvec4 &emissive, const glm::dvec4 &reflect) :
Shape(color, emissive, reflect),
_boxMin(boxMin),
_boxMax(boxMax) {

}

Shape * Box::copy() const {
	return new Box(
		_boxMin,
		_boxMax,
		getColor(),
		getEmissive(),
		getReflect()
	);
}

glm::dvec3 Box::normal(const glm::dvec3 &point) const {
	glm::dvec3 centerBox(
		(_boxMin.x + _boxMax.x)/2,
		(_boxMin.y + _boxMax.y)/2,
		(_boxMin.z + _boxMax.z)/2
	);
	int nb_faces = 6;
	std::vector<glm::dvec3> faceCenters = {
		glm::dvec3(_boxMin.x, centerBox.y, centerBox.z),
		glm::dvec3(_boxMax.x, centerBox.y, centerBox.z),
		glm::dvec3(centerBox.x, _boxMin.y, centerBox.z),
		glm::dvec3(centerBox.x, _boxMax.y, centerBox.z),
		glm::dvec3(centerBox.x, centerBox.y, _boxMin.z),
		glm::dvec3(centerBox.x, centerBox.y, _boxMax.z),
	};
	std::vector<glm::dvec3> faceNormals = {
		glm::dvec3(1, 0, 0),
		glm::dvec3(-1, 0, 0),
		glm::dvec3(0, 1, 0),
		glm::dvec3(0, -1, 0),
		glm::dvec3(0, 0, 1),
		glm::dvec3(0, 0, -1),
	};
	double distance = glm::compMax(_boxMax - _boxMin);
	int index_closest_face = -1;
	for (int index_face = 0; index_face < nb_faces; index_face++) {
		glm::dvec3 facePoint = point - faceCenters[index_face];
		double distanceFacePoint = glm::compMin(glm::abs(facePoint));
		if (distanceFacePoint < distance) {
			index_closest_face = index_face;
			distance = distanceFacePoint;
		}
	}
	return faceNormals[index_closest_face];
}

std::vector<double> Box::intersect(const Ray &ray) const {
	glm::dvec3 rayOrigin = ray.getOrigin();
	glm::dvec3 rayVector = ray.getVector();
	glm::dvec3 invdir(
		1/rayVector.x,
		1/rayVector.y,
		1/rayVector.z
	);
	int sign[3] = {rayVector.x <= 0, rayVector.y <= 0, rayVector.z <= 0};
	double boundsx[2] = {_boxMin.x, _boxMax.x};
	double boundsy[2] = {_boxMin.y, _boxMax.y};
	double boundsz[2] = {_boxMin.z, _boxMax.z};
	double txmin = (boundsx[sign[0]] - rayOrigin.x) * invdir.x;
	double txmax = (boundsx[1-sign[0]] - rayOrigin.x) * invdir.x;
	double tymin = (boundsy[sign[1]] - rayOrigin.y) * invdir.y;
	double tymax = (boundsy[1-sign[1]] - rayOrigin.y) * invdir.y;
	double tzmin = (boundsz[sign[2]] - rayOrigin.z) * invdir.z;
	double tzmax = (boundsz[1-sign[2]] - rayOrigin.z) * invdir.z;
	double tmin = txmin;
	double tmax = txmax;
	if (tmin >= tmax) {
		return {};
	}
	if ((tmin > tymax) || (tymin > tmax)) { 
		return {};
	}
	if (tymin > tmin) {
		tmin = tymin;
	}
	if (tymax < tmax) {
		tmax = tymax;
	}
	if ((tmin > tzmax) || (tzmin > tmax)) { 
		return {};
	}
	if (tzmin > tmin) {
		tmin = tzmin;
	}
	if (tzmax < tmax) {
		tmax = tzmax;
	}
	return {tmin, tmax};
}
