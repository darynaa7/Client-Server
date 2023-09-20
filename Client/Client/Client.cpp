import Network;
using namespace Network;

#include "ScreenshotUtils.h"

int main() 
{
    const auto client = new Client();

    client->createConnection();
    client->sendMessages();

    const auto screenshotUtil = new ScreenshotUtils();
    client->sendImage(ScreenshotUtils::captureAndSaveScreenshot());
}

