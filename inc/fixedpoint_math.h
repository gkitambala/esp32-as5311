/*
 * fixedpoint_math.h
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

#ifndef FIXEDPOINT_MATH_H_
#define FIXEDPOINT_MATH_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Qf 12
#define K (1 << (Qf - 1))
#define K_MASK 0xfff

int32_t float2Fixed(float f);
int32_t int2Fixed(int16_t i);
float fixed2Float(int32_t fi);
int16_t fixed2int16(int32_t fi);

int32_t add32(int32_t a, int32_t b);
int32_t sub32(int32_t a, int32_t b);
int32_t mul32(int32_t a, int32_t b);
int32_t div32(int32_t a, int32_t b);

#ifdef __cplusplus
}
#endif

#endif /* FIXEDPOINT_MATH_H_ */
