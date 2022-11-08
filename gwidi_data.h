#ifndef GODOT_GWIDI_DATA_H
#define GODOT_GWIDI_DATA_H

#include "core/reference.h"
#include "core/func_ref.h"
#include "gwidi/GwidiGuiData.h"
#include "gwidi/gwidi_midi_parser.h"
#include "gwidi/GwidiDataConverter.h"
#include "gwidi/GwidiPlayback.h"
#include "gwidi/GwidiOptions2.h"
#include "gwidi/gwidi_hotkey.h"
#include "core/array.h"
#include <string_view>

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
    double tempo();

    Gwidi_Gui_Data();
    ~Gwidi_Gui_Data();

private:
  friend class Gwidi_Gui_Playback;
  friend class Gwidi_Midi_Parser;

  void assignData(gwidi::data::gui::GwidiGuiData* data);
  gwidi::data::gui::GwidiGuiData* m_data{nullptr};
};

class Gwidi_Midi_Parser : public Reference {
    GDCLASS(Gwidi_Midi_Parser, Reference);

protected:
    static void _bind_methods();

public:
    Array getTrackMetaMap(String filename);
    Ref<Gwidi_Gui_Data> importMidi(String filename, int track);

    Gwidi_Midi_Parser();
    ~Gwidi_Midi_Parser();
};

class Gwidi_Gui_Playback : public Reference {
  GDCLASS(Gwidi_Gui_Playback, Reference);
protected:
    static void _bind_methods();

public:
    void setRealInput(bool real);
    void play();
    void pause();
    void stop();

    bool isPlaying();
    bool isPaused();
    bool isStopped();

    void assignTickCallbackFn(Ref<FuncRef> cb);
    void assignPlayCallbackFn(Ref<FuncRef> cb);
    void assignPlayEndedFn(Ref<FuncRef> cb);

    void assignInstrument(String instrument);
    void assignData(Ref<Gwidi_Gui_Data> data, int octaveBehavior);

    Gwidi_Gui_Playback();
    ~Gwidi_Gui_Playback();

private:
  std::string m_instrument;
  Ref<FuncRef> m_tickCbFn{nullptr};
  Ref<FuncRef> m_playCbFn{nullptr};
  Ref<FuncRef> m_playEndedFn{nullptr};
  Ref<Gwidi_Gui_Data> m_data{nullptr};
  gwidi::playback::GwidiPlayback* m_playback{nullptr};
};

class Gwidi_Options : public Reference {
  GDCLASS(Gwidi_Options, Reference);
protected:
    static void _bind_methods();

  public:
	Dictionary hotkeyMapping();

	// User inputs hotkeys and presses okay to send this request
	void assignHotkey(String name, Array keys);
	void reloadConfig();

    int timesPerMeasure();
    double tempo();
};

class Gwidi_HotKey : public Reference {
	GDCLASS(Gwidi_HotKey, Reference);
protected:
	static void _bind_methods();

public:
	Gwidi_HotKey();
	~Gwidi_HotKey();

	void beginListening();
	void stopListening();

	void assignHotkeyFunction(String hotkeyName, Ref<FuncRef> cb);

private:
	gwidi::hotkey::GwidiHotkey* m_hotkeys{nullptr};
	std::map<std::string, Ref<FuncRef>> m_assignedHotkeyFunctions;
};

class Gwidi_HotKeyAssignmentPressDetector : public Reference {
	GDCLASS(Gwidi_HotKeyAssignmentPressDetector, Reference);
protected:
	static void _bind_methods();

public:
	Gwidi_HotKeyAssignmentPressDetector();
	~Gwidi_HotKeyAssignmentPressDetector();

	void beginListening();
	void stopListening();

	// These 2 methods can be used in combination to initiate listening / listing keys that are pressed from the moment we ask to the moment we retrieve the list
	void clearPressedKeys();
	void assignPressedKeyListener(Ref<FuncRef> cb);
	Array pressedKeys();

private:
	gwidi::hotkey::GwidiHotkeyAssignmentPressDetector* m_hotkeyPressDetector{nullptr};
	Ref<FuncRef> m_pressedKeyCb{nullptr};
};


#endif // GODOT_GWIDI_DATA_H
