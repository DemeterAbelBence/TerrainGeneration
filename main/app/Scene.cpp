#include "Scene.hpp"

void Scene::initializeEvents() {
	cameraTranslationEventHandler
		.addEvent(Input::Event<Camera>( new glfw::Key(GLFW_KEY_DOWN), &Camera::moveUp, -1 ));
	cameraTranslationEventHandler
		.addEvent(Input::Event<Camera>( new glfw::Key(GLFW_KEY_UP), &Camera::moveUp, 1 ));
	cameraTranslationEventHandler
		.addEvent(Input::Event<Camera>( new glfw::Key(GLFW_KEY_LEFT), &Camera::moveRight, -1 ));
	cameraTranslationEventHandler
		.addEvent(Input::Event<Camera>( new glfw::Key(GLFW_KEY_RIGHT), &Camera::moveRight, 1 ));
	cameraTranslationEventHandler
		.addEvent(Input::Event<Camera>( new glfw::Key(GLFW_KEY_Q), &Camera::moveForward, 1 ));
	cameraTranslationEventHandler
		.addEvent(Input::Event<Camera>( new glfw::Key(GLFW_KEY_W), &Camera::moveForward, -1 ));
	cameraRotationEventHandler
		.addEvent(Input::Event<Camera>( new glfw::Key(GLFW_KEY_E), &Camera::rotate, -1 ));
	cameraRotationEventHandler
		.addEvent(Input::Event<Camera>( new glfw::Key(GLFW_KEY_R), &Camera::rotate, 1 ));

	objectTransformationEventHandler
		.addEvent(Input::Event<Object>( new glfw::Key(GLFW_KEY_DOWN), &Object::translateY, -1 ));
	objectTransformationEventHandler
		.addEvent(Input::Event<Object>( new glfw::Key(GLFW_KEY_UP), &Object::translateY, 1 ));
	objectTransformationEventHandler
		.addEvent(Input::Event<Object>( new glfw::Key(GLFW_KEY_LEFT), &Object::translateX, -1 ));
	objectTransformationEventHandler
		.addEvent(Input::Event<Object>( new glfw::Key(GLFW_KEY_RIGHT), &Object::translateX, 1 ));
	objectTransformationEventHandler
		.addEvent(Input::Event<Object>( new glfw::Key(GLFW_KEY_Q), &Object::translateZ, 1 ));
	objectTransformationEventHandler
		.addEvent(Input::Event<Object>( new glfw::Key(GLFW_KEY_W), &Object::translateZ, -1 ));
}

Scene::Scene() {
	center = glm::vec3(-2.0f, 0.0f, -5.0f);
	camera = new Camera();

	initializeEvents();
}

void Scene::setPrimitiveType(unsigned int type) {
	for (const auto& object : objects)
		object->setPrimitive(type);
}

void Scene::create() {
	TesselationProgram terrainShader("Patch Shader");
	terrainShader.readFragmentSource("main/app/shaders/patchFragment.shader");
	terrainShader.readVertexSource("main/app/shaders/patchVertex.shader");
	terrainShader.readTesselationControlSource("main/app/shaders/patchTesselationControl.shader");
	terrainShader.readTesselationEvaluationSource("main/app/shaders/patchTesselationEvaluation.shader");
	Texture grassTexture("Grass texture");
	grassTexture.load("main/app/images/dirt.jpg");
	Texture dirtTexture("Dirt texture");
	dirtTexture.load("main/app/images/rock.jpg");
	Texture rockTexture("Rock texture");
	rockTexture.load("main/app/images/rock.jpg");
	Texture snowTexture("Snow texture");
	snowTexture.load("main/app/images/snow.jpg");

	terrain = new Terrain(32);
	terrain->setSize(10.0f);
	terrain->setNewTesselationProgram(terrainShader);
	terrain->addNewTexture(grassTexture);
	terrain->addNewTexture(dirtTexture);
	terrain->addNewTexture(rockTexture);
	terrain->addNewTexture(snowTexture);
	terrain->setCenter(center + glm::vec3(-2.0f, -1.0f, -5.0f));
	terrain->create();

	GpuProgram sunShader("Sun Shader");
	sunShader.readFragmentSource("main/app/shaders/sunFragment.shader");
	sunShader.readVertexSource("main/app/shaders/sunVertex.shader");

	sun = new Sun(10, 10, center + glm::vec3(5.0f, 5.0f, -10.0f));
	sun->setNewProgram(sunShader);
	sun->setSize(1.0f);
	sun->setRadius(0.2f);
	sun->create();

	objects.push_back(terrain);
	objects.push_back(sun);
}

void Scene::draw() const {
	camera->setUniforms(*sun->getProgram());
	camera->setUniforms(*terrain->getProgram());

	sun->setUniformLight(*terrain->getProgram());
	terrain->setUniformParameters(*terrain->getProgram());

	for (const auto& object : objects)
		object->draw();
}

void Scene::update(GLFWwindow* window) {
	if (object_index > 0) {
		objectTransformationEventHandler.setEventParamValue(move_speed);
		objectTransformationEventHandler.handleEvents(window, objects[object_index]);
	} 
	else {
		cameraTranslationEventHandler.setEventParamValue(move_speed);
		if (cameraTranslationEventHandler.handleEvents(window, camera))
			camera->resetView();

		cameraRotationEventHandler.setEventParamValue(rotate_speed);
		if (cameraRotationEventHandler.handleEvents(window, camera))
			camera->resetView();
	}
}

Scene::~Scene() {
	delete camera;
}
