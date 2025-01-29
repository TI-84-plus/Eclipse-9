#include "InGame/Animation.hpp"


Animation::Animation(sf::Sprite &target, std::vector<std::unique_ptr<sf::Texture>> &textures) : m_textures{textures} 
{
    this->target = &target;	
    totalProgress = 0.0;
};


void Animation::addFrame(int left, int top, int width, int height, double duration) 
{	  
    std::vector<Frame> set_frame;	  
    for(int i = 0; i < 21; i++) 
    {				
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
};
	  
	
void Animation::update(double elapsed) 
{	
    totalProgress += elapsed;	
    double progress = totalProgress;		
    for(Frame &frame : frames[currentFrame]) 
    {		
        progress -= frame.duration;		
        if (progress <= 0.0 || &frame == &frames[currentFrame].back()) 
        {			
            target->setTextureRect(frame.rect);			

            //Reset
            if(&frame == &frames[currentFrame].back())
				{totalProgress = 0.0;} 
            
            break;
        }
    }
};