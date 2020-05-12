#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Menu.h"

class MapReader;
class Object;
class Player;

class Game
{
public:
	Game();
	void Run();

	void PlaySound(std::string input);
	void SetWin(bool result) { m_GameWin = result; }

private:
	void Init();

	void Update(float dt);
	void UpdateText();
	void UpdateCamera();
	void CheckGameState();

	void Draw();
	void DrawPauseText(sf::RenderWindow& window);
	void Reset();


private:
	sf::RenderWindow m_Window;

	MapReader m_MapReader;
	sf::View m_Camera;

	std::unique_ptr<Player> m_Player;
	sf::Texture m_PlayerTexture;

	std::vector<Enemy> m_Enemys;

	std::vector<std::unique_ptr<Object>> m_Objects;
	sf::Texture m_ObjectTexture;
	
	Menu m_Menu;

	sf::Font m_Font;
	sf::Text m_LivesText;
	sf::Text m_ScoreText;

	sf::SoundBuffer m_Buffer;
	sf::Sound m_Sound;
	sf::Music m_Music;

	bool m_Paused;
	bool m_GameOver;
	bool m_GameWin;


};

