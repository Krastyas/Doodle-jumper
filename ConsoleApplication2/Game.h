#pragma once
#include <string>
#include <windows.h>
#include "Platform.h"
#include "Player.h"

inline void BoostPlatform::ApplyEffect(Player* player)
{
	if (player)
		player->AddJumpPower(0.3f);
}

inline void WeakPlatform::ApplyEffect(Player* player)
{
	if (player)
		player->RemoveJumpPower(0.3f);
}

inline void SpringPlatform::ApplyEffect(Player* player)
{
	if (player)
		player->SetMaxPower();
}

class Game
{
private:
	WeakPlatform weakPlatform;
	BoostPlatform boostPlatform;
	SpringPlatform springPlatform;
	Platform* platforms[3];
	Player player;
	int selectedPlatform;
	int score;
	float gravity;

	float PlayerStartX(int platformIndex)
	{
		return platforms[platformIndex]->GetX() +
			(platforms[platformIndex]->GetWidth() - 3) / 2.0f;
	}

public:
	Game()
		: weakPlatform(9, 17),
		  boostPlatform(35, 17),
		  springPlatform(61, 17),
		  platforms{ &weakPlatform, &boostPlatform, &springPlatform },
			player(0, 15), selectedPlatform(1), score(0), gravity(0.35f)
	{
		player.SetX(PlayerStartX(selectedPlatform));
	}

	void Update()
	{
		int screenHeight = 24;
		int playerWidth = 3;
		float previousY = player.GetY();
		player.Update(gravity);

		if (!player.IsJumping())
			return;

		Platform* platform = platforms[selectedPlatform];
		float playerBottomBefore = previousY + player.GetHeight();
		float playerBottomAfter = player.GetY() + player.GetHeight();
		bool overlaps = player.GetX() + playerWidth > platform->GetX() &&
			player.GetX() < platform->GetX() + platform->GetWidth();
		bool crossedPlatform = player.GetVelocity() > 0 &&
			playerBottomBefore <= platform->GetY() &&
			playerBottomAfter >= platform->GetY();

		if (overlaps && crossedPlatform)
		{
			player.Land(platform->GetY() - player.GetHeight());
			platform->ApplyEffect(&player);
			score += 10;
		}
		else if (player.GetY() >= screenHeight - player.GetHeight())
		{
			player.Land(platform->GetY() - player.GetHeight());
			player.SetX(PlayerStartX(selectedPlatform));
		}
	}

	void Jump()
	{
		player.Jump();
	}

	void MoveLeft()
	{
		if (selectedPlatform > 0)
		{
			--selectedPlatform;
			player.SetX(PlayerStartX(selectedPlatform));
		}
	}

	void MoveRight()
	{
		if (selectedPlatform < 2)
		{
			++selectedPlatform;
			player.SetX(PlayerStartX(selectedPlatform));
		}
	}

	void Draw()
	{
		int screenWidth = 80;
		int screenHeight = 24;
		int playerWidth = 3;
		std::string frame[24];
		for (int y = 0; y < screenHeight; ++y)
			frame[y] = std::string(screenWidth, ' ');

		for (int x = 0; x < screenWidth; ++x)
		{
			frame[0][x] = '=';
			frame[screenHeight - 4][x] = '=';
		}

		for (int i = 0; i < 3; ++i)
		{
			Platform* platform = platforms[i];
			int platformX = platform->GetX();
			int platformRow = platform->GetY();
			char symbol = i == selectedPlatform ? '#' : '-';

			for (int x = platformX; x < platformX + platform->GetWidth(); ++x)
				frame[platformRow][x] = symbol;
		}

		int playerX = static_cast<int>(player.GetX());
		int playerY = static_cast<int>(player.GetY());
		for (int y = playerY; y < playerY + player.GetHeight(); ++y)
		{
			for (int x = playerX; x < playerX + playerWidth; ++x)
				if (y >= 0 && y < screenHeight - 4 && x >= 0 && x < screenWidth)
				{
					frame[y][x] = 'O';
				}
		}

		std::string status = "Score: " + std::to_string(score) +
			" | Jump power: " + std::to_string(player.GetJumpPower()) +
			" | Platform: " + platforms[selectedPlatform]->GetName();
		std::string controls = "SPACE: jump   LEFT/RIGHT or A/D: platform   Q: quit";
		frame[screenHeight - 3].replace(0, status.size(), status);
		frame[screenHeight - 2].replace(0, controls.size(), controls);

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD origin = { 0, 0 };
		SetConsoleCursorPosition(console, origin);

		for (std::string& row : frame)
		{
			DWORD written = 0;
			WriteConsoleA(console, row.c_str(), static_cast<DWORD>(row.size()), &written, nullptr);
			WriteConsoleA(console, "\r\n", 2, &written, nullptr);
		}
	}
};
