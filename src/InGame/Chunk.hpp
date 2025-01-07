#ifndef CHUNK_H
#define CHUNK_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
class Chunk
{
    private:
       sf::Texture texture;
       sf::Sprite sprite;
       sf::Vector2f pos;

    public:
        int ChunkSize = 16;
        int width = 16;
        int height = 16;


        
};

#endif
