#ifndef WINDOW_LAYER_CORE_H
#define WINDOW_LAYER_CORE_H

// Types
//=============================================================================

typedef enum Wl_EventType Wl_EventType;
enum Wl_EventType
{
    Wl_EventType_Null,
    Wl_EventType_Press,
    Wl_EventType_Release,
    Wl_EventType_MouseMove,
    Wl_EventType_Text,
    Wl_EventType_Scroll,
    Wl_EventType_WindowLoseFocus,
    Wl_EventType_WindowClose,
    Wl_EventType_WindowResize,
    Wl_EventType_FileDrop,
    Wl_EventType_Wakeup,
    Wl_EventType_COUNT
};

typedef enum Wl_ModKey Wl_ModKey;
enum Wl_ModKey
{
    Wl_ModKey_Ctrl  = (1<<0),
    Wl_ModKey_Shift = (1<<1),
    Wl_ModKey_Alt   = (1<<2),
    Wl_ModKey_Super = (1<<3),
};

typedef enum Wl_Key Wl_Key;
enum Wl_Key
{
    Wl_Key_Null,
    Wl_Key_Esc,
    Wl_Key_F1,
    Wl_Key_F2,
    Wl_Key_F3,
    Wl_Key_F4,
    Wl_Key_F5,
    Wl_Key_F6,
    Wl_Key_F7,
    Wl_Key_F8,
    Wl_Key_F9,
    Wl_Key_F10,
    Wl_Key_F11,
    Wl_Key_F12,
    Wl_Key_F13,
    Wl_Key_F14,
    Wl_Key_F15,
    Wl_Key_F16,
    Wl_Key_F17,
    Wl_Key_F18,
    Wl_Key_F19,
    Wl_Key_F20,
    Wl_Key_F21,
    Wl_Key_F22,
    Wl_Key_F23,
    Wl_Key_F24,
    Wl_Key_Tick,
    Wl_Key_0,
    Wl_Key_1,
    Wl_Key_2,
    Wl_Key_3,
    Wl_Key_4,
    Wl_Key_5,
    Wl_Key_6,
    Wl_Key_7,
    Wl_Key_8,
    Wl_Key_9,
    Wl_Key_Minus,
    Wl_Key_Equal,
    Wl_Key_Backspace,
    Wl_Key_Tab,
    Wl_Key_Q,
    Wl_Key_W,
    Wl_Key_E,
    Wl_Key_R,
    Wl_Key_T,
    Wl_Key_Y,
    Wl_Key_U,
    Wl_Key_I,
    Wl_Key_O,
    Wl_Key_P,
    Wl_Key_LeftBracket,
    Wl_Key_RightBracket,
    Wl_Key_BackSlash,
    Wl_Key_CapsLock,
    Wl_Key_A,
    Wl_Key_S,
    Wl_Key_D,
    Wl_Key_F,
    Wl_Key_G,
    Wl_Key_H,
    Wl_Key_J,
    Wl_Key_K,
    Wl_Key_L,
    Wl_Key_Semicolon,
    Wl_Key_Quote,
    Wl_Key_Return,
    Wl_Key_ShiftLeft,
    Wl_Key_ShiftRight,
    Wl_Key_Z,
    Wl_Key_X,
    Wl_Key_C,
    Wl_Key_V,
    Wl_Key_B,
    Wl_Key_N,
    Wl_Key_M,
    Wl_Key_Comma,
    Wl_Key_Period,
    Wl_Key_Slash,
    Wl_Key_CtrlLeft,
    Wl_Key_CtrlRight,
    Wl_Key_AltLeft,
    Wl_Key_AltRight,
    Wl_Key_Space,
    Wl_Key_Menu,
    Wl_Key_SuperLeft,
    Wl_Key_SuperRight,
    Wl_Key_Print,
    Wl_Key_ScrollLock,
    Wl_Key_Pause,
    Wl_Key_Insert,
    Wl_Key_Home,
    Wl_Key_PageUp,
    Wl_Key_Delete,
    Wl_Key_End,
    Wl_Key_PageDown,
    Wl_Key_Up,
    Wl_Key_Left,
    Wl_Key_Down,
    Wl_Key_Right,
    Wl_Key_Ex0,
    Wl_Key_Ex1,
    Wl_Key_Ex2,
    Wl_Key_Ex3,
    Wl_Key_Ex4,
    Wl_Key_Ex5,
    Wl_Key_Ex6,
    Wl_Key_Ex7,
    Wl_Key_Ex8,
    Wl_Key_Ex9,
    Wl_Key_Ex10,
    Wl_Key_Ex11,
    Wl_Key_Ex12,
    Wl_Key_Ex13,
    Wl_Key_Ex14,
    Wl_Key_Ex15,
    Wl_Key_Ex16,
    Wl_Key_Ex17,
    Wl_Key_Ex18,
    Wl_Key_Ex19,
    Wl_Key_Ex20,
    Wl_Key_Ex21,
    Wl_Key_Ex22,
    Wl_Key_Ex23,
    Wl_Key_Ex24,
    Wl_Key_Ex25,
    Wl_Key_Ex26,
    Wl_Key_Ex27,
    Wl_Key_Ex28,
    Wl_Key_Ex29,
    Wl_Key_NumLock,
    Wl_Key_NumSlash,
    Wl_Key_NumStar,
    Wl_Key_NumMinus,
    Wl_Key_NumPlus,
    Wl_Key_NumPeriod,
    Wl_Key_NumReturn,
    Wl_Key_Num0,
    Wl_Key_Num1,
    Wl_Key_Num2,
    Wl_Key_Num3,
    Wl_Key_Num4,
    Wl_Key_Num5,
    Wl_Key_Num6,
    Wl_Key_Num7,
    Wl_Key_Num8,
    Wl_Key_Num9,
    Wl_Key_LeftMouseButton,
    Wl_Key_MiddleMouseButton,
    Wl_Key_RightMouseButton,
    Wl_Key_COUNT,
};


typedef struct Wl_Event Wl_Event;
struct Wl_Event {
    Wl_ModKey mod_key;
    Wl_Key key;
    Vec2F32 pos;
    Wl_EventType type;
};

typedef struct Wl_State Wl_State;
struct Wl_State {
    Wl_Event event;
    Vec2I32 win_size;
    Vec2I32 display_size;
    bool win_should_close;
    U64 frame_prev_time;
    U64 frame_count;
    U32 fps;
};

// Basic Window functions
//=============================================================================

internal void wl_window_open(Str8 title, Vec2I32 win_size);
internal void wl_window_close(void);

// Window Close Functions
//=============================================================================

internal void wl_set_window_close(void);
internal bool wl_should_window_close(void);

// Event Functions
//=============================================================================

internal void wl_update_events();
internal Wl_Event wl_get_event(void);
internal bool wl_is_key_pressed(Wl_Key key);

// Get Window Information
//=============================================================================

internal U32 wl_get_display_width(void);
internal U32 wl_get_display_height(void);
internal U32 wl_get_window_width(void);
internal U32 wl_get_window_height(void);

// Window Icon
//=============================================================================

internal void wl_window_icon_set(U32 *icon_data, U32 width, U32 height);

// Global Variables
//=============================================================================

global Wl_State wl_state = ZERO_STRUCT;

#endif // WINDOW_LAYER_CORE_H
