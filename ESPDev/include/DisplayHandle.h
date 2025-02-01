#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

#include "main.h"

class DisplayHandler {
public:
    DisplayHandler();
    void init();
    void showMessage(String title, String message);
    void showDeviceInfo(String ip);
    void updateTime(String time);
    void CountUP(int count);
private:
    Adafruit_SSD1306 display;
};

#endif
