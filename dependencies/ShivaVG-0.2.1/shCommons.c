/*
 * Copyright (c) 2019 Vincenzo Pupillo
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library in the file COPYING;
 * if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "shCommons.h"

inline void
shDrawQuads(GLfloat v1x, GLfloat v1y, GLfloat v2x, GLfloat v2y, GLfloat v3x, GLfloat v3y, GLfloat v4x, GLfloat v4y)
{
      GLfloat corners[] = {v1x, v1y, v2x, v2y, v3x, v3y, v4x, v4y};
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(2, GL_FLOAT, 0, corners);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
      glDisableClientState(GL_VERTEX_ARRAY);
}

inline void
shDrawQuadsInt(GLint v1x, GLint v1y, GLint v2x, GLint v2y, GLint v3x, GLint v3y, GLint v4x, GLint v4y)
{
      GLint corners[] = {v1x, v1y, v2x, v2y, v3x, v3y, v4x, v4y};
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(2, GL_INT, 0, corners);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
      glDisableClientState(GL_VERTEX_ARRAY);
}

inline void
shDrawQuadsArray(GLfloat v[8])
{
      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(2, GL_FLOAT, 0, v);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
      glDisableClientState(GL_VERTEX_ARRAY);
}

inline void vgSetColor(VGPaint paint, VGuint rgba) {
  VGfloat rgba_f[4];
  rgba_f[0] = ((rgba >> 24) & 0xff)/255.0f;
  rgba_f[1] = ((rgba >> 16) & 0xff)/255.0f;
  rgba_f[2] = ((rgba >>  8) & 0xff)/255.0f;
  rgba_f[3] = ( rgba        & 0xff)/255.0f;
  vgSetParameterfv(paint, VG_PAINT_COLOR, 4, rgba_f);
}

#define CLAMP(x) ((x) < 0.0f ? 0.0f : ((x) > 1.0f ? 1.0f : (x)))
    
inline VGuint vgGetColor(VGPaint paint) {
  VGuint rgba;
  VGfloat rgba_f[4];
  int red, green, blue, alpha;
  vgGetParameterfv(paint, VG_PAINT_COLOR, 4, rgba_f);
  red   = (int)(CLAMP(rgba_f[0])*255.0f + 0.5f);
  green = (int)(CLAMP(rgba_f[1])*255.0f + 0.5f);
  blue  = (int)(CLAMP(rgba_f[2])*255.0f + 0.5f);
  alpha = (int)(CLAMP(rgba_f[3])*255.0f + 0.5f);
  rgba = (red << 24) | (green << 16) | (blue << 8) | alpha;
  return rgba;
}
