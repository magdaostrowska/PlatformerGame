#include "Shots.h"

#include "App.h"

#include "Textures.h"
#include "Render.h"
#include "Collisions.h"
#include "Player.h"

#include "SDL/include/SDL_timer.h"

Shots::Shots() : Module()
{
	for (uint i = 0; i < MAX_ACTIVE_SHOTS; ++i) particles[i] = nullptr;
}

Shots::~Shots()
{

}

bool Shots::Start()
{
	textureR = app->tex->Load("Assets/Textures/player/fireball_right.png");
	
	// Explosion particle
	shot.anim_right.PushBack({ 0, 0, 64, 64 });
	shot.anim_right.PushBack({ 64, 0,  64, 64 });
	shot.anim_right.PushBack({ 128, 0, 64, 64 });
	shot.anim_right.PushBack({ 192, 0, 64, 64 });
	shot.anim_right.PushBack({ 256, 0, 64, 64 });
	
	shot.anim_right.PushBack({ 320, 0, 64, 64 });
	shot.anim_right.PushBack({ 384, 0, 64, 64 });
	shot.anim_right.PushBack({ 448, 0, 64, 64 });
	shot.anim_right.PushBack({ 512, 0, 64, 64 });
	shot.anim_right.PushBack({ 576, 0, 64, 64 });

	shot.anim_right.PushBack({ 640, 0,  64, 64 });
	shot.anim_right.PushBack({ 704, 0, 64, 64 });
	shot.anim_right.PushBack({ 768, 0,  64, 64 });
	shot.anim_right.PushBack({ 832, 0, 64, 64 });
	shot.anim_right.PushBack({ 896, 0, 64, 64 });

	shot.anim_right.loop = false;
	shot.anim_right.speed = 0.5f;


	textureL = app->tex->Load("Assets/Textures/player/fireball_left.png");

	shot.anim_left.PushBack({ 896, 0, 64, 64 });
	shot.anim_left.PushBack({ 832, 0, 64, 64 });
	shot.anim_left.PushBack({ 768, 0,  64, 64 });
	shot.anim_left.PushBack({ 704, 0, 64, 64 });
	shot.anim_left.PushBack({ 640, 0,  64, 64 });

	shot.anim_left.PushBack({ 576, 0, 64, 64 });
	shot.anim_left.PushBack({ 512, 0, 64, 64 });
	shot.anim_left.PushBack({ 448, 0, 64, 64 });
	shot.anim_left.PushBack({ 384, 0, 64, 64 });
	shot.anim_left.PushBack({ 320, 0, 64, 64 });

	shot.anim_left.PushBack({ 256, 0, 64, 64 });
	shot.anim_left.PushBack({ 192, 0, 64, 64 });
	shot.anim_left.PushBack({ 128, 0, 64, 64 });
	shot.anim_left.PushBack({ 64, 0,  64, 64 });
	shot.anim_left.PushBack({ 0, 0, 64, 64 });

	shot.anim_left.loop = false;
	shot.anim_left.speed = 0.5f;


	shot.speed.x = 1 * 16 / 3;

	shot.lifetime = 180;

	return true;
}

bool Shots::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_SHOTS; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

bool Shots::CleanUp()
{

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_SHOTS; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void Shots::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_SHOTS; ++i)
	{

		/*
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
		*/
	}
}

bool Shots::Update(float dt)
{

	shot.speed.x = 1 * dt / 3;

	for (uint i = 0; i < MAX_ACTIVE_SHOTS; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if (particle->Update(dt) == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return true;
}

bool Shots::PostUpdate()
{
	// Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_SHOTS; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			if (particle->dir == 1) {
				app->render->DrawTexture(textureR, particle->position.x -32, particle->position.y-24, &(particle->anim_right.GetCurrentFrame()));
			}
			else if (particle->dir == -1){
				app->render->DrawTexture(textureL, particle->position.x-16 , particle->position.y-24, &(particle->anim_left.GetCurrentFrame()));
			}
			
		}
	}

	return true;
}

Particle* Shots::AddParticle(const Particle& particle, int x, int y, int direction, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_SHOTS; ++i)
	{
		// Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;
			newParticle->dir = direction;
			
			// Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = app->collisions->AddCollider({0,0, 16, 16}, colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}