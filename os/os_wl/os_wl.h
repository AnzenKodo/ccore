#ifndef OS_WL_H
#define OS_WL_H

// Types
//======

enum Os_EventType
{
  Os_EventType_Null,
  Os_EventType_Press,
  Os_EventType_Release,
  Os_EventType_MouseMove,
  Os_EventType_Text,
  Os_EventType_Scroll,
  Os_EventType_WindowLoseFocus,
  Os_EventType_WindowClose,
  Os_EventType_WindowResize,
  Os_EventType_FileDrop,
  Os_EventType_Wakeup,
  Os_EventType_COUNT
};
typedef enum Os_EventType Os_EventType;

enum Os_ModKey
{
    Os_ModKey_Ctrl  = (1<<0),
    Os_ModKey_Shift = (1<<1),
    Os_ModKey_Alt   = (1<<2),
};
typedef enum Os_ModKey Os_ModKey;

enum Os_Key
{
    Os_Key_Null,
    Os_Key_Esc,
    Os_Key_F1,
    Os_Key_F2,
    Os_Key_F3,
    Os_Key_F4,
    Os_Key_F5,
    Os_Key_F6,
    Os_Key_F7,
    Os_Key_F8,
    Os_Key_F9,
    Os_Key_F10,
    Os_Key_F11,
    Os_Key_F12,
    Os_Key_F13,
    Os_Key_F14,
    Os_Key_F15,
    Os_Key_F16,
    Os_Key_F17,
    Os_Key_F18,
    Os_Key_F19,
    Os_Key_F20,
    Os_Key_F21,
    Os_Key_F22,
    Os_Key_F23,
    Os_Key_F24,
    Os_Key_Tick,
    Os_Key_0,
    Os_Key_1,
    Os_Key_2,
    Os_Key_3,
    Os_Key_4,
    Os_Key_5,
    Os_Key_6,
    Os_Key_7,
    Os_Key_8,
    Os_Key_9,
    Os_Key_Minus,
    Os_Key_Equal,
    Os_Key_Backspace,
    Os_Key_Tab,
    Os_Key_Q,
    Os_Key_W,
    Os_Key_E,
    Os_Key_R,
    Os_Key_T,
    Os_Key_Y,
    Os_Key_U,
    Os_Key_I,
    Os_Key_O,
    Os_Key_P,
    Os_Key_LeftBracket,
    Os_Key_RightBracket,
    Os_Key_BackSlash,
    Os_Key_CapsLock,
    Os_Key_A,
    Os_Key_S,
    Os_Key_D,
    Os_Key_F,
    Os_Key_G,
    Os_Key_H,
    Os_Key_J,
    Os_Key_K,
    Os_Key_L,
    Os_Key_Semicolon,
    Os_Key_Quote,
    Os_Key_Return,
    Os_Key_Shift,
    Os_Key_Z,
    Os_Key_X,
    Os_Key_C,
    Os_Key_V,
    Os_Key_B,
    Os_Key_N,
    Os_Key_M,
    Os_Key_Comma,
    Os_Key_Period,
    Os_Key_Slash,
    Os_Key_Ctrl,
    Os_Key_Alt,
    Os_Key_Space,
    Os_Key_Menu,
    Os_Key_ScrollLock,
    Os_Key_Pause,
    Os_Key_Insert,
    Os_Key_Home,
    Os_Key_PageUp,
    Os_Key_Delete,
    Os_Key_End,
    Os_Key_PageDown,
    Os_Key_Up,
    Os_Key_Left,
    Os_Key_Down,
    Os_Key_Right,
    Os_Key_Ex0,
    Os_Key_Ex1,
    Os_Key_Ex2,
    Os_Key_Ex3,
    Os_Key_Ex4,
    Os_Key_Ex5,
    Os_Key_Ex6,
    Os_Key_Ex7,
    Os_Key_Ex8,
    Os_Key_Ex9,
    Os_Key_Ex10,
    Os_Key_Ex11,
    Os_Key_Ex12,
    Os_Key_Ex13,
    Os_Key_Ex14,
    Os_Key_Ex15,
    Os_Key_Ex16,
    Os_Key_Ex17,
    Os_Key_Ex18,
    Os_Key_Ex19,
    Os_Key_Ex20,
    Os_Key_Ex21,
    Os_Key_Ex22,
    Os_Key_Ex23,
    Os_Key_Ex24,
    Os_Key_Ex25,
    Os_Key_Ex26,
    Os_Key_Ex27,
    Os_Key_Ex28,
    Os_Key_Ex29,
    Os_Key_NumLock,
    Os_Key_NumSlash,
    Os_Key_NumStar,
    Os_Key_NumMinus,
    Os_Key_NumPlus,
    Os_Key_NumPeriod,
    Os_Key_Num0,
    Os_Key_Num1,
    Os_Key_Num2,
    Os_Key_Num3,
    Os_Key_Num4,
    Os_Key_Num5,
    Os_Key_Num6,
    Os_Key_Num7,
    Os_Key_Num8,
    Os_Key_Num9,
    Os_Key_LeftMouseButton,
    Os_Key_MiddleMouseButton,
    Os_Key_RightMouseButton,
    Os_Key_COUNT,
};
typedef enum Os_Key Os_Key;

struct Os_Event {
    Os_ModKey mod_key;
    Os_Key key;
    Vec2F32 pos;
    Os_EventType type;
    Vec2F32 win_size;
};
typedef struct Os_Event Os_Event;

struct Os_Wl_Handle {
    Arena *arena;
    Os_Event event;
    Bool win_close_status;
};
typedef struct Os_Wl_Handle Os_Wl_Handle;

// Function Define
//================

fn Os_Wl_Handle *os_window_open(Str8 title, Vec2F32 resolution);
fn void os_window_close(Os_Wl_Handle *os_handle);

fn void os_begin_draw(Os_Wl_Handle *os_handle);

//// Window close functions
////=======================

fn void os_set_window_close(Os_Wl_Handle *os_handle);
fn Bool os_should_window_close(Os_Wl_Handle *os_handle);

//// Event functions
////================

fn Os_Event os_event_get(void);
fn Bool os_is_key_pressed(Os_Wl_Handle *os_handle, Os_Key key);

// Include file based on OS
//=========================

#if OS_LINUX
#   include "ccore/os/os_wl/os_wl_linux.h"
#else
#   error OS window layer not implemented for this operating system.
#endif


#endif // OS_WL_H
