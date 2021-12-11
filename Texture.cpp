#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType, int mmType)
{
	// Assigns the type of the texture ot the texture object
	type = texType;

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	unsigned char mmRed[256 * 256 * 3];
	for (int i = 0; i < 256 * 256 * 3; i++) {
		if (i % 3 == 0) mmRed[i] = 255;
		else mmRed[i] = 0;
	}
	unsigned char mmGreen[256 * 256 * 3];
	for (int i = 0; i < 256 * 256 * 3; i++) {
		if (i % 3 == 1) mmGreen[i] = 255;
		else mmGreen[i] = 0;
	}
	unsigned char mmBlue[256 * 256 * 3];
	for (int i = 0; i < 256 * 256 * 3; i++) {
		if (i % 3 == 2) mmBlue[i] = 255;
		else mmBlue[i] = 0;
	}

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(texType, ID);
	if (mmType == 0) {
		// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);

		glGenerateMipmap(texType);
	}
	else if (mmType == 1) {
		// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(texType, GL_TEXTURE_MAX_LEVEL, 8);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, mmRed);
		glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, mmGreen);
		glTexImage2D(GL_TEXTURE_2D, 2, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, mmBlue);
		glTexImage2D(GL_TEXTURE_2D, 3, GL_RGB, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, mmRed);
		glTexImage2D(GL_TEXTURE_2D, 4, GL_RGB, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, mmGreen);
		glTexImage2D(GL_TEXTURE_2D, 5, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, mmBlue);
		glTexImage2D(GL_TEXTURE_2D, 6, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, mmRed);
		glTexImage2D(GL_TEXTURE_2D, 7, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, mmGreen);
		glTexImage2D(GL_TEXTURE_2D, 8, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, mmBlue);

	}
	else {
		// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(texType, GL_TEXTURE_MAX_LEVEL, 8);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, mmRed);
		glTexImage2D(GL_TEXTURE_2D, 1, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, mmGreen);
		glTexImage2D(GL_TEXTURE_2D, 2, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, mmBlue);
		glTexImage2D(GL_TEXTURE_2D, 3, GL_RGB, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, mmRed);
		glTexImage2D(GL_TEXTURE_2D, 4, GL_RGB, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, mmGreen);
		glTexImage2D(GL_TEXTURE_2D, 5, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, mmBlue);
		glTexImage2D(GL_TEXTURE_2D, 6, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, mmRed);
		glTexImage2D(GL_TEXTURE_2D, 7, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, mmGreen);
		glTexImage2D(GL_TEXTURE_2D, 8, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, mmBlue);

	}

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
