//
// Created by Nil on 06/03/2026.
//

#include "Engine/Renderer/Resources/Texture.h"
#include "Engine/Core/Logger.h"

#include "stb/stb_image.h"

namespace Engine {
    Texture::Texture(const std::string &path, TextureSettings settings) : path_(path) {
        stbi_set_flip_vertically_on_load(settings.flipY ? 1 : 0);

        unsigned char *data = stbi_load(path.c_str(), &width_, &height_, &channels_, 0);
        if (!data) {
            LOG_ERROR_C("Engine", "Texture: failed to load '" + path + "' " + stbi_failure_reason());
            return;
        }

        GLenum internalFormat = GL_RGB;
        GLenum dataFormat     = GL_RGB;
        if (channels_ == 4) {
            internalFormat = GL_RGBA8;
            dataFormat     = GL_RGBA;
        } else if (channels_ == 3) {
            internalFormat = GL_RGB8;
            dataFormat     = GL_RGB;
        } else if (channels_ == 1) {
            internalFormat = GL_R8;
            dataFormat     = GL_RED;
        }

        glGenTextures(1, &textureID_);
        glBindTexture(GL_TEXTURE_2D, textureID_);

        // Wrapping
        const auto wrap = static_cast<GLint>(settings.wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

        // Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(settings.magFilter));

        if (settings.mipMaps) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        } else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(settings.minFilter));
        }

        // Upload to GPU
        glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(internalFormat), width_, height_, 0, dataFormat,
                     GL_UNSIGNED_BYTE, data);

        if (settings.mipMaps)
            glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);

        LOG_INFO_C("Engine", "Texture loaded: " + path + " (" + std::to_string(width_) + "x" + std::to_string(height_) +
                                     ", " + std::to_string(channels_) + "ch)");
    }

    Texture::~Texture() {
        if (textureID_) {
            glDeleteTextures(1, &textureID_);
            textureID_ = 0;
        }
    }

    Texture::Texture(Texture &&other) noexcept :
        textureID_(other.textureID_), width_(other.width_), height_(other.height_), channels_(other.channels_),
        path_(std::move(other.path_)) {
        other.textureID_ = 0;
    }

    Texture &Texture::operator=(Texture &&other) noexcept {
        if (this != &other) {
            if (textureID_)
                glDeleteTextures(1, &textureID_);
            textureID_       = other.textureID_;
            width_           = other.width_;
            height_          = other.height_;
            channels_        = other.channels_;
            path_            = std::move(other.path_);
            other.textureID_ = 0;
        }
        return *this;
    }

    void Texture::bind(const unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, textureID_);
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void Texture::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
} // namespace Engine
