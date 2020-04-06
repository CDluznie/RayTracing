#include "sphere.hpp"


Sphere::Sphere(const glm::dvec3 &center, double radius, const glm::dvec4 &color, const glm::dvec4 &emissive, const glm::dvec4 &reflect) :
Shape(color, emissive, reflect),
_center(center),
_radius(radius) {

}

Shape * Sphere::copy() const {
	return new Sphere(
		_center,
		_radius,
		getColor(),
		getEmissive(),
		getReflect()
	);
}

glm::dvec3 Sphere::normal(const glm::dvec3 &point) const {
	return (_center - point)/_radius;
}

std::vector<double> Sphere::intersect(const Ray &ray) const {
	glm::dvec3 oc = ray.getOrigin() - _center;
    double a = glm::dot(ray.getVector(), ray.getVector());
    double b = 2.0 * glm::dot(oc, ray.getVector());
    double c = glm::dot(oc,oc) - _radius*_radius;
    double delta = b*b - 4*1*c;
    if (delta <= 0) {
		return {};
	}
    double t1 = (-b - sqrt(delta))/2;
	double t2 = (-b + sqrt(delta))/2;
    return {t1, t2};
}
