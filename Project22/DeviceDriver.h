#pragma once
#include "FlashMemoryDevice.h"
int ERASED_DATA = 0xFF;
class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};