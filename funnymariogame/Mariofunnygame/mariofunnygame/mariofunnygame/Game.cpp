/// <summary>
/// @author Kieran Cocker
/// @date Janurary 2023
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::KeyReleased == newEvent.type) // Code to check if key is released
		{
			processKeyReleases(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		changeCharacterName();
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	getDirection();
	if (checkBounds())
	{
		move();
	}
	move();

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_logoSprite);
	m_window.draw(m_marioSprite);
	m_window.draw(m_CharacterName);
	m_window.display();
}

void Game::move()
{
	sf::Vector2f move{ 0.0f,0.0f };
	switch (m_facing)
	{
	case Direction::None:
		break;
	case Direction::Up:
		move.y = -m_speed;
		break;
	case Direction::Down:
		move.y = m_speed;
		break;
	case Direction::Left:
		move.x = -m_speed;
		break;
	case Direction::Right:
		move.x = m_speed;
		break;
	default:
		break;
	}
	m_position += move;
	m_marioSprite.setPosition(m_position);
}

void Game::getDirection()
{
	m_facing = Direction::None;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_facing = Direction::Up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_facing = Direction::Down;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_facing = Direction::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_facing = Direction::Right;
	}
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_SuperMario256.loadFromFile("ASSETS\\FONTS\\SuperMario256.ttf"))
	{
		std::cout << "problem loading Super Mario font" << std::endl;
	}
	m_CharacterName.setFont(m_SuperMario256);
	m_CharacterName.setString("Mario");
	m_CharacterName.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_CharacterName.setPosition(400.0f, 50.0f);
	m_CharacterName.setCharacterSize(80U);
	m_CharacterName.setOutlineColor(sf::Color::Black);
	m_CharacterName.setFillColor(sf::Color::Red);
	m_CharacterName.setOutlineThickness(3.0f);

}

void Game::changeCharacterName()
{
	if (m_canChange)
	{
		if (m_imAMario)
		{
			m_CharacterName.setString("Luigi");
		}
		else
		{
			m_CharacterName.setString("Mario");
		}
		m_imAMario = !m_imAMario;
		m_canChange = false;
	}
	centreText(m_CharacterName, 50.0f);
	

	
}
void Game::processKeyReleases(sf::Event t_event)
{
	m_canChange = true;
}

bool Game::checkBounds()
{
	bool canMove{ true };
	if (m_position.y < 0.0f)
	{
		canMove = false;
		m_position.y = 0.0f;
	}
	if (m_position.y > 452.0f)
	{
		canMove = false;
		m_position.y = 452.0f;
	}
	if (m_position.x < 0.0f)
	{
		canMove = false;
		m_position.x = 0.0f;
	}
	if (m_position.x > 736.0f)
	{
		canMove = false;
		m_position.x = 736.0f;
	}
	return canMove;
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	m_buffer.loadFromFile("ASSETS\\AUDIO\\mario.wav");
	m_sound.setBuffer(m_buffer);
	m_sound.play();


	if (!m_marioTexture.loadFromFile("ASSETS\\IMAGES\\mario-luigi-64.png"))
	{
		// Error message if call fails
		std::cout << "problem loading sprite mario" << std::endl;
	}


	m_marioSprite.setTexture(m_marioTexture);
	m_marioSprite.setTextureRect(sf::IntRect(0, 0, 64, 148));
	m_marioSprite.setPosition(300.0f, 180.0f);
}

void Game::centreText(sf::Text& t_text, float t_yCoord)
{
	sf::Vector2f location{ 0.0f,0.0f };
	location.y = t_yCoord;
	location.x = 400.0f - t_text.getGlobalBounds().width / 2.0f;
	t_text.setPosition(location);
}
