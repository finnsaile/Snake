#include "../headers/CFood.hpp"

//food constructor
CFood::CFood(Difficulty difficulty): 
sf::Drawable(), 
counter(0, 960, 35, false),
settings(false),
foodRect(sf::IntRect(0, 0, 40, 40)),
highscore(initHighscore(difficulty), 40, 35, true),
difficulty(difficulty)
{
    //load crunch sound and apple texture
    crunchBuffer.loadFromFile(dataPath + "Sounds/Crunch.wav");
    foodTexture.loadFromFile(dataPath + "Floor/Apple.png");
    //set attributes for crunch sound
    crunch.setBuffer(crunchBuffer);
    crunch.setVolume(settings.getVolumeEat());
    //food gets spawned at random position in window
    this->setRandCoordinates();
    //set attributes of food sprite
    foodSprite.setTexture(foodTexture);
    foodSprite.setTextureRect(foodRect);
}
CFood::~CFood()
{
    switch(difficulty)
    {
        case Easy: highscoreEasy = highscore.getScore(); break;
        case Medium: highscoreMedium = highscore.getScore(); break;
        case Hard: highscoreHard = highscore.getScore(); break;
        case Extreme: highscoreExtreme = highscore.getScore(); break;
        case Impossible: highscoreImpossible = highscore.getScore(); break;
    }

    std::ofstream output;
    output.open(dataPath + "highscore.txt");
    output << highscoreEasy << "\n";
    output << highscoreMedium << "\n";
    output << highscoreHard << "\n";
    output << highscoreExtreme << "\n";
    output << highscoreImpossible << "\n";
    output.close();
}

//simple draw function
void CFood::draw(sf::RenderTarget& target, sf::RenderStates states) const
{   
    //draws counter and food
    target.draw(foodSprite);
    target.draw(counter);
    target.draw(highscore);
};

//returns food bounds for collition check
sf::FloatRect CFood::returnRect()
{
    return foodSprite.getGlobalBounds();
}

//function is called when food gets eaten
void CFood::gotEaten(CNode* head)
{
    //crunch sound
    crunch.play();
    //varibales for itteration and collition check
    CNode *temp = head;
    bool collition;

    //counter gets increased by one and new coordinates are set
    if(counter.getScore() >= highscore.getScore())
    {
        highscore.increaseScore(1);
    }
    counter.increaseScore(1);
    this->setRandCoordinates();
    
    //food bound of new food location and body bound for snake
    sf::FloatRect foodBound = this->returnRect();
    sf::FloatRect bodyBound;
    
    //do while checks once if new food coordinates collide with snake(if yes while loop until not)
    do
    {
        //temp pointer starts on head node, collition is set to false
        temp = head;
        collition = false;
        //while loop itterates through whole snake
        while(temp != NULL)
        {
            //body bound gets set to current node bound
            bodyBound = temp->m_node.getGlobalBounds();
            //when new food and node collide variable is set to true, new coordinates are set and while loop breaks
            if(foodBound.intersects(bodyBound)) 
            {
                this->setRandCoordinates();
                foodBound = this->returnRect();
                collition = true;
                break;
            }    
            //pointer points to next node
            temp = temp->next;
        }
    //loop itterates as long as collition is true        
    }while(collition == true);
    
}

//set coordinates for new food
void CFood::setRandCoordinates()
{
    //random coordinates get chosen
    posX = (rand() % 941 + 39);
    posY = (rand() % 941 + 39);
    //coordinates need to be increment of 40 to fit on grid
    posX = posX - (posX % 40);
    posY = posY - (posY % 40);
    //coordinates get passed to sprite
    foodSprite.setPosition(posX, posY);
}

unsigned int CFood::initHighscore(Difficulty difficulty)
{
    std::string highscoreStr;

    std::ifstream input;
    input.open(dataPath + "highscore.txt");

    std::getline(input, highscoreStr);
    highscoreEasy = stoi(highscoreStr);
    
    std::getline(input, highscoreStr);
    highscoreMedium = stoi(highscoreStr);
    
    std::getline(input, highscoreStr);
    highscoreHard = stoi(highscoreStr);
    
    std::getline(input, highscoreStr);
    highscoreExtreme = stoi(highscoreStr);
    
    std::getline(input, highscoreStr);
    highscoreImpossible = stoi(highscoreStr);

    input.close();
    switch(difficulty)
    {
        case Easy: return highscoreEasy;
        case Medium: return highscoreMedium;
        case Hard: return highscoreHard;
        case Extreme: return highscoreExtreme;
        case Impossible: return highscoreImpossible;
    }
}