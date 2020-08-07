#include "EntityDisplayApp.h"
#include "raylib.h"

EntityDisplayApp::EntityDisplayApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{

}

EntityDisplayApp::~EntityDisplayApp()
{

}

bool EntityDisplayApp::Startup()
{
	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);

	return true;
}

void EntityDisplayApp::Shutdown()
{
	CloseWindow();
}

void EntityDisplayApp::Update(float deltaTime)
{

}

void EntityDisplayApp::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// Draw entities
	for (auto& entity : m_entities)
	{
		DrawRectanglePro(
			Rectangle{ entity.x, entity.y, entity.size, entity.size }, // Rectangle
			Vector2{ entity.size / 2, entity.size / 2 }, // Origin
			entity.rotation,
			Color{ entity.r, entity.g, entity.b, 255 });
	}

	// Output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	EndDrawing();
}