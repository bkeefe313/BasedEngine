#include <iostream>

//include OpenGL Libraries
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

//method that receives errors from GLFW and relays them to the console
static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

//method that receives input events (key press and release)
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char* argv[]) {
	GLFWwindow* window;
	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;


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
	window = glfwCreateWindow(640, 480, "BasedEngine", nullptr, nullptr);
	if (!window) {
		cout << "GLFW Failed to open application window." << endl;
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions 
	glewExperimental = GL_TRUE;
	//set up GLEW and check if OK
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		cout << "GLEW failed to initialize." << endl;
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return -1;
	}

	//frame swap interval set to 1 to prevent screen tear
	glfwSwapInterval(1);

	//define vertex buffer object and bind to current array buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//create shader from C-string and compile
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//check if shader successfully compiles
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Game Loop
	while (!glfwWindowShouldClose(window)) {
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

