#pragma once

class Overlay {
	HINSTANCE h_instance;
	WCHAR overlayWindowName[100] = L"Overlay";
public:
	HWND window;
	HWND game;
	int width;
	int height;

	Overlay();
	

	void Initialize();
};

extern Overlay *overlay;

