#ifndef SOUNDEXAMPLE_H
#define SOUNDEXAMPLE_H

typedef struct _Mix_Music Mix_Music;
class Mix_Chunk;

class SoundExample
{
public:
	SoundExample();
	~SoundExample();

	void playWAV(const char* path);
	void playMP3(const char* path);

private:
	Mix_Chunk* wav = nullptr;
	Mix_Music* mus = nullptr;

	void init();

	void loadWAV(const char* path);
	void loadMP3(const char* path);

	void shutdown();
};
#endif // SOUNDEXAMPLE_H