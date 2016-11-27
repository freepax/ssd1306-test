#include <iostream>
#include <iomanip>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdlib.h>

#include <ssd1306.h>


static unsigned char arduino[1024] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x80, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xFF,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
    0x80, 0xFF, 0xFF, 0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x8C, 0x8E, 0x84, 0x00, 0x00, 0x80, 0xF8,
    0xF8, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80,
    0x00, 0xE0, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xC7, 0x01, 0x01,
    0x01, 0x01, 0x83, 0xFF, 0xFF, 0x00, 0x00, 0x7C, 0xFE, 0xC7, 0x01, 0x01, 0x01, 0x01, 0x83, 0xFF,
    0xFF, 0xFF, 0x00, 0x38, 0xFE, 0xC7, 0x83, 0x01, 0x01, 0x01, 0x83, 0xC7, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0xFF, 0xFF, 0x07, 0x01, 0x01, 0x01, 0x00, 0x00, 0x7F, 0xFF,
    0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0xFF,
    0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x0F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC7, 0xC7, 0x8F,
    0x8F, 0x9F, 0xBF, 0xFF, 0xFF, 0xC3, 0xC0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC,
    0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x01, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01,
    0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00,
    0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x03,
    0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x0F,
    0x87, 0xC7, 0xF7, 0xFF, 0xFF, 0x1F, 0x1F, 0x3D, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0x7C, 0x7D, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x07, 0x00, 0x30, 0x30, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xC0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xC0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x1F,
    0x0F, 0x07, 0x1F, 0x7F, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00,
    0x00, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x0E, 0xFC, 0xF8, 0x00, 0x00, 0xF0, 0xF8, 0x1C, 0x0E,
    0x06, 0x06, 0x06, 0x0C, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFC,
    0xFE, 0xFC, 0x00, 0x18, 0x3C, 0x7E, 0x66, 0xE6, 0xCE, 0x84, 0x00, 0x00, 0x06, 0xFF, 0xFF, 0x06,
    0x06, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x06, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0xC0, 0xF8,
    0xFC, 0x4E, 0x46, 0x46, 0x46, 0x4E, 0x7C, 0x78, 0x40, 0x18, 0x3C, 0x76, 0xE6, 0xCE, 0xCC, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x03, 0x07, 0x0E, 0x0C,
    0x18, 0x18, 0x0C, 0x06, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x01, 0x0F, 0x0E, 0x0C, 0x18, 0x0C, 0x0F,
    0x07, 0x01, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00,
    0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x07,
    0x07, 0x0C, 0x0C, 0x18, 0x1C, 0x0C, 0x06, 0x06, 0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


int initDisplay(SSD1306 *ssd1306)
{
    /// display off
    if (ssd1306->runCommand(Ssd1306DisplayOff) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -2;
    }

    /// set display clock div
    if (ssd1306->runCommand(Ssd1306SetDisplayClockDiv) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -3;
    }

    /// the clock div
    if (ssd1306->runCommand(0x80) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -4;
    }

    /// set multiplex
    if (ssd1306->runCommand(ssd1306SetMultiplex) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -5;
    }

    /// the multiplex
    if (ssd1306->runCommand(0x3f) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -6;
    }

    /// set display offset
    if (ssd1306->runCommand(Ssd1306SetDisplayOffset) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -7;
    }

    /// the display offset
    if (ssd1306->runCommand(0x0) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -8;
    }

    /// set start line
    if (ssd1306->runCommand(ssd1306SetStartLine | 0x0) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -9;
    }

    /// set charge pump
    if (ssd1306->runCommand(ssd1306ChcargePump) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -10;
    }

    /// charge pump set to external vcc
    if (ssd1306->runCommand(0x14) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -11;
    }

    /// set memory addressing mode
    if (ssd1306->runCommand(ssd1306MemoryMode) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -12;
    }

    /// memory mode set to 0x00
    if (ssd1306->runCommand(0x00) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -13;
    }

    /// set Seg Re Map
    if (ssd1306->runCommand(ssd1306SegReMap) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -14;
    }

    /// set Com Scan to Dec (write from top to bottom)
    if (ssd1306->runCommand(ssd1306ComScanDec) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -15;
    }

    /// set Com Pins
    if (ssd1306->runCommand(Ssd1306SetComPins) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -16;
    }

    /// the com pins
    if (ssd1306->runCommand(0x12) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -17;
    }

    /// set contrast
    if (ssd1306->runCommand(Ssd1306SetContrast) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -18;
    }

    /// internal vcc, run contrast 0xCF
    if (ssd1306->runCommand(0xCF) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -19;
    }

    /// set precharge
    if (ssd1306->runCommand(Ssd1306SetPreCharge) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -20;
    }

    /// internal vcc, run precharge 0xF1
    if (ssd1306->runCommand(0xF1) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -21;
    }

    /// set vcomdetect
    if (ssd1306->runCommand(Ssd1306SetVComDetect) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -22;
    }

    /// vcom detect
    if (ssd1306->runCommand(0x40) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -23;
    }

    /// set display on-resume
    if (ssd1306->runCommand(Ssd1306DisplayAllOnResume) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -24;
    }

#if 1
    /// set normal display
    if (ssd1306->runCommand(Ssd1306NormalDisplay) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -25;
    }
#else
    if (ssd1306->runCommand(Ssd1306InvertDisplay) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -26;
    }
#endif

    /// set normal display
    if (ssd1306->runCommand(Ssd1306DisplayOn) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
        return -27;
    }

    /// clear display
    if (ssd1306->clearDisplay() < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " clearDisplay failed" << std::endl;
        return -28;
    }

    return 0;
}


