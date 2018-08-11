#pragma once
#ifndef GLOBAL_EVENT_H
#define GLOBAL_EVENT_H

#include "global.h"
#include "utilitydef.h"
#include <cstdint>
#include "compilerdefines.h"


class CEvent           // event base class
{
public:
	enum Type {
		/*
		Global event type affecting widget controls
		*/
		None = 0,                               // invalid event
		Timer = 1,                              // timer event
		MouseButtonPress = 2,                   // mouse button pressed
		MouseButtonRelease = 3,                 // mouse button released
		MouseButtonDblClick = 4,                // mouse button double click
		MouseMove = 5,                          // mouse move
		KeyPress = 6,                           // key pressed
		KeyRelease = 7,                         // key released
		FocusIn = 8,                            // keyboard focus received
		FocusOut = 9,                           // keyboard focus lost
		FocusAboutToChange = 23,                // keyboard focus is about to be lost
		Enter = 10,                             // mouse enters widget
		Leave = 11,                             // mouse leaves widget
		Paint = 12,                             // paint widget
		Move = 13,                              // move widget
		Resize = 14,                            // resize widget
		Create = 15,                            // after widget creation
		Destroy = 16,                           // during widget destruction
		Show = 17,                              // widget is shown
		Hide = 18,                              // widget is hidden
		Close = 19,                             // request to close widget
		Quit = 20,                              // request to quit application
		ParentChange = 21,                      // widget has been reparented
		ParentAboutToChange = 131,              // sent just before the parent change is done
		ThreadChange = 22,                      // object has changed threads
		WindowActivate = 24,                    // window was activated
		WindowDeactivate = 25,                  // window was deactivated
		ShowToParent = 26,                      // widget is shown to parent
		HideToParent = 27,                      // widget is hidden to parent
		Wheel = 31,                             // wheel event
		WindowTitleChange = 33,                 // window title changed
		WindowIconChange = 34,                  // icon changed
		ApplicationWindowIconChange = 35,       // application icon changed
		ApplicationFontChange = 36,             // application font changed
		ApplicationLayoutDirectionChange = 37,  // application layout direction changed
		ApplicationPaletteChange = 38,          // application palette changed
		PaletteChange = 39,                     // widget palette changed
		Clipboard = 40,                         // internal clipboard event
		Speech = 42,                            // reserved for speech input
		MetaCall = 43,                         // meta call event
		SockAct = 50,                           // socket activation
		WinEventAct = 132,                      // win event activation
		DeferredDelete = 52,                    // deferred delete event
		DragEnter = 60,                         // drag moves into widget
		DragMove = 61,                          // drag moves in widget
		DragLeave = 62,                         // drag leaves or is cancelled
		Drop = 63,                              // actual drop
		DragResponse = 64,                      // drag accepted/rejected
		ChildAdded = 68,                        // new child widget
		ChildPolished = 69,                     // polished child widget
		ChildRemoved = 71,                      // deleted child widget
		ShowWindowRequest = 73,                 // widget's window should be mapped
		PolishRequest = 74,                     // widget should be polished
		Polish = 75,                            // widget is polished
		LayoutRequest = 76,                     // widget should be relayouted
		UpdateRequest = 77,                     // widget should be repainted
		UpdateLater = 78,                       // request update() later

		EmbeddingControl = 79,                  // ActiveX embedding
		ActivateControl = 80,                   // ActiveX activation
		DeactivateControl = 81,                 // ActiveX deactivation
		ContextMenu = 82,                       // context popup menu
		InputMethod = 83,                       // input method
		TabletMove = 87,                        // Wacom tablet event
		LocaleChange = 88,                      // the system locale changed
		LanguageChange = 89,                    // the application language changed
		LayoutDirectionChange = 90,             // the layout direction changed
		Style = 91,                             // internal style event
		TabletPress = 92,                       // tablet press
		TabletRelease = 93,                     // tablet release
		OkRequest = 94,                         // CE (Ok) button pressed
		HelpRequest = 95,                       // CE (?)  button pressed

		IconDrag = 96,                          // proxy icon dragged

		FontChange = 97,                        // font has changed
		EnabledChange = 98,                     // enabled state has changed
		ActivationChange = 99,                  // window activation has changed
		StyleChange = 100,                      // style has changed
		IconTextChange = 101,                   // icon text has changed.  Deprecated.
		ModifiedChange = 102,                   // modified state has changed
		MouseTrackingChange = 109,              // mouse tracking state has changed

		WindowBlocked = 103,                    // window is about to be blocked modally
		WindowUnblocked = 104,                  // windows modal blocking has ended
		WindowStateChange = 105,

		ReadOnlyChange = 106,                   // readonly state has changed

		ToolTip = 110,
		WhatsThis = 111,
		StatusTip = 112,

		ActionChanged = 113,
		ActionAdded = 114,
		ActionRemoved = 115,

		FileOpen = 116,                         // file open request

		Shortcut = 117,                         // shortcut triggered
		ShortcutOverride = 51,                  // shortcut override request

		WhatsThisClicked = 118,

		ToolBarChange = 120,                    // toolbar visibility toggled

		QueryWhatsThis = 123,                   // query what's this widget help
		EnterWhatsThisMode = 124,
		LeaveWhatsThisMode = 125,

		ZOrderChange = 126,                     // child widget has had its z-order changed

		HoverEnter = 127,                       // mouse cursor enters a hover widget
		HoverLeave = 128,                       // mouse cursor leaves a hover widget
		HoverMove = 129,                        // mouse cursor move inside a hover widget
	};


	explicit CEvent(Type type);
	CEvent(const CEvent &other);
	virtual ~CEvent();
	CEvent &operator=(const CEvent &other);
	inline Type type() const { return static_cast<Type>(t); }
	inline bool spontaneous() const { return spont; }

	inline void setAccepted(bool accepted) { m_accept = accepted; }
	inline bool isAccepted() const { return m_accept; }

	inline void accept() { m_accept = true; }
	inline void ignore() { m_accept = false; }

protected:
	uint16_t t;

private:
	uint16_t posted : 1;
	uint16_t spont : 1;
	uint16_t m_accept : 1;
	uint16_t reserved : 13;
};


#endif // !GLOBAL_EVENT_H
