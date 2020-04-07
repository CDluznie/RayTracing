/**
 * \file raytracer.hpp
 * \brief Methods to compute the raytracing
 *
 * Module that provide the ray tracing function.
 *
 */

#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

#include "scene.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "ray.hpp"
#include "png_renderer.hpp"
#include <glm/glm.hpp>

/** 
 * \class Raytracer
 * \brief Helper class to compute the result of the ray tracing
 */
class Raytracer {

public:

	/**
	 * Render a scene with a ray tracing algorithm
	 * \param scene : Scene to render
	 * \param camera : Camera used to film the scene
	 * \param renderer : Renderer used to register the result
	 * \param depth : Maximum number of ray reflections
	 */
	static void render(const Scene &scene, const Camera &camera, PNGRenderer &renderer, int depth);
	
	/**
	 * Render a scene with a ray tracing by displaying only the normals
	 *
	 * This function have been implemented for debugging purpose.
	 *
	 * \param scene : Scene to render
	 * \param camera : Camera used to film the scene
	 * \param renderer : Renderer used to register the result
	 */
	static void renderNormals(const Scene &scene, const Camera &camera, PNGRenderer &renderer);


	/**
	 * Render a scene with a ray tracing algorithm without any reflection
	 *
	 * This function have been implemented for debugging purpose.
	 *
	 * \param scene : Scene to render
	 * \param camera : Camera used to film the scene
	 * \param renderer : Renderer used to register the result
	 */
	static void renderWithoutReflection(const Scene &scene, const Camera &camera, PNGRenderer &renderer);

	/**
	 * Render a scene with a ray tracing algorithm with at most only one reflection
	 *
	 * This function have been implemented for debugging purpose.
	 *
	 * \param scene : Scene to render
	 * \param camera : Camera used to film the scene
	 * \param renderer : Renderer used to register the result
	 */
	static void renderWithOneReflection(const Scene &scene, const Camera &camera, PNGRenderer &renderer);


private:

	static glm::dvec4 throwRayForNormals(const Scene &scene, const Camera &camera, int px, int py);
	static glm::dvec4 throwRayWithoutReflection(const Scene &scene, const Camera &camera, int px, int py);
	static glm::dvec4 throwRayWithOneReflection(const Scene &scene, const Camera &camera, int px, int py);
	static glm::dvec4 throwRay(const Scene &scene, const Camera &camera, int px, int py, int depth);
	static glm::dvec4 followRay(const Scene &scene, const Ray &ray, const Shape *shape, const glm::dvec3 &point, int depth);
	static Ray initialRay(const Camera &camera, int px, int py, double distanceNear);

};

#endif
