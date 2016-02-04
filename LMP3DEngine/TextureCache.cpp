#include "TextureCache.h"
#include "LoadGLTexture.h"

#include <iostream>

namespace LMP3DEngine {

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath) {

		//loopup the texture and see if it's in the map
		auto mit = _textureMap.find(texturePath);

		if (mit == _textureMap.end()) {
			GLTexture newTexture = LoadGLTexture::LoadTexture(texturePath);

			//insert into map
			_textureMap.insert(make_pair(texturePath, newTexture));

			/**std::cout << "Loaded Texture!\n";**/
			return newTexture;
		}

		/**std::cout << "Used Cached Texture!\n";**/
		return mit->second;

	}

}