#ifndef __SHOTS_H__
#define __SHOTS_H__

#include "Module.h"

#include "Particle.h"
#include "Collider.h"

#define MAX_ACTIVE_SHOTS 100

struct SDL_Texture;
struct Collider;

class Shots : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	Shots();

	//Destructor
	~Shots();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all particles pending to delete
	bool PreUpdate();

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	bool Update(float dt);

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	bool PostUpdate();

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp();

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	Particle* AddParticle(const Particle& particle, int x, int y, int dir, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

public:
	
	//Template particle for a laser
	Particle shot;
	SDL_Rect shotRect = {24,24,16,16};

private:
	// Particles spritesheet loaded into an SDL Texture
	SDL_Texture* textureR = nullptr;
	SDL_Texture* textureL = nullptr;

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_SHOTS] = { nullptr };
};

#endif // __SHOTS_H__
