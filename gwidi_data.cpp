#include "gwidi_data.h"
#include "core/print_string.h"

// TODO: The question is: is it better to rely on the UI data in native or to generate in GD classes then pass to native when we want to translate?
// TODO: If we rely on UI data, we still have to translate over to GD classes for the native script to read

// TODO: As each call returns new arrays / dictionaries (even if they are referencing data that isn't cloned), this is somewhat inefficient
// TODO: If we could cache the arrays/dictionaries, this would work better but we may be required to do that in NativeScript, not here

Gwidi_Note::Gwidi_Note() {
}
Gwidi_Note::~Gwidi_Note() {
  print_line("Gwidi_Note destroyed!");
}

void Gwidi_Note::init(gwidi::data::gui::Note* note) {
  m_note = note;
}

Array Gwidi_Note::getLetters() {
  Array ret{};
  for(auto &letter : m_note->letters) {
    ret.append(String(letter.c_str()));
  }
  return ret;
}

int Gwidi_Note::measure() {
  return m_note->measure;
}

int Gwidi_Note::octave() {
  return m_note->octave;
}

int Gwidi_Note::time() {
  return m_note->time;
}

String Gwidi_Note::key() {
  return String(m_note->key.c_str());
}

void Gwidi_Note::toggle() {
  m_note->activated = !(m_note->activated);
}
bool Gwidi_Note::activated() {
  return m_note->activated;
}

void Gwidi_Note::_bind_methods() {
  ClassDB::bind_method(D_METHOD("getLetters"), &Gwidi_Note::getLetters);
  ClassDB::bind_method(D_METHOD("measure"), &Gwidi_Note::measure);
  ClassDB::bind_method(D_METHOD("octave"), &Gwidi_Note::octave);
  ClassDB::bind_method(D_METHOD("time"), &Gwidi_Note::time);
  ClassDB::bind_method(D_METHOD("key"), &Gwidi_Note::key);
  ClassDB::bind_method(D_METHOD("toggle"), &Gwidi_Note::toggle);
  ClassDB::bind_method(D_METHOD("activated"), &Gwidi_Note::activated);
}


Gwidi_Octave::Gwidi_Octave() {
}
Gwidi_Octave::~Gwidi_Octave() {
  print_line("Gwidi_Octave destroyed!");
}

void Gwidi_Octave::init(gwidi::data::gui::Octave* octave) {
  m_octave = octave;
}

Dictionary Gwidi_Octave::getTimes() {
  Dictionary ret{};
  for(auto &timeEntry : m_octave->notes) {
    int time = timeEntry.first;
    Array arr{};
    for(auto &n : timeEntry.second) {
      Ref<Gwidi_Note> note;
      note.instance();
      note->init(&n);
      arr.append(note);
    }
    ret[time] = arr;
  }
  return ret;
}

int Gwidi_Octave::num() {
  return m_octave->num;
}

int Gwidi_Octave::measure() {
  return m_octave->measure;
}

void Gwidi_Octave::_bind_methods() {
  ClassDB::bind_method(D_METHOD("getTimes"), &Gwidi_Octave::getTimes);
  ClassDB::bind_method(D_METHOD("measure"), &Gwidi_Octave::measure);
  ClassDB::bind_method(D_METHOD("num"), &Gwidi_Octave::num);
}



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
    Ref<Gwidi_Octave> octave;
    octave.instance();
    octave->init(&o);
    ret.append(octave);
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
  m_data = new gwidi::data::gui::GwidiGuiData(gwidi::data::gui::Instrument::HARP);
}

Gwidi_Data::~Gwidi_Data() {
  delete m_data;
  m_data = nullptr;
}

void Gwidi_Data::addMeasure() {
  m_data->addMeasure();
}

Array Gwidi_Data::getMeasures() {
  Array ret{};
  for(auto &m : m_data->getMeasures()) {
    Ref<Gwidi_Measure> measure;
    measure.instance();
    measure->init(&m);
    ret.append(measure);
  }
  return ret;
}

void Gwidi_Data::_bind_methods() {
  ClassDB::bind_method(D_METHOD("addMeasure"), &Gwidi_Data::addMeasure);
  ClassDB::bind_method(D_METHOD("getMeasures"), &Gwidi_Data::getMeasures);
}
