#ifndef WIN32_UTILS_H
#define WIN32_UTILS_H

#include <dwmapi.h>
#include <tchar.h>

#include <string>

#include "windows.h"

#define WINDOWS_11_22H2 22621
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20

class Win32Utils {
   private:
    int DWM_TRUE = 0x01;
    int DWM_FALSE = 0x00;

    int DWM_BACKDROP_DISABLE = 0x01;
    int DWM_BACKDROP_MICA = 0x02;
    int DWM_BACKDROP_TRANSIENT = 0x03;
    int DWM_BACKDROP_TABBED = 0x04;

   public:
    bool IsDarkTheme();
    int GetBuildNumber();
    void SetMicaEffect(HWND hWnd, bool isMicaEnable, bool isMicaAlt);
    void SetDarkMode(HWND hWnd, bool isDarkModeEnable, bool useSystemSetting);
};

#endif