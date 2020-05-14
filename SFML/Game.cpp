#include "Game.h"
#include "Object.h"
#include "MapReader.h"
#include "GoalObject.h"
#include "PointObject.h"

Game::Game()
	: m_Window(sf::VideoMode(1024, 1024), "2D Platformer")
	, m_MapReader("testlevel.txt")
	, m_Camera()
	, m_Player(nullptr)
	, m_PlayerTexture()
	, m_Enemys()
	, m_Objects()
	, m_Menu(m_Window, "Atari.ttf")
	, m_Font()
	, m_LivesText()
	, m_ScoreText()
	, m_Paused(false)
	, m_GameOver(false)
{
	Init();
}

void Game::Init()
{
	// loading texture and constructing player class
	m_PlayerTexture.loadFromFile("characterspritesheet.png");
	m_Player = std::make_unique<Player>(m_PlayerTexture);

	m_EnemyTexture.loadFromFile("enemyTexture.png");

	m_ObjectTexture.loadFromFile("objects.png");

	// load objects into list
	for (auto& obj : m_MapReader.GetObjectSpawnPositions())
	{
		// if the number of the enum found in the MapReader list is after 1 (or after Type::Star), it is a goal object. 
		if ((int)obj.objectType > 1)
		{
			m_Objects.push_back(std::make_unique<GoalObject>(obj.objectType, m_ObjectTexture));
		}
		// otherwise, its a point object
		else
		{
			m_Objects.push_back(std::make_unique<PointObject>(obj.objectType, m_ObjectTexture));
		}
	}

	// load enemys into list
	for (auto& x : m_MapReader.GetEnemySpawnPositions())
	{
		m_Enemys.push_back(Enemy(m_EnemyTexture));
	}

	// text for lives and score
	m_Font.loadFromFile("Atari.ttf");

	m_LivesText.setFont(m_Font);
	m_ScoreText.setFont(m_Font);

	m_LivesText.setString("Lives:\n" + std::to_string(m_Player->GetLives()));
	m_ScoreText.setString("Score:\n" + std::to_string(m_Player->GetScore()));
	
	m_Music.openFromFile("music.wav");

	Reset();
}

void Game::Run()
{
	m_Music.play();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time deltaTime = sf::seconds(1.f / 60.f);

	while (m_Window.isOpen())
	{
		sf::Event event;
		while (m_Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_Window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (m_GameOver || m_GameWin) 
					{
						Reset();
						m_GameOver = false;
						m_GameWin = false;
					}
				}

				if (event.key.code == sf::Keyboard::Escape)
				{
					PlaySound("smb_pause.wav");

					if (!m_Paused)
					{
						m_Music.pause();
						m_Paused = true;
					}
					else
					{
						m_Music.play();
						m_Paused = false;
					}
				}
			}
		}

		Update(deltaTime.asSeconds());

		m_Window.clear();
		Draw();

		m_Window.display();
	}
}

void Game::Update(float dt)
{
	if (!m_Paused && !m_GameOver && !m_GameWin)
	{
		m_Window.setView(m_Camera);

		// player/enemy/object/projectiles updates
		m_Player->Update(dt, m_MapReader);

		for (auto& enemy : m_Enemys)
		{
			enemy.Update(dt, m_MapReader, *m_Player);
		}

		for (auto& obj : m_Objects)
		{
			obj->DetectCollision(*m_Player, *this);
		}

		for (auto& prj : m_Player->GetProjectiles())
		{
			// if the projectie hits something, then remove it
			// p.s might cause problems if size > 1 because it always pops the first shot
			if (!prj.isExisting())
			{
				m_Player->GetProjectiles().pop_front();
			}

			prj.Update(dt, m_MapReader, m_Enemys, *m_Player);
			
		}
		
		UpdateText();
		UpdateCamera();
		CheckGameState();
	}
}

