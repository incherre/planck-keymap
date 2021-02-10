#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define UNICODE_SONG_MAC SONG(VIOLIN_SOUND)
    #define UNICODE_SONG_LNX SONG(GUITAR_SOUND)
#endif

#define UNICODE_SELECTED_MODES UC_MAC, UC_LNX

// https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold#permissive-hold
// #define PERMISSIVE_HOLD

// Threshold in milliseconds to interpret tap rather than hold
// #define TAPPING_TERM 200
