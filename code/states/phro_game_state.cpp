/***** P R O J E C T   P H R O N E S I S ******
**********************************************/

#include "phro_game_state.hpp"

GameState::GameState(Data* gameData, StateStack* stack): State(gameData, stack)
{
	//Additional load for this state
	//loadResources();
	
	emptyWorld = new World(data);
	
	guiView.setSize(sf::Vector2f(data->window.getSize()));
	guiView.setCenter(sf::Vector2f(data->window.getSize()) * 0.5f);
	
	//area = Section(10, 8, "assets/plain.section");
	//area = Section(16, 11, "assets/test.section");
	//area.acquireResource(&data->rscStorage);
}

GameState::~GameState()
{
	delete emptyWorld;
}

void GameState::draw()
{
	data->window.clear(sf::Color::Red);
	
	emptyWorld->draw();
	
	data->window.setView(guiView);
	//area.draw(data->window);
}

bool GameState::update(float dt)
{
	//area.updateTileVariant();
	emptyWorld->update(dt);
	return true;
}

bool GameState::handleEvent()
{
	if(data->inputSystem.isActive("resize"))
	{
		guiView.setSize(sf::Vector2f(data->window.getSize()));
		guiView.setCenter(sf::Vector2f(data->window.getSize()) * 0.5f);
		
		emptyWorld->resizeView();
	}
	
	return true;
}

void GameState::loadResources()
{
	sf::Vector2f screenCenter = sf::Vector2f(data->window.getSize()) * 0.5f;
	
	data->rscStorage.loadTexture("void00", "assets/tiles/generic/blackTile00.png");
	
	for(int i = 0; i <= 12; i++)
	{
		string tName;
		string tAddr;
		char tVar1 = '0' + (i/10);
		char tVar2 = '0' + (i%10);
		
		tName = "dirt";
		tName += tVar1; tName += tVar2;
		tAddr = "assets/tiles/dirt/dirtTile";
		tAddr += tVar1; tAddr += tVar2; tAddr += ".png";
		data->rscStorage.loadTexture(tName, tAddr);
		
		tName = "grass";
		tName += tVar1; tName += tVar2;
		tAddr = "assets/tiles/grass/grassTile";
		tAddr += tVar1; tAddr += tVar2; tAddr += ".png";
		data->rscStorage.loadTexture(tName, tAddr);
		
		tName = "lake";
		tName += tVar1; tName += tVar2;
		tAddr = "assets/tiles/lake/lakeTile";
		tAddr += tVar1; tAddr += tVar2; tAddr += ".png";
		data->rscStorage.loadTexture(tName, tAddr);
	}
}