/// write image (1024 bytes) to display
int writeImage(SSD1306* ssd1306, unsigned char image[1024])
{
    /// write image (1024 bytes) to display
    if (ssd1306->writeImage(image) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " writeImage failed" << std::endl;
        return -1;
    }

    return 0;
}


int writeByteTest(SSD1306 *ssd1306)
{
    /// for all 8 lines on display
    for (int line = 0; line < 8; line++) {

        /// 128 pixels across - each line is 8 byte hi
        for (int position = 0; position < 128; position++) {

            //std::cout << "line " << line << " position " << position << std::endl;

            /// write byte
            if (ssd1306->writeByte(line, position, 0xff) < 0) {
                std::cerr << __func__ << ":" << __LINE__ << " writeByte failed" << std::endl;
                return -1;
            }

            usleep(1000);
        } /// position
    } /// line

    ssd1306->clearDisplay();
}

/// create time and date string
int timeDateString(unsigned char *buffer)
{
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime (&rawtime);

    memset(buffer, 0, 26);
    int size = snprintf((char*)buffer, 25, "%s", asctime (timeinfo));
    if (size < 0 || size > 25) {
        std::cerr << __func__ << ":" << __LINE__ << "snprintf failed (" << size << ")" << std::endl;
        return -1;
    }

    return size;
}


