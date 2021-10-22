#include "Sounds.h"

Sounds::Sounds()
{
	loadSounds();
}
//----------------------------
void Sounds::loadSounds()
{
	if (   !m_mapSoundBuffer[TypeSound::EmeraldType].loadFromFile("Sonic the Hedgehog - Chaos Emerald.ogg")
		|| !m_mapSoundBuffer[TypeSound::Bounce].loadFromFile("bounce_sound.ogg")
		|| !m_mapSoundBuffer[TypeSound::EnemySlowType].loadFromFile("enemy_hit.ogg")
		|| !m_mapSoundBuffer[TypeSound::EnemyFastType].loadFromFile("fast_enemy_hit.ogg")
		|| !m_mapSoundBuffer[TypeSound::SpikesType].loadFromFile("spikes_sound.ogg")
		|| !m_mapSoundBuffer[TypeSound::PlayerHurt].loadFromFile("player_hurt.ogg")
		|| !m_mapSoundBuffer[TypeSound::BossHurt].loadFromFile("boss_hurt.ogg")
		|| !m_mapSoundBuffer[TypeSound::LevelComplete].loadFromFile("Level Complete.ogg")
		|| !m_mapSoundBuffer[TypeSound::GameOverSound].loadFromFile("Game Over.ogg")
		|| !m_mapSoundBuffer[TypeSound::ExtraLife].loadFromFile("Extra Life.ogg")
		|| !m_mapSoundBuffer[TypeSound::RingSound].loadFromFile("ringSound.ogg")
		|| !m_mapSoundBuffer[TypeSound::BossDead].loadFromFile("bossDeadSound.ogg")
		|| !m_mapSoundBuffer[TypeSound::MouseWheel].loadFromFile("mouseWheel.ogg")
		|| !m_mapSoundBuffer[TypeSound::Click].loadFromFile("click_sound.ogg")
		|| !m_mapSoundBuffer[TypeSound::SmoothClick].loadFromFile("smooth click.ogg")
		|| !m_mapSoundBuffer[TypeSound::BulletType].loadFromFile("bullet_sound.ogg")
		|| !m_mapSoundBuffer[TypeSound::JumpSound].loadFromFile("Sonic Jump Sound Effect.ogg"))
		throw std::runtime_error("Cannot load sound...\n");

	for (auto iter = m_mapSoundBuffer.begin(); iter != m_mapSoundBuffer.end(); iter++)
		m_mapSounds[iter->first].setBuffer(m_mapSoundBuffer[iter->first]);

	if (!m_mapMusic[TypeMusic::Music1].openFromFile("Genesis - Boss Battle.ogg")
	|| !m_mapMusic[TypeMusic::Music2].openFromFile("SpringYardZone.ogg")
	|| !m_mapMusic[TypeMusic::Music3].openFromFile("Sugar Splash.ogg")
	|| !m_mapMusic[TypeMusic::MainMenuMusic].openFromFile("Main Menu.ogg")
	|| !m_mapMusic[TypeMusic::HelpWindowMusic].openFromFile("Genesis - Rusty Ruins Zone - Act 1.ogg")
	|| !m_mapMusic[TypeMusic::GameOverWindowMusic].openFromFile("Sonic 3D - Credits.ogg")
	|| !m_mapMusic[TypeMusic::CreatorModeMusic].openFromFile("Sonic-Red Moon.ogg"))
		throw std::runtime_error("Can't load music...\n");

	for (auto iter = m_mapMusic.begin(); iter != m_mapMusic.end(); iter++)
		m_mapMusic[iter->first].setLoop(true);
}
//-----------------------------
Sounds& Sounds::instance()
{
	static Sounds inst;
	return inst;
}
//----------------------------------
void Sounds::playSound(TypeSound type)
{
	if((int)type < 0 || (int)type >= m_mapSounds.size())
		throw std::out_of_range("No sush sound loaded\n");
	m_mapSounds.find(type)->second.play();
}
//-------------------------------------
void Sounds::playMusic(TypeMusic type)
{
	if ((int)type < 0 || (int)type >= m_mapMusic.size())
		throw std::out_of_range("No sush music loaded\n");

	m_mapMusic.find(type)->second.pause();
	m_mapMusic.find(type)->second.setVolume(100);
	m_mapMusic.find(type)->second.setPlayingOffset(m_mapMusic[type].getPlayingOffset());
	m_mapMusic.find(type)->second.play();
}
//--------------------------------------
void Sounds::stopMusic(TypeMusic type)
{
	if ((int)type < 0 || (int)type >= m_mapMusic.size())
		throw std::out_of_range("No sush music loaded\n");

	m_mapMusic.find(type)->second.stop();
}
//-------------------------------------
void Sounds::pauseMusic(TypeMusic type)
{
	if ((int)type < 0 || (int)type >= m_mapMusic.size())
		throw std::out_of_range("No sush music loaded\n");

	m_mapMusic.find(type)->second.pause();
}
//-----------------------------------
void Sounds::lowMusic(TypeMusic type)
{
	if ((int)type < 0 || (int)type >= m_mapMusic.size())
		throw std::out_of_range("No sush music loaded\n");

	m_mapMusic.find(type)->second.pause();
	m_mapMusic.find(type)->second.setVolume(50);
	m_mapMusic.find(type)->second.setPlayingOffset(m_mapMusic[type].getPlayingOffset());
	m_mapMusic.find(type)->second.play();
}
//-------------------------------------
















	//m_mapSounds[TypeSound::EmeraldType].setBuffer(m_mapSoundBuffer[TypeSound::EmeraldType]);
	//m_mapSounds[TypeSound::Bounce].setBuffer(m_mapSoundBuffer[TypeSound::Bounce]);
	//m_mapSounds[TypeSound::EnemySlowType].setBuffer(m_mapSoundBuffer[TypeSound::EnemySlowType]);
	//m_mapSounds[TypeSound::EnemyFastType].setBuffer(m_mapSoundBuffer[TypeSound::EnemyFastType]);
	//m_mapSounds[TypeSound::SpikesType].setBuffer(m_mapSoundBuffer[TypeSound::SpikesType]);
	//m_mapSounds[TypeSound::SpikesType].setVolume(60);
	//m_mapSounds[TypeSound::PlayerHurt].setBuffer(m_mapSoundBuffer[TypeSound::PlayerHurt]);
	//m_mapSounds[TypeSound::BossHurt].setBuffer(m_mapSoundBuffer[TypeSound::BossHurt]);
	//m_mapSounds[TypeSound::LevelComplete].setBuffer(m_mapSoundBuffer[TypeSound::LevelComplete]);
	//m_mapSounds[TypeSound::GameOverSound].setBuffer(m_mapSoundBuffer[TypeSound::GameOverSound]);
	//m_mapSounds[TypeSound::ExtraLife].setBuffer(m_mapSoundBuffer[TypeSound::ExtraLife]);
	//m_mapSounds[TypeSound::RingSound].setBuffer(m_mapSoundBuffer[TypeSound::RingSound]);
	//m_mapSounds[TypeSound::BossDead].setBuffer(m_mapSoundBuffer[TypeSound::BossDead]);
	//m_mapSounds[TypeSound::MouseWheel].setBuffer(m_mapSoundBuffer[TypeSound::MouseWheel]);
	//m_mapSounds[TypeSound::Click].setBuffer(m_mapSoundBuffer[TypeSound::Click]);
	//m_mapSounds[TypeSound::SmoothClick].setBuffer(m_mapSoundBuffer[TypeSound::SmoothClick]);
	//m_mapSounds[TypeSound::FootSteps].setBuffer(m_mapSoundBuffer[TypeSound::FootSteps]);
	//m_mapSounds[TypeSound::BulletType].setBuffer(m_mapSoundBuffer[TypeSound::BulletType]);


	//m_mapMusic[TypeMusic::Music1].setLoop(true);
	//m_mapMusic[TypeMusic::Music2].setLoop(true);
	//m_mapMusic[TypeMusic::Music3].setLoop(true);
	//m_mapMusic[TypeMusic::MainMenuMusic].setLoop(true);
	//m_mapMusic[TypeMusic::HelpWindowMusic].setLoop(true);
	//m_mapMusic[TypeMusic::GameOverWindowMusic].setLoop(true);
	//m_mapMusic[TypeMusic::CreatorModeMusic].setLoop(true);