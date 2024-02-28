#include "Application.hpp"

GLFWwindow* Application::window = nullptr;
Scene* Application::scene = nullptr;

GLFWwindow* Application::initGlfwWindow(const char* windowName) {
    if (!glfwInit())
        throw "Glfw initialization error!\n";

    GLFWwindow* window;
    window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw "Glfw window creation error!\n";
    }
    glfwMakeContextCurrent(window);
    return window;
}

void Application::initOpenGl() {
    GLenum err = glewInit();
    std::cout << "Glew message: " << glewGetErrorString(err) << std::endl << std::endl;
    Debug::displayOpenGlInfo();
    Debug::initializeDebugContext();

    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    glDebugMessageCallback(&Debug::outputDebugMessage, (const void*)NULL);
}

void Application::initialize() {
    window = initGlfwWindow("TerrainGeneration");
    initOpenGl();

    scene = new Scene();
    scene->create();

    Gui::initialize(window, scene);
}

void Application::render() {
    float currentTime = 0;
    float previousTime = 0;
    float deltaTime = 0;
    const int FPS = 300;
    const float frameTime = (float)1000 / FPS; 

    while (!glfwWindowShouldClose(window)) {
        previousTime = currentTime;
        glfwPollEvents();
        glViewport(0, 0, sceneWidth, sceneHeight);
        glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        scene->update(window);
        scene->draw();

        Gui::render(sceneWidth, windowWidth, windowHeight);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        currentTime = glfwGetTime();
        deltaTime = (currentTime - previousTime);
       /* if (frameTime - deltaTime > 0)
            Sleep(frameTime - deltaTime);*/
    } 
}

void Application::close() {
    delete scene;
    glfwTerminate();
}