/*
 * as5311.h
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

#ifndef AS5311_H_
#define AS5311_H_

#include <stdint.h>

#include "fixedpoint_math.h"

class AS5311 {
public:
    AS5311(uint8_t PIN_CS, uint8_t PIN_CLK, uint8_t PIN_DO);
    int32_t getPosition();
    void readPositionFromChip();
    void reset();
    void setup();
    int16_t readRawPosition();
    int32_t calculateAbsPosition(int16_t newRawPosition);
private:
    uint8_t PIN_CSn;
    uint8_t PIN_CLK;
    uint8_t PIN_DO;

    int32_t position;
    int16_t increments;
    int16_t rawPosition;

    bool ocf;
    bool cof;
    bool lin;
    bool mag_inc;
    bool mag_dec;

    const int32_t C2 = float2Fixed(2.f);
    const int32_t C4096 = float2Fixed(4096.f);

    const float smoothingFactor = 0.5f;
    const int32_t sf = float2Fixed(smoothingFactor);
    const int32_t sfi = float2Fixed(1 - smoothingFactor);

    
    
};

#endif /* AS5311_H_ */