#ifndef _WALKINGENEMY_
#define _WALKINGENEMY_

#include "Enemy.h"
#include "ModuleEnemy.h"
#include "Collider.h"
#include "SDL/include/SDL.h"

class WalkingEnemy : public Enemy
{
public:
	WalkingEnemy();
	~WalkingEnemy() {};

	bool Awake(pugi::xml_node&) override;
	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool CleanUp() override;
	void OnCollision(Collider* c1, Collider* c2);

	void RenderEnemy() override;
	void CalculatePath();

public:
	SDL_Texture* textureIdle;

};

#endif // !_WALKINGENEMY_
