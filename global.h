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
