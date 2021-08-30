#include "../headers/CFood.hpp"

using namespace sf;
using namespace std;

//food constructor
CFood::CFood(Difficulty difficulty, CNode* head): 
m_counter(0, 960, 35, false),
m_highscore(initHighscore(difficulty), 40, 35, true),
m_difficulty(difficulty),
m_resource(CResources::getInstance())
{
    //set attributes for crunch sound
    m_crunch_sound.setBuffer(m_resource.m_crunch_buffer);
    m_crunch_sound.setVolume(m_settings.getVolumeEat());
    //set attributes of food sprite
    m_food_sprite.setTexture(m_resource.m_food_texture);
    //food gets spawned at random position in window
    setRandCoordinates(head);
}

CFood::~CFood()
{
    //get new highscore
    switch(m_difficulty)
    {
        case Easy: m_highscore_easy = m_highscore.getScore(); break;
        case Medium: m_highscore_medium = m_highscore.getScore(); break;
        case Hard: m_highscore_hard = m_highscore.getScore(); break;
        case Extreme: m_highscore_extreme = m_highscore.getScore(); break;
        case Impossible: m_highscore_impossible = m_highscore.getScore(); break;
    }

    //write all highscores to file
    ofstream output;
    output.open(m_resource.DATA_PATH + "highscore.txt");
    output << "HighscoreEasy{" << m_highscore_easy << "}\n";
    output << "HighscoreMedium{" << m_highscore_medium << "}\n";
    output << "HighscoreHard{" << m_highscore_hard << "}\n";
    output << "HighscoreExtreme{" << m_highscore_extreme << "}\n";
    output << "HighscoreImpossible{" << m_highscore_impossible << "}\n";
    output.close();
}

//simple draw function
void CFood::draw(RenderTarget& target, RenderStates states) const
{   
    //draws counter and food
    target.draw(m_food_sprite);
    target.draw(m_counter);
    target.draw(m_highscore);
};

//returns food bounds for collition check
FloatRect CFood::getFoodBounds()
{
    return m_food_sprite.getGlobalBounds();
}

//function is called when food gets eaten
void CFood::gotEaten(CNode* head)
{
    //crunch sound
    m_crunch_sound.play();
    //varibales for itteration and collition check
    CNode *temp = head;
    bool collition;

    //counter gets increased by one and new coordinates are set
    if(m_counter.getScore() >= m_highscore.getScore())
    {
        m_highscore.increaseScore(1);
    }
    m_counter.increaseScore(1);
    setRandCoordinates(head);
}

//set coordinates for new food
void CFood::setRandCoordinates(CNode* head)
{
    //food bound of new food location and body bound for snake
    FloatRect food_bound, body_bound;
    bool collition;
    CNode* temp;
    
    //do while checks once if new food coordinates collide with snake(if yes while loop until not)
    do
    {   
        //random coordinates get chosen
        m_pos_x = (rand() % 941 + 39);
        m_pos_y = (rand() % 941 + 39);
        //coordinates need to be increment of 40 to fit on grid
        m_pos_x = m_pos_x - (m_pos_x % 40);
        m_pos_y = m_pos_y - (m_pos_y % 40);
        //coordinates get passed to sprite
        m_food_sprite.setPosition(m_pos_x, m_pos_y);

        //temp pointer starts on head node, collition is set to false
        temp = head;
        collition = false;
        //while loop itterates through whole snake
        while(temp != NULL)
        {
            //body bound gets set to current node bound
            body_bound = temp->m_node.getGlobalBounds();
            //when new food and node collide variable is set to true, new coordinates are set and while loop breaks
            if(getFoodBounds().intersects(body_bound)) 
            {
                collition = true;
                break;
            }    
            //pointer points to next node
            temp = temp->next;
        }
    //loop itterates as long as collition is true        
    }while(collition == true);  
}

//initialise the highscore from text file
unsigned int CFood::initHighscore(Difficulty difficulty)
{
    int arr[5], fst, lst;
    string tempString;

    ifstream input;
    input.open(m_resource.DATA_PATH + "highscore.txt");

    //loop for retrieving values and writing them to temporary array
    for(int i = 0; i < 5; i++)
    {
        getline(input, tempString);
        //value is enclosed in curly brackets e.g. {20}
        fst = tempString.find("{");
        lst = tempString.find("}");
        //create substring only containing the value, convert it and write it to array
        arr[i] = stoi(tempString.substr(fst + 1, lst - fst));
    }
    
    //assign values from array to respective highscore variables
    m_highscore_easy = arr[0];
    m_highscore_medium = arr[1];
    m_highscore_hard = arr[2];
    m_highscore_extreme = arr[3];
    m_highscore_impossible = arr[4];

    input.close();

    //return difficulty value for highscore
    switch(difficulty)
    {
        case Easy: return m_highscore_easy;
        case Medium: return m_highscore_medium;
        case Hard: return m_highscore_hard;
        case Extreme: return m_highscore_extreme;
        case Impossible: return m_highscore_impossible;
    }
}