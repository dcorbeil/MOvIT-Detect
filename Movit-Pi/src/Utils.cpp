#include "Utils.h"
#include <stdio.h>
#include <thread>

uint8_t DECToBCD(const uint8_t &value)
{
    uint8_t ones = value % 10;
    uint8_t tens = (value / 10) << 4;

    return tens | ones;
}

uint8_t BCDToDEC(const uint8_t &value)
{
    return ((value & TENS_MASK) >> 4) * 10 + (value & ONES_MASK);
}

uint8_t BCDAdd(const uint8_t &BCDlvalue, const uint8_t &DECrvalue)
{
    uint8_t dec = BCDToDEC(BCDlvalue) + DECrvalue;

    return DECToBCD(dec);
}

uint8_t BCDSubstract(const uint8_t &BCDlvalue, const uint8_t &DECrvalue)
{
    if (DECrvalue >= BCDToDEC(BCDlvalue))
    {
        return 0;
    }

    uint8_t dec = BCDToDEC(BCDlvalue) - DECrvalue;

    return DECToBCD(dec);
}

void sleep_for_microseconds(uint32_t microseconds)
{
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}

void sleep_for_milliseconds(uint32_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
