#pragma once

#include "FixWindows.h"
#include <windows.h>
#include <vector>

struct Entity
{
	float x = 0, y = 0;
	float rotation = 0;
	float speed = 0;
	unsigned char r = 0, g = 0, b = 0;
	float size = 1;
};

class EntityDisplayApp
{
public:
	EntityDisplayApp(int screenWidth = 800, int screenHeight = 450);
	~EntityDisplayApp();

	bool Startup();
	void Shutdown();

	void Update(float deltaTime);
	void Draw();

	HANDLE fileEntity;
	HANDLE fileEntitySize;

protected:
	int m_screenWidth;
	int m_screenHeight;

	// an array of an unknown number of entities
	std::vector<Entity> m_entities;

	int* entitySize;
	Entity* sharedData;
};