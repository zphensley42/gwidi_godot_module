#ifndef GODOT_GWIDI_DATA_H
#define GODOT_GWIDI_DATA_H

#include "core/reference.h"
#include "gwidi/GwidiGuiData.h"
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

    Gwidi_Note();
    ~Gwidi_Note();
    void init(gwidi::data::gui::Note* note);

private:
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


class Gwidi_Data : public Reference {
    GDCLASS(Gwidi_Data, Reference);

protected:
    static void _bind_methods();

public:
    void addMeasure();
    int measureCount();
    Ref<Gwidi_Measure> measureAt(int index);

    Gwidi_Data();

private:
  gwidi::data::gui::GwidiGuiData m_data;
};

#endif // GODOT_GWIDI_DATA_H
