#include "stdafx.h"
#include "lodepng\lodepng.h"
#include "TextureManager.h"
#include "Opengl\OglErrorChecker.h"
#include "Common.h"

bool TextureManager::Init(unsigned int texMaxWidth, unsigned int texMaxHeight, unsigned int texArraySize)
{
	glGenTextures(1, &m_texArrayId);

	if (m_texArrayId == 0)
	{
		PRINT(OglErrorChecker::GetLastError());
		return false;
	}

	glBindTexture(GL_TEXTURE_2D_ARRAY, m_texArrayId);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 0);

	glTexStorage3D(
		GL_TEXTURE_2D_ARRAY,
		1,
		GL_RGBA8,
		texMaxWidth, texMaxHeight,
		texArraySize);

	m_textureMap.reserve(texArraySize);
	m_maxWidth = texMaxWidth;
	m_maxHeight = texMaxHeight;
	m_arraySize = texArraySize;

	return true;
}

TextureManager::~TextureManager()
{
	glDeleteTextures(1, &m_texArrayId);
}

void TextureManager::Load(Texture* texture, const char * filePath)
{
	// check if texture is already loaded

	if (CopyIfExists(texture, filePath))
		return;

	// get data from file

	std::vector<unsigned char> image;
	unsigned int width, height;
	unsigned int error = lodepng::decode(image, width, height, filePath, LodePNGColorType::LCT_RGBA);

	assert(error == 0);
	Load(texture, &image[0], width, height, filePath);

}

void TextureManager::Load(Texture* texture, unsigned char * buffer, int width, int height, const char* key)
{
	if (CopyIfExists(texture, key))
		return;

	Texture tex;

	assert(width <= m_maxWidth && height <= m_maxHeight);


	tex.ImageSize = Vec2((float)width, (float)height);

	// insert into gpu tex array

	// TODO order textures by time, not by initialization. Overwrite the least used first
	if (m_currentArrayPosition == m_arraySize - 1)
	{
		m_currentArrayPosition = 0;
	}

	// NOTE if using more than one texture slot, use glAtiveTexture(GL_TEXTURE0 + #texture)
	InsertImageDataIntoGpu(buffer, width, height, m_currentArrayPosition);

	// track position in array 

	tex.Index = m_currentArrayPosition;
	m_currentArrayPosition++;

	// insert tex into gpu and return it

	auto result = m_textureMap.insert(std::make_pair(key, tex)).first->second;
	memcpy(texture, &result, sizeof(Texture));
}

void TextureManager::InsertImageDataIntoGpu(unsigned char* data, int width, int height, int textureArrayIndex)
{
	glTexSubImage3D(
		GL_TEXTURE_2D_ARRAY, /// target
		0, /// mipmap levels
		0, 0, textureArrayIndex,/// x and y and z position. z is texture index
		width, height, 1, /// width, height, depth
		GL_RGBA, /// format
		GL_UNSIGNED_BYTE, /// data format
		data /// data
	);
}

bool TextureManager::CopyIfExists(Texture * texture, const char * key)
{
	auto it = m_textureMap.find(key);
	if (it != m_textureMap.end())
	{
		memcpy(texture, &it->second, sizeof(Texture));
		return true;
	}
	return false;
}
