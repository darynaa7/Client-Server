#include <string>
#include "ScreenshotUtils.h"


FILE* ScreenshotUtils::captureAndSaveScreenshot()
{
	pressKeys();
	if( OpenClipboard(nullptr) )
	{
		if( const auto hBitmap = static_cast<HBITMAP>(GetClipboardData(CF_BITMAP)); hBitmap != nullptr )
		{
			BITMAP bitmap;
			if( GetObject(hBitmap, sizeof(BITMAP), &bitmap) )
			{
				const int width = bitmap.bmWidth;
				const int height = bitmap.bmHeight;
				const auto buffer = new BYTE[bitmap.bmWidthBytes * height];

				GetBitmapBits(hBitmap, bitmap.bmWidthBytes * height, buffer);

				const std::string folderName = "D:/c++/taskglcamp1/Client/Client/";
				const auto folderNameL = L"D:/c++/taskglcamp1/Client/Client/";

				CreateDirectory(folderNameL, nullptr);

				SYSTEMTIME st;
				GetSystemTime(&st);
				char fileName[100];
				sprintf_s(fileName, "%04d%02d%02d_%02d%02d%02d.png", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

				const auto filePath = folderName + fileName;

				return saveBitmapToFile(buffer, filePath.c_str(), width, height);

				delete[] buffer;

				std::cout << "Image saved to: " << filePath << std::endl;
			}
		}
		CloseClipboard();
	}
	else
	{
		std::cerr << "Failed to open clipboard." << std::endl;
	}
	return nullptr;
}
void ScreenshotUtils::pressKeys()
{
	keybd_event(VK_MENU, 0, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_EXTENDEDKEY, 0);
	Sleep(100);
	keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
}

FILE* ScreenshotUtils::saveBitmapToFile(const BYTE* buffer, const char* filePath, const int width, const int height)
{
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;

	bmpFileHeader.bfType = 0x4D42;
	bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + width * height * 4;
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfoHeader.biWidth = width;
	bmpInfoHeader.biHeight = -height;
	bmpInfoHeader.biPlanes = 1;
	bmpInfoHeader.biBitCount = 32;
	bmpInfoHeader.biCompression = BI_RGB;
	bmpInfoHeader.biSizeImage = 0;
	bmpInfoHeader.biXPelsPerMeter = 0;
	bmpInfoHeader.biYPelsPerMeter = 0;
	bmpInfoHeader.biClrUsed = 0;
	bmpInfoHeader.biClrImportant = 0;

	FILE *imageFile;
	fopen_s(&imageFile, filePath, "wb");
	if( !imageFile )
	{
		std::cerr << "Failed to open file for writing: " << filePath << std::endl;
		return nullptr;
	}

	fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, imageFile);
	fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, imageFile);
	fwrite(buffer, 4, width * height, imageFile);
	//fclose(fp);

	return imageFile;
}
