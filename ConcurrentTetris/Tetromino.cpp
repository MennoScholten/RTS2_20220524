#include "Tetromino.h"

Tetromino::Tetromino()
{
	//Block a(0.f, 0.f, 0.f, 0.f, sf::Color::Cyan);
	this->blockArray.push_back(new Block(0.f, 0.f, 0.f, 0.f, sf::Color::Cyan));
}

Tetromino::Tetromino(blockType type)
{
	switch (type) {
	case I:
		setupIBlock(100, 100);
	case L:
		setupLBlock(100, 100);
	case J:
		setupJBlock(100, 100);
	case Z:
		setupZBlock(100, 100);
	case S:
		setupSBlock(100, 100);
	case T:
		setupTBlock(100, 100);
	case B:
		setupBBlock(100, 100);
	}
}

Tetromino::Tetromino(float posX, float posY, blockType type)
{
	this->positionX = posX;
	this->positionY = posY;
	switch (type) {
	case I:
		setupIBlock(this->positionX, this->positionY);
		break;
	case L:
		setupLBlock(this->positionX, this->positionY);
		break;
	case J:
		setupJBlock(this->positionX, this->positionY);
		break;
	case Z:
		setupZBlock(this->positionX, this->positionY);
		break;
	case S:
		setupSBlock(this->positionX, this->positionY);
		break;
	case T:
		setupTBlock(this->positionX, this->positionY);
		break;
	case B:
		setupBBlock(this->positionX, this->positionY);
		break;
	}

}

Tetromino::~Tetromino()
{
	this->blockArray.clear();
}

std::vector<Block*> Tetromino::getBlocks()
{
	return this->blockArray;
}


void Tetromino::getPosition(float& x, float& y)
{
	x = this->positionX;
	y = this->positionY;
}

void Tetromino::setPosition(float x, float y)
{
	this->positionX = x;
	this->positionY = y;
}

void Tetromino::setColor(const sf::Color blockColor)
{
	for (int i = 0; i < this->blockArray.size(); i++) {
		this->blockArray[i]->setColor(blockColor);
	}
}

void Tetromino::moveTetromino(float x, float y)
{
	for (int i = 0; i < this->blockArray.size(); i++) {
		this->blockArray[i]->moveBlock(x, y);
	}
}

void Tetromino::rotateTetromino(float angleDeg)
{
	for (int i = 0; i < this->blockArray.size(); i++) {
		this->blockArray[i]->rotateBlock(angleDeg);
	}
}

void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < this->blockArray.size(); i++) {
		target.draw(*blockArray[i]);
	}
}

void Tetromino::setupIBlock(float x, float y)
{
	this->blockArray.push_back(new Block(x, y, 100.f, 50.f, sf::Color::Cyan));
	this->blockArray.push_back(new Block(x, y, 50.f, 50.f, sf::Color::Cyan));
	this->blockArray.push_back(new Block(x, y, 0.f, 50.f, sf::Color::Cyan));
	this->blockArray.push_back(new Block(x, y, -50.f, 50.f, sf::Color::Cyan));
}

void Tetromino::setupLBlock(float x, float y)
{
	this->blockArray.push_back(new Block(x, y, 75.f, 75.f, sf::Color::White));
	this->blockArray.push_back(new Block(x, y, 75.f, 25.f, sf::Color::White));
	this->blockArray.push_back(new Block(x, y, 25.f, 25.f, sf::Color::White));
	this->blockArray.push_back(new Block(x, y, -25.f, 25.f, sf::Color::White));
}

void Tetromino::setupJBlock(float x, float y)
{
	this->blockArray.push_back(new Block(x, y, 75.f, 25.f, sf::Color::Blue));
	this->blockArray.push_back(new Block(x, y, 25.f, 25.f, sf::Color::Blue));
	this->blockArray.push_back(new Block(x, y, -25.f, 25.f, sf::Color::Blue));
	this->blockArray.push_back(new Block(x, y, -25.f, 75.f, sf::Color::Blue));
}

void Tetromino::setupZBlock(float x, float y)
{
	this->blockArray.push_back(new Block(x, y, 75.f, 25.f, sf::Color::Green));
	this->blockArray.push_back(new Block(x, y, 25.f, 25.f, sf::Color::Green));
	this->blockArray.push_back(new Block(x, y, 25.f, 75.f, sf::Color::Green));
	this->blockArray.push_back(new Block(x, y, -25.f, 75.f, sf::Color::Green));
}

void Tetromino::setupSBlock(float x, float y)
{
	this->blockArray.push_back(new Block(x, y, 75.f, 75.f, sf::Color::Red));
	this->blockArray.push_back(new Block(x, y, 25.f, 75.f, sf::Color::Red));
	this->blockArray.push_back(new Block(x, y, 25.f, 25.f, sf::Color::Red));
	this->blockArray.push_back(new Block(x, y, -25.f, 25.f, sf::Color::Red));
}

void Tetromino::setupTBlock(float x, float y)
{
	this->blockArray.push_back(new Block(x, y, 25.f, 75.f, sf::Color::Magenta));
	this->blockArray.push_back(new Block(x, y, 75.f, 25.f, sf::Color::Magenta));
	this->blockArray.push_back(new Block(x, y, 25.f, 25.f, sf::Color::Magenta));
	this->blockArray.push_back(new Block(x, y, -25.f, 25.f, sf::Color::Magenta));
}

void Tetromino::setupBBlock(float x, float y)
{
	this->blockArray.push_back(new Block(x, y, 50.f, 50.f, sf::Color::Yellow));
	this->blockArray.push_back(new Block(x, y, 0.f, 50.f, sf::Color::Yellow));
	this->blockArray.push_back(new Block(x, y, 50.f, 0.f, sf::Color::Yellow));
	this->blockArray.push_back(new Block(x, y, 0.f, 0.f, sf::Color::Yellow));
}
