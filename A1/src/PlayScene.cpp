#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive() )
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_LEFT))
	{
		//target moves to the left
		m_pSpaceShip->setRotationAngle(m_pSpaceShip->getRotationAngle() - 5);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_RIGHT))
	{
		//target moves to the left
		m_pSpaceShip->setRotationAngle(m_pSpaceShip->getRotationAngle() + 5);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		//target moves to the left
		m_pTarget->getTransform()->position.x = m_pTarget->getTransform()->position.x - 3;
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		//target moves to the right
		m_pTarget->getTransform()->position.x = m_pTarget->getTransform()->position.x + 3;
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		//target moves to the up
		m_pTarget->getTransform()->position.y = m_pTarget->getTransform()->position.y - 3;
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		//target moves to the down
		m_pTarget->getTransform()->position.y = m_pTarget->getTransform()->position.y + 3;
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{

	// Set GUI Title
	m_guiTitle = "Play Scene";
	

	// Target Sprite
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pTarget);

	// SpaceShip Sprite
	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 100.0f);
	m_pSpaceShip->setEnabled(false);
	m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pSpaceShip);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	//addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	//addChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press 1 for Seeking, 2 for Arrival,", "Roboto-Regular");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);
	addChild(m_pInstructionsLabel);


	m_pInstructionsLabel2 = new Label(" 3 for Fleeing, 4 for Obstical Avoidance", "Roboto-Regular");
	m_pInstructionsLabel2->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 525.0f);
	addChild(m_pInstructionsLabel2);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float shipSpeed = 2.0f;
	if (ImGui::SliderFloat("Ship Speed", &shipSpeed, 0.0f, 5.0f))
	{
		m_pSpaceShip->setMaxSpeed(shipSpeed);
	}


	static float angleInRadians = m_pSpaceShip->getRotationAngle();
	if (ImGui::SliderAngle("Orientation Angle", &angleInRadians))
	{
		m_pSpaceShip->setRotationAngle(angleInRadians * Util::Rad2Deg);
	}


	if(ImGui::Button("Initiate"))
	{
		m_pSpaceShip->setEnabled(true);
	}

	ImGui::SameLine();

	if (ImGui::Button("Stop"))
	{
		m_pSpaceShip->setEnabled(false);
		m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 100.0f);
	}
	ImGui::Separator();
	static float TargetPosition[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y };
	if (ImGui::SliderFloat2("Target", TargetPosition, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(TargetPosition[0], TargetPosition[1]);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}



	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
