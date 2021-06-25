#include "../headers/CGameOverMenu.hpp"

CGameOverMenu::CGameOverMenu(CGame* game, std::string menuTexturePath, std::string button1TexturePath, std::string button2TexturePath):
CGameMenu::CGameMenu(game, menuTexturePath, button1TexturePath, button2TexturePath, 490, 610)
{
    this->gameOverSoundBuffer.loadFromFile(dataPath + "Sounds/GameOverSound.wav");
    this->gameOverSound.setVolume(settings.getVolumeGameOver());
    this->gameOverSound.setBuffer(gameOverSoundBuffer);
    this->gameOverSound.play();
}

