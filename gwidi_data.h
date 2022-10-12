#ifndef GODOT_GWIDI_DATA_H
#define GODOT_GWIDI_DATA_H

#include "core/reference.h"
#include "gwidi/GwidiGuiData.h"
#include "core/array.h"

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
