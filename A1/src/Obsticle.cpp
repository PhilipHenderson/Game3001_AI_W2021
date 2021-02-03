#include "Obsticle.h"

#include "TextureManager.h"
#include "SoundManager.h"

Obsticle::Obsticle()
{
	TextureManager::Instance()->load("../Assets/textures/obstacle.png", "obsticle");

	auto size = TextureManager::Instance()->getTextureSize("obsticle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(OBSTICLE);
	getRigidBody()->isColliding = false;

	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay", SOUND_SFX);
}

Obsticle::~Obsticle()
= default;

void Obsticle::draw()
{
	TextureManager::Instance()->draw("obsticle", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Obsticle::update()
{
}

void Obsticle::clean()
{
}
