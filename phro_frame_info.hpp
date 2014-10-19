/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#ifndef PHRO_FRAME_INFO_HPP
#define PHRO_FRAME_INFO_HPP

#include <string>
#include <vector>
#include <map>
using namespace std;

#include <SFML/Graphics.hpp>

class FrameInfo
{
public:

	FrameInfo(){}
	FrameInfo(sf::Vector2i frameSize_, sf::Vector2i dimensions_)
	: frameSize(frameSize_), dimensions(dimensions_) {}

	void readFile(const string& fileName);
	
	sf::Vector2i frameOrigin(int frameNumber);
	int defaultFrame();
	sf::IntRect getFrameRect(int frameNumber);

	sf::Vector2i frameSize;
	sf::Vector2i dimensions;
	float frameDelay;
	map<string, vector<int> > modeType;
};

#endif // PHRO_FRAME_INFO_HPP
