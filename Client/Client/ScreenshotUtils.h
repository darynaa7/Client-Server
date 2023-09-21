#pragma once
#include <iostream>
#include <windows.h>

class ScreenshotUtils
{
public:
    static FILE* captureAndSaveScreenshot();
private:
	static void pressKeys();
	static FILE* saveBitmapToFile(const BYTE *buffer, const char *filePath, const int width, const int height);
};
