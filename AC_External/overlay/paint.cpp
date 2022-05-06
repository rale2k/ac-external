#include "includes.h"


void Paint::d2dInit(HWND hWnd, int width, int height) {

    GetClientRect(hWnd, &rc);

    D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &pD2DFactory
    );

    HRESULT hr = pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            hWnd,
            D2D1::SizeU(
                width,
                height)
        ),
        &pRenderTarget
    );

    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(&pD2DWriteFactory)
        );
    }

    if (SUCCEEDED(hr))
    {
        // Create a DirectWrite text format object.
        hr = pD2DWriteFactory->CreateTextFormat(
            fontName,
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            fontSize,
            L"", //locale
            &pD2DTextFormat
        );
    }
    if (SUCCEEDED(hr))
    {
        // Center the text horizontally and vertically.
        pD2DTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        pD2DTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    if (SUCCEEDED(hr))
    {
        pRenderTarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Red),
            &pBrush
        );
    }
}

Paint::Paint() {};

Paint::Paint(HWND hWnd, HWND targetWnd, int width, int height) {
    this->targetWnd = targetWnd;
    d2dInit(hWnd, width, height);
}

void Paint::render() {
    pRenderTarget->BeginDraw();
    pRenderTarget->Clear();
    if (GetForegroundWindow() == targetWnd) {
        if (features->esp) {
           features->ESP(this);
        }
    }
    pRenderTarget->EndDraw();
}

void Paint::drawRectHollow(RECT &rect, D2D1::ColorF::Enum color) {
    pBrush->SetColor(D2D1::ColorF(color));
    pRenderTarget->DrawRectangle(D2D1::RectF(rect.left, rect.top, rect.right, rect.bottom), pBrush, 1.0f);
}

void Paint::drawText(std::string string, float x, float y) {
    size_t len{ string.size() };
    std::wstring text{ std::wstring(string.begin(), string.end()) };

    pRenderTarget->DrawText(text.c_str(), len, pD2DTextFormat, D2D1::RectF(x - (len * 11 / 2 ), y, x + (len * 11 / 2), y + 15), pBrush);
}
