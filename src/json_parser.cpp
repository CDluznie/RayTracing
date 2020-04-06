#include "json_parser.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include <fstream>
#include <string>
#include <stdexcept>


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
	std::vector<Shape *> shapes;
	for (auto &jsonShape : jsonScene["shapes"]) {
		shapes.push_back(JSONToShape(jsonShape));
	}
	std::vector<Light *> lights;
	for (auto &jsonLight : jsonScene["lights"]) {
		lights.push_back(JSONToLight(jsonLight));
	}
	Scene scene = Scene(
		shapes,
		lights,
		JSONToVec4(jsonScene["backgroundColor"]),
		SCENE_DEFAULT_DISTANCE_NEAR,
		SCENE_DEFAULT_DISTANCE_FAR
	);
	for (Shape * shape : shapes) {
		delete shape;
	}
	shapes.clear();
	for (Light * light : lights) {
		delete light;
	}
	lights.clear();
	return scene;
}

Shape * JSONParser::JSONToShape(const json &jsonShape) {
	std::string shape = jsonShape["shape"];
	if (shape == "sphere") {
		return JSONToSphere(jsonShape);
	}
	if (shape == "box") {
		return JSONToBox(jsonShape);
	}
	throw std::invalid_argument(shape + " is not a valid shape");
}

Box * JSONParser::JSONToBox(const json &jsonBox) {
	return new Box(
		JSONToVec3(jsonBox["boxMin"]),
		JSONToVec3(jsonBox["boxMax"]),
		JSONToVec4(jsonBox["color"]),
		JSONToVec4(jsonBox["emissive"]),
		JSONToVec4(jsonBox["reflect"])
	);
}

Sphere * JSONParser::JSONToSphere(const json &jsonSphere) {
	return new Sphere(
		JSONToVec3(jsonSphere["center"]),
		jsonSphere["radius"],
		JSONToVec4(jsonSphere["color"]),
		JSONToVec4(jsonSphere["emissive"]),
		JSONToVec4(jsonSphere["reflect"])
	);
}

Light * JSONParser::JSONToLight(const json &jsonLight) {
	new Light(
		JSONToVec3(jsonLight["position"]),
		JSONToVec4(jsonLight["color"])
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
