#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <iostream>

namespace core
{

	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		: Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch),
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		updateCameraVectors();
	}

	Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	Camera::~Camera()
	{
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		//return glm::lookAt(Position, Position + Front, Up);
		return lookAt(Position, Position + Front, Up);
	}

	void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
	}

	void Camera::ProcessKeyboardFPS(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
		{
			Position.x += Front.x * velocity;
			Position.z += Front.z * velocity;
		}			
		if (direction == BACKWARD)
		{
			Position.x -= Front.x * velocity;
			Position.z -= Front.z * velocity;
		}
		if (direction == LEFT)
		{
			Position.x -= Right.x * velocity;
			Position.z -= Right.z * velocity;
		}			
		if (direction == RIGHT)
		{
			Position.x += Right.x * velocity;
			Position.z += Right.z * velocity;
		}
	}

	void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	void Camera::ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;

		std::cout << Zoom << '\n';
	}

	// calculates the front vector from the Camera's (updated) Euler Angles
	void Camera::updateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}

	glm::mat4 Camera::lookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
	{
		glm::vec3 direction = glm::normalize(eye - center);
		glm::vec3 right = glm::normalize(glm::cross(up, direction));
		glm::mat4 rotate = {
			right[0], up[0], direction[0], 0, // column 0
			right[1], up[1], direction[1], 0, // column 1
			right[2], up[2], direction[2], 0, // column 2
			0,        0,     0,            1  // column 3
		};

		glm::mat4 translate = glm::translate(glm::mat4(1.0f), -eye);

		glm::mat4 look_at = rotate * translate;
		return look_at;
	}

}