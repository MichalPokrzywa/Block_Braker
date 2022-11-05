module;
#include <windows.h>

export module WindowSettings;

export int windowWidth = GetSystemMetrics(SM_CXSCREEN);
export int windowHeight = GetSystemMetrics(SM_CYSCREEN);