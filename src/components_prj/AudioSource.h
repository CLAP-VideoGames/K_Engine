#pragma once
#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <ecs_prj/Component.h>
#include <string>

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
		AudioSource(Entity* e, AudioType type, std::string path, float vol, int channel, bool loop, bool start);

		virtual ~AudioSource();

		static std::string GetId();

		virtual void init(K_Map* information);

		virtual void start();

		/// <summary>
		/// It's called every frame of the game.
		/// </summary> 
		virtual void update(int frameTime);

		virtual void onEnable();
		virtual void onDisable();

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

		bool loopable, playStart;
		bool playing, paused;

		bool toPlay = false;
	};
}
#endif // AUDIOSOURCE_H