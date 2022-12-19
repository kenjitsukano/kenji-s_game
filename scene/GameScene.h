#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "Audio.h"
#include"CollisionPrimitive.h"
#include<stdlib.h>


struct Player
{
	float hp;
	float atk;
	float def;
	float spd;
	float defplus;
	float healing;
	float flag;
	int level;
};

struct Enemy
{
	float ehp;
	float eatk;
	float edef;
	float espd;
	float edefplus;
	float ehealing;
	float eflag;
	int elevel;
	int enumber;
};

struct Boss
{
	float bossHp;
	float bossAtk;
	float bossDef;
	float bossSpd;
	float bossDefPlus;
	float bossHealing;
	float bossFlag;
};

struct BossSet
{
	float bossHp;
	float bossAtk;
	float bossDef;
	float bossSpd;
	float bossDefPlus;
	float bossHealing;
	float bossFlag;
};

struct Plevel
{
	float plhp;
	float platk;
	float pldef;
	float plspd;
	float plhealing;
};

struct Elevel
{
	float elhp;
	float elatk;
	float eldef;
	float elspd;
};

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤー
	/// </summary>
	void PlayInti(float hp, float atk, float def, float spd, float defplus, float healing,float flag,int level);

	/// <summary>
	/// playerバトル
	/// </summary>
	void PlayButtel(Player* player, Enemy* enemy);

	/// <summary>
	/// playerディフェンス
	/// </summary>
	void PlayDefense(Player* player, Enemy* enemy);

	/// <summary>
	/// playerヒール
	/// </summary>
	void PlayHealing(Player* player, Enemy* enemy);

	void PlayerTrun();

	void PlaySet();

	void PlayLevelup(Plevel* plevel);

	void PlayerReset();

	/// <summary>
/// エネミー
/// </summary>
	void EnemyInti(float ehp, float eatk, float edef, float espd, float edefplus, float ehealing, float eflag, int elevel, int enumber);

	/// <summary>
/// enemyバトル
/// </summary>
	void EnemyButtel(Player* player, Enemy* enemy);

	/// <summary>
	/// enemyディフェンス
	/// </summary>
	void EnemyDefense(Player* player, Enemy* enemy);

	/// <summary>
	/// enemyヒール
	/// </summary>
	void EnemyHealing(Player* player, Enemy* enemy);

	void EnemyTrun();

	void EnemySet();

	void EnemyLevelup(Elevel* elevel);

	void EnemyReset();

	void EnemySkin();

	void Buttelmod();

	void ButtelScene();

	void ButtelCon();

	void AttackDrow();

	void AttackDrowMove();

	void DefenceDrow();

	void DefenceDrowMove();

	void HealingDrow();

	void HealingDrowMove();

	void EnemyAttackDrow();

	void EnemyAttackDrowMove();

	void EnemyDefenceDrow();
	
	void EnemyDefenceDrowMove();

	void EnemyHealingDrow();

	void EnemyHealingDrowMove();

	void BackGround();

	void SpriteMoveset();

	//boss
	void BossInti(float bossHp, float bossAtk, float bossDef, float bossSpd, float bossDefPlus, float bossHealing, float bossFlag);

	void BossSet(Boss* boss, Player* player);

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;


	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* spriteBG = nullptr;

	//ゲームリソース
	Sprite* spriteTexQ1 = nullptr;
	Sprite* edge = nullptr;
	Sprite* edge2 = nullptr;
	Sprite* first = nullptr;
	Sprite* win = nullptr;
	Sprite* lose = nullptr;
	Sprite* ins = nullptr;
	Sprite* move = nullptr;
	
	Sprite* fire = nullptr;
	Sprite* suru = nullptr;
	Sprite* gorem = nullptr;
	Sprite* eye = nullptr;

	DirectX::XMFLOAT2 rayp[8];
	Sprite* ef1 = nullptr;
	Sprite* ef2 = nullptr;
	Sprite* ef3 = nullptr;
	Sprite* ef4 = nullptr;
	Sprite* ef5 = nullptr;
	Sprite* ef6 = nullptr;
	Sprite* ef7 = nullptr;
	Sprite* ef8 = nullptr;


	DirectX::XMFLOAT2 shildp[7];
	Sprite* defef0 = nullptr;
	Sprite* defef1 = nullptr;
	Sprite* defef2 = nullptr;
	Sprite* defef3 = nullptr;
	Sprite* defef4 = nullptr;
	Sprite* defef5 = nullptr;
	Sprite* defef6 = nullptr;


	DirectX::XMFLOAT2 healing[4];
	Sprite* heal0 = nullptr;
	Sprite* heal1 = nullptr;
	Sprite* heal2 = nullptr;
	Sprite* heal3 = nullptr;

	DirectX::XMFLOAT2 eatkmove[1];
	DirectX::XMFLOAT2 esize[1];
	Sprite* enemyatkdrow = nullptr;

	DirectX::XMFLOAT2 edefmove[1];
	Sprite* enemydefensdrow = nullptr;

	DirectX::XMFLOAT2 ehealmove[4];
	Sprite* enemyhealdrow = nullptr;
	Sprite* eheal1 = nullptr;
	Sprite* eheal2 = nullptr;
	Sprite* eheal3 = nullptr;
	Sprite* eheal4 = nullptr;

	Sprite* BG1 = nullptr;
	Sprite* BG2 = nullptr;
	Sprite* BG3 = nullptr;
	Sprite* BG4 = nullptr;

	//当たり判定 球
	Sphere sphere;
	//当たり判定　平面
	Plane plane;
	//当たり判定　三角形
	Triangle triangle;
	//当たり判定　レイ
	//Ray ray;


	//ステータス
	struct Player player;
	float php;
	struct Plevel plevel;
	float maxhp;
	int playereffect = 0;

	float eplus;
	float enhp;
	int enemynum;
	struct Enemy enemy;
	struct Elevel elevel;
	float maxehp;
	int enowlevel;
	int eleveling;
	int randelevelup;
	int enemyeffect = 0;

	struct Boss boss;
	struct BossSet bossSet;

	int allenemy=4;

	int gamescene = 0;
	int enemykill = 0;
	int enemykillmax;

	float setmode = 300;
	
	int textplayer = 0;
	int textenemy = 0;

	int turn;

	int pmove = 0;
	int emove = 0;

	int pdef;

	float rute2 = 1.41421356237f;
	float isotri = rute2 / 2;

	float shildx = 200.0f;
	float shildy = 100.0f;

	float shildmoveX = 0.0f;
	float shildmoveY = 0.0f;

	float healingmove = 0.0f;

	float sizemove = 0.0f;

	float enemyguard = 0.0f;
	float stopmove = 0.0f;

	float efmove = 0.0f;

	DirectX::XMFLOAT2 test;


};

