#ifndef SOUNDEXAMPLE_H
#define SOUNDEXAMPLE_H

typedef struct _Mix_Music Mix_Music;
class Mix_Chunk;

#include <memory>

class AudioManager
{
public:
	static AudioManager* getInstance();

	void Init();
	void Shutdown();
	~AudioManager() {};

	void update() {}
	void playWAV(const char* path);
	void playMUS(const char* path);

private:
	static std::unique_ptr<AudioManager> instance;

	Mix_Chunk* wav = nullptr;
	Mix_Music* mus = nullptr;

	void loadWAV(const char* path);
	void loadMUS(const char* path);
};
#endif // SOUNDEXAMPLE_H
