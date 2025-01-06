#ifndef GFX_H
#define GFX_H

// Types
//======

typedef enum Gfx_EventType Gfx_EventType;
enum Gfx_EventType
{
  Gfx_EventType_Null,
  Gfx_EventType_Press,
  Gfx_EventType_Release,
  Gfx_EventType_MouseMove,
  Gfx_EventType_Text,
  Gfx_EventType_Scroll,
  Gfx_EventType_WindowLoseFocus,
  Gfx_EventType_WindowClose,
  Gfx_EventType_WindowResize,
  Gfx_EventType_FileDrop,
  Gfx_EventType_Wakeup,
  Gfx_EventType_COUNT
};

typedef enum Gfx_ModKey Gfx_ModKey;
enum Gfx_ModKey
{
    Gfx_ModKey_Ctrl  = (1<<0),
    Gfx_ModKey_Shift = (1<<1),
    Gfx_ModKey_Alt   = (1<<2),
};

typedef enum Gfx_Key Gfx_Key;
enum Gfx_Key
{
    Gfx_Key_Null,
    Gfx_Key_Esc,
    Gfx_Key_F1,
    Gfx_Key_F2,
    Gfx_Key_F3,
    Gfx_Key_F4,
    Gfx_Key_F5,
    Gfx_Key_F6,
    Gfx_Key_F7,
    Gfx_Key_F8,
    Gfx_Key_F9,
    Gfx_Key_F10,
    Gfx_Key_F11,
    Gfx_Key_F12,
    Gfx_Key_F13,
    Gfx_Key_F14,
    Gfx_Key_F15,
    Gfx_Key_F16,
    Gfx_Key_F17,
    Gfx_Key_F18,
    Gfx_Key_F19,
    Gfx_Key_F20,
    Gfx_Key_F21,
    Gfx_Key_F22,
    Gfx_Key_F23,
    Gfx_Key_F24,
    Gfx_Key_Tick,
    Gfx_Key_0,
    Gfx_Key_1,
    Gfx_Key_2,
    Gfx_Key_3,
    Gfx_Key_4,
    Gfx_Key_5,
    Gfx_Key_6,
    Gfx_Key_7,
    Gfx_Key_8,
    Gfx_Key_9,
    Gfx_Key_Minus,
    Gfx_Key_Equal,
    Gfx_Key_Backspace,
    Gfx_Key_Tab,
    Gfx_Key_Q,
    Gfx_Key_W,
    Gfx_Key_E,
    Gfx_Key_R,
    Gfx_Key_T,
    Gfx_Key_Y,
    Gfx_Key_U,
    Gfx_Key_I,
    Gfx_Key_O,
    Gfx_Key_P,
    Gfx_Key_LeftBracket,
    Gfx_Key_RightBracket,
    Gfx_Key_BackSlash,
    Gfx_Key_CapsLock,
    Gfx_Key_A,
    Gfx_Key_S,
    Gfx_Key_D,
    Gfx_Key_F,
    Gfx_Key_G,
    Gfx_Key_H,
    Gfx_Key_J,
    Gfx_Key_K,
    Gfx_Key_L,
    Gfx_Key_Semicolon,
    Gfx_Key_Quote,
    Gfx_Key_Return,
    Gfx_Key_Shift,
    Gfx_Key_Z,
    Gfx_Key_X,
    Gfx_Key_C,
    Gfx_Key_V,
    Gfx_Key_B,
    Gfx_Key_N,
    Gfx_Key_M,
    Gfx_Key_Comma,
    Gfx_Key_Period,
    Gfx_Key_Slash,
    Gfx_Key_Ctrl,
    Gfx_Key_Alt,
    Gfx_Key_Space,
    Gfx_Key_Menu,
    Gfx_Key_ScrollLock,
    Gfx_Key_Pause,
    Gfx_Key_Insert,
    Gfx_Key_Home,
    Gfx_Key_PageUp,
    Gfx_Key_Delete,
    Gfx_Key_End,
    Gfx_Key_PageDown,
    Gfx_Key_Up,
    Gfx_Key_Left,
    Gfx_Key_Down,
    Gfx_Key_Right,
    Gfx_Key_Ex0,
    Gfx_Key_Ex1,
    Gfx_Key_Ex2,
    Gfx_Key_Ex3,
    Gfx_Key_Ex4,
    Gfx_Key_Ex5,
    Gfx_Key_Ex6,
    Gfx_Key_Ex7,
    Gfx_Key_Ex8,
    Gfx_Key_Ex9,
    Gfx_Key_Ex10,
    Gfx_Key_Ex11,
    Gfx_Key_Ex12,
    Gfx_Key_Ex13,
    Gfx_Key_Ex14,
    Gfx_Key_Ex15,
    Gfx_Key_Ex16,
    Gfx_Key_Ex17,
    Gfx_Key_Ex18,
    Gfx_Key_Ex19,
    Gfx_Key_Ex20,
    Gfx_Key_Ex21,
    Gfx_Key_Ex22,
    Gfx_Key_Ex23,
    Gfx_Key_Ex24,
    Gfx_Key_Ex25,
    Gfx_Key_Ex26,
    Gfx_Key_Ex27,
    Gfx_Key_Ex28,
    Gfx_Key_Ex29,
    Gfx_Key_NumLock,
    Gfx_Key_NumSlash,
    Gfx_Key_NumStar,
    Gfx_Key_NumMinus,
    Gfx_Key_NumPlus,
    Gfx_Key_NumPeriod,
    Gfx_Key_Num0,
    Gfx_Key_Num1,
    Gfx_Key_Num2,
    Gfx_Key_Num3,
    Gfx_Key_Num4,
    Gfx_Key_Num5,
    Gfx_Key_Num6,
    Gfx_Key_Num7,
    Gfx_Key_Num8,
    Gfx_Key_Num9,
    Gfx_Key_LeftMouseButton,
    Gfx_Key_MiddleMouseButton,
    Gfx_Key_RightMouseButton,
    Gfx_Key_COUNT,
};

typedef struct Gfx_Event Gfx_Event;
struct Gfx_Event {
    Gfx_ModKey mod_key;
    Gfx_Key key;
    Vec2F32 pos;
    Gfx_EventType type;
    Vec2F32 win_size;
};

typedef struct Gfx_Os_Handle Gfx_Os_Handle;
struct Gfx_Os_Handle
{
  U64 u64[1];
};

typedef struct Gfx_Handle Gfx_Handle;
struct Gfx_Handle {
    Arena *arena;
    Gfx_Event event;
    Gfx_Os_Handle os_handle;
    Bool win_close_status;
};

// Function Define
//================

fn Gfx_Handle *gfx_win_open(Str8 title, Vec2F32 resolution);
fn void gfx_win_close(Gfx_Handle *gfx_handle);

fn void gfx_begin_draw(Gfx_Handle *gfx_handle);

//// Window close functions
////=======================

fn void gfx_set_win_close(Gfx_Handle *gfx_handle);
fn Bool gfx_should_win_close(Gfx_Handle *gfx_handle);

//// Event functions
////================

fn Gfx_Event gfx_event_get(Gfx_Handle *gfx_handle);
fn Bool gfx_is_key_pressed(Gfx_Handle *gfx_handle, Gfx_Key key);

// Include file based on OS
//=========================

#if OS_LINUX
#   include "core/gfx/gfx_linux.h"
#else
#   error OS core layer not implemented for this operating system.
#endif

#endif // GFX_H
