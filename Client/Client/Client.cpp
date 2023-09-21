#include <thread>

#include "ScreenshotUtils.h"

import Network;

using namespace Network;


int main() 
{
    const auto client = new Client();

    client->createConnection();
    client->sendMessages();

    const auto screenshotUtil = new ScreenshotUtils();
    for (int i = 0; i < 4; ++i)
    {
        client->sendImage(ScreenshotUtils::captureAndSaveScreenshot());
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
    //client->sendImage(ScreenshotUtils::captureAndSaveScreenshot());

    client->closeConnection();
}

