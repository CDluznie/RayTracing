#include "raytracer.hpp"
#include "camera.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "png_renderer.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <iostream>


int main(int argc, char **argv) {

	if(argc != 4) {
		std::cerr << "Error: bad usage" << std::endl
				  << argv[0] << " width height depth" << std::endl
				  << "\t- width: width of the image" << std::endl
				  << "\t- height: height of the image" << std::endl
		          << "\t- depth: maximum number of ray reflections" << std::endl;
		return 1;
	}

	int width = std::stoi(std::string(argv[1]));
	int height = std::stoi(std::string(argv[2]));
	int depth = std::stoi(std::string(argv[3]));

	if(width <= 0 || height <= 0) {
		std::cerr << "Error: width and height have to be strictly positive" << std::endl;
		return 1;
	}

	if(depth < 0) {
		std::cerr << "Error: depth have to be positive" << std::endl;
		return 1;
	}

	std::vector<Shape *> shapes = {
		new Box(
			glm::dvec3(-350.0, -350.0, -10.0),
			glm::dvec3(350.0, 350.0, 10.0),
			glm::dvec4(0.5, 0.5, 0.5, 1.0),
			glm::dvec4(0.1, 0.1, 0.1, 1.0),
				glm::dvec4(0.3, 0.3, 0.3, 1.0)
		),
		new Box(
			glm::dvec3(-60.0, -60.0, 30.0),
			glm::dvec3(60.0, 60.0, 150.0),
			glm::dvec4(0.1, 0.4, 0.1, 1.0),
			glm::dvec4(0.0, 0.0, 0.0, 1.0),
			glm::dvec4(0.7, 0.7, 0.7, 1.0)
		),
		new Box(
			glm::dvec3(-300.0, -330.0, 0.0),
			glm::dvec3(330.0, -310.0, 200.0),
			glm::dvec4(0.0, 1.0, 0.0, 1.0),
			glm::dvec4(0.1, 0.1, 0.1, 1.0),
			glm::dvec4(0.1, 0.1, 0.1, 1.0)
		),
		new Box(
			glm::dvec3(-330.0, -300.0, 0.0),
			glm::dvec3(-310.0, 300.0, 200.0),
			glm::dvec4(1.0, 0.0, 0.0, 1.0),
			glm::dvec4(0.1, 0.1, 0.1, 1.0),
			glm::dvec4(0.1, 0.1, 0.1, 1.0)
		),
		new Box(
			glm::dvec3(-300.0, 310.0, 0.0),
			glm::dvec3(330.0, 330.0, 200.0),
			glm::dvec4(0.0, 0.0, 1.0, 1.0),
			glm::dvec4(0.1, 0.1, 0.1, 1.0),
			glm::dvec4(0.1, 0.1, 0.1, 1.0)
		),
		new Sphere(
			glm::dvec3(50.0, -130.0, 80.0),
			40.0,
			glm::dvec4(0.0, 0.4, 0.4, 1.0),
			glm::dvec4(0.0, 0.0, 0.0, 1.0),
			glm::dvec4(1.0, 0.6, 0.6, 1.0)
		),
		new Sphere(
			glm::dvec3(-180.0, 180.0, 100.0),
			75.0,
			glm::dvec4(0.8, 0.8, 0.0, 1.0),
			glm::dvec4(0.0, 0.0, 0.0, 1.0),
			glm::dvec4(0.1, 0.1, 0.4, 1.0)
		),
		new Sphere(
			glm::dvec3(150.0, 150.0, 45.0),
			50.0,
			glm::dvec4(0.8, 0.8, 0.8, 1.0),
			glm::dvec4(0.0, 0.0, 0.0, 1.0),
			glm::dvec4(0.0, 0.2, 0.0, 1.0)
		),
		new Sphere(
			glm::dvec3(210.0, -25.0, 65.0),
			55.0,
			glm::dvec4(0.2, 0.2, 0.0, 1.0),
			glm::dvec4(0.0, 0.0, 0.0, 1.0),
			glm::dvec4(0.8, 0.8, 0.8, 1.0)
		)
	};

	std::vector<Light *> lights = {
		new Light(
			glm::dvec3(50.0, -500.0, 800.0),
			glm::dvec4(0.8, 0.8, 0.8, 1.0)
		),
		new Light(
			glm::dvec3(-350.0, 250.0, 600.0),
			glm::dvec4(0.5, 0.7, 0.5, 1.0)
		)
	};

	Scene scene = Scene(
		shapes,
		lights,
		glm::dvec4(0.3, 0.3, 0.4, 1.0),
		0.1,
		10000.0
	);

	Camera camera = Camera::create(
		glm::dvec3(700.0, 150.0, 400.0),
		glm::dvec3(0.0, 50.0, 0.0),
		glm::dvec3(0.0, 1.0, 0.0),
		glm::pi<double>() / 5.0,
		width,
		height
	);

	PNGRenderer renderer = PNGRenderer::create(camera);

	Raytracer::render(scene, camera, renderer, depth);

	renderer.save("output.png");

	return 0;

}

