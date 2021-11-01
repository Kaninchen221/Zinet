#pragma once

#include <glad/glad.h>

using ZtEnum = GLenum;
using ZtInt = GLint;
using ZtChar = GLchar;
using ZtSize = GLsizei;
using ZtBool = GLboolean;
using ZtBitfield = GLbitfield;
using ZtByte = GLbyte;
using ZtShort = GLshort;
using ZtUByte = GLubyte;
using ZtUShort = GLushort;
using ZtUInt = GLuint;
using ZtFloat = GLfloat;
using ZtClampf = GLclampf;
using ZtDouble = GLdouble;
using ZtDoublef = GLclampd;
using ZtVoid = GLvoid;
using ZtFixed = GLfixed;
using ZtInt64 = GLint64;
using ZtUInt64 = GLuint64;

using ZtTrueType = decltype(GL_TRUE);
using ZtFalseType = decltype(GL_FALSE);

#define ZtTrue GL_TRUE
#define ZtFalse GL_FALSE