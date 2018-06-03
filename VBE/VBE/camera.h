#pragma once

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVITY = 0.5f;
const GLfloat ZOOM = 45.0f;

class Camera
{
private:
	glm::vec3 m_WorldUp;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_Position;

	GLfloat m_Yaw;
	GLfloat m_Pitch;
	GLfloat m_MovementSpeed;
	GLfloat m_Zoom;
	GLfloat m_MouseSensitivity;

private:
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw))*cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Front, m_Right));
	}

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH)
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_Zoom(ZOOM), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY)
	{
		m_Position = position;
		m_WorldUp = up;
		m_Yaw = yaw;
		m_Pitch = pitch;
	}

	glm::mat4 getViewMatrix() const
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_WorldUp);
	}

	void processKeybord(Camera_Movement dir, GLfloat deltaTime)
	{
		GLfloat velocity = m_MovementSpeed * deltaTime;

		if (dir == FORWARD)
		{
			m_Position += m_Front * velocity;
		}
		if (dir == BACKWARD)
		{
			m_Position -= m_Front * velocity;
		}
		if (dir == LEFT)
		{
			m_Position -= m_Right * velocity;
		}
		if (dir == RIGHT)
		{
			m_Position += m_Right * velocity;
		}
	}

	void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true)
	{
		xOffset *= m_MouseSensitivity;
		yOffset *= m_MouseSensitivity;

		m_Yaw += xOffset;
		m_Pitch += yOffset;

		if (constrainPitch)
		{
			if (m_Pitch > 89.0f)
			{
				m_Pitch = 89.0f;
			}
			else if (m_Pitch < -89.0f)
			{
				m_Pitch = -89.0f;
			}
		}

		updateCameraVectors();
	}

	void processScroll(GLfloat offset)
	{
		if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
		{
			m_Zoom -= offset;
		}
		else if (m_Zoom < 1.0f)
		{
			m_Zoom = 1.0f;
		}
		else m_Zoom = 45.0f;
	}

	GLfloat getZoom() const
	{
		return m_Zoom;
	}

	glm::vec3 getPosition()
	{
		return m_Position;
	}
};
