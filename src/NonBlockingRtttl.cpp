// ---------------------------------------------------------------------------
// Created by Antoine Beauchamp based on the code from the ToneLibrary
//
// See "NonBlockingRtttl.h" for purpose, syntax, version history, links, and more.
// ---------------------------------------------------------------------------

#include "Arduino.h"
#include "NonBlockingRtttl.h"

/*********************************************************
 * RTTTL Library data
 *********************************************************/

namespace rtttl
{

const int notes[] = { 0,
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

//#define isdigit(n) (n >= '0' && n <= '9')
#define OCTAVE_OFFSET 0

const char * buffer = "";
const char * firstNote = "";
int bufferIndex = -32760;
byte default_dur = 4;
byte default_oct = 5;
int bpm = 63;
long wholenote;
byte pin = -1;
unsigned long noteDelay = 0; //m will always be after which means the last note is done playing
unsigned long loopGap;
byte loopCount;
bool playing = false;

//pre-declaration
void nextnote();

#ifdef ESP32
#ifdef ESP_ARDUINO_VERSION
  #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 0, 0)
    // Code specific to ESP32 core 3.x
    // Core 3.x manages channels automatically:
    // In all esp32 functions, input parameter 'channel' has been changed to 'pin'.
    // See official documentation for migrating from core 2.x to 3.x:
    // https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html

    #define LEDC_RESOLUTION 10

    // Function noTone() stop the PWM signal for the given pin.
    // It does not detach the pin from it's assigned channel.
    // You can have sequential calls to tone() and noTone()
    // without having to call toneSetup() between calls.
    void noTone(uint8_t pin) {
      ledcWriteTone(pin, 0);
    }

    // Function tone() set a pin to output a PWM signal that matches the given frequency.
    // The duration argument is ignored. The function signature 
    // matches arduino's tone() function for compatibility reasons.
    // Arduino tone() function:
    //   https://docs.arduino.cc/language-reference/en/functions/advanced-io/tone/
    // ESP32 ledcWriteTone() function:
    //   https://github.com/espressif/arduino-esp32/blob/2.0.17/cores/esp32/esp32-hal-ledc.c#L118
    void tone(uint8_t pin, unsigned int frq, unsigned long duration) {
      // don't care about the given duration
      ledcWriteTone(pin, frq);
    }

    // Function toneSetup() setup the given pin to output a PWM signal for generating tones with a piezo buzzer.
    void toneSetup(uint8_t pin) {
      ledcAttach(pin, 1000, LEDC_RESOLUTION);
    }
    
  #elif ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(2, 0, 0)
    // Code specific to ESP32 core 2.x
    // Core 2.x uses channels instead of pins:
    // In all esp32 functions, input parameter is a 'channel' instead of a given pin.
    // This library uses the function getEsp32ChannelForPin() to map a pin to a channel number.
    // This channel is then used with all esp32 apis functions.
    // See official documentation for migrating from core 2.x to 3.x:
    // https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html

    #define ESP32_INVALID_CHANNEL 0xFF

    // Function getEsp32ChannelForPin() maps a given pin to a esp32 channel.
    // Returns a value between 0 and n where n is the maximum of channel for your board.
    // Returns ESP32_INVALID_CHANNEL if there is no assigned channel for the given pin number.
    // See your board documentation for details.
    // See https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/ledc.html#led-control-ledc
    uint8_t getEsp32ChannelForPin(uint8_t pin) {
      // This library only supports 1 pin at a time.
      // Always returns channel 0
      return 0;
    }

    // Function noTone() stop the PWM signal for the given pin.
    // It does not detach the pin from it's assigned channel.
    // You can have sequential calls to tone() and noTone()
    // without having to call toneSetup() between calls.
    void noTone(uint8_t pin) {
      uint8_t channel = getEsp32ChannelForPin(pin);
      ledcWriteTone(channel, 0); // Silence the buzzer without detaching
    }

    // Function tone() set a pin to output a PWM signal that matches the given frequency.
    // The duration argument is ignored. The function signature 
    // matches arduino's tone() function for compatibility reasons.
    // Arduino tone() function:
    //   https://docs.arduino.cc/language-reference/en/functions/advanced-io/tone/
    // ESP32 ledcWriteTone() function:
    //   https://github.com/espressif/arduino-esp32/blob/2.0.17/cores/esp32/esp32-hal-ledc.c#L118
    void tone(uint8_t pin, unsigned int frq, unsigned long duration) {
      // don't care about the given duration
      uint8_t channel = getEsp32ChannelForPin(pin);
      ledcWriteTone(channel, frq);
    }

    // Function toneSetup() setup the given pin to output a PWM signal for generating tones with a piezo buzzer.
    void toneSetup(uint8_t pin) {
      uint8_t channel = getEsp32ChannelForPin(pin);
      ledcAttachPin(pin, channel); // Attach the pin to the LEDC channel
    }

  #else
    #error ESP32 arduino version unsupported
  #endif
#else
  // ESP_ARDUINO_VERSION is undefined.
  #error ESP32 arduino version unsupported.
#endif
#endif

void begin(byte iPin, const char * iSongBuffer, byte iLoopCount, unsigned long iLoopGap)
{
  #ifdef RTTTL_NONBLOCKING_DEBUG
  Serial.print("playing: ");
  Serial.println(iSongBuffer);
  #endif
    
  //init values
  pin = iPin;
  #if defined(ESP32)
  toneSetup(pin);
  #endif
  buffer = iSongBuffer;
  bufferIndex = 0;
  default_dur = 4;
  default_oct = 6;
  bpm=63;
  playing = true;
  noteDelay = 0;
  loopCount = iLoopCount;
  loopGap = iLoopGap;
  #ifdef RTTTL_NONBLOCKING_DEBUG
  Serial.print("noteDelay=");
  Serial.println(noteDelay);
  #endif
  
  //stop current note
  noTone(pin);

  //read buffer until first note
  int num;

  // format: d=N,o=N,b=NNN:
  // find the start (skip name, etc)

  while(*buffer != ':') buffer++;    // ignore name
  buffer++;                     // skip ':'

  // get default duration
  if(*buffer == 'd')
  {
    buffer++; buffer++;              // skip "d="
    num = 0;
    while(isdigit(*buffer))
    {
      num = (num * 10) + (*buffer++ - '0');
    }
    if(num > 0) default_dur = num;
    buffer++;                   // skip comma
  }

  #ifdef RTTTL_NONBLOCKING_INFO
  Serial.print("ddur: "); Serial.println(default_dur, 10);
  #endif
  
  // get default octave
  if(*buffer == 'o')
  {
    buffer++; buffer++;              // skip "o="
    num = *buffer++ - '0';
    if(num >= 3 && num <=7) default_oct = num;
    buffer++;                   // skip comma
  }

  #ifdef RTTTL_NONBLOCKING_INFO
  Serial.print("doct: "); Serial.println(default_oct, 10);
  #endif
  
  // get BPM
  if(*buffer == 'b')
  {
    buffer++; buffer++;              // skip "b="
    num = 0;
    while(isdigit(*buffer))
    {
      num = (num * 10) + (*buffer++ - '0');
    }
    bpm = num;
    buffer++;                   // skip colon
  }

  #ifdef RTTTL_NONBLOCKING_INFO
  Serial.print("bpm: "); Serial.println(bpm, 10);
  #endif

  // BPM usually expresses the number of quarter notes per minute
  wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)

  firstNote = buffer;

  #ifdef RTTTL_NONBLOCKING_INFO
  Serial.print("wn: "); Serial.println(wholenote, 10);
  #endif
}

void nextnote()
{
  long duration;
  byte note;
  byte scale;

  //stop current note
  noTone(pin);

  // first, get note duration, if available
  int num = 0;
  while(isdigit(*buffer))
  {
    num = (num * 10) + (*buffer++ - '0');
  }
  
  if(num) duration = wholenote / num;
  else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

  // now get the note
  note = 0;

  switch(*buffer)
  {
    case 'c':
      note = 1;
      break;
    case 'd':
      note = 3;
      break;
    case 'e':
      note = 5;
      break;
    case 'f':
      note = 6;
      break;
    case 'g':
      note = 8;
      break;
    case 'a':
      note = 10;
      break;
    case 'b':
      note = 12;
      break;
    case 'p':
    default:
      note = 0;
  }
  buffer++;

  // now, get optional '#' sharp
  if(*buffer == '#')
  {
    note++;
    buffer++;
  }

  // now, get optional '.' dotted note
  if(*buffer == '.')
  {
    duration += duration/2;
    buffer++;
  }

  // now, get scale
  if(isdigit(*buffer))
  {
    scale = *buffer - '0';
    buffer++;
  }
  else
  {
    scale = default_oct;
  }

  scale += OCTAVE_OFFSET;

  // now, get optional '.' dotted note again.
  // A dot /after/ the octave is allowed too, depending on which
  // RTTTL specification you read.
  // See https://github.com/end2endzone/NonBlockingRTTTL/issues/10
  if(*buffer == '.')
  {
    duration += duration/2;
    buffer++;
  }

  if(*buffer == ',')
    buffer++;       // skip comma for next note (or we may be at the end)

  // now play the note

  if(note)
  {
    #ifdef RTTTL_NONBLOCKING_INFO
    Serial.print("Playing: ");
    Serial.print(scale, 10); Serial.print(' ');
    Serial.print(note, 10); Serial.print(" (");
    Serial.print(notes[(scale - 4) * 12 + note], 10);
    Serial.print(") ");
    Serial.println(duration, 10);
    #endif
    
    tone(pin, notes[(scale - 4) * 12 + note], duration);
    
    noteDelay = millis() + (duration+1);
  }
  else
  {
    #ifdef RTTTL_NONBLOCKING_INFO
    Serial.print("Pausing: ");
    Serial.println(duration, 10);
    #endif
    
    noteDelay = millis() + (duration);
  }
}

void play()
{
  //if done playing the song, return
  if (!playing)
  {
    #ifdef RTTTL_NONBLOCKING_DEBUG
    Serial.println("done playing...");
    #endif
    
    return;
  }
  
  //are we still playing a note ?
  unsigned long m = millis();
  if (m < noteDelay)
  {
    #ifdef RTTTL_NONBLOCKING_DEBUG
    Serial.println("still playing a note...");
    #endif
    
    //wait until the note is completed
    return;
  }

  //ready to play the next note
  if (*buffer == '\0')
  {
    //no more notes. Reached the end of the last note

    #ifdef RTTTL_NONBLOCKING_DEBUG
    Serial.println("end of note...");
    #endif
    
    //issue #6: Bug for ESP8266 environment - noTone() not called at end of sound.
    //disable sound at the end of a normal playback.
    if(--loopCount) {
      noteDelay = millis() + loopGap;
      buffer = firstNote;

      #ifdef RTTTL_NONBLOCKING_INFO
        Serial.print("Loop n°");
        Serial.print(loopCount, 10);
        Serial.print(" with delay gap ");
        Serial.print(loopGap, 10);
        Serial.println("ms");
      #endif
    }
    else stop();

    return; //end of the song
  }
  else
  {
    //more notes to play...

    #ifdef RTTTL_NONBLOCKING_DEBUG
    Serial.println("next note...");
    #endif
    
    nextnote();
  }
}

void stop()
{
  if (playing)
  {
    //increase song buffer until the end
    while (*buffer != '\0')
    {
      buffer++;
    }

    //issue #6: Bug for ESP8266 environment - noTone() not called at end of sound.
    //disable sound if one abort playback using the stop() command.
    noTone(pin);

    playing = false;
  }
}

bool done()
{
  return !playing;
}

bool isPlaying()
{
  return playing;
}

}; //namespace
