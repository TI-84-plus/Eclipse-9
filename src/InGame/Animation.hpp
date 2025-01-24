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

      Animation(sf::Sprite &target, std::vector<std::unique_ptr<sf::Texture>> &textures) : m_textures{textures} { 
		this->target = &target;
		totalProgress = 0.0;
      }


	  void addFrame(int left, int top, int width, int height, double duration) {

		  std::vector<Frame> set_frame;

		  for(int i = 0; i < 21; i++) {
			
			Frame frame;
			frame.rect.top = top;
			frame.rect.left = left*i;
			frame.rect.width = width;
			frame.rect.height = height;
			frame.duration = duration;
			
			set_frame.push_back(frame);
			totalLength += frame.duration;
		}
			frames.push_back(set_frame);
	}
	  
	
	  void update(double elapsed) {
		totalProgress += elapsed;
		double progress = totalProgress;

		
		for(Frame &frame : frames[currentFrame]) {
			progress -= frame.duration;

			std::cout<<"totalprogress: "<<progress<<std::endl;	
			if (progress <= 0.0 || &frame == &frames[currentFrame].back()) {
				target->setTextureRect(frame.rect);

				//reset
				if(&frame == &frames[currentFrame].back())
					{totalProgress = 0.0;} 
				break;
			}
		}
		
	}	
 };


#endif
