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
		double duration = 0.1;
};


class Animation {

	private:
	std::vector<Frame> frames;
    sf::Sprite *target;
	double totalProgress = 0;

	
    public:
      Animation(sf::Sprite& target) { 
        this->target = &target;
      }

	  void update(double elapsed) {
		totalProgress += elapsed;
		double progress = totalProgress;
		for(Frame frame : frames) {
			progress -= frame.duration;
		}
	  }	
 };




#endif
