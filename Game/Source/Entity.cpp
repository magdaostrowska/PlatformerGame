#include "Entity.h"
#include "Player.h"
#include "EntityManager.h"


Entity::Entity(EntityType type) : type(type)
{
}

Entity::Entity(EntityType type, int x, int y) : position(x, y)
{
	spawnPos = position;
}

Entity::~Entity()
{
}

void Entity::Draw()
{
	if (currentAnim != nullptr) {
		if (app->titleScreen->inTitle == 0)
			app->render->DrawTexture(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));

	}
}

void Entity::OnCollision(Collider* collider)
{
	//app->particles->AddParticle(app->particles->explosion, position.x, position.y);
	//app->audio->PlayFx(destroyedFx);

	//SetToDelete();
}

void Entity::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

//const Collider* Entity::GetCollider() const
//{
//	return collider;
//}

Player* Entity::FindSubClassPlayer()
{
	Player* ret = nullptr;

	for (int i = 0; i < playerList.size(); i++) {
			ret = playerList.at(i);
	}
	return ret;
}

Items* Entity::FindSubClassItem()
{
	Items* ret = nullptr;

	for (int i = 0; i < itemList.size(); i++) {
		ret = itemList.at(i);
	}
	return ret;
}


