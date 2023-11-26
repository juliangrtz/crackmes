// includes
#include <sstream>
#include <iomanip>
#include "serial.h"

std::wstring getSerial(uint32_t year, uint32_t month, uint32_t day) {

	std::wstringstream stream;
	std::wstring serialString = L"";
	uint32_t daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeapYear(year)) {
		daysInMonth[1] = 29;
	}

	if ( year >= 11 && month >= 1 && month <= 12 && day >= 1 && day <= daysInMonth[month - 1] ) {
		year -= month;
		year += year;
		day += year;
		day *= year;
		day *= 1337;
		stream << std::uppercase << std::hex << std::setw(8) << std::setfill(L'0') << day;
		serialString = stream.str();
	} else {
		return L"Please enter a valid date!";
	}

	return serialString;
}

bool isLeapYear(uint32_t year) {
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		return true;
	} else {
		return false;
	}
}