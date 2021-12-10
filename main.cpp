#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VBO.h"
#include"EBO.h"
#include"VAO.h"
#include"Texture.h"
#include"Camera.h"
#include"Cylinder.h"

//Initial setup of code to use GLFW provided by Victor Gordon and found at this link https://www.youtube.com/watch?v=45MIykWJ-C4

const float PI = 3.1415926f;

int width = 800;
int height = 800;

glm::vec3 shoulderPos = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 upperPos = glm::vec3(5.0f, 5.0f, 5.0f);
glm::vec3 forearmPos = glm::vec3(2.5f, 2.5f, 2.5f);
glm::vec3 handPos = glm::vec3(1.25f, 1.25f, 1.25f);

// Top Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom
	0, 2, 3 // Bottom
};

GLfloat frontVertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f
};

GLuint frontIndices[] = {
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] = {
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};



//Cylinder x = r * cos theta, y = r * sin theta, z = h/2 or -h/2


int main() {
	//Initialize
	glfwInit();
	//Tell GLFW what version of OpenGL we are using and what functionalities to use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create the window
	GLFWwindow* window = glfwCreateWindow(800, 800, "Test", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Add window to context
	glfwMakeContextCurrent(window);
	//Load openGL
	gladLoadGL();
	//Esablish the size of the viewport
	glViewport(0, 0, width, height);


	//Creates the shader program for rendering
	Shader shaderProgram("default.vert", "default.frag");

	Shader cubeShader("cube.vert", "cube.vert");

	//Cylinder shoulder = Cylinder(shoulderPos.x, shoulderPos.y, shoulderPos.z, 36, 8, true);

	//Creates and Binds the Vertex Array
	VAO VAO1;
	VAO1.Bind();

	//Creates and Binds Vertex Buffer and Element Buffers
	VBO VBO1( vertices, sizeof(vertices));
	EBO EBO1( indices, sizeof(indices));

	VBO1.Bind();
	EBO1.Bind();

	//int stride = shoulder.getInterleavedStride();
	int stride = 11 * sizeof(float);

	//Links Vertex Buffer to Vertex Array
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, stride, (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, stride, (void*)(8 * sizeof(float)));

	//Unbinds everything
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO VAO2;
	VAO2.Bind();

	//Creates and Binds Vertex Buffer and Element Buffers
	VBO VBO2(frontVertices, sizeof(frontVertices));
	EBO EBO2(frontIndices, sizeof(frontIndices));

	VBO2.Bind();
	EBO2.Bind();

	VAO2.LinkAttrib(VBO1, 0, 3, GL_FLOAT, stride, (void*)0);
	VAO2.LinkAttrib(VBO1, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO1, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));
	VAO2.LinkAttrib(VBO1, 3, 3, GL_FLOAT, stride, (void*)(8 * sizeof(float)));

	//Unbinds everything
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	glm::mat4 cybeView 

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	cubeShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr)

	Texture testTexture("GrandpaOwens.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	testTexture.texUnit(shaderProgram, "tex0", 0);

	GLuint cubeID;
	glGenTextures(2, &cubeID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeID);

	std::string texturesFiles[6] = {"GrandpaOwens.png", "Besh.jpg", "car.png", "whiteSquare.png", "whiteSquare.png", "whiteSquare.png"};

	int width, height, nrChannels;
	unsigned char* data;

	data = stbi_load(texturesFiles[0].c_str(), &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	data = stbi_load(texturesFiles[1].c_str(), &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	data = stbi_load(texturesFiles[2].c_str(), &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	data = stbi_load(texturesFiles[3].c_str(), &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);

	data = stbi_load(texturesFiles[4].c_str(), &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_BLUE, GL_UNSIGNED_BYTE, data);

	data = stbi_load(texturesFiles[5].c_str(), &width, &height, &nrChannels, 0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_GREEN, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	glfwSwapBuffers(window);
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	

	//Keep screen open while not closed
	while (!glfwWindowShouldClose(window)) {
		//Set color each frame
		glClearColor(.07f, .13f, .17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		camera.Inputs(window);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		//Use the shader to draw a triangle
		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");

		testTexture.Bind();
		VAO1.Bind();
		
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, (void*)0);

		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(frontIndices) / sizeof(int), GL_UNSIGNED_INT, (void*)0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, (void*)0);

		//swap window buffers
		glfwSwapBuffers(window);
		
		//Process events on the window
		glfwPollEvents();
	}

	//Close vertex arrays and the shader program
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	testTexture.Delete();
	shaderProgram.Delete();

	//Close the window and end the rendering
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


