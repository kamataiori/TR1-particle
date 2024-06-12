#include "Result.h"


void Result::Initialize()
{
	line = {
		{ 0.0f,600.0f },
		{ 1280.0f,600.0f },
		WHITE,
	};

	particle = {

		{0.0f,0.0f},
		{0.0f,0.98f},
		{false},
		{rand() % 3 + 1}
	};
	for (int i = 0; i < 500; i++)
	{
		particle.pos[i].x = 0.0f;
		particle.pos[i].y = 0.0f;
		particle.acceleration[i].x = 0.0f;
		particle.acceleration[i].y = 0.98f;
		particle.isShot[i] = false;
		particle.radius[i] = rand() % 8 + 5;
	}

	box =
	{
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},

		{640.0f,50.0f},

		{40.0f},

		{100.0f},
	};

	e = 0.4f;
	ViscosityCoefficient = 0.1f;
	for (int i = 0; i < 500; i++)
	{
		fx = -ViscosityCoefficient * particle.acceleration[i].x;
		fy = -ViscosityCoefficient * particle.acceleration[i].y;
	}

	particleStart = false;

}

void Result::Update(char* keys)
{
	
	if (keys[DIK_D])
	{
		box.widelength++;
	}

	if (keys[DIK_A])
	{
		box.widelength--;
	}

	if (keys[DIK_W])
	{
		box.heghtlength++;
	}

	if (keys[DIK_S])
	{
		box.heghtlength--;
	}

	if (box.heghtlength <= 5)
	{
		box.heghtlength = 5;
	}

	if (box.widelength <= 5)
	{
		box.widelength = 5;
	}


	if (particleStart == false)
	{
		for (int i = 0; i < 500; i++)
		{
			particle.acceleration[i].x = 0.0f;
			particle.acceleration[i].y = 0.0f;
			fx = 0.0f;
			fy = 0.0f;
		}

		if (keys[DIK_SPACE])
		{
			particleStart = true;
		}
	}


	if (particleStart == true)
	{

		for (int i = 0; i < 500; i++)
		{
			particle.acceleration[i].x += fx;
			particle.acceleration[i].y += fy;
		}

		//パーティクルを移動させる
		for (int i = 0; i < 500; i++)
		{
			particle.pos[i].y += particle.acceleration[i].y;
			particle.pos[i].x += particle.acceleration[i].x;
		}

		for (int i = 0; i < 500; i++)
		{
			if (particle.isShot[i] == false)
			{
				particle.isShot[i] = true;
				particle.pos[i].x = box.center.x + rand() % (int)box.widelength - (int)box.widelength / 2;
				particle.pos[i].y = box.center.y + rand() % (int)box.heghtlength - (int)box.heghtlength / 2;
				particle.acceleration[i].y = 0.98f;
				break;
			}

		}

		for (int i = 0; i < 500; i++)
		{
			if (particle.isShot[i] == true)
			{
				particle.acceleration[i].y += 0.4f;
			}
		}

		for (int i = 0; i < 500; i++)
		{
			if (particle.pos[i].y >= line.Start.y - 8)
			{
				// 50%の確率でプラス方向に、残りの50%の確率でマイナス方向に動く
				particle.acceleration[i].x = 4.98f * ((rand() % 2) * 2 - 1);
				particle.acceleration[i].y = -particle.acceleration[i].y * e;
			}
		}

	}

	if (particleStart == true)
	{
		if (keys[DIK_RETURN])
		{
			particleStart = false;
		}
	}



}

void Result::Draw()
{
	Novice::DrawBox((int)box.center.x - (int)box.widelength / 2, (int)box.center.y - (int)box.heghtlength / 2, (int)box.widelength, (int)box.heghtlength, 0.0f, WHITE, kFillModeWireFrame);

	Novice::DrawLine((int)line.Start.x, (int)line.Start.y, (int)line.End.x, (int)line.End.y, line.color);

	if (particleStart == true)
	{
		for (int i = 0; i < 500; i++)
		{
			if (particle.isShot[i] == true)
			{
				Novice::DrawEllipse((int)particle.pos[i].x, (int)particle.pos[i].y, particle.radius[i], particle.radius[i], 0.0f, WHITE, kFillModeSolid);

			}

		}
	}

	
}
