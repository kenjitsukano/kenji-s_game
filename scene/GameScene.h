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

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;	

	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* spriteBG = nullptr;
	Sprite* spriteTex = nullptr;
	Sprite* spriteTexQ1 = nullptr;
	Sprite* spriteTexQ2 = nullptr;
	Sprite* spriteTexQ3 = nullptr;
	Sprite* spriteTexQ4 = nullptr;
	Sprite* spriteTexQ5 = nullptr;
	Sprite* spriteTexQ6 = nullptr;

	Model* modelSkydome = nullptr;
	Model* modelGround = nullptr;
	Model* modelFighter = nullptr;

	Object3d* objSkydome = nullptr;
	Object3d* objGround = nullptr;
	Object3d* objFighter = nullptr;

	//当たり判定 球
	Sphere sphere;
	//当たり判定　平面
	Plane plane;
	//当たり判定　三角形
	Triangle triangle;
	//当たり判定　レイ
	//Ray ray;


	//ステータス
	float hp = 10.0f;
	float atk = 2.0f;
	float def = 1.0f;
	float spd = 2.0f;

	float ehp = 15.0f;
	float eatk = 3.0f;
	float edef = 1.0f;
	float espd = 1.0f;

	float dmg;

	int buttel = 0;
	float timer = 10.0f;

	float cas = 300.0f;

	float atkmod = 0.0f;
	float defmod = 0.0f;
	float helmod = 0.0f;

	int scene = 0;
	int i = 100;
	int moved = 0;
};

