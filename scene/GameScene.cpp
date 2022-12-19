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
	safe_delete(suru);
	safe_delete(spriteTexQ1);
	safe_delete(edge);
	safe_delete(edge2);
	safe_delete(first);
	safe_delete(win);
	safe_delete(lose);
	safe_delete(ins);
	safe_delete(move);
	safe_delete(fire);

	safe_delete(ef1);
	safe_delete(ef2);
	safe_delete(ef3);
	safe_delete(ef4);
	safe_delete(ef5);
	safe_delete(ef6);
	safe_delete(ef7);
	safe_delete(ef8);

	safe_delete(defef0);
	safe_delete(defef1);
	safe_delete(defef2);
	safe_delete(defef3);
	safe_delete(defef4);
	safe_delete(defef5);
	safe_delete(defef6);

	safe_delete(heal0);
	safe_delete(heal1);
	safe_delete(heal2);
	safe_delete(heal3);

	safe_delete(enemyatkdrow);
	safe_delete(enemydefensdrow);
	safe_delete(enemyhealdrow);
	safe_delete(eheal1);
	safe_delete(eheal2);
	safe_delete(eheal3);
	safe_delete(eheal4);

	safe_delete(BG1);
	safe_delete(BG2);
	safe_delete(BG3);
	safe_delete(BG4);
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

	//if (!Sprite::LoadTexture(1, L"Resources/back.png")) {
	//	assert(0);
	//	return;
	//}

	// 背景スプライト生成
	//spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成

	// テクスチャ

	Sprite::LoadTexture(3, L"Resources/huti.png");
	spriteTexQ1 = Sprite::Create(3, { 20.0f,170.0f });

	Sprite::LoadTexture(5, L"Resources/first.png");
	first = Sprite::Create(5, { 0.0f,0.0f });

	//Sprite::LoadTexture(5, L"Resources/w.png");
	//first = Sprite::Create(5, { 0.0f,0.0f });

	Sprite::LoadTexture(6, L"Resources/win.png");
	win = Sprite::Create(6, { 0.0f,0.0f });

	Sprite::LoadTexture(7, L"Resources/lose.png");
	lose = Sprite::Create(7, { 0.0f,0.0f });

	Sprite::LoadTexture(8, L"Resources/ins.png");
	ins = Sprite::Create(8, { 0.0f,0.0f });

	Sprite::LoadTexture(9, L"Resources/move.png");
	move = Sprite::Create(9, { 415.0f, 480.0f });

	Sprite::LoadTexture(4, L"Resources/huti-a.png");
	edge = Sprite::Create(4, { 1160.0f,150.0f });

	Sprite::LoadTexture(11, L"Resources/huti-a.png");
	edge2 = Sprite::Create(11, { 20.0f,150.0f });

	EnemySkin();

	AttackDrow();

	DefenceDrow();

	HealingDrow();

	EnemyAttackDrow();

	EnemyDefenceDrow();

	EnemyHealingDrow();

	BackGround();

	//プレイヤーステータス
	PlaySet();

	//エネミーステータス
	EnemySet();

	srand((unsigned int)time(NULL));
	enemykillmax = 10 + rand()%10;
}

