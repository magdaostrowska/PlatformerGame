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

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void CalculatePath();

private:
	bool set_path;
	bool set_timer;

	SDL_Texture* debug_tex;

	int path_num;
	int tick1, tick2;

	int speed;

	bool stun;
	bool reset;
	bool ready;

	iPoint objective;
};

#endif // !_WALKINGENEMY_
