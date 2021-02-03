#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "CollisionManager.h"
using namespace std;

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

	if (CollisionManager::AABBCheck(m_pSpaceShip4, m_pObsticle))
	{
		m_pSpaceShip3->getRigidBody()->velocity -= m_pSpaceShip3->getRigidBody()->velocity;
	}
	CollisionManager::AABBCheck(m_pSpaceShip, m_pTarget);
	CollisionManager::AABBCheck(m_pSpaceShip2, m_pTarget);
	CollisionManager::AABBCheck(m_pSpaceShip3, m_pTarget);
	CollisionManager::AABBCheck(m_pSpaceShip4, m_pTarget);

	if (Util::distance(m_pSpaceShip3->getTransform()->position, m_pTarget->getTransform()->position) < 30)
	{
		m_pSpaceShip3->getRigidBody()->velocity -= m_pSpaceShip3->getRigidBody()->velocity;
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();
	int Drawn = 0;
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_KP_0))
	{	
		m_pSpaceShip->setEnabled(false);
		m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setRotationAngle(0.0f); // set angle to 0 degrees

		m_pSpaceShip2->setEnabled(false);
		m_pSpaceShip2->getTransform()->position = glm::vec2(600.0f, 400.0f);
		m_pSpaceShip2->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip2->setRotationAngle(0.0f); // set angle to 0 degrees

		m_pSpaceShip3->setEnabled(false);
		m_pSpaceShip3->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceShip3->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip3->setRotationAngle(0.0f); // set angle to 0 degrees

		m_pSpaceShip4->setEnabled(false);
		m_pSpaceShip4->getTransform()->position = glm::vec2(100.0f, 300.0f);
		m_pSpaceShip4->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip4->setRotationAngle(0.0f); // set angle to 0 degrees

		m_pTarget->setEnabled(false);
		m_pTarget->getTransform()->position = glm::vec2(700.0f, 500.0f);
		m_pTarget->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);

		m_pObsticle->setEnabled(false);
		m_pObsticle->getTransform()->position = glm::vec2(600.0f, 300.0f);
		m_pObsticle->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_KP_1))
	{
		//Seeking
		m_pSpaceShip->setEnabled(true);
		m_pTarget->setEnabled(true);

	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_KP_2))
	{
		//Fleeing
		m_pSpaceShip2->setEnabled(true);
		m_pTarget->setEnabled(true);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_KP_3))
	{
		//Arrival
		m_pSpaceShip3->setEnabled(true);
		m_pTarget->setEnabled(true);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_KP_4))
	{
		//Obstical Avoidance
		m_pSpaceShip4->setEnabled(true);
		m_pObsticle->setEnabled(true);
		m_pTarget->setEnabled(true);
		m_pTarget->getTransform()->position = glm::vec2(700.0f, 300.0f);
		m_pTarget->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		//target moves to the left
		m_pTarget->getTransform()->position.x = m_pTarget->getTransform()->position.x - 3;
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip2->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip3->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip4->setDestination(m_pTarget->getTransform()->position);

	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		//target moves to the right
		m_pTarget->getTransform()->position.x = m_pTarget->getTransform()->position.x + 3;
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip2->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip3->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip4->setDestination(m_pTarget->getTransform()->position);
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		//target moves to the up
		m_pTarget->getTransform()->position.y = m_pTarget->getTransform()->position.y - 3;
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip2->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip3->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip4->setDestination(m_pTarget->getTransform()->position);
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		//target moves to the down
		m_pTarget->getTransform()->position.y = m_pTarget->getTransform()->position.y + 3;
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip2->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip3->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip4->setDestination(m_pTarget->getTransform()->position);
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
	m_pTarget->getTransform()->position = glm::vec2(700.0f, 500.0f);
	m_pTarget->setEnabled(false);
	addChild(m_pTarget);

	//Obsticle Sprite
	m_pObsticle = new Obsticle();
	m_pObsticle->getTransform()->position = glm::vec2(600.0f, 300.0f);
	m_pObsticle->setEnabled(false);
	addChild(m_pObsticle);


	// SpaceShip Sprite
	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->getTransform()->position = glm::vec2(100.0f,100.0f);
	m_pSpaceShip->setEnabled(false);
	m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pSpaceShip);

	// SpaceShip Sprite2
	m_pSpaceShip2 = new SpaceShip2();
	m_pSpaceShip2->getTransform()->position = glm::vec2(600.0f, 400.0f);
	m_pSpaceShip2->setEnabled(false);
	m_pSpaceShip2->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pSpaceShip2);

	// SpaceShip Sprite3
	m_pSpaceShip3 = new SpaceShip3();
	m_pSpaceShip3->getTransform()->position = glm::vec2(100.0f, 100.0f);
	m_pSpaceShip3->setEnabled(false);
	m_pSpaceShip3->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pSpaceShip3);

	// SpaceShip Sprite4
	m_pSpaceShip4 = new SpaceShip4();
	m_pSpaceShip4->getTransform()->position = glm::vec2(100.0f, 300.0f);
	m_pSpaceShip4->setEnabled(false);
	m_pSpaceShip4->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pSpaceShip4);

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

	m_pInstructionsLabel2 = new Label(" Use W,A,S,D to Move The Target", "Roboto-Regular");
	m_pInstructionsLabel2->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 550.0f);
	addChild(m_pInstructionsLabel2);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Game3001 - Lab 2", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float shipSpeed = 2.0f;
	if (ImGui::SliderFloat("Ship Speed", &shipSpeed, 0.0f, 15.0f))
	{
		m_pSpaceShip->setMaxSpeed(shipSpeed);
	}
	static float shipSpeed2 = 2.0f;
	if (ImGui::SliderFloat("Ship Speed", &shipSpeed2, 0.0f, 15.0f))
	{
		m_pSpaceShip2->setMaxSpeed(shipSpeed2);
	}
	static float shipSpeed3 = 2.0f;
	if (ImGui::SliderFloat("Ship Speed", &shipSpeed3, 0.0f, 15.0f))
	{
		m_pSpaceShip3->setMaxSpeed(shipSpeed3);
	}

	static float acceleration_rate = 2.0;
	if (ImGui::SliderFloat("Acceleration Rate", &acceleration_rate, 0.0f, 300.0f))
	{
		m_pSpaceShip->setAccelerationRate(acceleration_rate);
	}
	static float acceleration_rate2 = 2.0;
	if (ImGui::SliderFloat("Acceleration Rate", &acceleration_rate2, 0.0f, 300.0f))
	{
		m_pSpaceShip2->setAccelerationRate(acceleration_rate2);
	}
	static float acceleration_rate3 = 2.0;
	if (ImGui::SliderFloat("Acceleration Rate", &acceleration_rate3, 0.0f, 300.0f))
	{
		m_pSpaceShip3->setAccelerationRate(acceleration_rate3);
	}

	static float angleInRadians = m_pSpaceShip->getRotationAngle();
	static float turn_rate = 5.0f;
	if (ImGui::Button("Stop"))
	{
		m_pSpaceShip->setEnabled(false);
		m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setRotationAngle(0.0f); // set angle to 0 degrees
		angleInRadians = m_pSpaceShip->getRotationAngle();
		turn_rate = 5.0f;
		acceleration_rate = 2.0f;
		shipSpeed = 2.0f;
		shipSpeed2 = 2.0f;
		shipSpeed3 = 2.0f;
	}


	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
