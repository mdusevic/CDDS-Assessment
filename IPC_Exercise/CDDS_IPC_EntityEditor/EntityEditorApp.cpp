#include "EntityEditorApp.h"
#include "FixWindows.h"
#include "raylib.h"
#include <random>
#include <time.h>
#include <windows.h>
#include <iostream>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

EntityEditorApp::EntityEditorApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{

}

EntityEditorApp::~EntityEditorApp()
{

}

bool EntityEditorApp::Startup()
{
	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);

	srand(time(nullptr));
	for (auto& entity : m_entities)
	{
		entity.x = rand()%m_screenWidth;
		entity.y = rand()%m_screenHeight;
		entity.size = 10;
		entity.speed = rand() % 100;
		entity.rotation = rand() % 360;
		entity.r = rand() % 255;
		entity.g = rand() % 255;
		entity.b = rand() % 255;
	}

	// Opening shared memory block
	fileEntity = CreateFileMapping(INVALID_HANDLE_VALUE, // a handle to an existing virtual file, or invalid
		nullptr, // optional security attributes
		PAGE_READWRITE, // read/write access control
		0, sizeof(Entity) * ENTITY_COUNT, // size of the memory block, 
		L"SharedMemoryEntity");

	fileEntitySize = CreateFileMapping(INVALID_HANDLE_VALUE, // a handle to an existing virtual file, or invalid
		nullptr, // optional security attributes
		PAGE_READWRITE, // read/write access control
		0, sizeof(int), // size of the memory block, 
		L"SharedMemoryEntitySize");

	if (fileEntity == nullptr || fileEntitySize == nullptr)
	{
		std::cout << "Server - Could not create file mapping object: " << GetLastError() << std::endl;
		return false;
	}

	// Map the memory from the shared block to a pointer we can manipulate
	sharedData = (Entity*)MapViewOfFile(fileEntity,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		sizeof(Entity) * ENTITY_COUNT);

	sharedSize = (int*)MapViewOfFile(fileEntitySize,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		sizeof(int));

	if (sharedData == nullptr || sharedSize == nullptr)
	{
		std::cout << "Server - Could not map view of file: " << GetLastError() << std::endl;
		CloseHandle(fileEntity);
		CloseHandle(fileEntitySize);
		return false;
	}  

	return true;
}

void EntityEditorApp::Shutdown()
{
	// Unmap the memory block since we're done with it
	UnmapViewOfFile(sharedData);

	// Close the shared file
	CloseHandle(fileEntity);

	CloseHandle(fileEntitySize);

	CloseWindow();
}

void EntityEditorApp::Update(float deltaTime)
{
	// Select an entity to edit
	static int selection = 0;
	static bool selectionEditMode = false;
	static bool xEditMode = false;
	static bool yEditMode = false;
	static bool rotationEditMode = false;
	static bool sizeEditMode = false;
	static bool speedEditMode = false;
	static Color colorPickerValue = WHITE;

	if (GuiSpinner(Rectangle{ 90, 25, 125, 25 }, "Entity", &selection, 0, ENTITY_COUNT - 1, selectionEditMode))
	{
		selectionEditMode = !selectionEditMode;
	}
	
	int intX = (int)m_entities[selection].x;	
	int intY = (int)m_entities[selection].y;
	int intRotation = (int)m_entities[selection].rotation;
	int intSize = (int)m_entities[selection].size;
	int intSpeed = (int)m_entities[selection].speed;

	// Display editable stats within a GUI	
	GuiGroupBox(Rectangle{ 25, 70, 480, 220 }, "Entity Properties");

	if (GuiValueBox(Rectangle{ 90, 90, 125, 25 }, "x", &intX, 0, m_screenWidth, xEditMode))
	{
		xEditMode = !xEditMode;
		m_entities[selection].x = intX;
	}

	if (GuiValueBox(Rectangle{ 90, 120, 125, 25 }, "y", &intY, 0, m_screenHeight, yEditMode))
	{
		yEditMode = !yEditMode;
		m_entities[selection].y = intY;
	}

	m_entities[selection].rotation = GuiSlider(Rectangle{ 90, 150, 125, 25 }, "rotation", TextFormat("%2.2f", m_entities[selection].rotation), m_entities[selection].rotation, 0, 360);
	m_entities[selection].size = GuiSlider(Rectangle{ 90, 180, 125, 25 }, "size", TextFormat("%2.2f", m_entities[selection].size), m_entities[selection].size, 0, 100);
	m_entities[selection].speed = GuiSlider(Rectangle{ 90, 210, 125, 25 }, "speed", TextFormat("%2.2f", m_entities[selection].speed), m_entities[selection].speed, 0, 100);
	
	colorPickerValue = GuiColorPicker(Rectangle{ 260, 90, 156, 162 }, Color{ m_entities[selection].r, m_entities[selection].g, m_entities[selection].b });
	m_entities[selection].r = colorPickerValue.r;
	m_entities[selection].g = colorPickerValue.g;
	m_entities[selection].b = colorPickerValue.b;

	// Move entities
	for (int i = 0; i < ENTITY_COUNT; i++)
	{
		if (selection == i)
		{
			continue;
		}

		float s = sinf(m_entities[i].rotation) * m_entities[i].speed;
		float c = cosf(m_entities[i].rotation) * m_entities[i].speed;
		m_entities[i].x -= s * deltaTime;
		m_entities[i].y += c * deltaTime;

		// Wrap position around the screen
		m_entities[i].x = fmod(m_entities[i].x, m_screenWidth);
		
		if (m_entities[i].x < 0)
		{
			m_entities[i].x += m_screenWidth;
		}

		m_entities[i].y = fmod(m_entities[i].y, m_screenHeight);

		if (m_entities[i].y < 0)
		{
			m_entities[i].y += m_screenHeight;
		}
	}

	// Writing to shared memory block
	for (int i = 0; i < ENTITY_COUNT; i++)
	{
		sharedData[i] = m_entities[i];
	}

	*sharedSize = ENTITY_COUNT;
}

void EntityEditorApp::Draw()
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