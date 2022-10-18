#ifndef GODOT_GWIDI_DATA_H
#define GODOT_GWIDI_DATA_H

#include "core/reference.h"
#include "gwidi/GwidiGuiData.h"
#include "gwidi/gwidi_midi_parser.h"
#include "core/array.h"

class Gwidi_Note : public Reference {
  GDCLASS(Gwidi_Note, Reference);
protected:
    static void _bind_methods();

public:
    Array getLetters();
    int measure();
    int octave();
    int time();
    String key();

    void toggle();
    bool activated();

    Gwidi_Note();
    ~Gwidi_Note();
    void init(gwidi::data::gui::Note* note);

private:
  friend class Gwidi_Gui_Data;
  gwidi::data::gui::Note* m_note;
};

class Gwidi_Octave : public Reference {
  GDCLASS(Gwidi_Octave, Reference);
protected:
    static void _bind_methods();

public:
    Dictionary getTimes();
    int num();
    int measure();

    Gwidi_Octave();
    ~Gwidi_Octave();
    void init(gwidi::data::gui::Octave* octave);

private:
  gwidi::data::gui::Octave* m_octave;
};

class Gwidi_Measure : public Reference {
  GDCLASS(Gwidi_Measure, Reference);
protected:
    static void _bind_methods();

public:
    Array getOctaves();
    int num();

    Gwidi_Measure();
    ~Gwidi_Measure();
    void init(gwidi::data::gui::Measure* measure);

private:
  gwidi::data::gui::Measure* m_measure;
};


class Gwidi_Gui_Data : public Reference {
    GDCLASS(Gwidi_Gui_Data, Reference);

protected:
    static void _bind_methods();

public:

    void addMeasure();
    Array getMeasures();
    void toggleNote(Ref<Gwidi_Note> note);

    Gwidi_Gui_Data();
    ~Gwidi_Gui_Data();

private:
  gwidi::data::gui::GwidiGuiData* m_data{nullptr};
};

class Gwidi_Midi_Parser : public Reference {
    GDCLASS(Gwidi_Midi_Parser, Reference);

protected:
    static void _bind_methods();

public:
    Array getTrackMetaMap(String filename);

    Gwidi_Midi_Parser();
    ~Gwidi_Midi_Parser();
};

#endif // GODOT_GWIDI_DATA_H
