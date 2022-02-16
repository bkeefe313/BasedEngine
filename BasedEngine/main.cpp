#include <iostream>

//include OpenGL Libraries
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

int main(int argc, char* argv[]) {
	//check if glfw initializes OK
	if (!glfwInit()) {
		cout << "GLFW Initialization failed." << endl;
		glfwTerminate();
		return -1;
	}

	//create window and check if created OK
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", nullptr, nullptr);
	if (!window) {
		cout << "GLFW Failed to open application window." << endl;
		return -1;
	}

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions 
	glewExperimental = GL_TRUE;
	//set up GLEW and check if OK
	GLenum err = glewInit();
	if (GLEW_OK == err) {
		cout << "GLEW failed to initialize." << endl;
		return -1;
	}

	//Game Loop
	while (!glfwWindowShouldClose(window)) {

	}

	return 0;
}