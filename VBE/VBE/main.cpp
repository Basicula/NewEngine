#include <iostream>
#include <vector>
#include <random>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <SOIL2.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "camera.h"
#include "Shader.h"

const int width = 800, height = 600;
int screenWidth, screenHeight;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = width / 2;
float lastY = height / 2;

glm::mat4 projection;

float lastFrame = 0.0f;
float deltaTime = 0.0f;

bool keys[1024];
bool firstMouse;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLU_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	camera.processMouseMovement(xOffset, yOffset);

	lastX = xPos;
	lastY = yPos;
}

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	camera.processScroll(yOffset);
}

glm::vec3 testLightPos(0.0f);
float lightSpeed = 5.0f;
void doMovement()
{
	float velocity = lightSpeed * deltaTime;
	if (keys[GLFW_KEY_W])
	{
		camera.processKeybord(FORWARD, deltaTime);
		//testLightPos.z -= velocity;
	}

	if (keys[GLFW_KEY_UP])
	{
		//camera.processKeybord(FORWARD, deltaTime);
		//testLightPos.y -= velocity;
	}

	if (keys[GLFW_KEY_DOWN])
	{
		//camera.processKeybord(FORWARD, deltaTime);
		//testLightPos.y += velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		camera.processKeybord(BACKWARD, deltaTime);
		//testLightPos.z += velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		camera.processKeybord(RIGHT, deltaTime);
		//testLightPos.x += velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		camera.processKeybord(LEFT, deltaTime);
		//testLightPos.x -= velocity;
	}
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(width, height, "First", nullptr, nullptr);

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed init GLEW" << std::endl;
		return 1;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	glEnable(GL_DEPTH_TEST);

	Shader shader("Shaders/vertexshader.vert", "Shaders/fragmentshader.frag");
	Shader lamp("Shaders/lamp.vert", "Shaders/lamp.frag");

	GLfloat vertices[] =
	{
		//vertex					//color						//texture coords
		-0.5f,	-0.5f,	0.0f,		1.0f,	0.0f,	0.0f,	1.0f,		0.0f,	0.0f,
		-0.5f,	0.5f,	0.0f,		1.0f,	0.0f,	0.0f,	1.0f,		0.0f,	1.0f,
		0.5f,	0.5f,	0.0f,		1.0f,	1.0f,	1.0f,	1.0f,		1.0f,	1.0f,
		0.5f,	-0.5f,	0.0f,		1.0f,	1.0f,	1.0f,	1.0f,		1.0f,	0.0f
	};


	GLfloat cube[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	GLuint indices[] =
	{
		0,1,2,
		2,3,0
	};

	glm::vec3 frame[] =
	{
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,0.0f,10.0f),
		glm::vec3(0.0f,10.0f,0.0f),
		glm::vec3(0.0f,10.0f,10.0f),
		glm::vec3(10.0f,0.0f,0.0f),
		glm::vec3(10.0f,0.0f,10.0f),
		glm::vec3(10.0f,10.0f,0.0f),
		glm::vec3(10.0f,10.0f,10.0f)
	};

	GLfloat line[] =
	{
		0.0f,0.0f,0.0f,
		0.0f,0.0f,10.0f,

		0.0f,0.0f,10.0f,
		10.0f,0.0f,10.0f,

		10.0f,0.0f,10.0f,
		10.0f,0.0f,0.0f,

		10.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,

		10.0f,10.0f,10.0f,
		10.0f,10.0f,0.0f,

		10.0f,10.0f,0.0f,
		0.0f,10.0f,0.0f,

		0.0f,10.0f,0.0f,
		0.0f,10.0f,10.0f,

		0.0f,10.0f,10.0f,
		10.0f,10.0f,10.0f,

		0.0f,0.0f,0.0f,
		0.0f,10.0f,0.0f,

		0.0f,0.0f,10.0f,
		0.0f,10.0f,10.0f,

		10.0f,0.0f,10.0f,
		10.0f,10.0f,10.0f,

		10.0f,0.0f,0.0f,
		10.0f,10.0f,0.0f
	};

	std::vector<glm::vec3> vertexPos =
	{
		glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(0.0f,0.0f,-2.0f),
		glm::vec3(0.0f,3.0f,0.0f),
		glm::vec3(0.0f,-4.0f,0.0f),
		glm::vec3(5.0f,0.0f,0.0f),
		glm::vec3(-6.0f,0.0f,0.0f)
	};

	GLuint VBO, VAO, EBO, cubeVAO, cubeVBO, lampVBO, lampVAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//texture
	/*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid *)(7 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);*/

	glBindVertexArray(0);

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);

	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);

	glGenVertexArrays(1, &lampVAO);
	glGenBuffers(1, &lampVBO);
	
	glBindVertexArray(lampVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lampVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	//texture
	/*GLuint texture;

	int width, height;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *image = SOIL_load_image("Images/lenna2.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	GLuint lineVBO, lineVAO;
	glGenVertexArrays(1, &lineVAO);
	glGenBuffers(1, &lineVBO);

	glBindVertexArray(lineVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);


	projection = glm::perspective(camera.getZoom(), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 1000.0f);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//check events (mouse,key,etc.)
		glfwPollEvents();
		doMovement();
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			vertexPos.push_back(camera.getPosition());
		}

		//Render
		//Clear color buffer
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		glm::mat4 view = camera.getViewMatrix();

		GLint projLoc = glGetUniformLocation(shader.getProgram(), "projection");
		GLint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
		GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");

		GLint lightColorLoc = glGetUniformLocation(shader.getProgram(), "lightColor");
		GLint viewPosLoc = glGetUniformLocation(shader.getProgram(), "viewPos");
		GLint objectColorLoc = glGetUniformLocation(shader.getProgram(), "objectColor");

		GLint lighLoc = glGetUniformLocation(shader.getProgram(), "light.position");
		GLint lAmbientLoc = glGetUniformLocation(shader.getProgram(), "light.ambient");
		GLint lDiffuseLoc = glGetUniformLocation(shader.getProgram(), "light.diffuse");
		GLint lSpecularLoc = glGetUniformLocation(shader.getProgram(), "light.specular");

		GLint mAmbientLoc = glGetUniformLocation(shader.getProgram(), "material.ambient");
		GLint mDiffuseLoc = glGetUniformLocation(shader.getProgram(), "material.diffuse");
		GLint mSpecularLoc = glGetUniformLocation(shader.getProgram(), "material.specular");
		GLint mShineLoc = glGetUniformLocation(shader.getProgram(), "material.shine");

		//ruby material
		glUniform3f(mAmbientLoc, 0.1745f, 0.01175f, 0.01175f);
		glUniform3f(mDiffuseLoc, 0.61424f, 0.04136f, 0.04136f);
		glUniform3f(mSpecularLoc, 0.727811f, 0.626959f, 0.626959f);
		glUniform1f(mShineLoc, 0.6f);

		glUniform3f(lAmbientLoc, 0.2f, 0.2f, 0.2f);
		glUniform3f(lDiffuseLoc, 0.5f, 0.5f, 0.5f);
		glUniform3f(lSpecularLoc, 1.0f, 1.0f, 1.0f);

		glm::vec3 viewPos = camera.getPosition();
		glUniform3f(viewPosLoc, viewPos.x, viewPos.y, viewPos.z);
		glUniform3f(lighLoc, testLightPos.x, testLightPos.y, testLightPos.z);
		glUniform4f(lightColorLoc, 1.0f, 1.0f, 1.0f, 1.0f);

		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glUniform4f(objectColorLoc, 1.0f, 0.0f, 0.0f, 1.0f);

		glBindVertexArray(cubeVAO);
		for (glm::vec3 cb : vertexPos)
		{
			glm::mat4 model;
			model = glm::translate(model, cb);
			model = glm::rotate(model, (float)glfwGetTime() * 5.0f, glm::vec3(0.1f, 0.2f, 0.3f));
			model = glm::scale(model, glm::vec3(0.5f));

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		glUniform4f(objectColorLoc, 0.0f, 1.0f, 0.0f, 1.0f);

		/*glBindVertexArray(lineVAO);
		glm::mat4 ps;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(ps));
		glDrawArrays(GL_LINES, 0, 72);
		glBindVertexArray(0);*/


		//texture
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shader.getProgram(), "texture"), 0);*/

		lamp.Use();

		projLoc = glGetUniformLocation(lamp.getProgram(), "projection");
		viewLoc = glGetUniformLocation(lamp.getProgram(), "view");
		modelLoc = glGetUniformLocation(lamp.getProgram(), "model");

		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 model;
		model = glm::translate(model, testLightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(lampVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//swap the screen buffers
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);

	glDeleteVertexArrays(1, &lineVAO);
	glDeleteBuffers(1, &lineVBO);

	glfwTerminate();

	return 0;
}