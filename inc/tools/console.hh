#pragma once

#define BEL '\x07'
#define BS '\x08'
#define HT '\x09'
#define LF '\x0a'
#define VT '\x0b'
#define FF '\x0c'
#define SO '\x0e'
#define SI '\x0f'
#define CAN '\x18'
#define SUB '\x1a'
#define ESC '\x1b'
#define DEL '\x7f'

#define RIS "\x1b\x63"
#define IND "\x1b\x44"
#define NEL "\x1b\x45"
#define HTS "\x1b\x48"
#define RI "\x1b\x4d"
#define DECID "\x1b\x5a"
#define DECSD "\x1b\x37"
#define DECRD "\x1b\x38"
#define CSI "\x1b\x5b"
#define DECALN "\x1b\x23\x38"
#define DECPNM "\x1b\x3e"
#define DECPAM "\x1b\x3d"

#define SGR_RESET_ALL "\x1b\x5b\x30\x6d"
#define SGR_BOLD "\x1b\x5b\x31\x6d"
#define SGR_HALF_BRIGHT "\x1b\x5b\x32\x6d"
#define SGR_UNDERSCORE "\x1b\x5b\x34\x6d"
#define SGR_BLINK_ON "\x1b\x5b\x35\x6d"
#define SGR_REVERSE_VIDEO_ON "\x1b\x5b\x37\x6d"
#define SGR_RESET_SELECTED "\x1b\x5b\x31\x30\x6d"
#define SGR_UNDERLINE_ON "\x1b\x5b\x32\x31\x6d"
#define SGR_NORMAL_INTENSITY "\x1b\x5b\x32\x32\x6d"
#define SGR_UNDERLINE_OFF "\x1b\x5b\x32\x34\x6d"
#define SGR_BLINK_OFF "\x1b\x5b\x32\x35\x6d"
#define SGR_REVERSE_VIDEO_OFF "\x1b\x5b\x32\x37\x6d"
#define SGR_BLACK_FOREGROUND "\x1b\x5b\x33\x30\x6d"
#define SGR_RED_FOREGROUND "\x1b\x5b\x33\x31\x6d"
#define SGR_GREEN_FOREGROUND "\x1b\x5b\x33\x32\x6d"
#define SGR_BROWN_FOREGROUND "\x1b\x5b\x33\x33\x6d"
#define SGR_BLUE_FOREGROUND "\x1b\x5b\x33\x34\x6d"
#define SGR_MAGENTA_FOREGROUND "\x1b\x5b\x33\x35\x6d"
#define SGR_CYAN_FOREGROUND "\x1b\x5b\x33\x36\x6d"
#define SGR_WHITE_FOREGROUND "\x1b\x5b\x33\x37\x6d"
#define SGR_BLACK_BACKGROUND "\x1b\x5b\x34\x30\x6d"
#define SGR_RED_BACKGROUND "\x1b\x5b\x34\x31\x6d"
#define SGR_GREEN_BACKGROUND "\x1b\x5b\x34\x32\x6d"
#define SGR_BROWN_BACKGROUND "\x1b\x5b\x34\x33\x6d"
#define SGR_BLUE_BACKGROUND "\x1b\x5b\x34\x34\x6d"
#define SGR_MAGENTA_BACKGROUND "\x1b\x5b\x34\x35\x6d"
#define SGR_CYAN_BACKGROUND "\x1b\x5b\x34\x36\x6d"
#define SGR_WHITE_BACKGROUND "\x1b\x5b\x34\x37\x6d"
