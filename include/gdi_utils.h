#ifndef GDI_UTILS_H
#define GDI_UTILS_H

#include "windows.h"
#include <gdiplus.h>

class GdiUtils {
    public:
        void InitGDI();
        void DestroyGDI();
    private:
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;
};

#endif