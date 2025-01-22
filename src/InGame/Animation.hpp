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
	  std::vector<Frame> frames;
      Animation(sf::Sprite &target, std::vector<std::unique_ptr<sf::Texture>> &textures) : m_textures{textures} { 
		this->target = &target;
		//this->textures std::move(textures);
		//this->textures.push_back(std::make_unique<sf::Texture>(texture));
		totalProgress = 0.0;
      }

	  void addFrame(Frame frame) {
		  frames.push_back(frame);
		  totalLength += frame.duration;
	}
	  void update(double elapsed) {
		totalProgress += elapsed;
		double progress = totalProgress;

		for(Frame &frame : frames) {
			progress -= frame.duration;

			if (progress <= 0.0 || &frame == &frames.back()) {
				target->setTextureRect(frame.rect);
				
				break;
			}
		}
		//Start over
		if(progress == 21) {
			totalProgress = 0.0;
		}
		
		}	
 };


#endif
