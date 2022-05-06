#include "includes.h"

Paint* paint;

ATOM registerClass(HINSTANCE hInstance);

void Overlay::Initialize() {
    game = FindWindow(NULL, L"AssaultCube");
    h_instance = GetModuleHandle(NULL);
    registerClass(h_instance);

    RECT rect;

    // stinky magic numbers to work around window borders
    if (GetWindowRect(game, &rect))
    {
        width = rect.right - rect.left - 6;
        height = rect.bottom - rect.top - 29;
    }

    window = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, overlayWindowName, overlayWindowName, WS_POPUP,
        1, 1, width, height, nullptr, nullptr, h_instance, nullptr);

    SetLayeredWindowAttributes(window, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(window, 1);

    paint = new Paint(window, game, width, height);
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (GetWindowRect(game, &rect))
        { // more stinky
            width = rect.right - rect.left - 6;
            height = rect.bottom - rect.top - 29;
        }

        MoveWindow(window, rect.left + 3, rect.top + 26, width, height, true);
        std::this_thread::sleep_for(std::chrono::milliseconds(7));
    }
}

Overlay::Overlay() {};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT:
        paint->render();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

ATOM registerClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName = L"Overlay";
    wcex.lpszClassName = L"Overlay";
    wcex.hIconSm = 0;

    return RegisterClassExW(&wcex);
}

Overlay* overlay = new Overlay;
