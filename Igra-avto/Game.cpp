#include "Game.h"

/*
	* TO DO:
	* HIGH SCORE
	* Potholes
	* **Vec vozil
*/

//Private functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->pointss = 0;
	this->CrteSpawnTimerMax = 50.f;
	this->health = 100;
	this->CrteSpawnTimer = this->CrteSpawnTimerMax;
	this->lineSpeed = 2;
	this->enemySpeed = 0.0;
	this->maxEnemies = 5;
	this->mouseHeld = false;
	this->arrowX = 375;
	this->arrowY = 480;
	this->movementSpeed = 8;
	this->spawned = 0;
	this->score = 0;
	this->spd = false;
	this->lane = 0;
	this->spd2 = false;
	this->neki = false;
	this->TextSpawnTimer = 0.f;
	this->TextSpawnTimerMax = 300.f;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("arial.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
	}
}

void Game::initText()
{
	this->points.setFont(this->font);
	this->points.setPosition(5.f, 0.f);
	this->points.setCharacterSize(24);
	this->points.setFillColor(sf::Color::White);
	this->points.setStyle(sf::Text::Bold);

	this->startText.setFont(this->font);
	this->startText.setPosition(100.f, 250.f);
	this->startText.setCharacterSize(24);
	this->startText.setFillColor(sf::Color::Black);
	this->startText.setStyle(sf::Text::Bold);
	this->startText.setString("IZOGIBAJ SE NASPROTI VOZECIM AVTOMOBILOM \n              Z UPORABO SMERNIH TIPK");
}

void Game::initRoad() {
	this->road.setPosition(200.f, 0.f);
	this->road.setSize(sf::Vector2f(400.f, 600.f));
	this->road.setFillColor(sf::Color(128,128,128));
	this->road.setOutlineColor(sf::Color::White); 
	this->road.setOutlineThickness(4.f);

	this->crta.setPosition(395.f, 0.f);
	this->crta.setSize(sf::Vector2f(10.f, 600.f));
	this->crta.setFillColor(sf::Color(255, 255, 255));
}

void Game::initTrava() {
	this->trava.setPosition(0.f, 0.f);
	this->trava.setSize(sf::Vector2f(196.f, 600.f));
	this->trava.setFillColor(sf::Color(34, 139, 34));

	this->trava2.setPosition(604.f, 0.f);
	this->trava2.setSize(sf::Vector2f(196.f, 600.f));
	this->trava2.setFillColor(sf::Color(34, 139, 34));
}

void Game::initPlayer() {
	if (!this->pTexture.loadFromFile("player3.png"))
		std::cout << "error, NE DELA PIZDA" << std::endl;
	playerImage.setTexture(pTexture);
	playerImage.setPosition(400.f, 500.f);
}

void Game::initEnemy1() {
	if (!this->e1Texture.loadFromFile("enemy2.png"))
		std::cout << "error, NE DELA PIZDA - enemy" << std::endl;
	enemy1Image.setTexture(e1Texture);
	enemy1Image.setPosition(-100.f, 0.f);
	if (!this->e2Texture.loadFromFile("enemy3.png"))
		std::cout << "error, NE DELA PIZDA - enemy2" << std::endl;
	enemy2Image.setTexture(e2Texture);
	enemy2Image.setPosition(-100.f, 0.f);
}

//Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initPlayer();
	this->initRoad();
	this->initTrava();
	this->initEnemy1();
	//this->initEnemy();
	//this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Functions

void Game::spawnCrtkanaCrta() {
	this->crtkanaCrta1.setPosition(290.f, -50.f);
	this->crtkanaCrta1.setSize(sf::Vector2f(10.f, 50.f));
	this->crtkanaCrta1.setFillColor(sf::Color(255, 255, 255));

	this->crtkanaCrta2.setPosition(490.f, -50.f);
	this->crtkanaCrta2.setSize(sf::Vector2f(10.f, 50.f));
	this->crtkanaCrta2.setFillColor(sf::Color(255, 255, 255));

	this->crtkanaCrta3.setPosition(390.f, -50.f);
	this->crtkanaCrta3.setSize(sf::Vector2f(10.f, 50.f));
	this->crtkanaCrta3.setFillColor(sf::Color(255, 255, 255));

	this->CrtkaneCrte1.push_back(this->crtkanaCrta1);
	this->CrtkaneCrte2.push_back(this->crtkanaCrta2);
	this->CrtkaneCrte3.push_back(this->crtkanaCrta3);
}

void Game::spawnEnemy()
{
	int newlane = rand() % 4;
	while (newlane == this->lane) {
		newlane = rand() % 4;
	}
	this->lane = newlane;
	if (lane == 0) this->enemy1Image.setPosition(220.f, -110.f);
	else if (lane == 1) this->enemy1Image.setPosition(320.f, -110.f);
	else if (lane == 2) this->enemy1Image.setPosition(420.f, -110.f);
	else this->enemy1Image.setPosition(530.f, -110.f);
}

