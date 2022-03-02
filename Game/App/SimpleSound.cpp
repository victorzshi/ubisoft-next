///////////////////////////////////////////////////////////////////////////////
// Filename: CSimpleSound.cpp
// Privides a very simple DSOUND wrapper to load and play wav files.
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "stdafx.h"
//-----------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <assert.h>
//-----------------------------------------------------------------------------
#include "SimpleSound.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Singleton Accessor.
//-----------------------------------------------------------------------------
CSimpleSound &CSimpleSound::GetInstance()
{
	static CSimpleSound theSoundClass;
	return theSoundClass;
}

CSimpleSound::CSimpleSound() : m_directSound(nullptr), m_primaryBuffer(nullptr)
{
}

CSimpleSound::~CSimpleSound()
{
	Shutdown();
}

bool CSimpleSound::Initialize(HWND hwnd)
{
	// Initialize direct sound and the primary sound buffer.
	return InitializeDirectSound(hwnd);
}

void CSimpleSound::Shutdown()
{
	// Release the secondary buffers.
	for (auto sound : m_sounds) 
	{
		if( sound.second )
		{
			sound.second->Release();
		}		
	}
	// Shutdown the Direct Sound API.
	ShutdownDirectSound();
	m_sounds.clear();
	return;
}

bool CSimpleSound::InitializeDirectSound(HWND hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;

	// Initialize the direct sound interface pointer for the default sound device.
	result = DirectSoundCreate8(NULL, &m_directSound, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	result = m_directSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if(FAILED(result))
	{
		return false;
	}

	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Get control of the primary sound buffer on the default sound device.
	result = m_directSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Setup the format of the primary sound bufffer.
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the primary buffer to be the wave format specified.
	result = m_primaryBuffer->SetFormat(&waveFormat);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void CSimpleSound::ShutdownDirectSound()
{
	// Release the primary sound buffer pointer.
	if(m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = 0;
	}

	// Release the direct sound interface pointer.
	if(m_directSound)
	{
		m_directSound->Release();
		m_directSound = 0;
	}

	return;
}

bool CSimpleSound::PlaySound(const char *filename, DWORD flags)
{
	HRESULT result;

	// Set position at the beginning of the sound buffer.
	//result = m_secondaryBuffer1->SetCurrentPosition(0);
	if (m_sounds[filename] == nullptr)
	{
		result = LoadWaveFile(filename);
		if (FAILED(result))
		{
			return false;
		}
	}

	if (m_sounds[filename])
	{
		result = m_sounds[filename]->SetCurrentPosition(0);
		if (FAILED(result))
		{
			return false;
		}

		// Set volume of the buffer to 100%.
		result = m_sounds[filename]->SetVolume(DSBVOLUME_MAX);
		if (FAILED(result))
		{
			return false;
		}

		// Play the contents of the secondary sound buffer.
		result = m_sounds[filename]->Play(0, 0, flags);
		if (FAILED(result))
		{
			return false;
		}
		return true;
	}
	return false;
}


bool CSimpleSound::IsPlaying(const char *filename)
{
	if (m_sounds[filename] != nullptr)
	{
		DWORD dwStatus;
		HRESULT result = m_sounds[filename]->GetStatus(&dwStatus);
		if (!FAILED(result))
		{
			return (dwStatus&DSBSTATUS_PLAYING) != 0;
		}			
	}
	return false;
}

bool CSimpleSound::StopSound(const char *filename)
{
	if (IsPlaying(filename) )
	{
		if (m_sounds[filename] != nullptr)
		{
			HRESULT result = m_sounds[filename]->Stop();
			return (FAILED(result));
		}
	}
	return false;
}

bool CSimpleSound::LoadWaveFile(const char* filename)
{	
	int error;
	FILE* filePtr = nullptr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;
	// Find entry in map.
	IDirectSoundBuffer8** secondaryBuffer = &m_sounds[filename];

	// Open the wave file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the wave file header.
	count = (unsigned int)fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Check that the chunk ID is the RIFF format.
	if ((waveFileHeader.m_chunkId[0] != 'R') || (waveFileHeader.m_chunkId[1] != 'I') ||
		(waveFileHeader.m_chunkId[2] != 'F') || (waveFileHeader.m_chunkId[3] != 'F'))
	{
		return false;
	}

	// Check that the file format is the WAVE format.
	if ((waveFileHeader.m_format[0] != 'W') || (waveFileHeader.m_format[1] != 'A') ||
		(waveFileHeader.m_format[2] != 'V') || (waveFileHeader.m_format[3] != 'E'))
	{
		return false;
	}

	// Check that the sub chunk ID is the fmt format.
	if ((waveFileHeader.m_subChunkId[0] != 'f') || (waveFileHeader.m_subChunkId[1] != 'm') ||
		(waveFileHeader.m_subChunkId[2] != 't') || (waveFileHeader.m_subChunkId[3] != ' '))
	{
		return false;
	}

	// Check for the data chunk header.
	if ((waveFileHeader.m_dataChunkId[0] != 'd') || (waveFileHeader.m_dataChunkId[1] != 'a') ||
		(waveFileHeader.m_dataChunkId[2] != 't') || (waveFileHeader.m_dataChunkId[3] != 'a'))
	{
		return false;
	}

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = waveFileHeader.m_audioFormat;
	waveFormat.nSamplesPerSec = waveFileHeader.m_sampleRate;
	waveFormat.wBitsPerSample = waveFileHeader.m_bitsPerSample;
	waveFormat.nChannels = waveFileHeader.m_numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.m_dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	result = m_directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader.m_dataSize];
	if (!waveData)
	{
		return false;
	}

	// Read in the wave file data into the newly created buffer.
	count = (unsigned int)fread(waveData, 1, waveFileHeader.m_dataSize, filePtr);
	if (count != waveFileHeader.m_dataSize)
	{
		return false;
	}

	// Close the file once done reading.
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// Lock the secondary buffer to write wave data into it.
	result = (*secondaryBuffer)->Lock(0, waveFileHeader.m_dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader.m_dataSize);

	// Unlock the secondary buffer after the data has been written to it.
	result = (*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Release the wave data since it was copied into the secondary buffer.
	delete[] waveData;
	waveData = 0;

	return true;
}