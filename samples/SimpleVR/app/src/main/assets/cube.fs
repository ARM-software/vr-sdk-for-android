#version 300 es

/* Copyright (c) 2015-2017, ARM Limited and Contributors
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

precision highp float;

in vec3 v_position;
in vec3 v_normal;
in float v_depth;
out vec4 f_color;

vec3 light(vec3 n, vec3 l, vec3 c)
{
    float ndotl = max(dot(n, l), 0.0);
    return ndotl * c;
}

void main()
{
    vec3 n = normalize(v_normal);
    f_color.rgb = vec3(0.0);
    f_color.rgb += light(n, normalize(vec3(1.0)), vec3(1.0));
    f_color.rgb += light(n, normalize(vec3(-1.0, -1.0, 0.0)), vec3(0.2, 0.23, 0.35));

    // Fog
    f_color.rgb *= 1.0 - smoothstep(0.9, 10.0, v_depth);

    // Gamma
    f_color.rgb = sqrt(f_color.rgb);

    f_color.a = 1.0;
}
