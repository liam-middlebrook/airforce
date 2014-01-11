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

        PNGDecoder decoder(path_ + name);

        if (!decoder.init())
        {
            return TexturePtr();
        }

        std::vector<Byte> data;

        if (!decoder.decode(data))
        {
            return TexturePtr();
        }

        GLuint id;

        ogl.GenTextures(1, &id);
        ogl.BindTexture(GL_TEXTURE_2D, id);
        ogl.TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                       decoder.width(), decoder.height(), 0, GL_RGBA,
                       GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(&data[0]));
        ogl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        ogl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        ogl.BindTexture(GL_TEXTURE_2D, 0);

        TexturePtr texture = boost::make_shared<Texture>(id,
                                                         decoder.width(),
                                                         decoder.height());

        textures_[name] = texture;

        return texture;
    }
}
