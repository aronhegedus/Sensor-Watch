#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "sea_shanty_face.h"
#include "watch_utility.h"

void sea_shanty_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr) {
    (void) settings;
    (void) watch_face_index;
    if (*context_ptr == NULL) {
        *context_ptr = malloc(sizeof(sea_shanty_state_t));
        // Where do we free this???
        memset(*context_ptr, 0, sizeof(sea_shanty_state_t));
    }
}

void sea_shanty_face_activate(movement_settings_t *settings, void *context) {
    (void) settings;
    (void) context;
}

// I can do "Alarm AND beep" if TICK gets broken.
// but still can't do 2 sounds.
// can't do sound for 150!20!, but 10 works...
// Same when I have EVENT_LIGHT_BUTTON_DOWN
// Basically use watch_buzzer_play_sequence() instead, as it's already dealing with this stuff.

bool sea_shanty_face_loop(movement_event_t event, movement_settings_t *settings, void *context) {
    sea_shanty_state_t *state = (sea_shanty_state_t *)context;


    int8_t signal_tune_aron[] = {
        BUZZER_NOTE_E6, 7,
        BUZZER_NOTE_REST, 2,
        BUZZER_NOTE_E6, 7,
        BUZZER_NOTE_REST, 10,
        BUZZER_NOTE_E6, 7,
        BUZZER_NOTE_REST, 11,
        BUZZER_NOTE_C6, 7,
        BUZZER_NOTE_REST, 1,
        BUZZER_NOTE_E6, 7,
        BUZZER_NOTE_REST, 10,
        BUZZER_NOTE_G6, 8,
        BUZZER_NOTE_REST, 30,
        BUZZER_NOTE_G5, 8,
        0
        };

    int8_t sea_shanty_song[] = {
            BUZZER_NOTE_A7, 5,
            BUZZER_NOTE_REST, 5,
            BUZZER_NOTE_E7, 5,
            BUZZER_NOTE_D7, 5,
            BUZZER_NOTE_C7SHARP_D7FLAT, 10,
            BUZZER_NOTE_REST, 5,
            BUZZER_NOTE_C7SHARP_D7FLAT, 5,
            BUZZER_NOTE_D7, 5,
            BUZZER_NOTE_E7, 5,
            BUZZER_NOTE_F7SHARP_G7FLAT, 5,
            BUZZER_NOTE_G7SHARP_A7FLAT, 5,
            BUZZER_NOTE_E7, 10,
            BUZZER_NOTE_REST, 10,

            BUZZER_NOTE_F7SHARP_G7FLAT, 5,
            BUZZER_NOTE_REST, 5,
            BUZZER_NOTE_E7,5,
            BUZZER_NOTE_D7, 5,
            BUZZER_NOTE_C7SHARP_D7FLAT, 5,
            BUZZER_NOTE_REST, 5,
            BUZZER_NOTE_C7SHARP_D7FLAT, 5,
            BUZZER_NOTE_REST, 5,
            BUZZER_NOTE_B6,5,
            BUZZER_NOTE_REST, 5,
            BUZZER_NOTE_C7SHARP_D7FLAT, 5,
            BUZZER_NOTE_REST, 5,
            BUZZER_NOTE_D7, 10,
            BUZZER_NOTE_REST, 10,

            BUZZER_NOTE_A7, 5,
            BUZZER_NOTE_REST, 5,
            BUZZER_NOTE_E7, 5,
            BUZZER_NOTE_D7, 5,
            BUZZER_NOTE_C7SHARP_D7FLAT, 10,
            BUZZER_NOTE_REST, 10,
            BUZZER_NOTE_C7SHARP_D7FLAT, 5,
            BUZZER_NOTE_D7, 5,
            BUZZER_NOTE_E7, 5,
            BUZZER_NOTE_F7SHARP_G7FLAT, 5,
            BUZZER_NOTE_D7, 10,
            BUZZER_NOTE_REST, 10,

            BUZZER_NOTE_F7SHARP_G7FLAT, 5,
            BUZZER_NOTE_E7, 5,
            BUZZER_NOTE_D7, 5,
            BUZZER_NOTE_C7SHARP_D7FLAT, 5,
            BUZZER_NOTE_B6,5,
            BUZZER_NOTE_C7SHARP_D7FLAT, 5,
            BUZZER_NOTE_D7, 5,
            BUZZER_NOTE_F7SHARP_G7FLAT, 5,
            BUZZER_NOTE_E7, 5,
            BUZZER_NOTE_D7, 5,
            BUZZER_NOTE_C7SHARP_D7FLAT, 5,
            BUZZER_NOTE_B6,5,
            BUZZER_NOTE_A6,10,
            BUZZER_NOTE_REST, 10,
            0
    };

    switch (event.event_type) {
        case EVENT_ACTIVATE:
            watch_display_string("cool songs", 0);
            break;
        case EVENT_LIGHT_BUTTON_DOWN:
            watch_display_string("Se2 shanty", 0);
            watch_buzzer_play_sequence(sea_shanty_song, NULL);
            break;
        case EVENT_LIGHT_LONG_UP:
            // watch_display_string("Alarm", 0);
            // watch_buzzer_play_note(BUZZER_NOTE_E6, 10);
            // watch_buzzer_play_note(BUZZER_NOTE_C6, 10);
            // watch_buzzer_play_note(BUZZER_NOTE_E6, 10);
            // watch_buzzer_play_note(BUZZER_NOTE_C6, 5);
            // This works, but it NEVER lets us escape after!!!
            break;
        case EVENT_ALARM_BUTTON_DOWN:
            watch_display_string("mario  ", 0);
            watch_buzzer_play_sequence(signal_tune_aron, NULL);
            break;
        // case EVENT_MODE_LONG_PRESS:
        //     movement_move_to_next_face();
        //     break;
        // case EVENT_TICK:
        //     // state->song_index++;
        //     // watch_display_string("tick", 0);
        //     break;
        default:
            movement_default_loop_handler(event, settings);
            break;
    }

    return false;
}

void sea_shanty_face_resign(movement_settings_t *settings, void *context){
    (void) settings;
    sea_shanty_state_t *state = (sea_shanty_state_t *)context;
    state->song_index = 0;
}