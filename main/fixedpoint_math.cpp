/*
 * fixedpoint_math.cpp
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

#include "fixedpoint_math.h"

#include <USBAPI.h>

int32_t float2Fixed(float f) {

    int32_t result;

    float temp = f * (1 << Qf);
    temp += (temp >= 0) ? 0.5f : -0.5f;

    result = (int32_t) temp;
    return result;
}

int32_t int2Fixed(int16_t i) {
    int32_t result = (int32_t) i * (1 << Qf);
    return result;
}

float fixed2Float(int32_t fi) {

    float result = ((float) fi) * 1.0f / (float) (1 << Qf);
    return result;
}

int16_t fixed2int16(int32_t fi) {
    int16_t result = (int16_t) (fi >> Qf);
    return result;
}

int32_t add32(int32_t a, int32_t b) {

    int32_t result = a + b;
    return result;
}

int32_t sub32(int32_t a, int32_t b) {

    int32_t result = a - b;
    return result;
}

int32_t mul32(int32_t a, int32_t b) {

    int32_t result;

    int64_t temp = (int64_t) a * (int64_t) b;
    temp += K;

    result = (int32_t) (temp >> Qf);
    return result;
}

int32_t div32(int32_t a, int32_t b) {

    int32_t result;
    int64_t temp;

    // pre-multiply by the base (Upscale to Q64 so that the result will be in Q32 format)
    temp = (int64_t) a << Qf;

    // Rounding: mid values are rounded up (down for negative values).
    if ((temp >= 0 && b >= 0) || (temp < 0 && b < 0)) {
        temp += b / 2;
    } else {
        temp -= b / 2;
    }

    result = (int32_t) (temp / b);
    return result;
}
