#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "headerEnum.hpp"
#include "Resources.hpp"

class SettingsValues
{
    public:
        ~SettingsValues();
        static SettingsValues& getInstance();
        int* getVolumeMusic();
        int* getVolumeEat();
        int* getVolumeClick();
        int* getVolumeGameOver();
        int* getLength();
        int* getFoodCount();
        bool* getWallCrash();
        bool* getSelfCrash();
        Difficulty* getDifficulty();

        void setSettings();
        void getSettings();
    private:
        SettingsValues();
        SettingsValues(const SettingsValues&) = delete;
        void operator=(const SettingsValues&) = delete;
        static SettingsValues m_instance;

        Resources& m_resource;

        int m_volume_music;
        int m_volume_eat;
        int m_volume_click;
        int m_volume_game_over;
        int m_length;
        int m_food_count;
        bool m_wall_crash_b;
        bool m_self_crash_b;
        Difficulty m_difficulty;
};