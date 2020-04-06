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

	if(argc != 5) {
		std::cerr << "Error: bad usage" << std::endl
				  << argv[0] << " scene width height depth" << std::endl
				  << "\t- scene: path to the scene file" << std::endl
				  << "\t- width: width of the image" << std::endl
				  << "\t- height: height of the image" << std::endl
		          << "\t- depth: maximum number of ray reflections" << std::endl;
		return 1;
	}

	std::string inputPath = std::string(argv[1]);
	std::size_t fnamePos = inputPath.find_last_of("/")+1;
	std::string fname = inputPath.substr(fnamePos);
	std::string outputFname = fname.substr(0, fname.find(".")) + ".png";
	int width = std::stoi(std::string(argv[2]));
	int height = std::stoi(std::string(argv[3]));
	int depth = std::stoi(std::string(argv[4]));

	if(width <= 0 || height <= 0) {
		std::cerr << "Error: width and height have to be strictly positive" << std::endl;
		return 1;
	}

	if(depth < 0) {
		std::cerr << "Error: depth have to be positive" << std::endl;
		return 1;
	}

	std::pair<Scene,Camera> parsingResult = JSONParser::parse(inputPath, width, height);

	Scene scene = std::get<0>(parsingResult);
	Camera camera = std::get<1>(parsingResult);
	PNGRenderer renderer = PNGRenderer::create(camera);

	Raytracer::render(scene, camera, renderer, depth);

	renderer.save(outputFname);
	std::cout << "Result saved in " << outputFname << std::endl;

	return 0;

}