/// create network strings and write them to the display
int networkPage(SSD1306 *ssd1306)
{
    unsigned char buffer[26];
    struct ifaddrs *ifaddr, *ifa;
    char host[NI_MAXHOST];
    int size = 0;

    /// prepare buffer for write
    memset(buffer, 0, 26);
    size = snprintf((char*)buffer, 25, "N E T W O R K ");
    if (size < 0 || size > 25) {
        std::cerr << __func__ << ":" << __LINE__ << "snprintf failed (" << size << ")" << std::endl;
        return -1;
    }

    /// write buffer to display
    if (ssd1306->writeLine(0, buffer) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << "writeLine failed" << std::endl;
        return -2;
    }

    /// get addresses
    if (getifaddrs(&ifaddr) == -1) {
        std::cerr << __func__ << ":" << __LINE__ << "getifaddrs failed" << std::endl;
        return -3;
    }

    int line = 4;

    /// loop over ifa list of devices and get hold of interfaces which is up
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        int family = ifa->ifa_addr->sa_family;

        /// Only INET interfaces
        if (family == AF_INET) {
            int s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0) {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                return -4;
            }

            //std::cout << "Interface " << ifa->ifa_name << " address " << host << std::endl;

            /// prepare buffer for write
            memset(buffer, 0, 26);
            size = snprintf((char*)buffer, 25, "%s %s", ifa->ifa_name, host);
            if (size > 25) {
                std::cerr << __func__ << ":" << __LINE__ << "snprintf failed (" << size << ")" << std::endl;
                return -5;
            }

            /// write buffer to display
            if (ssd1306->writeLine(line++, buffer) < 0) {
                std::cerr << __func__ << ":" << __LINE__ << "writeLine failed" << std::endl;
                return -6;
            }
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    std::cout << "ex_ssd1306" << std::endl;

    /// SSD device
    SSD1306 ssd1306((char*)FirmwareI2CDeviceses::i2c_1);

    /// set i2c address
    if (ssd1306.setAddress(SSD1306Addresses::SSD1306Address1) < 0)
        return 0;

    /// open ssd 1306
    if (ssd1306.openDevice() < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " openDevice failed" << std::endl;
        return 0;
    }

    /// initialize display
    if (initDisplay(&ssd1306) < 0) {
        std::cerr << __func__ << ":" << __LINE__ << " initDisplay failed" << std::endl;
        return 0;
    }

    while (true) {
        int size = 0;
        unsigned char buffer[26];

        /// deactivate scroll
        if (ssd1306.runCommand(Ssd1306DeactivateScroll) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << " deactivate scroll failed" << std::endl;
            return 0;
        }

        /// populate buffer with first part of upper case letters
        memset(buffer, 0, 26);
        size = snprintf((char*)buffer, 25, "A B C D E F G H I J K L M");
        if (size < 0 || size != 25) {
            std::cerr << __func__ << ":" << __LINE__ << "snprintf failed (" << size << ")" << std::endl;
            return -1;
        }

        /// write first part of upper case letters to display
        if (ssd1306.writeLine(0, buffer) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << "writeLine failed" << std::endl;
            return -2;
        }

        /// populate buffer with last part of upper case letters
        memset(buffer, 0, 26);
        size = snprintf((char*)buffer, 25, "N O P Q R S T U V W X Y Z");
        if (size < 0 || size != 25) {
            std::cerr << __func__ << ":" << __LINE__ << "snprintf failed (" << size << ")" << std::endl;
            return -1;
        }

        /// write last part of upper case letters
        if (ssd1306.writeLine(1, buffer) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << "writeLine failed" << std::endl;
            return -1;
        }

        /// populate buffer with numbers
        memset(buffer, 0, 26);
        size = snprintf((char*)buffer, 25, "0 1 2 3 4 5 6 7 8 9 _ -  ");
        if (size < 0 || size != 25) {
            std::cerr << __func__ << ":" << __LINE__ << "snprintf failed (" << size << ")" << std::endl;
            return -1;
        }

        /// write numbers to display
        if (ssd1306.writeLine(2, buffer) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << "writeLine failed" << std::endl;
            return -1;
        }


        /// populate buffer with first part of lower case letters
        memset(buffer, 0, 26);
        size = snprintf((char*)buffer, 25, "a b c d e f g h i j k l m");
        if (size < 0 || size != 25) {
            std::cerr << __func__ << ":" << __LINE__ << "snprintf failed (" << size << ")" << std::endl;
            return -1;
        }

        /// write first part of lower case letters
        if (ssd1306.writeLine(4, buffer) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << "writeLine failed" << std::endl;
            return -1;
        }

        /// populate buffer with last part of lower case letters
        memset(buffer, 0, 26);
        size = snprintf((char*)buffer, 25, "n o p q r s t u v w x y z");
        if (size < 0 || size != 25) {
            std::cerr << __func__ << ":" << __LINE__ << "snprintf failed (" << size << ")" << std::endl;
            return -1;
        }

        /// write last part of lower case letters
        if (ssd1306.writeLine(5, buffer) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << "writeLine failed" << std::endl;
            return -1;
        }

        memset(buffer, 0, 26);
        size = snprintf((char*)buffer, 25, "Time and date at exec");
        if (size < 0 || size > 25) {
            std::cerr << __func__ << ":" << __LINE__ << "snprintf failed (" << size << ")" << std::endl;
            return -1;
        }

        if (ssd1306.writeLine(6, buffer) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << "writeLine failed" << std::endl;
            return -1;
        }

        /// get time and date string
        if (timeDateString(buffer) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << "timeDateString failed" << std::endl;
            return 0;
        }

        /// write time and date to display
        if (ssd1306.writeLine(7, buffer) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << "writeLine failed" << std::endl;
            return -1;
        }

        //Ssd1306LeftHorizontalScroll;
        //Ssd1306RightHorizontalScroll
        //Ssd1306VerticalAndLeftHorizontalScroll;
        //Ssd1306VerticalAndRightHorizontalScroll;
#if 0
        /// horizontal scroll
        if (ssd1306.setScroll(Ssd1306LeftHorizontalScroll, 0x05, 0x07, 0x00, 0x00) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << "horizontalScroll failed" << std::endl;
            return 0;
        }

        usleep(5000000);
        usleep(2000000);

        if (ssd1306.runCommand(Ssd1306DeactivateScroll) < 0) {
            std::cerr << "SSD1306::"  << __func__ << ":" << __LINE__ << " runCommand failed" << std::endl;
            return -2;
        }

        /// clear display
        if (ssd1306.clearDisplay() < 0) {
            std::cerr << __func__ << ":" << __LINE__ << " clearDisplay failed" << std::endl;
            return 0;
        }


        /// run byte test
        if (writeByteTest(&ssd1306) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << " writeLineTest failed with status " << status << std::endl;
            return 0;
        }
        ssd1306.clearDisplay()();
#endif

        /// write image (adruino) to display
        if (writeImage(&ssd1306, arduino) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << " writeImage failed" << std::endl;
            return 0;
        }

        usleep(1000000);

        /// clear display
        if (ssd1306.clearDisplay() < 0) {
            std::cerr << __func__ << ":" << __LINE__ << " clearDisplay failed" << std::endl;
            return 0;
        }

        /// show network information on display
        if (networkPage(&ssd1306) < 0) {
            std::cerr << __func__ << ":" << __LINE__ << " networkPage failed" << std::endl;
            return 0;
        }

        usleep(2000000);

        /// clear display
        if (ssd1306.clearDisplay() < 0) {
            std::cerr << __func__ << ":" << __LINE__ << " clearDisplay failed" << std::endl;
            return 0;
        }


    } /// end of while

    ssd1306.closeDevice();

    return 0;
}
