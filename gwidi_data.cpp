#include "gwidi_data.h"
#include "core/print_string.h"

// TODO: The question is: is it better to rely on the UI data in native or to generate in GD classes then pass to native when we want to translate?
// TODO: If we rely on UI data, we still have to translate over to GD classes for the native script to read

Gwidi_Measure::Gwidi_Measure() {
}

Gwidi_Measure::~Gwidi_Measure() {
  print_line("Gwidi_Measure destroyed!");
}

void Gwidi_Measure::init(gwidi::data::gui::Measure* measure) {
  m_measure = measure;
}

Array Gwidi_Measure::getOctaves() {
  Array ret{};
  for(auto &o : m_measure->octaves) {
    ret.append(o.num);
  }
  return ret;
}

int Gwidi_Measure::num() {
  return m_measure->num;
}

void Gwidi_Measure::_bind_methods() {
  ClassDB::bind_method(D_METHOD("getOctaves"), &Gwidi_Measure::getOctaves);
  ClassDB::bind_method(D_METHOD("num"), &Gwidi_Measure::num);
}






Gwidi_Data::Gwidi_Data() {
}

void Gwidi_Data::addMeasure() {
  m_data.addMeasure();
}

int Gwidi_Data::measureCount() {
  return m_data.getMeasures().size();
}

Ref<Gwidi_Measure> Gwidi_Data::measureAt(int index) {
  Ref<Gwidi_Measure> measure;
  measure.instance();
  auto &data_measure = m_data.getMeasures()[index];
  measure->init(&data_measure);
  return measure;
}

void Gwidi_Data::_bind_methods() {
  ClassDB::bind_method(D_METHOD("addMeasure"), &Gwidi_Data::addMeasure);
  ClassDB::bind_method(D_METHOD("measureCount"), &Gwidi_Data::measureCount);
  ClassDB::bind_method(D_METHOD("measureAt", "index"), &Gwidi_Data::measureAt);
}
