#pragma once

// includes
#include <string>
#include <cstdint>

// prototypes
std::wstring getSerial(uint32_t year, uint32_t month, uint32_t day);
bool isLeapYear(uint32_t year);