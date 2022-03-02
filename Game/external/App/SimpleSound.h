//-----------------------------------------------------------------------------
// SimpleSound.h
// Privides a very simple DSOUND wrapper to load and play wav files.
//-----------------------------------------------------------------------------
#ifndef _SIMPLESOUND_H_
#define _SIMPLESOUND_H_

#include <dsound.h>
#include <map>

//-----------------------------------------------------------------------------
// CSimpleSound
//-----------------------------------------------------------------------------
class CSimpleSound
{
private:
	struct WaveHeaderType
	{
		char			m_chunkId[4];
		unsigned long	m_chunkSize;
		char			m_format[4];
		char			m_subChunkId[4];
		unsigned long	m_subChunkSize;
		unsigned short	m_audioFormat;
		unsigned short	m_numChannels;
		unsigned long	m_sampleRate;
		unsigned long	m_bytesPerSecond;
		unsigned short	m_blockAlign;
		unsigned short	m_bitsPerSample;
		char			m_dataChunkId[4];
		unsigned long	m_dataSize;
	};

public:
	static CSimpleSound &CSimpleSound::GetInstance();
	CSimpleSound();	
	~CSimpleSound();

	bool Initialize(HWND);
	void Shutdown();
	
	bool PlaySound(const char *filename, DWORD flags = 0);
	bool StopSound(const char *filename);
	bool IsPlaying(const char *filename);
private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();

	bool LoadWaveFile(const char*);
	
private:
	IDirectSound8* m_directSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSoundBuffer8* m_secondaryBuffer1;
	std::map<const char *, IDirectSoundBuffer8 *> m_sounds;
};

#endif