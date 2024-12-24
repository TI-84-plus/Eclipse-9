#ifndef CHUNK_H
#define CHUNK_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
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