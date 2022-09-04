#include "GameScene.h"
#include "Model.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include"Collision.h"
#include<sstream>
#include<iomanip>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteBG);
	safe_delete(spriteTex);
	safe_delete(spriteTexQ1);
	safe_delete(spriteTexQ2);
	safe_delete(spriteTexQ3);
	safe_delete(spriteTexQ4);
	safe_delete(spriteTexQ5);
	safe_delete(spriteTexQ6);

}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;



	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	//if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
	//	assert(0);
	//	return;
	//}
	if (!Sprite::LoadTexture(1, L"Resources/black.png")) {
		assert(0);
		return;
	}
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成

	// テクスチャ2番に読み込み
	Sprite::LoadTexture(2, L"Resources/suru.png");
	spriteTex = Sprite::Create(2, { 400.0f,100.0f });

	Sprite::LoadTexture(3, L"Resources/huti.png");
	spriteTexQ1 = Sprite::Create(3, { 20.0f,170.0f });

	Sprite::LoadTexture(4, L"Resources/huti.png");
	spriteTexQ2 = Sprite::Create(4, { 1150.0f,170.0f });

	Sprite::LoadTexture(5, L"Resources/first.png");
	spriteTexQ3 = Sprite::Create(5, { 0.0f,0.0f });

	Sprite::LoadTexture(6, L"Resources/win.png");
	spriteTexQ4 = Sprite::Create(6, { 0.0f,0.0f });

	Sprite::LoadTexture(7, L"Resources/lose.png");
	spriteTexQ5 = Sprite::Create(7, { 0.0f,0.0f });

	Sprite::LoadTexture(8, L"Resources/ins.png");
	spriteTexQ6 = Sprite::Create(8, { 0.0f,0.0f });




}

void GameScene::Update()
{

	if (scene == 0) {
		if (input->TriggerKey(DIK_SPACE)) {
			scene = 1;
			i = 100;
		}
	}
	if (scene == 1) {
		i--;
		if (i <= 0) {
			scene = 2;
			moved = 0;
		}
	}
	if (scene == 2) {

		if (input->TriggerKey(DIK_DOWN)) {
			cas += 20.0f;
			if (cas > 340) {
				cas = 300;
			}
		}
		if (input->TriggerKey(DIK_UP)) {
			cas -= 20.0f;
			if (cas < 300) {
				cas = 340;
			}
		}

		if (input->TriggerKey(DIK_SPACE)) {
			if (buttel == 0) {
				if (cas == 300) {
					atkmod = 1.0f;
					buttel = 1;
				}
				if (cas == 320) {
					defmod = 1.0f;
					buttel = 1;
				}
				if (cas == 340) {
					helmod = 1.0f;
					buttel = 1;
				}
			}
		}


		if (buttel == 1) {

			if (atkmod == 1.0f) {
				if (spd >= espd) {
					ehp -= atk - edef;
					hp -= eatk - def;
					moved = 1;
					atkmod = 0.0f;
					buttel = 0;
				}
				if (espd > spd) {
					hp -= eatk - def;
					ehp -= atk - edef;
					moved = 1;
					atkmod = 0.0f;
					buttel = 0;
				}
			}

			if (defmod == 1.0f) {
				def += 2.0f;
				hp -= eatk - def;
				def -= 2.0f;
				moved = 2;
				defmod = 0.0f;
				buttel = 0;
			}

			if (helmod == 1.0f) {
				hp += 4.0f;
				moved = 3;
				helmod = 0.0f;
				buttel = 0;
			}
		}

		if (moved == 1) {
			debugText.Print("Player->Attack", 450, 500, 3.0f);
			debugText.Print("Enemy->Attack", 450, 550, 3.0f);
		}

		if (moved == 2) {
			debugText.Print("Player->Defense", 450, 500, 3.0f);
			debugText.Print("Enemy->Attack", 450, 550, 3.0f);
		}

		if (moved == 3) {
			debugText.Print("Player->Healing", 450, 500, 3.0f);
			debugText.Print("Enemy->Attack", 450, 550, 3.0f);
		}
		//自分表示
		std::ostringstream hpstr;
		hpstr << "HP:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< hp,
			debugText.Print(hpstr.str(), 50, 180, 1.0f);

		std::ostringstream atkstr;
		atkstr << "ATK:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< atk,
			debugText.Print(atkstr.str(), 50, 200, 1.0f);

		std::ostringstream defstr;
		defstr << "DEF:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< def,
			debugText.Print(defstr.str(), 50, 220, 1.0f);

		std::ostringstream spdstr;
		spdstr << "SPD:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< spd,
			debugText.Print(spdstr.str(), 50, 240, 1.0f);

		debugText.Print("ATK", 50, 300, 1.0f);
		debugText.Print("DEF", 50, 320, 1.0f);
		debugText.Print("HEL", 50, 340, 1.0f);

		debugText.Print("->", 30, cas, 1.0f);



		//敵表示
		std::ostringstream ehpstr;
		ehpstr << "EHP:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< ehp,
			debugText.Print(ehpstr.str(), 1175, 180, 1.0f);

		std::ostringstream eatkstr;
		eatkstr << "EATK:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< eatk,
			debugText.Print(eatkstr.str(), 1175, 200, 1.0f);

		std::ostringstream edefstr;
		edefstr << "EDEF:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< edef,
			debugText.Print(edefstr.str(), 1175, 220, 1.0f);

		std::ostringstream espdstr;
		espdstr << "ESPD:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< espd,
			debugText.Print(espdstr.str(), 1175, 240, 1.0f);

		if (hp <= 0) {
			scene = 3;
			hp = 10.0f;
			ehp = 15.0f;
		}
		if (ehp <= 0&&hp>0) {
			scene = 4;
			hp = 10.0f;
			ehp = 15.0f;
		}
	}
	if (scene == 3) {
		if (input->TriggerKey(DIK_RETURN)) {
			scene = 0;
		}
	}
	if (scene == 4) {
		if (input->TriggerKey(DIK_RETURN)) {
			scene = 0;
		}
	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	if (scene == 0) {
		spriteTexQ3->Draw();
	}
	if (scene == 1) {
		spriteTexQ6->Draw();
	}
	if (scene == 2) {
		spriteBG->Draw();
		spriteTex->Draw();
		spriteTexQ1->Draw();
		spriteTexQ2->Draw();
	}
	if (scene == 3) {
		spriteTexQ5->Draw();
	}
	if (scene == 4) {
		spriteTexQ4->Draw();
	}
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画
	//sprite1->Draw();
	//sprite2->Draw();

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
