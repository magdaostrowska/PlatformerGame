#include "AnyItem.h"

#include "App.h"
#include "Collisions.h"
//#include "Particles.h"
#include "Audio.h"
#include "Render.h"
#include "Title.h"

AnyItem::AnyItem(int x, int y) : position(x, y)
{
	spawnPos = position;
}

AnyItem::~AnyItem()
{
	//if (collider != nullptr)
		//collider->pendingToDelete = true;
}

const Collider* AnyItem::GetCollider() const
{
	return collider;
}

void AnyItem::Update(float dt)
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	//if (collider != nullptr)
		//collider->SetPos(position.x, position.y);
}

void AnyItem::Draw()
{
	if (currentAnim != nullptr) {
		if (app->titleScreen->inTitle == 0) {
			app->render->DrawTexture(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		}
		
	}
		
}


void AnyItem::OnCollision(Collider* collider)
{
	//app->particles->AddParticle(app->particles->explosion, position.x, position.y);
	//app->audio->PlayFx(destroyedFx);

	//SetToDelete();
}


void AnyItem::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}