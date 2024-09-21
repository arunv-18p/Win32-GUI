// HelloWindowsDesktop.cpp
#include "../include/window.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, "Failed to register class", "Win32-GUI", NULL);
        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindowExA(
        WS_EX_OVERLAPPEDWINDOW, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_DEFAULT_WIDTH,
        WINDOW_DEFAULT_HEIGHT, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, "Failed to create window", "Win32-GUI", NULL);
        return 1;
    }

    // init gdi+
    gdiUtils.InitGDI();

    // apply mica effect (windows 11) & dark mode
    win32Utils.SetMicaEffect(hWnd, true, false);
    win32Utils.SetDarkMode(hWnd, true, true);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void OnPaint(HWND hWnd, HDC hdc) {
    Gdiplus::Graphics gfx = Gdiplus::Graphics(hdc);
    DrawWindowBackground(&gfx);
}

void OnResize(HWND hWnd, int width, int height) {
    windowWidth = width;
    windowHeight = height;
}

void OnCreate(HWND hWnd) { 
    // OnCreate function
    cout << "window created" << endl; 
}

void OnKeyDown(HWND hWnd, WPARAM wParam) {
    // close window when escape key is pressed
    if (wParam == VK_ESCAPE)
        PostQuitMessage(0);
}

void OnDestroy(HWND hWnd) {
    gdiUtils.DestroyGDI();
    PostQuitMessage(0);
}

void DrawWindowBackground(Gdiplus::Graphics* gfx) {
    bool isDarkTheme = win32Utils.IsDarkTheme();
    Gdiplus::Color darkBGColor(10, 10, 10);
    Gdiplus::Color lightBGColor(255, 255, 255);
    Gdiplus::SolidBrush brush(isDarkTheme ? darkBGColor : lightBGColor);
    gfx->FillRectangle(&brush, 0, 0, windowWidth, windowHeight);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            OnPaint(hWnd, hdc);
            EndPaint(hWnd, &ps);
            break;
        case WM_CREATE:
            OnCreate(hWnd);
        case WM_SIZE:
            OnResize(hWnd, LOWORD(lParam), HIWORD(lParam));
            break;
        case WM_DESTROY:
            OnDestroy(hWnd);
            break;
        case WM_KEYDOWN:
            OnKeyDown(hWnd, wParam);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }

    return 0;
}