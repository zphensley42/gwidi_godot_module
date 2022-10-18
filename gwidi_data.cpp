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
  m_note->activated = !m_note->activated;
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






Gwidi_Gui_Data::Gwidi_Gui_Data() {
  m_data = new gwidi::data::gui::GwidiGuiData(gwidi::data::gui::Instrument::HARP);
}

Gwidi_Gui_Data::~Gwidi_Gui_Data() {
  delete m_data;
  m_data = nullptr;
}

void Gwidi_Gui_Data::addMeasure() {
  m_data->addMeasure();
}

Array Gwidi_Gui_Data::getMeasures() {
  Array ret{};
  for(auto &m : m_data->getMeasures()) {
    Ref<Gwidi_Measure> measure;
    measure.instance();
    measure->init(&m);
    ret.append(measure);
  }
  return ret;
}

void Gwidi_Gui_Data::toggleNote(Ref<Gwidi_Note> note) {
  // note->toggle(); Don't toggle, the below method already does that
  m_data->toggleNote(note->m_note);
}

void Gwidi_Gui_Data::_bind_methods() {
  ClassDB::bind_method(D_METHOD("addMeasure"), &Gwidi_Gui_Data::addMeasure);
  ClassDB::bind_method(D_METHOD("getMeasures"), &Gwidi_Gui_Data::getMeasures);
  ClassDB::bind_method(D_METHOD("toggleNote"), &Gwidi_Gui_Data::toggleNote);
}


Gwidi_Midi_Parser::Gwidi_Midi_Parser() {

}

Gwidi_Midi_Parser::~Gwidi_Midi_Parser() {

}

Array Gwidi_Midi_Parser::getTrackMetaMap(String filename) {

  std::wstring filename_wstr = filename.c_str();
  std::string filename_str( filename_wstr.begin(), filename_wstr.end() );

  auto trackMeta = gwidi::midi::GwidiMidiParser::getInstance().getTrackMetaMap(filename_str.c_str());
  Array ret{};

  for(auto &entry : trackMeta) {
    Dictionary trackInfo{};
    trackInfo["name"] = String(entry.second.name.c_str());
    trackInfo["instrument"] = String(entry.second.instrument.c_str());
    trackInfo["num_notes"] = entry.second.num_notes;
    trackInfo["tempo"] = entry.second.tempo;
    trackInfo["duration"] = entry.second.duration;
    ret.append(trackInfo);
  }
  return ret;
 }

void Gwidi_Midi_Parser::_bind_methods() {
  ClassDB::bind_method(D_METHOD("getTrackMetaMap"), &Gwidi_Midi_Parser::getTrackMetaMap);
}
