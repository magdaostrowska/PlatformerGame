#include "Collisions.h"

#include "App.h"

#include "Render.h"
#include "Input.h"
#include "Title.h"
#include "SDL/include/SDL_Scancode.h"

Collisions::Collisions() : Module()
{
	name.Create("collisions");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::GROUND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::COIN] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::POTION] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SHOT] = false;

	matrix[Collider::Type::GROUND][Collider::Type::GROUND] = false;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::GROUND][Collider::Type::WALL] = false;
	matrix[Collider::Type::GROUND][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::GROUND][Collider::Type::COIN] = false;
	matrix[Collider::Type::GROUND][Collider::Type::POTION] = false;
	matrix[Collider::Type::GROUND][Collider::Type::SHOT] = false;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::GROUND] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::COIN] = false;
	matrix[Collider::Type::WALL][Collider::Type::POTION] = false;
	matrix[Collider::Type::WALL][Collider::Type::SHOT] = true;

	matrix[Collider::Type::COIN][Collider::Type::WALL] = false;
	matrix[Collider::Type::COIN][Collider::Type::GROUND] = false;
	matrix[Collider::Type::COIN][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::COIN][Collider::Type::COIN] = false;
	matrix[Collider::Type::COIN][Collider::Type::POTION] = false;
	matrix[Collider::Type::COIN][Collider::Type::SHOT] = false;

	matrix[Collider::Type::POTION][Collider::Type::WALL] = false;
	matrix[Collider::Type::POTION][Collider::Type::GROUND] = false;
	matrix[Collider::Type::POTION][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::POTION][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::POTION][Collider::Type::COIN] = false;
	matrix[Collider::Type::POTION][Collider::Type::POTION] = false;
	matrix[Collider::Type::POTION][Collider::Type::SHOT] = false;

	matrix[Collider::Type::SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::SHOT][Collider::Type::GROUND] = false;
	matrix[Collider::Type::SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::SHOT][Collider::Type::COIN] = false;
	matrix[Collider::Type::SHOT][Collider::Type::POTION] = false;
	matrix[Collider::Type::SHOT][Collider::Type::SHOT] = false;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::GROUND] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::COIN] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::POTION] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::SHOT] = true;
}

Collisions::~Collisions()
{
}

bool Collisions::PreUpdate()
{

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{

		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{

			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}
	return true;
}

bool Collisions::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	return true;
}

bool Collisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return true;
}

void Collisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		if (app->titleScreen->inTitle == 0) {

			switch (colliders[i]->type)
			{
			case Collider::Type::NONE: // white
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;

			case Collider::Type::PLAYER: // blue
				app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case Collider::Type::GROUND: // green
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
				break;

			case Collider::Type::WALL: // yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case Collider::Type::ENEMY: // red
				app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
				break;

			case Collider::Type::SHOT: // light yellow
				app->render->DrawRectangle(colliders[i]->rect, 150, 150, 0, alpha);
				break;

			case Collider::Type::POTION: // light yellow
				app->render->DrawRectangle(colliders[i]->rect, 150, 230, 50, alpha);
				break;

			case Collider::Type::COIN: // light yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 100, 0, alpha);
				break;
			}
		}
	}
}

bool Collisions::CleanUp()
{
	//LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* Collisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}
	return ret;
}

void Collisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}