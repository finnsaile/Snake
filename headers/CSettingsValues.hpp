#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "headerEnum.hpp"
#include "CResources.hpp"

class CSettingsValues
{
    public:
        ~CSettingsValues();
        static CSettingsValues& getInstance();
        int* getVolumeMusic();
        int* getVolumeEat();
        int* getVolumeClick();
        int* getVolumeGameOver();
        int* getLength();
        Difficulty* getDifficulty();

        void setSettings();
        void getSettings();
    private:
        CSettingsValues();
        CSettingsValues(const CSettingsValues&) = delete;
        void operator=(const CSettingsValues&) = delete;
        static CSettingsValues m_instance;

        CResources& m_resource;

        int m_volume_music;
        int m_volume_eat;
        int m_volume_click;
        int m_volume_game_over;
        int m_length;
        Difficulty m_difficulty;
};