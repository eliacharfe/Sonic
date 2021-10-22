#pragma once
#include "Utilities.h" 

class Sounds {
public:
	static Sounds& instance();

	void playSound(TypeSound type);

	void playMusic(TypeMusic type);
	void stopMusic(TypeMusic type);
	void pauseMusic(TypeMusic type);
	void lowMusic(TypeMusic type);

private:
	Sounds();
	Sounds(const Sounds&) = default;
	Sounds& operator=(const Sounds&) = default;
	void loadSounds();

	map < TypeSound, sf::SoundBuffer > m_mapSoundBuffer;
	map < TypeSound, sf::Sound > m_mapSounds;

	map < TypeMusic, sf::Music > m_mapMusic;

};