void GameScene::Update()
{
	SpriteMoveset();

	if (gamescene == 0) {
		textplayer = 0;
		textenemy = 0;
		turn = 0;
		pmove = 0;
		emove = 0;
		PlaySet();
		EnemySet();
		if (player.spd >= enemy.espd) {
			turn = 0;
		} else {
			turn = 1;
		}
		if (!input->TriggerKey(DIK_SPACE) && input->PushKey(DIK_SPACE)) {
			gamescene = 1;
		}

	}

	if (gamescene == 1) {
		switch (playereffect)
		{
		case 0:
			break;
		case 1:
			AttackDrowMove();
			break;
		case 2:
			DefenceDrowMove();
			break;
		case 3:
			HealingDrowMove();
			break;
		default:
			break;
		}

		if (input->TriggerKey(DIK_W)) {
			enemyeffect = 3;
		}
		if (input->TriggerKey(DIK_S)) {
			enemyeffect = 0;
		}

		switch (enemyeffect)
		{
		case 0:
			break;
		case 1:
			EnemyAttackDrowMove();
			break;
		case 2:
			EnemyDefenceDrowMove();
			break;
		case 3:
			EnemyHealingDrowMove();
			break;
		default:
			break;
		}

		//if (bdrowf == 1) {
		//	AttackDrowMove();
		//}
		//if (bdrowf == 2) {
		//	DefenceDrowMove();
		//}

		if (turn == 0) {
			if (playereffect == 0 && enemyeffect == 0) {
				PlayerTrun();
			}
		}
		if (turn == 1) {
			if (playereffect == 0 && enemyeffect == 0) {
				EnemyTrun();
			}
		}
		ButtelCon();
	}
	if (input->TriggerKey(DIK_R)) {
		enemy.ehp = 1;
		//enemy.edef = 10.0f;
	}

	if (input->TriggerKey(DIK_E)) {
		player.hp = 1;
	}

	if (input->TriggerKey(DIK_M)) {
		PlayLevelup(&plevel);
	}

	if (gamescene == 2) {
		if (input->TriggerKey(DIK_RETURN)) {
			PlayerReset();
			EnemyLevelup(&elevel);
			playereffect = 0;
			gamescene = 0;
		}
	}
	if (gamescene == 3) {
		if (input->TriggerKey(DIK_RETURN)) {

			PlayLevelup(&plevel);
			EnemyReset();
			playereffect = 0;
			gamescene = 0;
		}
	}

	//std::ostringstream hpstr;
	//hpstr << "HP:"
	//	<< std::fixed << std::setprecision(0)//小数点以下2桁まで
	//	<< player.hp,//p1.hp,
	//	debugText.Print(hpstr.str(), 50, 180, 1.0f);

	//std::ostringstream ehpstr;
	//ehpstr << "EHP:"
	//	<< std::fixed << std::setprecision(0)//小数点以下2桁まで
	//	<< enemy.ehp,
	//	debugText.Print(ehpstr.str(), 1175, 180, 1.0f);

	//std::ostringstream emstr;
	//emstr << "turn:"
	//	<< std::fixed << std::setprecision(0)//小数点以下2桁まで
	//	<< enemy.enumber,
	//	debugText.Print(emstr.str(), 625, 180, 1.0f);
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	//first->Draw();
	// 背景スプライト描画
	if (gamescene == 0) {
		first->Draw();
	}
	if (gamescene == 1) {

		switch (enemy.enumber)
		{
		case 0:
			break;
		case 1:
			BG1->Draw();
			suru->Draw();
			break;
		case 2:
			BG2->Draw();
			fire->Draw();
			break;
		case 3:
			BG3->Draw();
			gorem->Draw();
			break;
		case 4:
			BG4->Draw();
			eye->Draw();
		default:
			break;
		}
		edge->Draw();
		edge2->Draw();

		//UI系
			//player表示
		std::ostringstream levstr;
		levstr << "Lv."
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< player.level,
			debugText.Print(levstr.str(), 50, 160, 1.0f);

		std::ostringstream hpstr;
		hpstr << "HP:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< player.hp,//p1.hp,
			debugText.Print(hpstr.str(), 50, 180, 1.0f);

		std::ostringstream atkstr;
		atkstr << "ATK:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< player.atk,
			debugText.Print(atkstr.str(), 50, 200, 1.0f);

		std::ostringstream defstr;
		defstr << "DEF:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< player.def,
			debugText.Print(defstr.str(), 50, 220, 1.0f);

		std::ostringstream spdstr;
		spdstr << "SPD:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< player.spd,
			debugText.Print(spdstr.str(), 50, 240, 1.0f);

		//enemy表示
		std::ostringstream elevstr;
		elevstr << "Lv."
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< enemy.elevel,
			debugText.Print(elevstr.str(), 1190, 160, 1.0f);

		std::ostringstream ehpstr;
		ehpstr << "EHP:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< enemy.ehp,
			debugText.Print(ehpstr.str(), 1180, 180, 1.0f);


		std::ostringstream eatkstr;
		eatkstr << "EATK:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< enemy.eatk,
			debugText.Print(eatkstr.str(), 1180, 200, 1.0f);

		std::ostringstream edefstr;
		edefstr << "EDEF:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< enemy.edef,
			debugText.Print(edefstr.str(), 1180, 220, 1.0f);

		std::ostringstream espdstr;
		espdstr << "ESPD:"
			<< std::fixed << std::setprecision(0)//小数点以下2桁まで
			<< enemy.espd,
			debugText.Print(espdstr.str(), 1180, 240, 1.0f);

		//Buttelmod();
		debugText.Print("ATK", 50, 300, 1.0f);
		debugText.Print("DEF", 50, 320, 1.0f);
		debugText.Print("HEL", 50, 340, 1.0f);

		debugText.Print("->", 30, setmode, 1.0f);

		switch (playereffect)
		{
		case 0:
			break;
		case 1:
			ef1->Draw();
			ef2->Draw();
			ef3->Draw();
			ef4->Draw();
			ef5->Draw();
			ef6->Draw();
			ef7->Draw();
			ef8->Draw();
			break;
		case 2:
			defef0->Draw();
			defef1->Draw();
			defef2->Draw();
			defef3->Draw();
			defef4->Draw();
			defef5->Draw();
			defef6->Draw();
			break;
		case 3:
			heal0->Draw();
			heal1->Draw();
			heal2->Draw();
			heal3->Draw();
			break;
		default:
			break;
		}

		switch (enemyeffect)
		{
		case 0:
			break;
		case 1:
			enemyatkdrow->Draw();
			break;
		case 2:
			enemydefensdrow->Draw();
			break;
		case 3:
			enemyhealdrow->Draw();
			eheal1->Draw();
			eheal2->Draw();
			eheal3->Draw();
			eheal4->Draw();
			break;
		default:
			break;
		}
		move->Draw();
		switch (textplayer)
		{
		case 0:
			break;
		case 1:
			debugText.Print("Player->Attack", 450, 500, 3.0f);
			break;
		case 2:
			debugText.Print("Player->Defense", 450, 500, 3.0f);
			break;
		case 3:
			debugText.Print("Player->Healing", 450, 500, 3.0f);
			break;
		}
		switch (textenemy)
		{
		case 0:
			break;
		case 1:
			debugText.Print("Enemy->Attack", 450, 550, 3.0f);
			break;
		case 2:
			debugText.Print("Enemy->Defense", 450, 550, 3.0f);
			break;
		case 3:
			debugText.Print("Enemy->Healing", 450, 550, 3.0f);
			break;
		}

	}
	if (gamescene == 2) {
		lose->Draw();
	}
	if (gamescene == 3) {
		win->Draw();
	}

	//確認
	//wenemyatkdrow->Draw();
	//enemydefensdrow->Draw();

	//eheal1->Draw();
	//eheal2->Draw();
	//eheal3->Draw();
	//eheal4->Draw();

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

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::PlayInti(float hp, float atk, float def, float spd, float defplus, float healing, float flag, int level)
{
	player.hp = hp;
	player.atk = atk;
	player.def = def;
	player.spd = spd;
	player.defplus = defplus;
	player.healing = healing;
	player.flag = flag;
	player.level = level;
	maxhp = hp;
}

void GameScene::EnemyInti(float ehp, float eatk, float edef, float espd, float edefplus, float ehealing, float eflag, int elevel, int enumber)
{
	enemy.ehp = ehp;
	enemy.eatk = eatk;
	enemy.edef = edef;
	enemy.espd = espd;
	enemy.edefplus = edefplus;
	enemy.ehealing = ehealing;
	enemy.eflag = eflag;
	enemy.elevel = elevel;
	enemy.enumber = enumber;
	maxehp = ehp;
	enowlevel = elevel;
}

void GameScene::PlayButtel(Player* player, Enemy* enemy)
{
	//enemy->ehp -= player->atk - enemy->edef;
	if (player->atk - enemy->edef <= 0) {
		enemy->ehp -= 1.0f;
	} else {
		enemy->ehp -= player->atk - enemy->edef;
	}

	textplayer = 1;
	pmove = 1;
}

void GameScene::PlayDefense(Player* player, Enemy* enemy)
{
	player->def += player->defplus;
	//player->hp -= enemy->eatk - player->def;
	textplayer = 2;
	pdef = 1;
	pmove = 1;
}

void GameScene::PlayHealing(Player* player, Enemy* enemy)
{
	player->hp += player->healing;
	if (player->hp > maxhp) {
		player->hp = maxhp;
	}
	textplayer = 3;
	pmove = 1;
}

void GameScene::EnemyButtel(Player* player, Enemy* enemy)
{
	//player->hp -= enemy->eatk - player->def;
	if (enemy->eatk - player->def <= 0) {
		player->hp -= 1.0f;
	} else {
		player->hp -= enemy->eatk - player->def;
	}
	textenemy = 1;
	emove = 1;
}

void GameScene::EnemyDefense(Player* player, Enemy* enemy)
{
	enemy->edef += enemy->edefplus;
	textenemy = 2;
	eplus = 1;
	emove = 1;
}

void GameScene::EnemyHealing(Player* player, Enemy* enemy)
{
	enemy->ehp += enemy->ehealing;
	if (enemy->ehp > maxehp) {
		enemy->ehp = maxehp;
	}
	textenemy = 3;
	emove = 1;
}

void GameScene::Buttelmod()
{
	if (input->TriggerKey(DIK_UP)) {
		setmode -= 20.0f;
		if (setmode < 300) {
			setmode = 340;
		}
	}
	if (input->TriggerKey(DIK_DOWN)) {
		setmode += 20.0f;
		if (setmode > 340) {
			setmode = 300;
		}
	}
}

void GameScene::ButtelScene()
{
	if (player.spd >= enemy.espd) {
		PlayButtel(&player, &enemy);
		if (enemy.ehp > 0) {
			EnemyButtel(&player, &enemy);
		}
	}
	if (player.spd < enemy.espd) {
		EnemyButtel(&player, &enemy);
		if (player.hp > 0) {
			PlayButtel(&player, &enemy);
		}
	}
}

void GameScene::ButtelCon() {
	if (enemy.ehp <= 0) {
		player.level += 1;
		enemy.eflag = 0;
	} else if (player.hp <= 0 && enemy.ehp > 0) {
		enemy.elevel += 1;
		player.flag = 0;
	}
	if (enemy.eflag == 0) {
		//gamescene = 3;
		enemykill += 1;
		EnemyReset();
		pmove = 0;
		emove = 0;
		if (player.spd >= enemy.espd) {

			turn = 0;
		} else {
			turn = 1;
		}
		if (enemykillmax == enemykill) {
			gamescene = 3;
			enemykill = 0;
		}
	}
	if (player.flag == 0) {
		gamescene = 2;
	}
}


void GameScene::PlayerTrun()
{
	pdef = 0;
	Buttelmod();
	if (input->TriggerKey(DIK_SPACE)) {
		if (setmode == 300) {
			PlayButtel(&player, &enemy);
			playereffect = 1;
		}
		if (setmode == 320)
		{
			PlayDefense(&player, &enemy);
			playereffect = 2;
		}
		if (setmode == 340)
		{
			PlayHealing(&player, &enemy);
			playereffect = 3;
		}
	}
	if (pmove == 1) {
		if (eplus == 1) {
			enemy.edef -= enemy.edefplus;
			emove = 0;
			turn = 1;
		} else {
			emove = 0;
			turn = 1;
		}
	}
}

void GameScene::EnemyTrun()
{
	eplus = 0;
	srand((unsigned int)time(NULL));
	int  em = 1 + ((1 + rand() % 15) % 3);
	switch (em)
	{
	case 1:
		EnemyButtel(&player, &enemy);
		enemyeffect = 1;
		break;
	case 2:
		EnemyDefense(&player, &enemy);
		enemyeffect = 2;
		break;
	case 3:
		EnemyHealing(&player, &enemy);
		enemyeffect = 3;
		break;
	default:
		break;
	}
	if (emove == 1) {
		if (pdef == 1) {
			player.def -= player.defplus;
			pmove = 0;
			turn = 0;
		} else {
			pmove = 0;
			turn = 0;
		}
	}
}

void GameScene::PlaySet()
{
	srand((unsigned int)time(NULL));
	php = 15.0f + rand() % 5;
	PlayInti(php, 3.0f, 1.0f, 2.0f, 2.0f, 4.0f, 1.0f, 1);
}

void GameScene::EnemySet()
{
	srand((unsigned int)time(NULL));
	enemynum = 1 + rand() % allenemy;
	if (enowlevel <= 0) {
		enowlevel = 1;
	}
	switch (enemynum)
	{
	case 0:
		break;
	case 1:
		enhp = 15.0f + rand() % 3;
		EnemyInti(enhp, 3.0f, 1.0f, 1.0f, 5.0f, 3.0f, 1.0f, 1, enemynum);
		break;
	case 2:
		enhp = 10.0f + rand() % 3;
		EnemyInti(enhp, 2.0f, 2.0f, 1.0f, 5.0f, 3.0f, 1.0f, 1, enemynum);
		break;
	case 3:
		enhp = 8.0f + rand() % 3;
		EnemyInti(enhp, 1.0f, 3.0f, 1.0f, 5.0f, 3.0f, 1.0f, 1, enemynum);
		break;
	case 4:
		enhp = 9.0f + rand() % 3;
		EnemyInti(enhp, 1.0f, 1.0f, 3.0f, 5.0f, 3.0f, 1.0f, enowlevel, enemynum);
		break;
	default:
		break;
	}
}

void GameScene::PlayLevelup(Plevel* plevel)
{
	player.hp = maxhp;
	srand((unsigned int)time(NULL));
	plevel->plhp = rand() % 5;
	srand((unsigned int)time(NULL) - 4);
	plevel->platk = rand() % 3;
	srand((unsigned int)time(NULL) * 3);
	plevel->pldef = rand() % 3;
	srand((unsigned int)time(NULL) + 8);
	plevel->plspd = rand() % 2;
	srand((unsigned int)time(NULL) - 8);
	plevel->plhealing = rand() % 3;


	player.hp += plevel->plhp;
	player.atk += plevel->platk;
	player.def += plevel->pldef;
	player.spd += plevel->plspd;
	player.healing += plevel->plhealing;
	maxhp = player.hp;
}

void GameScene::EnemyLevelup(Elevel* elevel)
{
	enemy.ehp = maxehp;
	randelevelup = rand() % 3;
	switch (randelevelup)
	{
	case 0:
		srand((unsigned int)time(NULL));
		elevel->elhp = 1 + rand() % 5;
		srand((unsigned int)time(NULL) * 2 - 5);
		elevel->elatk = 1 + rand() % 3;
		srand((unsigned int)time(NULL) - 2);
		elevel->eldef = 1 + rand() % 3;
		srand((unsigned int)time(NULL) + 5);
		elevel->elspd = rand() % 2;
		break;
	case 1:
		srand((unsigned int)time(NULL) / 2);
		elevel->elhp = 1 + rand() % 7;
		srand((unsigned int)time(NULL) * 3);
		elevel->elatk = 1 + rand() % 2;
		srand((unsigned int)time(NULL) + 2);
		elevel->eldef = 1 + rand() % 2;
		srand((unsigned int)time(NULL) - 5);
		elevel->elspd =rand() % 2;
		break;
	case 2:
		srand((unsigned int)time(NULL) + 3);
		elevel->elhp = 1 + rand() % 3;
		srand((unsigned int)time(NULL) * 6);
		elevel->elatk = 1 + rand() % 4;
		srand((unsigned int)time(NULL) - 9);
		elevel->eldef = 1 + rand() % 4;
		srand((unsigned int)time(NULL) / 3);
		elevel->elspd = rand() % 3;
		break;
	default:
		break;
	}

	enemy.ehp += elevel->elhp;
	enemy.eatk += elevel->elatk;
	enemy.edef += elevel->eldef;
	enemy.espd += elevel->elspd;
	enemy.enumber = enemynum = 1 + rand() % allenemy;
	maxehp = enemy.ehp;
	enowlevel = enemy.elevel;
}

void GameScene::PlayerReset()
{
	player.hp = maxhp;
	player.flag = 1.0f;
}

void GameScene::EnemyReset()
{
	//enemy.ehp = maxehp;
	//enemy.eflag = 1.0f;
	eplus = 0;
	srand((unsigned int)time(NULL));
	enemy.enumber = enemynum = 1 + rand() % allenemy;
	//eleveling = 1;
	srand((unsigned int)time(NULL) + 4);
	eleveling += rand() % 2;
	if (enowlevel <= 0) {
		enowlevel = 1;
	}
	switch (enemynum)
	{
	case 0:
		break;
	case 1:
		enhp = 15.0f + rand() % 3;
		EnemyInti(enhp, 3.0f, 1.0f, 1.0f, 5.0f, 2.0f, 1.0f, enowlevel, enemynum);
		break;
	case 2:
		enhp = 10.0f + rand() % 3;
		EnemyInti(enhp, 2.0f, 2.0f, 1.0f, 5.0f, 2.0f, 1.0f, enowlevel, enemynum);
		break;
	case 3:
		enhp = 8.0f + rand() % 3;
		EnemyInti(enhp, 1.0f, 3.0f, 1.0f, 5.0f, 2.0f, 1.0f, enowlevel, enemynum);
		break;
	case 4:
		enhp = 9.0f + rand() % 3;
		EnemyInti(enhp, 1.0f, 1.0f, 3.0f, 5.0f, 2.0f, 1.0f, enowlevel, enemynum);
		break;
	default:
		break;
	}
	if (enowlevel < eleveling) {
		EnemyLevelup(&elevel);
		enemy.elevel += 1;
		enowlevel++;
	}
}

void GameScene::EnemySkin()
{
	Sprite::LoadTexture(2, L"Resources/suru.png");
	suru = Sprite::Create(2, { 440.0f,100.0f });

	Sprite::LoadTexture(10, L"Resources/fire.png");
	fire = Sprite::Create(10, { 440.0f,100.0f });

	Sprite::LoadTexture(38, L"Resources/gorem.png");
	gorem = Sprite::Create(38, { 440.0f,100.0f });

	Sprite::LoadTexture(39, L"Resources/eye.png");
	eye = Sprite::Create(39, { 440.0f,100.0f });

}


void GameScene::AttackDrow() {


	for (int i = 0; i < 8; i++) {
		rayp[i].x = 570.0f;
		rayp[i].y = 280.0f;
	}

	Sprite::LoadTexture(12, L"Resources/ray.png");
	ef1 = Sprite::Create(12, { rayp[0].x,rayp[0].y });

	Sprite::LoadTexture(13, L"Resources/ray.png");
	ef2 = Sprite::Create(13, { rayp[1].x,rayp[1].y });

	Sprite::LoadTexture(14, L"Resources/ray.png");
	ef3 = Sprite::Create(14, { rayp[2].x,rayp[2].y });

	Sprite::LoadTexture(15, L"Resources/ray.png");
	ef4 = Sprite::Create(15, { rayp[3].x,rayp[3].y });

	Sprite::LoadTexture(16, L"Resources/ray.png");
	ef5 = Sprite::Create(16, { rayp[4].x,rayp[4].y });

	Sprite::LoadTexture(17, L"Resources/ray.png");
	ef6 = Sprite::Create(17, { rayp[5].x,rayp[5].y });

	Sprite::LoadTexture(18, L"Resources/ray.png");
	ef7 = Sprite::Create(18, { rayp[6].x,rayp[6].y });

	Sprite::LoadTexture(19, L"Resources/ray.png");
	ef8 = Sprite::Create(19, { rayp[7].x,rayp[7].y });

}

void GameScene::AttackDrowMove()
{
	rayp[0].y -= 10.0f;

	rayp[1].x += 10.0f * isotri;
	rayp[1].y -= 10.0f * isotri;

	rayp[2].x += 10.0f;

	rayp[3].x += 10.0f * isotri;
	rayp[3].y += 10.0f * isotri;

	rayp[4].y += 10.0f;

	rayp[5].x -= 10.0f * isotri;
	rayp[5].y += 10.0f * isotri;

	rayp[6].x -= 10.0f;

	rayp[7].x -= 10.0f * isotri;
	rayp[7].y -= 10.0f * isotri;

	if (rayp[1].x >= 800.0f) {
		AttackDrow();
		playereffect = 0;
	}
}

void GameScene::DefenceDrow()
{
	shildp[0].x = 580.0f;
	shildp[0].y = 300.0f;
	Sprite::LoadTexture(20, L"Resources/shild.png");
	defef0 = Sprite::Create(20, { shildp[0].x,shildp[0].y });


	shildp[1].x = 644.5f + shildx;
	shildp[1].y = 300.0f;
	Sprite::LoadTexture(21, L"Resources/shild.png");
	defef1 = Sprite::Create(21, { shildp[1].x,shildp[1].y });

	shildp[2].x = 515.6f - shildx;
	shildp[2].y = 300.0f;
	Sprite::LoadTexture(22, L"Resources/shild.png");
	defef2 = Sprite::Create(22, { shildp[2].x,shildp[2].y });

	shildp[3].x = 548.0f;
	shildp[3].y = 202.6f - shildy;
	Sprite::LoadTexture(23, L"Resources/shild.png");
	defef3 = Sprite::Create(23, { shildp[3].x,shildp[3].y });

	shildp[4].x = 612.5f;
	shildp[4].y = 202.6f - shildy;
	Sprite::LoadTexture(24, L"Resources/shild.png");
	defef4 = Sprite::Create(24, { shildp[4].x,shildp[4].y });

	shildp[5].x = 548.0f;
	shildp[5].y = 397.5f + shildy;
	Sprite::LoadTexture(25, L"Resources/shild.png");
	defef5 = Sprite::Create(25, { shildp[5].x,shildp[5].y });

	shildp[6].x = 612.5f;
	shildp[6].y = 397.5f + shildy;
	Sprite::LoadTexture(26, L"Resources/shild.png");
	defef6 = Sprite::Create(26, { shildp[6].x,shildp[6].y });
}

void GameScene::DefenceDrowMove()
{
	if (shildmoveY <= 0.0f) {
		shildmoveX += 0.1f;
		shildp[1].x -= shildmoveX;
		shildp[2].x += shildmoveX;
	}
	if (shildmoveX >= 6.2f) {
		shildmoveY += 0.1f;
		shildp[3].y += shildmoveY;
		shildp[4].y += shildmoveY;
		shildp[5].y -= shildmoveY;
		shildp[6].y -= shildmoveY;
	}
	if (shildmoveY >= 4.6f) {
		DefenceDrow();
		shildmoveX = shildmoveY = 0;
		playereffect = 0;
	}
}

void GameScene::HealingDrow()
{
	healing[0].x = 300.0f;
	healing[0].y = 400.0f;
	Sprite::LoadTexture(27, L"Resources/Heal.png");
	heal0 = Sprite::Create(27, { healing[0].x,healing[0].y });

	healing[1].x = 400.0f;
	healing[1].y = 200.0f;
	Sprite::LoadTexture(28, L"Resources/Heal.png");
	heal1 = Sprite::Create(28, { healing[1].x,healing[1].y });

	healing[2].x = 700.0f;
	healing[2].y = 500.0f;
	Sprite::LoadTexture(29, L"Resources/Heal.png");
	heal2 = Sprite::Create(29, { healing[2].x,healing[2].y });

	healing[3].x = 800.0f;
	healing[3].y = 150.0f;
	Sprite::LoadTexture(30, L"Resources/Heal.png");
	heal3 = Sprite::Create(30, { healing[3].x,healing[3].y });
}

void GameScene::HealingDrowMove()
{
	healingmove += 1.0f;
	healing[0].y -= healingmove;
	healing[1].y -= healingmove;
	healing[2].y -= healingmove;
	healing[3].y -= healingmove;
	if (healingmove >= 30.0f) {
		playereffect = 0;
		healingmove = 0;
		HealingDrow();
	}
}

void GameScene::EnemyAttackDrow()
{
	eatkmove[0].x = 570.0f;
	eatkmove[0].y = 280.0f;

	esize[0].x = 100.0f;
	esize[0].y = 100.0f;

	Sprite::LoadTexture(31, L"Resources/rayZ.png");
	enemyatkdrow = Sprite::Create(31, { eatkmove[0].x ,eatkmove[0].y });
}

void GameScene::EnemyAttackDrowMove()
{
	sizemove += 0.5f;
	esize[0].x += sizemove;
	esize[0].y += sizemove;
	eatkmove[0].x -= sizemove / 2;
	eatkmove[0].y -= sizemove / 2;

	if (sizemove >= 20) {
		enemyeffect = 0;
		sizemove = 0.0f;
		EnemyAttackDrow();
	}

	//if (enemyattckdrow[0].x >= 700) {
	//	enemyeffect = 0;
	//}
}

void GameScene::EnemyDefenceDrow()
{
	edefmove[0].x = 570.0f;
	edefmove[0].y = 120.0f;

	Sprite::LoadTexture(32, L"Resources/guard.png");
	enemydefensdrow = Sprite::Create(32, { edefmove[0].x ,edefmove[0].y });
}

void GameScene::EnemyDefenceDrowMove()
{
	if (stopmove == 0.0f) {
		enemyguard += 0.5f;
		edefmove[0].y += enemyguard;
	}
	if (enemyguard >= 14.0f) {
		stopmove += 1.0f;
		if (stopmove >= 15.0f) {
			enemyeffect = 0;
			enemyguard = 0.0f;
			stopmove = 0.0f;
			EnemyDefenceDrow();
		}
	}
}

void GameScene::EnemyHealingDrow()
{
	Sprite::LoadTexture(33, L"Resources/ehe.png");
	enemyhealdrow = Sprite::Create(33, { 520.0f,240.0f });

	ehealmove[0].x = 500.0f;
	ehealmove[0].y = 450.0f;

	ehealmove[1].x = 700.0f;
	ehealmove[1].y = 400.0f;

	ehealmove[2].x = 680.0f;
	ehealmove[2].y = 480.0f;

	ehealmove[3].x = 580.0f;
	ehealmove[3].y = 500.0f;



	Sprite::LoadTexture(34, L"Resources/effects.png");
	eheal1 = Sprite::Create(34, { ehealmove[0].x,ehealmove[0].y });

	Sprite::LoadTexture(35, L"Resources/effects.png");
	eheal2 = Sprite::Create(35, { ehealmove[1].x,ehealmove[1].y });

	Sprite::LoadTexture(36, L"Resources/effects.png");
	eheal3 = Sprite::Create(36, { ehealmove[2].x,ehealmove[2].y });

	Sprite::LoadTexture(37, L"Resources/effects.png");
	eheal4 = Sprite::Create(37, { ehealmove[3].x,ehealmove[3].y });

}

void GameScene::EnemyHealingDrowMove()
{
	efmove += 0.2f;
	ehealmove[0].y -= efmove;
	ehealmove[1].y -= efmove;
	ehealmove[2].y -= efmove;
	ehealmove[3].y -= efmove;


	if (efmove >= 10.0f) {
		enemyeffect = 0;
		efmove = 0.0f;
		EnemyHealingDrow();
	}
}

void GameScene::BackGround()
{
	Sprite::LoadTexture(40, L"Resources/back_s.png");
	BG1 = Sprite::Create(40, { 0.0f,0.0f });

	Sprite::LoadTexture(41, L"Resources/back_f.png");
	BG2 = Sprite::Create(41, { 0.0f,0.0f });

	Sprite::LoadTexture(42, L"Resources/back_g.png");
	BG3 = Sprite::Create(42, { 0.0f,0.0f });

	Sprite::LoadTexture(43, L"Resources/back_e.png");
	BG4 = Sprite::Create(43, { 0.0f,0.0f });
}

void GameScene::SpriteMoveset()
{
	//移動系
	ef1->SetPosition(rayp[0]);
	ef2->SetPosition(rayp[1]);
	ef3->SetPosition(rayp[2]);
	ef4->SetPosition(rayp[3]);
	ef5->SetPosition(rayp[4]);
	ef6->SetPosition(rayp[5]);
	ef7->SetPosition(rayp[6]);
	ef8->SetPosition(rayp[7]);

	defef0->SetPosition(shildp[0]);
	defef1->SetPosition(shildp[1]);
	defef2->SetPosition(shildp[2]);
	defef3->SetPosition(shildp[3]);
	defef4->SetPosition(shildp[4]);
	defef5->SetPosition(shildp[5]);
	defef6->SetPosition(shildp[6]);

	heal0->SetPosition(healing[0]);
	heal1->SetPosition(healing[1]);
	heal2->SetPosition(healing[2]);
	heal3->SetPosition(healing[3]);

	enemyatkdrow->SetSize(esize[0]);
	enemyatkdrow->SetPosition(eatkmove[0]);

	enemydefensdrow->SetPosition(edefmove[0]);

	eheal1->SetPosition(ehealmove[0]);
	eheal2->SetPosition(ehealmove[1]);
	eheal3->SetPosition(ehealmove[2]);
	eheal4->SetPosition(ehealmove[3]);
}

void GameScene::BossInti(float bossHp, float bossAtk, float bossDef, float bossSpd, float bossDefPlus, float bossHealing, float bossFlag)
{
	boss.bossHp = bossHp;
	boss.bossAtk = bossAtk;
	boss.bossDef = bossDef;
	boss.bossSpd = bossSpd;
	boss.bossDefPlus = bossDefPlus;
	boss.bossHealing = bossHealing;
	boss.bossFlag = bossFlag;
}

void GameScene::BossSet(Boss* boss, Player* player)
{
	srand((unsigned int)time(NULL));
	bossSet.bossHp = maxhp * 2 + rand() % 50;
	bossSet.bossAtk = 15 + rand() % 10;
	srand((unsigned int)time(NULL));
	bossSet.bossDef = player->atk - rand()%8;
	//BossInti(bossSet.bossHp,bossSet.bossAtk)
}
