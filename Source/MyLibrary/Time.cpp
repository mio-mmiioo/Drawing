#include "Time.h"
#include <Windows.h>
#include <DxLib.h>

namespace Time
{
	LARGE_INTEGER frequency;
	LARGE_INTEGER current;
	float deltaTime;
	float refreshRate;
}

void Time::Init()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&current);

	HDC hdc = GetDC(GetMainWindowHandle()); // デバイスコンテキストの取得
	refreshRate = (float)GetDeviceCaps(hdc, VREFRESH); // リフレッシュレートの取得
	ReleaseDC(GetMainWindowHandle(), hdc); // デバイスコンテキストの解放
}

void Time::Update()
{
	LARGE_INTEGER last = current;
	QueryPerformanceCounter(&current);
	float dt = static_cast<float>(current.QuadPart - last.QuadPart) / frequency.QuadPart;
	int frames = (int)((dt * 1.2f) * refreshRate);
	if (frames >= 2)
	{
		frames = 2;
	}
	deltaTime = frames / refreshRate;
}

void Time::Release()
{

}

float Time::DeltaTime()
{
	return deltaTime;
}