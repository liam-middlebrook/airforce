#include "TextureManager.h"
#include "OGL.h"
#include "af/PNGDecoder.h"
#include <boost/make_shared.hpp>

namespace af
{
    TextureManager textureManager;

    template <>
    Single<TextureManager>* Single<TextureManager>::single = NULL;

    TextureManager::TextureManager()
    {
    }

    TextureManager::~TextureManager()
    {
    }

    bool TextureManager::init(const std::string& path)
    {
        path_ = path + "/";

        return true;
    }

    void TextureManager::shutdown()
    {
        /*
         * TODO: Delete textures.
         */
    }

    TexturePtr TextureManager::loadTexture(const std::string& name)
    {
        TextureMap::iterator it = textures_.find(name);

        if (it != textures_.end()) {
            return it->second;
        }

        GLuint id;

        ogl.GenTextures(1, &id);
        ogl.BindTexture(GL_TEXTURE_2D, id);

        PNGDecoder decoder(path_ + name);

        std::vector<Byte> data;

        TexturePtr texture;

        if (decoder.init() && decoder.decode(data)) {
            ogl.TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                           decoder.width(), decoder.height(), 0, GL_RGBA,
                           GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(&data[0]));

            texture = boost::make_shared<Texture>(id,
                                                  decoder.width(),
                                                  decoder.height());
        } else {
            ogl.TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                           1, 1, 0, GL_RGBA,
                           GL_UNSIGNED_BYTE, NULL);

            texture = boost::make_shared<Texture>(id, 1, 1);
        }

        ogl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        ogl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        ogl.BindTexture(GL_TEXTURE_2D, 0);

        textures_[name] = texture;

        return texture;
    }
}
