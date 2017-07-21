#version 300 es
#extension GL_OVR_multiview2 : enable

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

layout(num_views = 4) in;

in vec3 position;
in vec3 normal;
uniform mat4 projection[4];
uniform mat4 view[4];
uniform mat4 model;
out float v_depth;
out vec3 v_position;
out vec3 v_normal;

void main()
{
    vec4 view_pos = view[gl_ViewID_OVR] * model * vec4(position, 1.0);
    gl_Position = projection[gl_ViewID_OVR] * view_pos;
    v_normal = (view[gl_ViewID_OVR] * model * vec4(normal, 0.0)).xyz;
    v_depth = -view_pos.z;
    v_position = position;
}
