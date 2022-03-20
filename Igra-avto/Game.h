#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text points;
	sf::Text startText;

	//Game logic
	bool endGame;
	unsigned pointss;
	float CrteSpawnTimer;
	float CrteSpawnTimerMax;
	float TextSpawnTimer;
	float TextSpawnTimerMax;
	bool spd;
	int lineSpeed;
	float enemySpeed;
	int health;
	int maxEnemies;
	bool mouseHeld;
	int arrowX;
	int arrowY;
	int movementSpeed;
	bool spawned;
	bool spd2;
	int score;
	int lane;
	int enemySpawnTimer;
	int enemySpawnTimerMax;
	int enemySpawn;

	bool neki;

	//Game objects

	sf::Texture pTexture;
	sf::Sprite playerImage;

	sf::Texture e1Texture;
	sf::Sprite enemy1Image;

	sf::Texture e2Texture;
	sf::Sprite enemy2Image;

	sf::RectangleShape road;
	sf::RectangleShape crta;
	sf::RectangleShape trava;
	sf::RectangleShape trava2;

	std::vector<sf::RectangleShape> CrtkaneCrte1;
	sf::RectangleShape crtkanaCrta1;

	std::vector<sf::RectangleShape> CrtkaneCrte2;
	sf::RectangleShape crtkanaCrta2;

	std::vector<sf::RectangleShape> CrtkaneCrte3;
	sf::RectangleShape crtkanaCrta3;

	//Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initRoad();
	void initTrava();
	void initText();
	void initPlayer();
	void initEnemy1();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	//void spawnEnemy();
	void spawnEnemy();
	void spawnEnemy2();
	void spawnCrtkanaCrta();

	void pollEvents();
	void updateMousePositions();
	void updatePlayer();
	void updateText();
	void updateEnemy1();
	void updateRoad();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderStartText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void renderPlayer(sf::RenderTarget& target);
	void renderRoad(sf::RenderTarget& target);
	void renderTrava(sf::RenderTarget& target);
	void render();
};