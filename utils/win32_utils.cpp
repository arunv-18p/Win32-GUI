#include "../include/win32_utils.h"

#include <iostream>
using namespace std;

bool Win32Utils::IsDarkTheme() {
    DWORD use_light_theme;
    DWORD use_light_theme_size = sizeof(use_light_theme);
    RegGetValue(
        HKEY_CURRENT_USER,
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        "AppsUseLightTheme", RRF_RT_REG_DWORD, nullptr, &use_light_theme,
        &use_light_theme_size);

    return use_light_theme ? false : true;
}

int Win32Utils::GetBuildNumber() {
    DWORD value;
    DWORD BufferSize = sizeof(value);

    RegGetValue(HKEY_LOCAL_MACHINE,
                "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                "CurrentBuild", RRF_RT_REG_SZ, 0, &value, &BufferSize);

    return value;
}

void Win32Utils::SetMicaEffect(HWND hWnd, bool isMicaEnable, bool isMicaAlt) {
    auto micaEffect = isMicaAlt ? &DWM_BACKDROP_TABBED : &DWM_BACKDROP_MICA;
    if (GetBuildNumber() < WINDOWS_11_22H2) return;
    if (isMicaEnable) {
        DwmSetWindowAttribute(hWnd, 38, micaEffect, sizeof(int));
    } else {
        DwmSetWindowAttribute(hWnd, 38, &DWM_FALSE, sizeof(int));
    }
}

void Win32Utils::SetDarkMode(HWND hWnd, bool isDarkModeEnable, bool useSystemSetting) {
    if (isDarkModeEnable) {
        BOOL value = useSystemSetting ? IsDarkTheme() : true;
        DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));
    }
}