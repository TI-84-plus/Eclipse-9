#ifndef TEXTUREHANDLER_HPP
#define TEXTUREHANDLER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <unordered_map>

class TextureHandler {
	public:
		
		enum ResourceID {
			tileset,
		};

		std::unordered_map<ResourceID, sf::Texture> TextureMap;
		
		void AddResource(sf::Texture texture, ResourceID name) {

			switch(name) {
				case tileset: texture.loadFromFile("/home/fiveeght/Proc_Gen/src/content/tileset.png");
					break;
			};


			//text_arr.emplace_back(texture); 
		}

	private:



};

#endif
