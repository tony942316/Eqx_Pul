module;

#include <stb_image.h>

export module Eqx.Stbim;

export namespace stbim
{
    inline void vertical_flip(bool flip) noexcept;
    inline unsigned char* load(const char* path, int* width, int* height,
        int* nrChannels) noexcept;
    inline void free(unsigned char* data) noexcept;
}

namespace stbim
{
    inline void vertical_flip(bool flip) noexcept
    {
        stbi_set_flip_vertically_on_load(flip);
    }

    inline unsigned char* load(const char* path, int* width, int* height,
        int* nrChannels) noexcept
    {
        return stbi_load(path, width, height, nrChannels, 0);
    }

    inline void free(unsigned char* data) noexcept
    {
        stbi_image_free(data);
    }
}
