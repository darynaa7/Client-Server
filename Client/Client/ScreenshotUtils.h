#pragma once
#include <iostream>
#include <windows.h>

class ScreenshotUtils
{
public:
    static FILE* captureAndSaveScreenshot();
	
private:
	static void pressKeys();
	/*{
		keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY, 0);
		keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_EXTENDEDKEY, 0);
		Sleep(100);
		keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	}*/

	static FILE* saveBitmapToFile(const BYTE *buffer, const char *filePath, const int width, const int height);
	//{
	//	BITMAPFILEHEADER bmpFileHeader;
	//	BITMAPINFOHEADER bmpInfoHeader;

	//	bmpFileHeader.bfType = 0x4D42;
	//	bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + width * height * 4;
	//	bmpFileHeader.bfReserved1 = 0;
	//	bmpFileHeader.bfReserved2 = 0;
	//	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	//	bmpInfoHeader.biWidth = width;
	//	bmpInfoHeader.biHeight = -height;
	//	bmpInfoHeader.biPlanes = 1;
	//	bmpInfoHeader.biBitCount = 32;
	//	bmpInfoHeader.biCompression = BI_RGB;
	//	bmpInfoHeader.biSizeImage = 0;
	//	bmpInfoHeader.biXPelsPerMeter = 0;
	//	bmpInfoHeader.biYPelsPerMeter = 0;
	//	bmpInfoHeader.biClrUsed = 0;
	//	bmpInfoHeader.biClrImportant = 0;

	//	FILE *fp;
	//	fopen_s(&fp, filePath, "wb");
	//	if( !fp )
	//	{
	//		std::cerr << "Failed to open file for writing: " << filePath << std::endl;
	//		return;
	//	}

	//	fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	//	fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	//	fwrite(buffer, 4, width * height, fp);
	//	fclose(fp);
	//}
};
