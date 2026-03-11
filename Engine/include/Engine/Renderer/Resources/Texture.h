#pragma once

#include <glad/glad.h>
#include <string>

#include "Engine/Core/DLLExports.h"

namespace Engine {
    enum class TextureWrap {
        Repeat         = GL_REPEAT,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        ClampToEdge    = GL_CLAMP_TO_EDGE,
    };

    enum class TextureFilter {
        Nearest = GL_NEAREST,
        Linear  = GL_LINEAR,
    };

    struct ENGINE_API TextureSettings {
        TextureWrap   wrap      = TextureWrap::Repeat;
        TextureFilter minFilter = TextureFilter::Nearest;
        TextureFilter magFilter = TextureFilter::Nearest;
        bool          mipMaps   = true;
        bool          flipY     = true;
    };

    class ENGINE_API Texture {
    public:
        explicit Texture(const std::string &path, TextureSettings settings = {});
        ~Texture();

        Texture(const Texture &)            = delete;
        Texture &operator=(const Texture &) = delete;
        Texture(Texture &&other) noexcept;
        Texture &operator=(Texture &&other) noexcept;

        void bind(unsigned int slot = 0) const;
        void unbind() const;

        [[nodiscard]] bool        isValid() const { return textureID_ != 0; }
        [[nodiscard]] GLuint      id() const { return textureID_; }
        [[nodiscard]] int         width() const { return width_; }
        [[nodiscard]] int         height() const { return height_; }
        [[nodiscard]] int         channels() const { return channels_; }
        [[nodiscard]] std::string path() const { return path_; }

    private:
        GLuint      textureID_ = 0;
        int         width_ = 0, height_ = 0, channels_ = 0;
        std::string path_;
    };
} // namespace Engine
