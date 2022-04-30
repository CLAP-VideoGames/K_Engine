#pragma once
#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <ecs_prj/Component.h>

typedef struct _Mix_Music Mix_Music;
class Mix_Chunk;

namespace K_Engine {
	class AudioManager;
	struct Audio;
	enum class AudioType;

	class __declspec(dllexport) AudioSource : public Component
	{
	public:
		AudioSource();
		AudioSource(Entity* e);
		AudioSource(Entity* e, AudioType type, char* path, int vol, bool loop, bool start);

		virtual ~AudioSource();

		static std::string GetId();

		virtual void init(K_Map* information);

		virtual void start();

		/// <summary>
		/// It's called every frame of the game.
		/// </summary> 
		virtual void update(int frameTime);

		// Play Audio
		void play();
		void pause();
		void resume();
		void stop();

		// Volume
		void setVolume(float vol);
		float getVolume();

	private:
		//Required
		static std::string name;

		K_Engine::AudioManager* audioMan;

		Audio* audio;
		int volume; // Volume of audio

		bool loopable, playStart;
		bool playing, paused;
	};
}
#endif // AUDIOSOURCE_H