void Game::spawnEnemy2() {
	int newlane = rand() % 4;
	while (newlane == this->lane) {
		newlane = rand() % 4;
	}
	this->lane = newlane;
	if (this->lane == 0) this->enemy2Image.setPosition(220.f, -110.f);
	else if (this->lane == 1) this->enemy2Image.setPosition(320.f, -110.f);
	else if (this->lane == 2) this->enemy2Image.setPosition(420.f, -110.f);
	else this->enemy2Image.setPosition(520.f, -110.f);
}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			else if (this->ev.key.code == sf::Keyboard::Left) 
			{
				this->arrowX -= this->movementSpeed;
			}
			else if (this->ev.key.code == sf::Keyboard::Right)
			{
				this->arrowX += this->movementSpeed;
			}
			else if (this->ev.key.code == sf::Keyboard::Up)
			{
				this->arrowY -= this->movementSpeed;
			}
			else if (this->ev.key.code == sf::Keyboard::Down)
			{
				this->arrowY += this->movementSpeed;
			}
			
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/**
		@ return void
		Updates the mouse positions:
		- Mouse position relative to window (Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateRoad() {
	//Spawnanje crte
	if (this->CrteSpawnTimer >= this->CrteSpawnTimerMax)
	{
		//Spawn crto and reset timer
		this->spawnCrtkanaCrta();
		this->CrteSpawnTimer = 0.f;
	}
	else
		this->CrteSpawnTimer += 1.f;

	for (int i = 0; i < this->CrtkaneCrte1.size(); i++)
	{
		this->CrtkaneCrte1[i].move(0, lineSpeed);
		this->CrtkaneCrte2[i].move(0, lineSpeed);
		this->CrtkaneCrte3[i].move(0, lineSpeed);

		if (this->CrtkaneCrte1[i].getPosition().y > this->window->getSize().y)
		{
			this->CrtkaneCrte1.erase(this->CrtkaneCrte1.begin() + i);
			this->CrtkaneCrte2.erase(this->CrtkaneCrte2.begin() + i);
			this->CrtkaneCrte3.erase(this->CrtkaneCrte3.begin() + i);
		}
	}
}

void Game::updateText() {
	std::stringstream ss;
	std::string krampir;
	ss << this->score;
	ss >> krampir;
	this->points.setString(krampir);
}

void Game::updatePlayer() {
	this->playerImage.setPosition(this->arrowX, this->arrowY);
	if (playerImage.getPosition().x < 190) {
		std::cout << "Zletel si s ceste!" << std::endl;
		this->endGame = true;
	}
	else if (playerImage.getPosition().x > 560) {
		std::cout << "Zletel si s ceste!" << std::endl;
		this->endGame = true;
	}
}

void Game::updateEnemy1() {
	//Spawna prvi avto
	if (spawned == 0 && this->TextSpawnTimer==300) {
		this->spawnEnemy();
		this->enemySpeed = 2;
		spawned = 1;
	}
	//Premikanje - povecuje hitrost
	bool deleted = false;
	int enemySpawned = rand() % 2;
	if (score == 5 && score != 0 && spd != true) {
		this->enemySpeed += 1.0;
		this->spd = true;
		std::cout << "FASTER" << std::endl;
	}
	else if (score == 20 && score != 0 && spd2 != true) {
		this->enemySpeed += 0.5;
		this->spd2 = true;
		std::cout << "FASTER" << std::endl;
		this->spd = false;
	}
	else if(score == 40 && score != 0 && spd != true){
		this->enemySpeed += 0.5;
		this->spd = true;
		std::cout << "FASTER" << std::endl;
	}
	else if (score == 60 && score != 0 && spd != true) {
		this->enemySpeed += 0.5;
		this->spd2 = true;
		std::cout << "FASTER" << std::endl;
		this->spd2 = false;
	}
	else if (score == 80 && score != 0 && spd2 != true) {
		this->enemySpeed += 0.5;
		this->spd2 = true;
		std::cout << "FASTER" << std::endl;
	}
	//Preveri ce se player zaleti v drug avto
	if (this->playerImage.getGlobalBounds().intersects(enemy1Image.getGlobalBounds()) || this->playerImage.getGlobalBounds().intersects(enemy2Image.getGlobalBounds())) {
		std::cout << "Zaletel si se!" << std::endl;
		this->endGame = true;
	}
	//Premika avto 1 in avto 2
	this->enemy1Image.move(0, enemySpeed);
	this->enemy2Image.move(0, enemySpeed);
	if (this->enemy1Image.getPosition().y > 300 && neki!=true) {
		this->spawnEnemy2();
		this->neki = true;
	}
	if (this->enemy1Image.getPosition().y > this->window->getSize().y) this->neki = false;
	//Spawna
	if (this->enemy1Image.getPosition().y > this->window->getSize().y)
	{
		score++;
		std::cout << "Score: " << score << std::endl;
		this->spawnEnemy();
	}
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateRoad();

		this->updatePlayer();

		this->updateEnemy1();
		
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->points);
}

void Game::renderStartText(sf::RenderTarget& target) {
	if (this->TextSpawnTimer < this->TextSpawnTimerMax)
	{
		target.draw(this->startText);
		this->TextSpawnTimer += 1.f;
	}
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	target.draw(this->enemy1Image);
	target.draw(this->enemy2Image);
}

void Game::renderPlayer(sf::RenderTarget& target)
{
	
	target.draw(this->playerImage);
}

void Game::renderRoad(sf::RenderTarget& target)
{
	target.draw(this->road);
	for (auto& e : this->CrtkaneCrte1)
	{
		target.draw(e);
	}
	for (auto& e : this->CrtkaneCrte2)
	{
		target.draw(e);
	}
	for (auto& e : this->CrtkaneCrte3)
	{
		target.draw(e);
	}
}

void Game::renderTrava(sf::RenderTarget& target) {
	target.draw(this->trava);
	target.draw(this->trava2);
}

void Game::render()
{
	/**
		@return void
		- clear old frame
		- render objects
		- display frame in window
		Renders the game objects.
	*/

	this->window->clear();

	//Draw game objects
	this->renderRoad(*this->window);

	this->renderTrava(*this->window);

	this->renderEnemies(*this->window);

	this->renderPlayer(*this->window);

	this->renderText(*this->window);

	this->renderStartText(*this->window);

	this->window->display();
}