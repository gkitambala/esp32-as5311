/*
 * as5311.cpp
 *
 * Copyright (C) 2019 David Schmelter

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <https://gitlab.com/schmelly/DRO/blob/master/dro_arduino/> or
 * <http://www.gnu.org/licenses/>.
 */

#include "as5311.h"
#include "fixedpoint_math.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//#include <USBAPI.h>

AS5311::AS5311(gpio_num_t PIN_CSn, gpio_num_t PIN_CLK, gpio_num_t PIN_DO) {
    this->PIN_CSn = PIN_CSn;
    this->PIN_CLK = PIN_CLK;
    this->PIN_DO = PIN_DO;
    reset();
}

int32_t AS5311::calculateAbsPosition(int16_t newRawPosition) {

    int32_t absPosition = 0;

    if (newRawPosition >= 2048 && //
            this->rawPosition < 2048 && //
            abs(newRawPosition - this->rawPosition) >= 2048) {
        this->increments = this->increments - 1;
    } else if (newRawPosition < 2048 && //
            this->rawPosition >= 2048 && //
            abs(newRawPosition - this->rawPosition) >= 2048) {
        this->increments = this->increments + 1;
    }

    int32_t fixedNewRawPosition = int2Fixed(newRawPosition);
    int32_t fixedIncrements = int2Fixed(this->increments);

    // absPosition = (float) newRawPosition * 2.0f / 4096.0f
    //        + 2.0f * (float) this->increments;
    absPosition = //
            add32( //
                    div32( //
                            mul32(fixedNewRawPosition, this->C2), //
                            this->C4096), //
                    mul32(this->C2, fixedIncrements));

    this->rawPosition = newRawPosition;

    return absPosition;
}

int32_t AS5311::getPosition() {

    return this->position;
}

void AS5311::readPositionFromChip() {

    int16_t newRawPosition = readRawPosition();
    int32_t newAbsPosition = calculateAbsPosition(newRawPosition);

    // exponential moving average filter
    this->position = add32( //
            mul32(sf, newAbsPosition), //
            mul32(sfi, this->position));
}

int16_t AS5311::readRawPosition() {

    uint16_t word = 0;
    int16_t rawPosition = 0;
    int curBit = 0;

    // enable serial transfer for this chip
    gpio_set_level(this->PIN_CLK, 1);
    gpio_set_level(this->PIN_CSn, 0);

    for (int i = 0; i < 18; i++) {
        gpio_set_level(this->PIN_CLK, 0);
        gpio_set_level(this->PIN_CLK, 1);

        curBit = gpio_get_level(this->PIN_DO);
        word = (word << 1) | curBit;

        switch (i) {
        case 11:
            rawPosition = word;
            break;
        case 12:
            this->ocf = curBit > 0 ? true : false;
            break;
        case 13:
            this->cof = curBit > 0 ? true : false;
            break;
        case 14:
            this->lin = curBit > 0 ? true : false;
            break;
        case 15:
            this->mag_inc = curBit > 0 ? true : false;
            break;
        case 16:
            this->mag_dec = curBit > 0 ? true : false;
            break;
        default:
            break;
        }
    }

    // disable serial transfer for this chip
    gpio_set_level(this->PIN_CSn, 1);

    return rawPosition;
}

void AS5311::reset() {
    this->position = 0;
    this->increments = 0;
    this->rawPosition = 0;

    this->ocf = false;
    this->cof = true;
    this->lin = true;
    this->mag_inc = true;
    this->mag_dec = true;

    setup();
}

void AS5311::setup() {
    gpio_set_direction(this->PIN_CSn, GPIO_MODE_OUTPUT);
    gpio_set_direction(this->PIN_CLK, GPIO_MODE_OUTPUT);
    gpio_set_direction(this->PIN_DO, GPIO_MODE_INPUT);
}