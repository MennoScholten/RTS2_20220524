#pragma once
#include "Block.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Tetromino : public sf::Drawable
{
	std::vector<Block*> blockArray;
	float originX = 0.0;    // X-axis Origin of the shape 
	float originY = 0.0;    // Y-axis Origin of the shape

	float positionX = 0.0;  // X-axis pixel position of the shape
	float positionY = 0.0;  // Y-axis Pixel position of the shape

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Virtual function to draw custom classes 

	void setupIBlock(float x, float y);
	void setupLBlock(float x, float y);
	void setupJBlock(float x, float y);
	void setupZBlock(float x, float y);
	void setupSBlock(float x, float y);
	void setupTBlock(float x, float y);
	void setupBBlock(float x, float y);

public:
	enum blockType { I, L, J, Z, S, T, B }; // Enum for holding blocktypes

	// Constructors
	Tetromino();
	Tetromino(blockType type);
	Tetromino(float posX, float posY, blockType type);
	~Tetromino();

	std::vector<Block*> getBlocks();

	void getPosition(float& x, float& y);

	void setPosition(float x, float y);
	void setColor(const sf::Color blockColor);

	void moveTetromino(float x, float y);
	void rotateTetromino(float angleDeg);

};
