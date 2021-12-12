#include "AnyEnemy.h"

#include "App.h"
#include "Collisions.h"
#include "Audio.h"
#include "Render.h"
#include "Title.h"

AnyEnemy::AnyEnemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

AnyEnemy::~AnyEnemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* AnyEnemy::GetCollider() const
{
	return collider;
}

void AnyEnemy::Update(float dt)
{
	/*
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
		*/

	if (app->titleScreen->inTitle != 0) {
		SetToDelete();
	}
	
}

void AnyEnemy::PostUpdate() {

}

void AnyEnemy::Draw()
{
	if (currentAnim != nullptr){
		if (app->titleScreen->inTitle == 0) {
			switch (dir) {
			case 1:
				app->render->DrawTexture(texture_right, position.x, position.y, &(currentAnim->GetCurrentFrame()));
				break;
			case -1:
				app->render->DrawTexture(texture_left, position.x, position.y, &(currentAnim->GetCurrentFrame()));
				break;
			}
			
		}
	}
}

void AnyEnemy::OnCollision(Collider* collider)
{
	//app->particles->AddParticle(App->particles->explosion, position.x, position.y);
	//app->audio->PlayFx(destroyedFx);

	//SetToDelete();
}

void AnyEnemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}