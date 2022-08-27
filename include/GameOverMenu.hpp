#pragma once
#include <SFML/Graphics.hpp>
#include "GameMenu.hpp"
class GameOverMenu : public GameMenu
{
    public:
        GameOverMenu(Game*, sf::Texture&, sf::Texture&, sf::Texture&);
    private:
        sf::Sound m_game_over_sound;
};

