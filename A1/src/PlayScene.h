#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "SpaceShip.h"
#include "SpaceShip2.h"
#include "SpaceShip3.h"
#include "SpaceShip4.h"
#include "Button.h"
#include "Label.h"
#include "Target.h"
#include "Obsticle.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Target* m_pTarget;
	SpaceShip* m_pSpaceShip;
	SpaceShip2* m_pSpaceShip2;
	SpaceShip3* m_pSpaceShip3;
	SpaceShip4* m_pSpaceShip4;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	Label* m_pInstructionsLabel2;
	Obsticle* m_pObsticle;

};

#endif /* defined (__PLAY_SCENE__) */