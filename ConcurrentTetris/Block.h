#pragma once
#include <SFML/Graphics.hpp>

class Block : public sf::Drawable
{
private:

    sf::RectangleShape block;   // Datatype to draw a rectangular/square block 

    const float width = 30; // Size in pixels 
    const float height = 30; // Size in pixels

    float originX = 0.0;    // X-axis Origin of the shape 
    float originY = 0.0;    // Y-axis Origin of the shape

    float positionX = 0.0;  // X-axis pixel position of the shape
    float positionY = 0.0;  // Y-axis Pixel position of the shape

    int position_row = 0; // position in gameboard          // Might be removed!
    int position_column = 0; // position in gameboard       // Might be removed!

    sf::Color color = sf::Color::Transparent;
    bool isAlive = false;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Virtual function to draw custom classes 

public:
    // Constructors
    Block();    // Default constructor
    Block(int row, int col, const sf::Color blockColor);   // Might be removed!
    Block(float positionX, float positionY,  sf::Color blockColor); // float originX, float originY,

    // Accessors
    float getWidth() const;
    float getHeight() const;
    sf::Color getColor() const;

    void getPosition(float& x, float& y);
    float getPositionX();
    float getPositionY();
    void getOrigin(float& x, float& y);
    float getOriginX();
    float getOriginY();

    // Modifiers

    void setPosition(float x, float y);
    void setPositionX(float x);
    void setPositionY(float y);
    void setOrigin(float x, float y);
    void setOriginX(float x);
    void setOriginY(float y);
    void setColor(const sf::Color blockColor);

    // Public Member functions
    void moveBlock(float x, float y);   // Function to move block to (X-Y) pixel location
    void rotateBlock(float a);          // Function to rotate block around origin by angle amount
    sf::Transform getBlockTransform();

};
