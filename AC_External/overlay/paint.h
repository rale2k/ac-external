#pragma once

class Paint {
private:
    const WCHAR fontName[16] = L"Trebuchet";
    const FLOAT fontSize = 12;

    ID2D1Factory* pD2DFactory = NULL;
    IDWriteFactory* pD2DWriteFactory = NULL;
    IDWriteTextFormat* pD2DTextFormat = NULL;
    ID2D1HwndRenderTarget* pRenderTarget = NULL;
    ID2D1SolidColorBrush* pBrush = NULL;
    RECT rc;
    HWND targetWnd;

    void d2dInit(HWND hWnd, int width, int height);

public:
    void drawRectHollow(RECT& rect, D2D1::ColorF::Enum color);
    void drawText(std::string string, float x, float y);
    void render();

    Paint(HWND hWnd, HWND targetWnd, int width, int height);
    Paint();
};

