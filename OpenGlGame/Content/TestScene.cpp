#include "stdafx.h"
#include "TestScene.h"
#include "Game.h"
#include "Render\Render.h"
#include "DummyInputComponent.h"
#include "RotateComponent.h"
#include "Render\TileMapComponent.h"

void TestScene::OnCreate()
{

	auto go = Spawn<GameObject>(Vec3(50, 50, 0.0f));
	
	auto rc = go->AddComponent<RenderComponent>();
	auto tex = TheGame->Render().LoadTexture("Resources\\Textures\\test.png");
	rc->SetTexture(tex);
	//rc->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
	rc->SetSize({ 256, 256.0f });
	
	//auto tm = AddComponent<TileMapComponent>();
	//tm->Load("Resources\\Tiles\\base.json");

	/*Font f;
	if (f.Load("Resources\\Fonts\\arial.fnt"))
	{
		auto tc = go->AddComponent<TextComponent>();
		tc->SetText(&f, "abcdefghijk lmnopqr\nstuvwxyz");
	}*/
	


	auto go1 = Spawn<GameObject>({ 0, 0, 0 });
	auto rc1 = go1->AddComponent<RenderComponent>();
	rc1->SetColor({ 0, 1, 0, 1 });
	rc1->SetSize({ 5, 5 });
	go->Attach(go1);



	/*auto px = go->AddComponent<PhysicsComponent>();
	auto dc = go->AddComponent<DummyInputComponent>();
	dc->SetStep(10.0f);*/
	
	/*auto rotation1 = go->AddComponent<RotateComponent>();
	rotation1->SetFrequency(0.1);
	rotation1->SetAmplitude(500.0f);
	rotation1->SetPos(900);*/
	
}


	
