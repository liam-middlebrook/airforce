#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "Single.h"
#include "Texture.h"
#include <map>

namespace af
{
    class TextureManager : public Single<TextureManager>
    {
    public:
        TextureManager();
        virtual ~TextureManager();

        bool init(const std::string& path);

        void shutdown();

        TexturePtr loadTexture(const std::string& name);

    private:
        typedef std::map<std::string, TexturePtr> TextureMap;

        std::string path_;
        TextureMap textures_;
    };

    extern TextureManager textureManager;
}

#endif
