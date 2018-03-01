#pragma once

#include "GL\glew.h"
#include "Texture.h"

class TextureManager
{
	unsigned int
		m_maxWidth,
		m_maxHeight,
		m_arraySize,
		m_currentArrayPosition;

	GLuint m_texArrayId;

	std::unordered_map<const char*, Texture> m_textureMap;

	//

	void InsertImageDataIntoGpu(unsigned char* data, int width, int height, int arrayPosition);

	bool CopyIfExists(Texture* texture, const char* key);

public:
	TextureManager() :
		m_maxWidth(0),
		m_maxHeight(0),
		m_arraySize(0),
		m_currentArrayPosition(0),
		m_texArrayId(0)
	{}

	~TextureManager();

	bool Init(unsigned int texMaxWidth, unsigned int texMaxHeight, unsigned int texArraySize);

	//

	int GetTextureArrayId()
	{
		return m_texArrayId;
	}

	//

	void Load(Texture* texture, const char* filePath);

	void Load(Texture* texture, unsigned char* buffer, int width, int height, const char* key);

};