/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "gwidi_data.h"

void register_gwidi_data_types() {
    ClassDB::register_class<Gwidi_Data>();
    ClassDB::register_class<Gwidi_Measure>();
}

void unregister_gwidi_data_types() {
    // Nothing to do here in this example.
}
