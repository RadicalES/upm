/*
 * Author: Yevgeniy Kiveisha <yevgeniy.kiveisha@intel.com>
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include <unistd.h>

#include "lcd.h"
#include "lcd_private.h"

using namespace upm;

LCD::LCD(int bus, int lcdAddress) : m_i2c_lcd_control(bus)
{
    m_lcd_control_address = lcdAddress;
    m_bus = bus;

    mraa_result_t ret = m_i2c_lcd_control.address(m_lcd_control_address);
    if (ret != MRAA_SUCCESS) {
        fprintf(stderr, "Messed up i2c bus\n");
    }
}

LCD::~LCD()
{
}

mraa_result_t
LCD::write(int row, int column, std::string msg)
{
    setCursor(row, column);
    return write(msg);
}

mraa_result_t
LCD::createChar(uint8_t charSlot, uint8_t charData[])
{
    mraa_result_t error = MRAA_SUCCESS;
    charSlot &= 0x07; // only have 8 positions we can set
    error = m_i2c_lcd_control.writeReg(LCD_CMD, LCD_SETCGRAMADDR | (charSlot << 3));
    if (error == MRAA_SUCCESS) {
        for (int i = 0; i < 8; i++) {
            error = m_i2c_lcd_control.writeReg(LCD_DATA, charData[i]);
        }
    }

    return error;
}

std::string
LCD::name()
{
    return m_name;
}