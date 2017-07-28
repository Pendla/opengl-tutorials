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
    glm::vec3 mRight;

    float yaw = -90.0f;
    float pitch = 0.0f;

    glm::mat4 view;

    Camera(glm::vec3 position, glm::vec3 up) {
        mPosition = position;
        mUp = up;
        mRight = glm::cross(mDirection, mUp);

        updateCameraVectors();
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
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            mPosition -= cameraSpeed * mUp;
        } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            mPosition += cameraSpeed * mUp;
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

        updateCameraVectors();
    }

private:
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        mDirection = glm::normalize(front);
        // Also re-calculate the Right and mUp vector
        mRight = glm::normalize(glm::cross(mDirection, glm::vec3(0.0f, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        mUp    = glm::normalize(glm::cross(mRight, mDirection));
    }
};

#endif //SURVIVAL_CAMERA_H
