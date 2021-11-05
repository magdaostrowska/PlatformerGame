#include "Collisions.h"

#include "App.h"

#include "Render.h"
#include "Input.h"
#include "SDL/include/SDL_Scancode.h"

Collisions::Collisions() : Module()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::GROUND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DEATH] = true;

	matrix[Collider::Type::GROUND][Collider::Type::GROUND] = false;
	matrix[Collider::Type::GROUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::GROUND][Collider::Type::WALL] = false;
	matrix[Collider::Type::GROUND][Collider::Type::DEATH] = false;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::GROUND] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::DEATH] = false;
	
/*
	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::WALL][Collider::Type::TOUCH] = true;
	matrix[Collider::Type::WALL][Collider::Type::BOX] = false;
	matrix[Collider::Type::WALL][Collider::Type::TOUCHB] = true;
	matrix[Collider::Type::WALL][Collider::Type::BALL] = true;
	matrix[Collider::Type::WALL][Collider::Type::UI] = false;


	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::TOUCH] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BOX] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::TOUCHB] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::UI] = true;

	matrix[Collider::Type::TOUCH][Collider::Type::WALL] = true;
	matrix[Collider::Type::TOUCH][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::TOUCH][Collider::Type::TOUCH] = false;
	matrix[Collider::Type::TOUCH][Collider::Type::BOX] = true;
	matrix[Collider::Type::TOUCH][Collider::Type::TOUCHB] = false;
	matrix[Collider::Type::TOUCH][Collider::Type::BALL] = false;
	matrix[Collider::Type::TOUCH][Collider::Type::UI] = false;

	matrix[Collider::Type::BOX][Collider::Type::WALL] = false;
	matrix[Collider::Type::BOX][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BOX][Collider::Type::TOUCH] = true;
	matrix[Collider::Type::BOX][Collider::Type::BOX] = false;
	matrix[Collider::Type::BOX][Collider::Type::TOUCHB] = true;
	matrix[Collider::Type::BOX][Collider::Type::BALL] = true;
	matrix[Collider::Type::BOX][Collider::Type::UI] = false;

	matrix[Collider::Type::TOUCHB][Collider::Type::WALL] = true;
	matrix[Collider::Type::TOUCHB][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TOUCHB][Collider::Type::TOUCH] = false;
	matrix[Collider::Type::TOUCHB][Collider::Type::BOX] = true;
	matrix[Collider::Type::TOUCHB][Collider::Type::TOUCHB] = false;
	matrix[Collider::Type::TOUCHB][Collider::Type::BALL] = false;
	matrix[Collider::Type::TOUCHB][Collider::Type::UI] = false;

	matrix[Collider::Type::BALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::BALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BALL][Collider::Type::TOUCH] = false;
	matrix[Collider::Type::BALL][Collider::Type::BOX] = true;
	matrix[Collider::Type::BALL][Collider::Type::TOUCHB] = false;
	matrix[Collider::Type::BALL][Collider::Type::BALL] = false;
	matrix[Collider::Type::BALL][Collider::Type::UI] = false;

	matrix[Collider::Type::UI][Collider::Type::WALL] = false;
	matrix[Collider::Type::UI][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::UI][Collider::Type::TOUCH] = false;
	matrix[Collider::Type::UI][Collider::Type::BOX] = false;
	matrix[Collider::Type::UI][Collider::Type::TOUCHB] = false;
	matrix[Collider::Type::UI][Collider::Type::BALL] = false;
	matrix[Collider::Type::UI][Collider::Type::UI] = false;
	*/



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
		case Collider::Type::DEATH: // red
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			/*
		case Collider::Type::BOX: // yellow
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case Collider::Type::TOUCHB: // celeste
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case Collider::Type::BALL: // fuxia
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 255, alpha);
			break;

		case Collider::Type::UI: // salmon
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;*/
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