void Game::UpdateText()
{
	// move text along with the camera
	m_ScoreText.setPosition(m_Camera.getCenter().x + 300, m_Camera.getCenter().y - 475);
	m_LivesText.setPosition(m_Camera.getCenter().x - 475, m_Camera.getCenter().y - 475);

	// changing lives text
	if (m_Player->LivesChanged())
	{
		if (m_Player->GetLives() == 0)
		{
			m_Music.stop();
			PlaySound("smb_gameover.wav");
			m_GameOver = true;
		}

		m_LivesText.setString("Lives:\n" + std::to_string(m_Player->GetLives()));
		m_Player->SetPosition(m_MapReader.GetPlayerSpawnPosition());
		m_Player->SetLivesChanged(false);
		Reset();
	}

	// changing score text
	if (m_Player->ScoreChanged())
	{
		m_ScoreText.setString("Score:\n" + std::to_string(m_Player->GetScore()));
		m_Player->SetScoreChanged(false);
	}
}

void Game::UpdateCamera()
{
	// camera update
	// rightmost out-of-bounds area
	if (m_Player->GetPosition().x >= 5500.f)
	{
		m_Camera.setCenter(5500.f, 512);
	}
	// leftmost out-of-bounds area
	else if (m_Player->GetPosition().x <= 530.f)
	{
		m_Camera.setCenter(530.f, 512);
	}
	// if the camera isn't out-of-bounds, follow the player
	else
	{
		m_Camera.setCenter(std::floor(m_Player->GetPosition().x), 512);
	}
}

void Game::CheckGameState()
{	
	// draw game over menu if the player is dead
	if (m_GameOver)
	{
		m_Menu.SetGameOverScreen();
	}
	// draw game over menu if the player has won
	else if (m_GameWin)
	{
		m_Music.stop();
		m_Menu.SetWinScreen();
	}
}

void Game::DrawPauseText(sf::RenderWindow& window)
{
	sf::Text text;

	text.setFont(m_Font);
	text.setPosition(m_Camera.getCenter().x - 50, m_Camera.getCenter().y - 150);
	text.setString("PAUSED");

	window.draw(text);

}

void Game::Draw()
{
	// draw map/text
	m_Window.draw(m_MapReader);
	
	m_Window.draw(m_LivesText);
	m_Window.draw(m_ScoreText);

	// drawing player/enemies/objects
	m_Player->DrawSprite(m_Window);

	for (auto& objSprite : m_Objects)
	{
		objSprite->DrawSprite(m_Window);
	}

	for (auto& enemy : m_Enemys)
	{
		enemy.DrawSprite(m_Window);
	}

	for (auto& prj : m_Player->GetProjectiles())
	{
		prj.Draw(m_Window);
	}

	// drawing menu or pause screen
	if (m_GameOver || m_GameWin)
	{
		m_Window.setView(m_Camera);
		m_Menu.DrawMenu(m_Window);
	}
	else if (m_Paused)
	{
		DrawPauseText(m_Window);
	}
}

void Game::Reset()
{
	if (!m_GameOver)
	{
		m_Music.play();
	}

	// player reset
	if (m_GameOver || m_GameWin)
	{
		m_Player->Reset();
		m_LivesText.setString("Lives:\n" + std::to_string(m_Player->GetLives()));
		m_ScoreText.setString("Score:\n" + std::to_string(m_Player->GetScore()));

		m_Player->SetPosition(m_MapReader.GetPlayerSpawnPosition());
	}

	// enemy reset
	for (int i = 0; i < m_Enemys.size(); i++)
	{
		m_Enemys[i].Reset();
		m_Enemys[i].SetPosition(m_MapReader.GetEnemySpawnPositions()[i]);
	}
	
	// object reset
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->SetTaken(false);
		m_Objects[i]->SetPosition(m_MapReader.GetObjectSpawnPositions()[i].position);
	}
}

void Game::PlaySound(std::string input)
{
	m_Buffer.loadFromFile(input);
	m_Sound.setBuffer(m_Buffer);
	m_Sound.play();
}

