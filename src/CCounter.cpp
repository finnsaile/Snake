#include "../headers/CCounter.hpp"


//Counter constructor initializes 2 colors and score with parameter
CCounter::CCounter(unsigned int initScore, int x, int y, bool highBool): 
sf::Drawable(), 
myBlack(0, 0, 0, 200), 
myGreen(140, 198, 63, 200),
myRed(198, 100, 63, 200),
score(initScore),
posX(x),
posY(y),
highscoreCounter(highBool)
{   
    //load score Font and set score text to initial value
    scoreFont.loadFromFile(dataPath + "Fonts/ARCADE_R.TTF");
    scoreText.setString(std::to_string(score));
    
    //counter attributes and position are initialized
    setCounterAttributes();
    setCounterPosition();
}

//increses score by given amount
void CCounter::increaseScore(unsigned int amount)
{
    score += amount;
    //score text gets updated
    scoreText.setString(std::to_string(score));
    //score position gets updated
    setCounterPosition();
}

//draw function draws score text
void CCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(scoreText);
}

//sets position of score counter
void CCounter::setCounterPosition()
{
    scoreText.getGlobalBounds();
    //origin is in the top right corner so score stays at the same position despite 2 digits
    if(highscoreCounter == true)
    {
        scoreText.setOrigin(0, 0);
    }
    else
    {
        scoreText.setOrigin(scoreText.getGlobalBounds().width, 0);
    }
    scoreText.setPosition(posX, posY);
}

//attributes of counter are set
void CCounter::setCounterAttributes()
{
    scoreText.setFont(scoreFont);
    
    scoreText.setCharacterSize(80);
    scoreText.setOutlineThickness(2);
    //own colors being used
    if(highscoreCounter == true)
    {
        scoreText.setFillColor(myRed);
    }
    else 
    {
        scoreText.setFillColor(myGreen);
    }
    
    scoreText.setOutlineColor(myBlack);
}

unsigned int CCounter::getScore()
{
    return score;
}