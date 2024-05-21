#include "DeviceDriver.h"
#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));
    // TODO: implement this method properly
    for (int i = 1; i < 5; i++)
    {
        if (result != (int)(m_hardware->read(address)))
            throw std::exception("ReadFailException");
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    int written_data = (int)(m_hardware->read(address));
    if (written_data != ERASED_DATA)
        throw std::exception("WriteFailException");

    m_hardware->write(address, (unsigned char)data);
}