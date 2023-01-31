/// <summary>
/// author Kieran Cocker
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void centreText();
	void changeCharacterName();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_SuperMario256; // font used by message
	sf::Text m_CharacterName; // Name of character displayed on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	sf::Texture m_marioTexture; // texture used for mario and luigi
	sf::Sprite m_marioSprite; // sprite used for mario and luigi
	bool m_exitGame; // control exiting game
	bool m_imAMario{ true }; // Change from mario to luigi

};

#endif // !GAME_HPP

