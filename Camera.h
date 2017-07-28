#ifndef SURVIVAL_CAMERA_H
#define SURVIVAL_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    glm::vec3 mUp;
    glm::vec3 mDirection;
    glm::vec3 mPosition;

    float yaw = 0.0f;
    float pitch = 0.0f;

    glm::mat4 view;

    Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up) {
        mPosition = position;
        mDirection = direction;
        mUp = up;
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(mPosition, mPosition + mDirection, mUp);
    }

    void processKeyboardInput(GLFWwindow* window, float deltaTime) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        float cameraSpeed = 2.5f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            mPosition += cameraSpeed * mDirection;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            mPosition -= cameraSpeed * mDirection;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            glm::vec3 cameraRight = glm::normalize(glm::cross(mDirection, mUp));
            mPosition -= cameraSpeed * cameraRight;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            glm::vec3 cameraRight = glm::normalize(glm::cross(mDirection, mUp));
            mPosition += cameraSpeed * cameraRight;
        }
    }

    void processMouseInput(float deltaX, float deltaY) {
        float sensitivity = 0.05f;
        deltaX *= sensitivity;
        deltaY *= sensitivity;

        yaw += deltaX;
        pitch += deltaY;

        if (pitch >= 89.0f) pitch = 89.0f;
        if (pitch <= -89.0f) pitch = -89.0f;

        glm::vec3 newDirection;
        newDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newDirection.y = sin(glm::radians(pitch));
        newDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        mDirection = glm::normalize(newDirection);
    }

private:

};

#endif //SURVIVAL_CAMERA_H
