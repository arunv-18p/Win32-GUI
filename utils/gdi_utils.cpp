#include "../include/gdi_utils.h"

void GdiUtils::InitGDI() {
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

void GdiUtils::DestroyGDI() {
    Gdiplus::GdiplusShutdown(gdiplusToken);
}