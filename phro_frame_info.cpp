/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include <iostream>
#include <fstream>
#include <sstream>

#include "phro_frame_info.hpp"

void FrameInfo::readFile(const string& fileName)
{
	ifstream infoFile;
	infoFile.open(fileName);
	
	if(infoFile.is_open())
	{
		//cout << "Reading file [" << fileName << "]:" << endl;
		
		string desc, line;
		float sizeX, sizeY;
		int dimX, dimY;
		vector<string> modes;
		
		infoFile >> desc >> sizeX >> sizeY;
		infoFile >> desc >> dimX >> dimY;
		
		frameSize = sf::Vector2i(sizeX, sizeY);
		dimensions = sf::Vector2i(dimX, dimY);
		
		infoFile >> desc >> frameDelay;
		
		infoFile >> desc;
		getline(infoFile, line);
		stringstream lineStream(line);
		
		while(!lineStream.fail())
		{
			string modeName;
			lineStream >> modeName;
			if(!lineStream.fail())
				modes.push_back(modeName);
		}
		lineStream.clear();
		
		for(int i = 0; i < modes.size(); i++)
		{
			vector<int> framePos;
			
			getline(infoFile, line);
			lineStream.str(line);
			
			lineStream >> desc;
			while(!lineStream.fail())
			{
				int pos;
				lineStream >> pos;
				if(!lineStream.fail())
					framePos.push_back(pos);
			}
			
			modeType[modes[i]] = framePos;
			lineStream.clear();
		}
		
		infoFile.close();
		
		/*cout << "frameSize: " << sizeX << " " << sizeY << endl;
		cout << "dimensions: " << dimX << " " << dimY << endl;
		for(auto mtype : modeType)
		{
			cout << "  key: ";
			for(int i = 0; i < mtype.second.size(); i++)
				cout << mtype.second[i] << " ";
			cout << endl;
		}*/
		
	}
	else
	{
		cout << "Fail loading [" << fileName << "]" << endl;
		exit(1);
	}
}

sf::Vector2i FrameInfo::frameOrigin(int frameNumber)
{
	int row = (frameNumber-1) / dimensions.x;
	int column = (frameNumber-1) % dimensions.x;
	return sf::Vector2i(column * frameSize.x, row * frameSize.y);
}

int FrameInfo::defaultFrame()
{
	int def = 1;
	if(modeType.count("default") > 0)
		def = modeType["default"][0];
	return def;
}

sf::IntRect FrameInfo::getFrameRect(int frameNumber)
{
	return sf::IntRect(frameOrigin(frameNumber), frameSize);
}
