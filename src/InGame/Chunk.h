#ifndef CHUNK_H
#define CHUNK_H

#include "SFML/Config.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
class Chunk
{
    private:
       int ChunkSize = 8;
       sf::Texture texture;
       sf::Sprite sprite;
       sf::Vector2f pos;

};

#endif