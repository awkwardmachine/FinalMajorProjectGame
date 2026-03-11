#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Engine/Core/DLLExports.h"

namespace Engine {
    struct ENGINE_API Vec3 {
        float x, y, z;
    };
    struct ENGINE_API Vec4 {
        float x, y, z, w;
    };
    struct ENGINE_API Mat4 {
        float data[16];
    };

    class ENGINE_API Shader {
    public:
        Shader(const std::string &vertexPath, const std::string &fragmentPath);
        ~Shader();

        Shader(const Shader &)            = delete;
        Shader &operator=(const Shader &) = delete;
        Shader(Shader &&other) noexcept;
        Shader &operator=(Shader &&other) noexcept;

        void bind() const;
        void unbind() const;

        [[nodiscard]] bool   isValid() const { return programID_ != 0; }
        [[nodiscard]] GLuint programID() const { return programID_; }

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec3(const std::string &name, const Vec3 &value) const;
        void setVec4(const std::string &name, const Vec4 &value) const;
        void setMat4(const std::string &name, const Mat4 &value) const;

        void setVec3Raw(const std::string &name, const float *v) const;
        void setVec4Raw(const std::string &name, const float *v) const;
        void setMat4Raw(const std::string &name, const float *m, bool transpose = false) const;

    private:
        GLuint programID_ = 0;

        mutable std::unordered_map<std::string, GLint> uniformCache_;
        mutable std::unordered_set<std::string>        warnedUniforms_;

        [[nodiscard]] static GLuint compileStage_(const std::string &source, GLenum type);
        [[nodiscard]] GLint         getUniformLocation_(const std::string &name) const;
    };
} // namespace Engine
