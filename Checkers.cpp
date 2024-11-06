#include "Checkers.h"

void CheckerBoard::drawBoard(sf::RenderWindow& window)
{   
    //Variables
    sf::Vector2u windowSize = window.getSize();
    unsigned int windowWidth = windowSize.x;
    unsigned int windowHeight = windowSize.y;
    float newWidth = windowWidth;
 

    // Create a texture for the checkerboard (you need to provide a file path)
    sf::Texture texture;
    if (!texture.loadFromFile(image)) {
        // Error loading image
        return;
    }

    // Create a sprite using the loaded texture
    sf::Sprite sprite(texture);

    //retrieve the aspect ratio 
    float aspectRatio = static_cast<float>(texture.getSize().x) / texture.getSize().y;

    // sets the height to the width/aspectratio
    float newHeight = windowWidth / aspectRatio;

    //ensures things run as smoothly as possible
    if (newHeight > windowHeight) {
        newHeight = windowHeight;
        newWidth = newHeight * aspectRatio;
    }



    // Sets the origin of the window to the middle of the screen
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);


    // sets the position
    sprite.setPosition(windowWidth / 2.f, windowHeight / 2.f);

    //sets the scale
    sprite.setScale(newWidth / texture.getSize().x, newHeight / texture.getSize().y);

    //Draws the sprite onto the window
    window.draw(sprite);
}

float Piece::getPositionX()
{
    return positionX;
}

float Piece::getPositionY()
{
    return positionY;
}

void Piece::setPositionX(float x)
{
    positionX = x;
}

void Piece::setPositionY(float y)
{
    positionY = y;
}

float Piece::getRadius()
{
    return radius;
}

void Piece::drawPiece(sf::RenderWindow& window,float x, float y)
{  
    // Create a circle shape
    sf::CircleShape circle;

    // Set the radius of the circle
    circle.setRadius(radius);

  
    circle.setPosition(x - radius, y - radius); // Position the circle so its center is at (x, y)

    // Set the fill color to red
    circle.setFillColor(col);
    
    //draws the circle
    window.draw(circle);

}

void Player::addPiece(Piece piece)
{
    pieces.push_back(piece);
    
}

void Player::removePiece(Piece piece)
{
    for (unsigned short i = 0; i <pieces.size(); i++)
    {
        if (piece.getPositionX()== pieces.at(i).getPositionX())
        {
            pieces.erase(pieces.begin() + i);
        }
    }
}

void Player::draw_allPieces(sf::RenderWindow& window)
{
    for (int i = 0; i < pieces.size(); i++)
    {
        drawPiece(window, pieces.at(i).getPositionX(), pieces.at(i).getPositionY());

        // testing purposes
    //    std::cout << std::endl;
      //  std::cout << pieces.at(i).getPositionX() << ", " << pieces.at(i).getPositionY();
    }
        
    
}

void Piece::setColor(sf::Color lol)
{
    col = lol;
}

Piece Player::getPiece(int i)
{
    return pieces.at(i);
}

Piece Player::selectPiece(sf::RenderWindow& window, CheckerBoard& board, const sf::Event::MouseButtonEvent& event) {

    sf::FloatRect rect;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    for (int u = 0; u < pieces.size(); u++)
    {
        sf::FloatRect rect(getPiece(u).getPositionX() - 20.0f, getPiece(u).getPositionY() - 20.0f, 50, 50);
        if (rect.contains(static_cast<sf::Vector2f>(mousePosition)))
        {
            pieces.at(u).setColor(sf::Color::Green);
            pieces.at(u).drawPiece(window, getPiece(u).getPositionX(), getPiece(u).getPositionY());
            std::cout << "You are hovering" << std::endl;

            if (event.button == sf::Event::MouseButtonPressed) {
                if (event.button == sf::Mouse::Left) {
                    std::cout << "You clicked on a button " << std::endl;
                    return getPiece(u);
                }

            }
        }
    }
}

float CheckerBoard::getY(int x,int y)
{
    return coordinatestop[x][y].second;
}

float CheckerBoard::getX(int x, int y)
{
    return coordinatestop[x][y].first;
}

void Player::movePiece(Piece piece, sf::RenderWindow& window, CheckerBoard& board, const sf::Event::MouseButtonEvent& event)
{
    sf::FloatRect rect;
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y< 4; y++)
        {
            sf::FloatRect rect(board.getX(x, y) - 20.0f, board.getY(x, y) - 20.0f, 50, 50);
            if (rect.contains(static_cast<sf::Vector2f>(mousePosition)))
            {
                if (event.button== sf::Event::MouseButtonPressed) {
                    if (event.button == sf::Mouse::Left) {
                        std::cout << "You clicked on a button" << std::endl;
                        piece.setPositionX(board.getX(x,y)); piece.setPositionY(board.getY(x,y));
                        std::cout << "Piece has successfully moved" << std::endl;
                    }
                }
            }
        }
    }
}
