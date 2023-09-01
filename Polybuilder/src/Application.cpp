#include "Application.h"
#include "CommonIncludes.h"


void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

// Called each time the window resizes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void initializeGLFW() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


void draw();
unsigned int setShaderProgram();
unsigned int setVerticesAndIndices();

// Initialize Window 
int window(void)
{
	// Create Window Object
	GLFWwindow* window = glfwCreateWindow(800, 600, "Polybuilder", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Checking if Glad is initialized
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// For resizing
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	unsigned int shaderProgram = setShaderProgram();
	unsigned int VAO = setVerticesAndIndices();

	std::cout << "Render starting!" << std::endl;
	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// takes user input
		processInput(window);

		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Drawer.cpp
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 5, 3);

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;

}


//start application
void start() {
	bool status = true;
	std::cout << "Welcome to Polybuilder!" << std::endl;
	initializeGLFW();
    window();
}