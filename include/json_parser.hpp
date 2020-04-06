/**
 * \file json_parser.hpp
 * \brief Methods to parse JSON files
 *
 * Module that provide the functions to parse JSON representation of displayable scene.
 *
 */

#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include "scene.hpp"
#include "camera.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "light.hpp"
#include <json/json.hpp>
#include <string>
#include <utility>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using json = nlohmann::json;

/** 
 * \class JSONParser
 * \brief Helper class to parse the JSON scene files
 */
class JSONParser {

public:

	/**
	 * Default value for the camera field of view angle in height
	 */
	static constexpr double CAMERA_DEFAULT_HEIGHT_FOV = glm::pi<double>() / 5.0;

	/**
	 * Default value for the camera up vector
	 */
	static constexpr glm::dvec3 CAMERA_DEFAULT_UP_VECTOR = glm::dvec3(0.0, 1.0, 0.0);

	/**
	 * Default value for the scene minimum rendering distance
	 */
	static constexpr double SCENE_DEFAULT_DISTANCE_NEAR = 0.1;

	/**
	 * Default value for the scene maximum rendering distance
	 */
	static constexpr double SCENE_DEFAULT_DISTANCE_FAR = 10000.0;

	/**
	 * Parse a JSON file scene
	 *
	 * TODO detail format
	 * The description file contains the scene itself and the used camera to record the scene.
	 * Then the function return a pair of the scene and the camera described in the file.
	 *
	 * \param fname : File to parse
	 * \param width : Width of the image
	 * \param height : Height of the image
	 */
	static std::pair<Scene,Camera> parse(const std::string &fname, int width, int height);
	
private:

	static Scene JSONToScene(const json &jsonScene);
	static Camera JSONToCamera(const json &jsonCamera, int width, int height);
	static Shape * JSONToShape(const json &jsonShape);
	static Box * JSONToBox(const json &jsonBox);
	static Sphere * JSONToSphere(const json &jsonSphere);
	static Light * JSONToLight(const json &jsonLight);
	static glm::dvec3 JSONToVec3(const json &jsonVec3);
	static glm::dvec4 JSONToVec4(const json &jsonVec4);

};

#endif
