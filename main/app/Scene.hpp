#pragma once

#include "src/util/gl/GpuProgram.hpp"
#include "src/util/gl/TesselationProgram.hpp"
#include "src/util/gl/VertexArray.hpp"
#include "src/util/Object.hpp"
#include "src/Input.hpp"
#include "src/util/datatypes/Material.hpp"

#include "src/Camera.hpp"
#include "src/Sun.hpp"
#include "Terrain.hpp"

class Scene {

private:
	Sun* sun;
	Terrain* terrain;
	Camera* camera;

private:
	glm::vec3 center;
	std::vector<Object*> objects;
	Input::InputHandler<Camera> cameraTranslationEventHandler;
	Input::InputHandler<Camera> cameraRotationEventHandler;
	Input::InputHandler<Object> objectTransformationEventHandler;

private:
	float move_speed = 0.0f;
	float rotate_speed = 0.0f;
	unsigned int object_index = 0;

private:
	void initializeEvents();

public:
	Scene();

	inline void setObjectIndex(unsigned int value) { object_index = value; }
	inline void setMoveSpeed(float value) { move_speed = value; }
	inline void setRotateSpeed(float value) { rotate_speed = value; }
	inline Camera* getCamera() const { return camera; }
	inline Terrain* getTerrain() const { return terrain; }

	void setPrimitiveType(unsigned int type);

	void create();
	void draw() const;
	void update(GLFWwindow* window);

	~Scene();	
};