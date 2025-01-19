#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Frame {
	public:
		sf::IntRect rect;
		double duration;
};


class Animation {

	private:
	std::vector<Frame> frames;
    sf::Sprite *target;
	sf::Texture *texture;
	double totalProgress;
	double totalLength;

    public:
      Animation(sf::Sprite &target, sf::Texture &texture) { 
        this->target = &target;
		this->texture = &texture;
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
				std::cout<<progress<<std::endl;
				target->setTexture(*texture);
				break;
			}
		}
		//Start over
		if(progress == 21) {
			totalProgress = 0.0;
			std::cout<<"reset"<<std::endl;
		}
		
		}	
 };


#endif
