/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "gwidi_data.h"

void register_gwidi_data_types() {
    ClassDB::register_class<Gwidi_Options>();
    ClassDB::register_class<Gwidi_Gui_Playback>();
    ClassDB::register_class<Gwidi_Midi_Parser>();
    ClassDB::register_class<Gwidi_Gui_Data>();
    ClassDB::register_class<Gwidi_Measure>();
    ClassDB::register_class<Gwidi_Octave>();
    ClassDB::register_class<Gwidi_Note>();
    ClassDB::register_class<Gwidi_HotKey>();
    ClassDB::register_class<Gwidi_HotKeyAssignmentPressDetector>();
}

void unregister_gwidi_data_types() {
    // Nothing to do here in this example.
}
