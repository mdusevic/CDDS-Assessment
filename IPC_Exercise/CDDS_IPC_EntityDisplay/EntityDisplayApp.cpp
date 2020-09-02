#include "EntityDisplayApp.h"
#include "FixWindows.h"
#include "raylib.h"
#include <windows.h>
#include <iostream>

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

	// Gain access to shared memory block
	fileEntity = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"SharedMemoryEntity");
	fileEntitySize = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"SharedMemoryEntitySize");

	if (fileEntity == nullptr || fileEntitySize == nullptr)
	{
		std::cout << "Client - Could not create file mapping object: " << GetLastError() << std::endl;
		return false;
	}

	// Map the memory from the shared block to a pointer we can manipulate
	entitySize = (int*)MapViewOfFile(fileEntitySize, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
	sharedData = (Entity*)MapViewOfFile(fileEntity, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Entity) * *entitySize);

	if (sharedData == nullptr || entitySize == nullptr)
	{
		std::cout << "Client - Could not map view of file: " << GetLastError() << std::endl;
		CloseHandle(fileEntity);
		CloseHandle(fileEntitySize);
		return false;
	}

	for (int i = 0; i < *entitySize; i++)
	{
		Entity temp;
		m_entities.push_back(temp);
	}

	return true;
}

void EntityDisplayApp::Shutdown()
{
	// Unmap the memory block since we're done with it
	UnmapViewOfFile(sharedData);

	// Close the shared file
	CloseHandle(fileEntity);
	CloseHandle(fileEntitySize);

	CloseWindow();
}

void EntityDisplayApp::Update(float deltaTime)
{
	// Reading data from shared memory block

	sharedData = (Entity*)MapViewOfFile(fileEntity, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(Entity) * *entitySize);

	entitySize = (int*)MapViewOfFile(fileEntitySize, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));

	for (int i = 0; i < *entitySize; i++)
	{
		m_entities[i] = sharedData[i];
	}
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