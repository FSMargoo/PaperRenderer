/*
 * Copyright (c) 2023~Now Margoo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * \file vMessage.cpp
 * \brief The message type in the VUILib
 */

#include <include/base/message/vMessage.h>

VBaseMessage::VBaseMessage(Window Trigger) : Target(Trigger) {

}
VMouseMoveMessage::VMouseMoveMessage(Window Trigger, const int &IX, const int &IY)
    : VBaseMessage(Trigger), X(IX), Y(IY) {

}
VMouseClickMessage::VMouseClickMessage(Window Trigger, const int &IX, const int &IY, const VMouseButton &IButton, const VClickType &IClick)
    : VBaseMessage(Trigger), X(IX), Y(IY), Button(IButton), Click(IClick) {

}
VRepaintMessage::VRepaintMessage(Window Trigger, const VRect &Rectangle) : VBaseMessage(Trigger), DirtyRectangle(Rectangle) {

}