#include <iostream>
#include <SFML/Window.hpp>
#include <string>
#include <SFML/Graphics.hpp>
#include <algorithm> // for std::find and std::remove_if
#include "mouse.cpp"


class CheckerBoard //This class has everything to do with the checkerboard and how it is displayed
{
private:
	// this is the location to the checkerboard used in the program
	std::string image= "C:/SoftwareDev/Project1/ImagesProject1/board.jpg";

	static const int coor_X = 9;
	static const int coor_Y = 4;
	

public:
	//this function draws the board onto a window
	void drawBoard(sf::RenderWindow& window);

	std::pair<float, float> coordinatestop[coor_X][coor_Y];
    void iniCoordinates()
    {
        // these two consts are used to to help initialize the values in the array
        const float holdx = 260.9f;
        const float holdy = 260.9f;
        float x = 140.0f;
        float y = 50.0f;
        float altx = 260.0f;
        float alty = 175.0f;
        // this section of code will be used to fuck around so I can get this god damn fucking code to work
        //_____________________________________________________________________________

        for (int i = 0; i < coor_X; i++)
        {
            if (i % 2 == 0 && i != 0)
            {
                for (int j = 0; j < coor_Y; j++)
                {
                    coordinatestop[i][j] = std::make_pair(altx, alty);
                    altx += holdx;
                }
                alty += holdy;
                altx = 270.0f;
            }

            else {
                for (int j = 0; j < coor_Y; j++) {

                    coordinatestop[i][j] = std::make_pair(x, y); // Set x and y coordinates


                    x += holdx;

                }
                y += holdy;
                x = 150.0f;
            }
        }
    }
    float getX(int x, int y);
    float getY(int x, int y);

};


class Piece // this class contains all the relevant info needed to manipulate a piece
{
private:
	float positionX;
	float positionY;
	float radius = 30.0f;
	sf::Color col = sf::Color::Red;
	
public:
	float getPositionX();
	float getPositionY();
	float getRadius();
	void setPositionX(float x);
	void setPositionY(float y);
	void drawPiece(sf::RenderWindow& window, float x, float y);
	void setColor(sf::Color lol);
};

class Player : public Piece // this class controls the player and what he can and cannot control it inherits the Piece class
{
private:
	int score;
	std::vector<Piece> pieces; // Collection of pieces owned by the player


public:
	int getScore();
	void addPiece(Piece piece);
	void removePiece(Piece piece);
	Piece getPiece(int i);
	Piece selectPiece(sf::RenderWindow& window, CheckerBoard& board,const sf::Event::MouseButtonEvent& event);
	void draw_allPieces(sf::RenderWindow& window);
    void movePiece(Piece piece, sf::RenderWindow& window, CheckerBoard& board, const sf::Event::MouseButtonEvent& event);
};
