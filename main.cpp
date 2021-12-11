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

GLfloat cubeX = 0.0f;
GLfloat cubeY = 0.0f;
GLfloat cubeZ = 0.0f;
// Vertices coordinates
GLfloat verticesLeft[] =
{ //     COORDINATES								/        COLORS          /    TexCoord   /        NORMALS       //
	cubeX - 1.0f, cubeY - 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f, //0
	cubeX - 1.0f, cubeY - 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f, //1
	cubeX - 1.0f, cubeY + 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f, //2
	cubeX - 1.0f, cubeY + 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f  //3
};
GLfloat verticesRight[] =
{ //     COORDINATES								/        COLORS          /    TexCoord   /        NORMALS       //
	cubeX + 1.0f, cubeY - 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f, //4
	cubeX + 1.0f, cubeY - 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f, //5
	cubeX + 1.0f, cubeY + 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		1.0f, 0.0f, 0.0f, //6
	cubeX + 1.0f, cubeY + 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f  //7
};
GLfloat verticesTop[] =
{ //     COORDINATES								/        COLORS          /    TexCoord   /        NORMALS       //
	cubeX - 1.0f, cubeY + 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f, //2
	cubeX - 1.0f, cubeY + 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f, //3
	cubeX + 1.0f, cubeY + 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f, //6
	cubeX + 1.0f, cubeY + 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f  //7
};
GLfloat verticesBottom[] =
{ //     COORDINATES								/        COLORS          /    TexCoord   /        NORMALS       //
	cubeX - 1.0f, cubeY - 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f, //0
	cubeX - 1.0f, cubeY - 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f, //1
	cubeX + 1.0f, cubeY - 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f, //4
	cubeX + 1.0f, cubeY - 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f  //5
};
GLfloat verticesFront[] =
{ //     COORDINATES								/        COLORS          /    TexCoord   /        NORMALS       //
	cubeX - 1.0f, cubeY - 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f, //0
	cubeX - 1.0f, cubeY + 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f, //2
	cubeX + 1.0f, cubeY - 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, -1.0f, //4
	cubeX + 1.0f, cubeY + 1.0f,  cubeZ - 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f  //6
};
GLfloat verticesBack[] =
{ //     COORDINATES								/        COLORS          /    TexCoord   /        NORMALS       //
	cubeX - 1.0f, cubeY - 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f, //1
	cubeX - 1.0f, cubeY + 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f, //3
	cubeX + 1.0f, cubeY - 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f, //5
	cubeX + 1.0f, cubeY + 1.0f,  cubeZ + 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f  //7
};


// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom
	1, 2, 3 // Bottom
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

	//Cylinder shoulder = Cylinder(shoulderPos.x, shoulderPos.y, shoulderPos.z, 36, 8, true);

//Left Square
	//Creates and Binds the Vertex Array
	VAO VAO1;
	VAO1.Bind();

	//Creates and Binds Vertex Buffer and Element Buffers
	VBO VBO1( verticesLeft, sizeof(verticesLeft));
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

//Right Square
	VAO VAO2;
	VAO2.Bind();

	//Creates and Binds Vertex Buffer and Element Buffers
	VBO VBO2( verticesRight, sizeof(verticesRight));
	EBO EBO2( indices, sizeof(indices));

	VBO2.Bind();
	EBO2.Bind();

	//int stride = shoulder.getInterleavedStride();
	stride = 11 * sizeof(float);

	//Links Vertex Buffer to Vertex Array
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, stride, (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 3, 3, GL_FLOAT, stride, (void*)(8 * sizeof(float)));

	//Unbinds everything
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();


//Top Square
	VAO VAO3;
	VAO3.Bind();

	//Creates and Binds Vertex Buffer and Element Buffers
	VBO VBO3( verticesTop, sizeof(verticesTop));
	EBO EBO3( indices, sizeof(indices));

	VBO3.Bind();
	EBO3.Bind();

	//int stride = shoulder.getInterleavedStride();
	stride = 11 * sizeof(float);

	//Links Vertex Buffer to Vertex Array
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, stride, (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 3, 3, GL_FLOAT, stride, (void*)(8 * sizeof(float)));

	//Unbinds everything
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();


//Bottom Square
	VAO VAO4;
	VAO4.Bind();

	//Creates and Binds Vertex Buffer and Element Buffers
	VBO VBO4( verticesBottom, sizeof(verticesBottom));
	EBO EBO4( indices, sizeof(indices));

	VBO4.Bind();
	EBO4.Bind();

	//int stride = shoulder.getInterleavedStride();
	stride = 11 * sizeof(float);

	//Links Vertex Buffer to Vertex Array
	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, stride, (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 3, 3, GL_FLOAT, stride, (void*)(8 * sizeof(float)));

	//Unbinds everything
	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();


