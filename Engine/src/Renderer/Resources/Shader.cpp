//
// Created by Nil on 06/03/2026.
//

#include <glad/glad.h>

#include "Engine/Core/Logger.h"
#include "Engine/Renderer/Resources/Shader.h"
#include "Engine/Utils/FileUtils.h"

namespace Engine {
    Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
        const std::string vertexShaderSource   = FileUtils::readFile(vertexPath);
        const std::string fragmentShaderSource = FileUtils::readFile(fragmentPath);

        if (vertexShaderSource.empty()) {
            LOG_ERROR_C("Engine", "Shader: vertex source empty. Check path: " + vertexPath);
            return;
        }
        if (fragmentShaderSource.empty()) {
            LOG_ERROR_C("Engine", "Shader: fragment source empty. Check path: " + fragmentPath);
            return;
        }

        const GLuint vert = compileStage_(vertexShaderSource, GL_VERTEX_SHADER);
        const GLuint frag = compileStage_(fragmentShaderSource, GL_FRAGMENT_SHADER);

        if (!vert || !frag) {
            if (vert)
                glDeleteShader(vert);
            if (frag)
                glDeleteShader(frag);
            return;
        }

        programID_ = glCreateProgram();
        glAttachShader(programID_, vert);
        glAttachShader(programID_, frag);
        glLinkProgram(programID_);

        GLint success;
        glGetProgramiv(programID_, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(programID_, 512, nullptr, infoLog);
            LOG_ERROR_C("Engine", std::string("Shader link failed ") + infoLog);
            glDeleteProgram(programID_);
            programID_ = 0;
        }

        glDeleteShader(vert);
        glDeleteShader(frag);

        if (programID_)
            LOG_INFO_C("Engine", "Shaders compiled and linked: " + vertexPath + " + " + fragmentPath);
    }

    Shader::~Shader() {
        if (programID_) {
            glDeleteProgram(programID_);
            programID_ = 0;
        }
    }

    Shader::Shader(Shader &&other) noexcept : programID_(other.programID_) { other.programID_ = 0; }

    Shader &Shader::operator=(Shader &&other) noexcept {
        if (this != &other) {
            if (programID_)
                glDeleteProgram(programID_);
            programID_       = other.programID_;
            other.programID_ = 0;
        }
        return *this;
    }

    void Shader::bind() const { glUseProgram(programID_); }
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void Shader::unbind() const { glUseProgram(0); }

    void Shader::setBool(const std::string &name, const bool value) const {
        glUniform1i(getUniformLocation_(name), static_cast<int>(value));
    }

    void Shader::setInt(const std::string &name, const int value) const {
        glUniform1i(getUniformLocation_(name), value);
    }

    void Shader::setFloat(const std::string &name, const float value) const {
        glUniform1f(getUniformLocation_(name), value);
    }

    void Shader::setVec3(const std::string &name, const Vec3 &value) const {
        glUniform3f(getUniformLocation_(name), value.x, value.y, value.z);
    }

    void Shader::setVec4(const std::string &name, const Vec4 &value) const {
        glUniform4f(getUniformLocation_(name), value.x, value.y, value.z, value.w);
    }

    void Shader::setMat4(const std::string &name, const Mat4 &value) const {
        glUniformMatrix4fv(getUniformLocation_(name), 1, GL_FALSE, value.data);
    }

    void Shader::setVec3Raw(const std::string &name, const float *v) const {
        glUniform3fv(getUniformLocation_(name), 1, v);
    }

    void Shader::setVec4Raw(const std::string &name, const float *v) const {
        glUniform4fv(getUniformLocation_(name), 1, v);
    }

    void Shader::setMat4Raw(const std::string &name, const float *m, const bool transpose) const {
        glUniformMatrix4fv(getUniformLocation_(name), 1, transpose ? GL_TRUE : GL_FALSE, m);
    }

    GLuint Shader::compileStage_(const std::string &source, const GLenum type) {
        const GLuint shader = glCreateShader(type);
        const char  *src    = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            const std::string typeName = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
            LOG_ERROR_C("Engine", "Shader: " + typeName + " compilation failed " + infoLog);
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    GLint Shader::getUniformLocation_(const std::string &name) const {
        if (const auto cached = uniformCache_.find(name); cached != uniformCache_.end())
            return cached->second;

        const GLint loc = glGetUniformLocation(programID_, name.c_str());
        if (loc == -1 && !warnedUniforms_.contains(name)) {
            LOG_WARN_C("Engine", "Shader: uniform '" + name + "' not found");
            warnedUniforms_.insert(name);
        }

        uniformCache_[name] = loc;
        return loc;
    }
} // namespace Engine
