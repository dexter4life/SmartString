/*
This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.

Author: Peter Nwanosike
Email:dexter4life@gmail.com
*/

#pragma once

#ifndef GLOBAL_DEF_H
#define GLOBAL_DEF_H
#include "compilerdefines.h"
#include "flags.h"

BEGIN_GLOBAL_NAMESPACE

enum KeyboardModifier {
	NoModifier = 0x00000000,
	ShiftModifier = 0x02000000,
	ControlModifier = 0x04000000,
	AltModifier = 0x08000000,
	GroupSwitchModifier = 0x40000000,//modify later
	// Do not extend the mask to include 0x01000000
	KeyboardModifierMask = 0xfe000000
};

CT_DECLARE_FLAGS(KeyboardModifiers, KeyboardModifier)

enum Modifier {
	SHIFT = Ct::ShiftModifier,
	CTRL = Ct::ControlModifier,
	ALT = Ct::AltModifier,
	MODIFIER_MASK = KeyboardModifierMask,
	UNICODE_ACCEL = 0x00000000
};

enum MouseButton {
	NoButton = 0x00000000,
	LeftButton = 0x00000001,
	RightButton = 0x00000002,
	BackButton = 0x00000008,
	AllButtons = 0x07ffffff,
};
CT_DECLARE_FLAGS(MouseButtons, MouseButton)

enum _CaseSensitivity {
	CaseInsensitive,
	CaseSensitive
};
CT_DECLARE_FLAGS(CaseSensitivity, _CaseSensitivity)


END_GLOBAL_NAMESPACE
#endif // !GLOBAL_DEF_H