//Front Square
	VAO VAO5;
	VAO5.Bind();

	//Creates and Binds Vertex Buffer and Element Buffers
	VBO VBO5( verticesFront, sizeof(verticesFront));
	EBO EBO5( indices, sizeof(indices));

	VBO5.Bind();
	EBO5.Bind();

	//int stride = shoulder.getInterleavedStride();
	stride = 11 * sizeof(float);

	//Links Vertex Buffer to Vertex Array
	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, stride, (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 3, 3, GL_FLOAT, stride, (void*)(8 * sizeof(float)));

	//Unbinds everything
	VAO5.Unbind();
	VBO5.Unbind();
	EBO5.Unbind();


//Back Square
	VAO VAO6;
	VAO6.Bind();

	//Creates and Binds Vertex Buffer and Element Buffers
	VBO VBO6( verticesBack, sizeof(verticesBack));
	EBO EBO6( indices, sizeof(indices));

	VBO6.Bind();
	EBO6.Bind();

	//int stride = shoulder.getInterleavedStride();
	stride = 11 * sizeof(float);

	//Links Vertex Buffer to Vertex Array
	VAO6.LinkAttrib(VBO6, 0, 3, GL_FLOAT, stride, (void*)0);
	VAO6.LinkAttrib(VBO6, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 3, 3, GL_FLOAT, stride, (void*)(8 * sizeof(float)));

	//Unbinds everything
	VAO6.Unbind();
	VBO6.Unbind();
	EBO6.Unbind();






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

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	Texture textureLeft("GrandpaOwens.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	Texture textureRight("Besh.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	Texture textureTop("car.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	Texture textureBottom("toadnohat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	Texture textureFront("", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE, 1);
	Texture textureBack("", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE, 2);
	textureLeft.texUnit(shaderProgram, "tex0", 0);
	textureRight.texUnit(shaderProgram, "tex0", 0);
	textureTop.texUnit(shaderProgram, "tex0", 0);
	textureBottom.texUnit(shaderProgram, "tex0", 0);
	textureFront.texUnit(shaderProgram, "tex0", 0);
	textureBack.texUnit(shaderProgram, "tex0", 0);


	glfwSwapBuffers(window);
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 10.0f));

	float rot = 1.0f;

	//Keep screen open while not closed
	while (!glfwWindowShouldClose(window)) {
		//Set color each frame
		glClearColor(.07f, .13f, .17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		camera.Inputs(window);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		
		//Use the shader to draw a triangle
		shaderProgram.Activate();
		
		
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				pyramidModel = glm::rotate(pyramidModel, glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));
			}
			else {
				pyramidModel = glm::rotate(pyramidModel, glm::radians(-rot), glm::vec3(1.0f, 0.0f, 0.0f));
			}
		}

		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				pyramidModel = glm::rotate(pyramidModel, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else {
				pyramidModel = glm::rotate(pyramidModel, glm::radians(-rot), glm::vec3(0.0f, 1.0f, 0.0f));
			}
		}

		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				pyramidModel = glm::rotate(pyramidModel, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
			}
			else {
				pyramidModel = glm::rotate(pyramidModel, glm::radians(-rot), glm::vec3(0.0f, 0.0f, 1.0f));
			}
		}

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (lightColor.x + .01f > 1.0f) {
					lightColor.x = 1.0f;
				}
				else {
					lightColor.x += .01f;
				}
			}
			else {
				if (lightColor.x - .01f < 0.0f) {
					lightColor.x = 0.0f;
				}
				else {
					lightColor.x -= .01f;
				}
			}
		}

		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (lightColor.y + .01f > 1.0f) {
					lightColor.y = 1.0f;
				}
				else {
					lightColor.y += .01f;
				}
			}
			else {
				if (lightColor.y - .01f < 0.0f) {
					lightColor.y = 0.0f;
				}
				else {
					lightColor.y -= .01f;
				}
			}
		}

		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (lightColor.z + .01f > 1.0f) {
					lightColor.z = 1.0f;
				}
				else {
					lightColor.z += .01f;
				}
			}
			else {
				if (lightColor.z - .01f < 0.0f) {
					lightColor.z = 0.0f;
				}
				else {
					lightColor.z -= .01f;
				}
			}
		}

		lightPos = camera.Position + camera.lightOffset;
		lightModel = translate(lightModel, lightPos);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));

		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		camera.Matrix(shaderProgram, "camMatrix");

		//left
		textureLeft.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, (void*)0);
		textureLeft.Unbind();
		//right
		textureRight.Bind();
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, (void*)0);
		textureRight.Unbind();
		//top
		textureTop.Bind();
		VAO3.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, (void*)0);
		textureTop.Unbind();
		//bottom
		textureBottom.Bind();
		VAO4.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, (void*)0);
		textureBottom.Unbind();
		//front
		textureFront.Bind();
		VAO5.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, (void*)0);
		textureFront.Unbind();
		//back
		textureBack.Bind();
		VAO6.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, (void*)0);
		textureBack.Unbind();

		lightShader.Activate();

		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));

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
	textureLeft.Delete();
	textureRight.Delete();
	textureTop.Delete();
	textureBottom.Delete();
	textureFront.Delete();
	textureBack.Delete();
	shaderProgram.Delete();

	//Close the window and end the rendering
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


