#include "json_parser.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include <fstream>

using json = nlohmann::json;

std::pair<Scene,Camera> JSONParser::parse(const std::string &fname, int width, int height) {
	json jsonScene;
	std::ifstream sceneFile(fname);
	sceneFile >> jsonScene;
	sceneFile.close();
	return std::make_pair(
		JSONToScene(jsonScene["scene"]),
		JSONToCamera(jsonScene["camera"], width, height)
	);
}

Scene JSONParser::JSONToScene(const json &jsonScene) {
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

		return Scene(
			shapes,
			lights,
			JSONToVec4(jsonScene["backgroundColor"]),
			SCENE_DEFAULT_DISTANCE_NEAR,
			SCENE_DEFAULT_DISTANCE_FAR
		);
}

Camera JSONParser::JSONToCamera(const json &jsonCamera, int width, int height) {
	return Camera::create(
		JSONToVec3(jsonCamera["position"]),
		JSONToVec3(jsonCamera["target"]),
		glm::dvec3(CAMERA_DEFAULT_UP_VECTOR),
		CAMERA_DEFAULT_HEIGHT_FOV,
		width,
		height
	);
}

glm::dvec3 JSONParser::JSONToVec3(const json &jsonVec3) {
	return glm::dvec3(jsonVec3[0], jsonVec3[1], jsonVec3[2]);
}

glm::dvec4 JSONParser::JSONToVec4(const json &jsonVec4) {
	return glm::dvec4(jsonVec4[0], jsonVec4[1], jsonVec4[2], jsonVec4[3]);
}