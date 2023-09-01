#include "Drawer.h"
#include "CommonIncludes.h"

float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

unsigned int VBO, VAO, EBO;

unsigned int setVerticesAndIndices() {
	std::cout << "Set VBO, VAO, and EBO!" << std::endl;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    return VAO;
}

//void draw(unsigned int shaderProgram) {
//    glUseProgram(shaderProgram);
//    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//    //glDrawArrays(GL_TRIANGLES, 0, 6);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//}


//void checkShaderCompilation(unsigned int shader)
//{
//	char typeShader[5] = "type";
//
//	int success;
//	char infoLog[512];
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//
//	if (!success)
//	{
//		glGetShaderInfoLog(shader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	else 
//	{
//		std::cout << typeShader << " shader compiled successfully!" << std::endl;
//	}
//}
//
//unsigned int createVertexShader() {
//	// Creating the shader via GLSL
//	const char* vertexShaderSource = "#version 330 core\n"
//		"layout (location = 0) in vec3 aPos;\n"
//		"void main()\n"
//		"{\n"
//		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//		"}\0";
//
//	// Create Shader Object and declare its type
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//	// Attach the shader source to the shader object then compile
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	return vertexShader;
//}
//
//unsigned int createFragmentShader() {
//	// Create Fragment Shader
//	const char* fragmentShaderSource = "#version 330 core\n"
//		"out vec4 FragColor;\n"
//		"void main()\n"
//		"{\n"
//		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//		"}\0";
//
//	// Create Shader Object and declare its type
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//	// Attach the shader source to the shader object then compile
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	return fragmentShader;
//}
//
//void linkShaderProgram(unsigned int shaderProgram, unsigned int vertexShader, unsigned int fragmentShader) {
//	// Create the shader program and link multiple shaders
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	//Check program compilation, make neat later...
//	int success;
//	char infoLog[512];
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//}
//
//
//
//void draw()
//{
//
//	float vertices[] = {
//	 0.5f,  0.5f, 0.0f,  // top right
//	 0.5f, -0.5f, 0.0f,  // bottom right
//	-0.5f, -0.5f, 0.0f,  // bottom left
//	-0.5f,  0.5f, 0.0f   // top left 
//	};
//	unsigned int indices[] = {  // note that we start from 0!
//		0, 1, 3,   // first triangle
//		1, 2, 3    // second triangle
//	};
//
//	// Allows for sending large batches of vertex data
//
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	unsigned int vertexShader = createVertexShader();
//	unsigned int fragmentShader = createFragmentShader();
//
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	// Create the shader program and link multiple shaders
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//	linkShaderProgram(shaderProgram, vertexShader, fragmentShader);
//
//
//	//activate program
//	glUseProgram(shaderProgram);
//
//	// delete individual shaders
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	// Instructing OpenGL how to interpret the vertex data
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	unsigned int VAO;
//	glGenVertexArrays(1, &VAO);
//
//	// ..:: Initialization code (done once (unless your object frequently changes)) :: ..
//// 1. bind Vertex Array Object
//	glBindVertexArray(VAO);
//	// 2. copy our vertices array in a buffer for OpenGL to use
//	unsigned int VBO;
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// Copies the previously defined data to the buffer's memory
//	// (type, size(bytes), vertexData, dataManagementType)
//	// Types of ways to manage data:
//	//		1. GL_STREAM_DRAW -  the data is set only once and used by the GPU at most a few times.
//	//		2. GL_STATIC_DRAW: the data is set only once and used many times.
//	//		3. GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	// 3. then set our vertex attributes pointers
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// Draw the object
//	glUseProgram(shaderProgram);
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}


