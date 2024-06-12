#pragma once
#include "Novice.h"
#include "Vector2.h"
#include "struct.h"

class Result
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(char* keys);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	Line line;

	Particle particle;

	Box box;

private:

	float e{};
	float ViscosityCoefficient{};
	float fx{};
	float fy{};

	bool particleStart{};

};

