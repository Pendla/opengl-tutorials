#ifndef SURVIVAL_SHADER_H
#define SURVIVAL_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader {
public:

    Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
        std::string vertexShaderSourceCode = readShader(vertexPath);
        std::string fragmentShaderSourceCode = readShader(fragmentPath);


        unsigned int shaders[] = {
            compileShader(GL_VERTEX_SHADER, vertexShaderSourceCode.c_str()),
            compileShader(GL_FRAGMENT_SHADER, fragmentShaderSourceCode.c_str())
        };
        createProgram(shaders);
    }

    void use() {
        glUseProgram(id);
    }

    void setBool(const std::string& name, bool value){
        setInt(name.c_str(), (int)value);
    }

    void setInt(const std::string& name, int value) {
        int location = glGetUniformLocation(id, name.c_str());
        glUniform1i(location, value);
    }

    void setFloat(const std::string& name, float value) {
        int location = glGetUniformLocation(id, name.c_str());
        glUniform1f(location, value);
    }

    void setMatrix(const std::string& name, glm::mat4 matrix) {
        int location = glGetUniformLocation(id, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void setVec3(const std::string& name, glm::vec3 vec) {
        int location = glGetUniformLocation(id, name.c_str());
        glUniform3f(location, vec.x, vec.y, vec.z);
    }

    void setVec3(const std::string& name, float x, float y, float z) {
        int location = glGetUniformLocation(id, name.c_str());
        glUniform3f(location, x, y, z);
    }

private:
    unsigned int id;

    std::string readShader(const std::string path) {
        std::ifstream fileReader(path);

        if (fileReader.is_open()) {
            std::stringstream shaderSourceStream;
            shaderSourceStream << fileReader.rdbuf();
            fileReader.close();

            return shaderSourceStream.str();
        } else {
            std::cout << "FAILED TO OPEN FILE (" << path << ")" << std::endl;
            return nullptr;
        }
    }

    unsigned int compileShader(GLenum shaderType, const char* shaderSourceCode) {
        unsigned int shader = glCreateShader(shaderType);

        glShaderSource(shader, 1, &shaderSourceCode, NULL);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[1024];
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR - SHADER COMPILATION FAILED:" << std::endl << infoLog << std::endl;
        }

        return shader;
    }

    void createProgram(unsigned int shaders[]) {
        id = glCreateProgram();

        for (int i = 0; i < sizeof(shaders) / sizeof(unsigned int); i++) {
            glAttachShader(id, shaders[i]);
        }

        glLinkProgram(id);

        int success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "ERROR - SHADER PROGRAM LINKING FAILED:" << std::endl << infoLog << std::endl;
        }

        for (int i = 0; i < sizeof(shaders) / sizeof(unsigned int); i++) {
            glDeleteShader(shaders[i]);
        }
    }
};

#endif //SURVIVAL_SHADER_H
