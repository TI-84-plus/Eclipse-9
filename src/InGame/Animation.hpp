#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>


class Frame {
	public:
		sf::IntRect rect;
		double duration;
};


class Animation {

	private:
    sf::Sprite *target;
	std::vector<std::unique_ptr<sf::Texture>> &m_textures;
	double totalProgress;
	double totalLength;

    public:
	  std::vector<std::vector<Frame>> frames;
	  int currentFrame = 0;

      Animation(sf::Sprite &target, std::vector<std::unique_ptr<sf::Texture>> &textures);
  
	  void addFrame(int left, int top, int width, int height, double duration); 
	  
	  void update(double elapsed);
};


#endif
