#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <gdiplus.h>
#include <uxtheme.h>
#include <iostream>

#include "../include/gdi_utils.h"
#include "../include/win32_utils.h"

#define WINDOW_DEFAULT_WIDTH 800
#define WINDOW_DEFAULT_HEIGHT 500

using namespace std;

int windowWidth = WINDOW_DEFAULT_WIDTH;
int windowHeight = WINDOW_DEFAULT_HEIGHT;

Win32Utils win32Utils;
GdiUtils gdiUtils;

static TCHAR szWindowClass[] = _T("Win32");
static TCHAR szTitle[] = _T("Win32-GUI");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void OnPaint(HWND hWnd, HDC hdc);
void OnResize(HWND hWnd, int width, int height);
void OnKeyDown(HWND hWnd, WPARAM wParam);
void OnCreate(HWND hWnd);
void OnDestroy(HWND hWnd);

void DrawWindowBackground(Gdiplus::Graphics* gfx);
