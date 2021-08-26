#pragma once
#include <SFML/Graphics.hpp>
#include "dataPath.hpp"

class CResources 
{
    public:
        static CResources& getInstance();

        std::string DATA_PATH;
        
        sf::Texture m_head_w;
        sf::Texture m_head_a;
        sf::Texture m_head_s;
        sf::Texture m_head_d;

        sf::Texture m_body_ws;
        sf::Texture m_body_ad;

        sf::Texture m_body_aw;
        sf::Texture m_body_dw;
        sf::Texture m_body_as;
        sf::Texture m_body_ds;

        sf::Texture m_tail_w;
        sf::Texture m_tail_a;
        sf::Texture m_tail_s;
        sf::Texture m_tail_d;

    private:
        CResources();
        CResources(const CResources&) = delete;
        void operator=(const CResources&) = delete;
        static CResources m_instance;
};
