#include "raytracer.hpp"
#include "camera.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "json_parser.hpp"
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

	std::pair<Scene,Camera> parsingResult = JSONParser::parse("../scenes/scene_1.json", width, height);

	Scene scene = std::get<0>(parsingResult);
	Camera camera = std::get<1>(parsingResult);
	PNGRenderer renderer = PNGRenderer::create(camera);

	Raytracer::render(scene, camera, renderer, depth);

	renderer.save("output.png");

	return 0;

}

