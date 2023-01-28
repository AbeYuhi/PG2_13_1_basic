#include <Novice.h>
#include <math.h>
#include "Enemy.h"


const char kWindowTitle[] = "学籍番号";

typedef struct Bullet {
	Vector2 pos;
	int radius;
	bool isAlive;
}BUllet;

bool Enemy::isAlive = true;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Enemy* enemy1 = new Enemy({600.0f, 400.0f }, {6.0f, 0.0f }, 16);
	Enemy* enemy2 = new Enemy({430.0f, 500.0f }, {4.0f, 0.0f }, 16);


	Vector2 size = { 32, 32 };
	Vector2 pos = { 640, 600 };

	Bullet bullet[50] = {};
	int bulletCooldown = 10;

	for (int i = 0; i < 50; i++) {
		bullet[i].isAlive = false;
		bullet[i].radius = 16;
	}

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		if (keys[DIK_R]) {
			Enemy::isAlive = true;
		}

		if (keys[DIK_A]) {
			pos.x -= 4;
		}
		if (keys[DIK_D]) {
			pos.x += 4;
		}
		if (keys[DIK_W]) {
			pos.y -= 4;
		}
		if (keys[DIK_S]) {
			pos.y += 4;
		}

		enemy1->Move();
		enemy2->Move();

		if (keys[DIK_SPACE]) {
			for (int i = 0; i < 50; i++) {
				if (!bullet[i].isAlive && bulletCooldown <= 0) {
					bulletCooldown = 10;
					bullet[i].isAlive = true;
					bullet[i].pos = pos;

					break;
				}
			}
		}
		if (bulletCooldown > 0) {
			bulletCooldown--;
		}

		for (int i = 0; i < 50; i++) {
			if (bullet[i].isAlive) {
				bullet[i].pos.y -= 4;

				if (bullet[i].pos.y <= -50) {
					bullet[i].isAlive = false;
				}
			}
		}

		for (int i = 0; i < 50; i++) {
			if (bullet[i].isAlive) {
				int a = bullet[i].pos.x - enemy1->GetPos().x;
				int b = bullet[i].pos.y - enemy1->GetPos().y;

				int c = sqrtf(powf(a, 2) + powf(b, 2));

				if (c <= enemy1->GetRadius() + bullet[i].radius) {
					Enemy::isAlive = false;
				}

			}
			if (bullet[i].isAlive) {
				int a = bullet[i].pos.x - enemy2->GetPos().x;
				int b = bullet[i].pos.y - enemy2->GetPos().y;

				int c = sqrtf(powf(a, 2) + powf(b, 2));

				if (c <= enemy2->GetRadius() + bullet[i].radius) {
					Enemy::isAlive = false;
				}

			}
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		enemy1->Draw();
		enemy2->Draw();

		Novice::DrawEllipse(pos.x, pos.y, size.x, size.y, 0, WHITE, kFillModeSolid);

		for (int i = 0; i < 50; i++) {
			if (bullet[i].isAlive) {
				Novice::DrawEllipse(bullet[i].pos.x, bullet[i].pos.y, bullet[i].radius, bullet[i].radius, 0, BLUE, kFillModeSolid);
			}
		}


		Novice::ScreenPrintf(0, 0, "enemyA isAlive = d", enemy1->isAlive);
		Novice::ScreenPrintf(0, 20, "enemyB isAlive = d", enemy2->isAlive);
		Novice::ScreenPrintf(0, 40, "WASD : PlayerMove");
		Novice::ScreenPrintf(0, 60, "shot : Space");
		Novice::ScreenPrintf(0, 80, "enemy respawn : R");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete enemy1;
	delete enemy2;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
