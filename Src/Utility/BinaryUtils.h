#pragma once

#include <fstream>
#include <cassert>
#include <vector>

// TODO create a global image memory cache
// char* ImageMemoryCache = new char[SOME_BIG_SIZE];


template <typename T>
T FromBytes(const char* bytes, unsigned int offset = 0,  unsigned int bytesToReadCount = 1)
{
	assert(sizeof(T) >= bytesToReadCount);

	T val = 0;
	int bitOffset = (bytesToReadCount * 8) - 8;
	int cursor = offset + bytesToReadCount - 1; // cursor is an index, not a lenght, so -1
	
	while (bitOffset >= 0)
	{
		val |= (bytes[cursor] << bitOffset);
		bitOffset -= 8;
		cursor -= 1;
	} 

	return val;
	
}

class Bitmap
{
public:

	Bitmap(const Bitmap& bitmap) = delete;
	
	Bitmap& operator=(const Bitmap& bitmap) = delete;
	
	~Bitmap()
	{
		if (m_data != 0)
		{
			delete m_data;
		}
	}



	enum DibHeaderType : int
	{
		UNDEFINED = 0,
		CORE_OSX21 = 12,
		OS22X_VARIANT = 16,
		OS22X = 64,
		V1 = 40,
		V2 = 52,
		V3 = 56,
		V4 = 108,
		V5 = 124
	};



	const std::string& GetHeaderField() const
	{
		return m_headerField;
	}

	unsigned int GetSize() 
	{
		return m_size;
	}

	DibHeaderType GetDibHeaderType()
	{
		return m_dibHeaderType;
	}

	unsigned int GetWidth()
	{
		return m_width;
	}

	unsigned int GetHeight()
	{
		return m_height;
	}

	unsigned int GetBitDepth()
	{
		return m_bitDepth;
	}

	unsigned int GetImageDataSizeBytes()
	{
		return m_imageDataSizeBytes;
	}

	const char* GetData()
	{
		return m_data;
	}

	bool IsLoadSuccessful()
	{
		return m_isLoadSuccessful;
	}



	static Bitmap* Create(const char* filePath)
	{

		std::ifstream stream;
		stream.open(filePath, std::ios::binary | std::ios::ate);
		std::ifstream::pos_type pos = stream.tellg();
		int lenght = (int)pos;
		stream.seekg(0, std::ios::beg);


		Bitmap* bi = new Bitmap();
		bi->m_data = new char[lenght];
		char * buffer = bi->m_data;
		
		if (stream.read(buffer, lenght))
		{
			bi->m_headerField = std::string(buffer, 2);
			bi->m_size = FromBytes<unsigned int>(buffer, 2, 4);
			
			if (bi->m_size == lenght) // if file length not equals file size in header, file is corrupted. exit.
			{
				// where bitmap data begins
				bi->m_dataOffset = FromBytes<unsigned int>(buffer, 10, 4);

				// type of the bmp header
				bi->m_dibHeaderType = (Bitmap::DibHeaderType)FromBytes<int>(buffer, 14, 4);
				if (bi->m_dibHeaderType != Bitmap::DibHeaderType::UNDEFINED)
				{
					switch (bi->m_dibHeaderType)
					{
					case Bitmap::CORE_OSX21:
						bi->m_width = FromBytes<unsigned int>(buffer, 18, 2);
						bi->m_height = FromBytes<unsigned int>(buffer, 20, 2);
						bi->m_bitDepth = FromBytes<unsigned int>(buffer, 24, 2);
						break;
					default:
						bi->m_width = FromBytes<unsigned int>(buffer, 18, 4);
						bi->m_height = FromBytes<unsigned int>(buffer, 22, 4);
						bi->m_bitDepth = FromBytes<unsigned int>(buffer, 28, 2);
						break;
				
					}
				
					// store where the in memory data is kept
					bi->m_data = buffer;

					// looks good. go ahead.
					bi->m_isLoadSuccessful = true;
				}

			}
		}
		
		// clean up in case of failure
		if (!bi->m_isLoadSuccessful)
		{
			delete[] buffer;
			delete bi;
			return 0;
		}

		return bi;
	}

	static void Destroy(Bitmap* bitmap)
	{
		delete bitmap;
	}

private:
	Bitmap():
		m_isLoadSuccessful(false),
		m_headerField(""),
		m_size(0),
		m_dataOffset(0),
		m_dibHeaderType(Bitmap::DibHeaderType::UNDEFINED),
		m_width(0),
		m_height(0),
		m_bitDepth(0),
		m_data(0),
		m_imageDataSizeBytes(0)
	{}

	bool m_isLoadSuccessful;
	std::string m_headerField;
	DibHeaderType m_dibHeaderType;
	unsigned int m_size,
				 m_dataOffset,
				 m_width,
				 m_height,
				 m_bitDepth,
				 m_imageDataSizeBytes;
	char* m_data;


};


