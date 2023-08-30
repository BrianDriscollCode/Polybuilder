#include "Drawer.h"
#include "CommonIncludes.h"

void checkShaderCompilation(unsigned int shader)
{
	char typeShader[5] = "type";

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else 
	{
		std::cout << typeShader << " shader compiled successfully!" << std::endl;
	}
}


void draw()
{

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f
	};

	// Managing vertex data memory usage via "vertex buffer objects (VBO)"
	// Allows for sending large batches of vertex data
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// Binds the newly created buffer to type "GL_ARRAY_BUFFER" <- one of many types
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Copies the previously defined data to the buffer's memory
	// (type, size(bytes), vertexData, dataManagementType)
	// Types of ways to manage data:
	//		1. GL_STREAM_DRAW -  the data is set only once and used by the GPU at most a few times.
	//		2. GL_STATIC_DRAW: the data is set only once and used many times.
	//		3. GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Creating the shader via GLSL
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// Create Shader Object and declare its type
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Attach the shader source to the shader object then compile
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	checkShaderCompilation(vertexShader);

	// Create Fragment Shader
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	// Create Shader Object and declare its type
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Attach the shader source to the shader object then compile
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	checkShaderCompilation(fragmentShader);

	// Create the shader program and link multiple shaders
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	//Check program compilation, make neat later...
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//activate program
	glUseProgram(shaderProgram);

	// delete individual shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Instructing OpenGL how to interpret the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// ..:: Initialization code (done once (unless your object frequently changes)) :: ..
// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


