![NonBlockingRTTTL logo](docs/NonBlockingRtttl-splashscreen.png?raw=true)


[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Github Releases](https://img.shields.io/github/release/end2endzone/NonBlockingRTTTL.svg)](https://github.com/end2endzone/NonBlockingRTTTL/releases)



# NonBlockingRTTTL #

NonBlockingRTTTL is a non-blocking arduino library for playing RTTTL melodies. The library allows your program to read or write IOs pins while playing. Implementing "stop" or "next song" push buttons is really easy!

It's main features are:

*  Fully support the RTTTL format standard.
*  Support unofficial frequencies and tempo/beats per minutes
*  Really small increase in memory & code footprint compared to the usual blocking algorithm.



## Status ##

Build:

| Service | Build | Tests |
|----|-------|-------|
| AppVeyor | [![Build status](https://img.shields.io/appveyor/ci/end2endzone/NonBlockingRTTTL/master.svg?logo=appveyor)](https://ci.appveyor.com/project/end2endzone/NonBlockingRTTTL) | [![Tests status](https://img.shields.io/appveyor/tests/end2endzone/NonBlockingRTTTL/master.svg?logo=appveyor)](https://ci.appveyor.com/project/end2endzone/NonBlockingRTTTL/branch/master/tests) |
| Travis CI | [![Build Status](https://img.shields.io/travis/end2endzone/NonBlockingRTTTL/master.svg?logo=travis&style=flat)](https://travis-ci.org/end2endzone/NonBlockingRTTTL) |  |

Statistics:

| AppVeyor | Travic CI |
|----------|-----------|
| [![Statistics](https://buildstats.info/appveyor/chart/end2endzone/NonBlockingRTTTL)](https://ci.appveyor.com/project/end2endzone/NonBlockingRTTTL/branch/master) | [![Statistics](https://buildstats.info/travisci/chart/end2endzone/NonBlockingRTTTL)](https://travis-ci.org/end2endzone/NonBlockingRTTTL) |



# Purpose #

Most code that can be found on the internet that "play" an RTTTL string is build this way: sequential calls to the `tone()` function followed by a call to the `delay()` function:

```cpp
tone(pin, note1, duration1);
delay(note_delay1);
tone(pin, note2, duration2);
delay(note_delay2);
tone(pin, note3, duration3);
delay(note_delay3);
//etc...
```

This type of implementation might be good for robots but not for realtime application or projects that needs to monitor pins while the song is playing.

This library is non-blocking which make it suitable to be used by more advanced algorithm. The non-blocking RTTTL library is a port of the RTTTL example from the [Tone library](http://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/rogue-code/Arduino-Library-Tone.zip).




# RTTTL format

The Ring Tone Text Transfer Language (RTTTL) audio format is an audio format for storing single tone (monolithic) melodies. Each melody is composed of successive tone frequencies.

The RTTTL format is [human readable](http://stackoverflow.com/questions/568671/why-should-i-use-a-human-readable-file-format) and usually more compressed than note & duration arrays which helps reduce its memory footprint.

The format is really suitable for embedded device that are limited in memory which can’t store PCM (wav) or even MP3 data.

*Note that RTTTL can also be spelled RTTL (Ringtone Text Transfer Language). According to Samsung phones, a ringtone can also be spelled as a single word...*

More information on the RTTTL format is available on its [Wikipedia acticle](https://en.wikipedia.org/wiki/Ring_Tone_Transfer_Language).



# Usage #

The following instructions show how to use the library.



## General ##

Call `rtttl::begin()` to setup the non-blocking RTTTL library then call `rtttl::play()` to update the library's state and play notes as required.

Use `rtttl::done()` or `rtttl::isPlaying()` to know if the library is done playing the given song. Anytime playing, one can call `rtttl::stop()` to stop playing the current song.

Define `RTTTL_NONBLOCKING_INFO` to enable the debugging of the library state on the serial port. Use `NONBLOCKINGRTTTL_VERSION` to read the current version of the library.



### Play a melody: ###
The following example plays 3 melodies. The first melody is played for 5 seconds and stopped. The second and third melodies and played completely and then the program restart again.

```cpp
#include <NonBlockingRtttl.h>
 
//project's contants
#define BUZZER_PIN 8
const char * tetris = "tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";
const char * arkanoid = "Arkanoid:d=4,o=5,b=140:8g6,16p,16g.6,2a#6,32p,8a6,8g6,8f6,8a6,2g6";
const char * mario = "mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";
byte songIndex = 0; //which song to play when the previous one finishes
 
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
 
  Serial.begin(115200);
  Serial.println();
}
 
void loop() {
  if ( !rtttl::isPlaying() )
  {
    if (songIndex == 0)
    {
      rtttl::begin(BUZZER_PIN, mario);
      songIndex++; //ready for next song
 
      //play for 5 sec then stop.
      //note: this is a blocking code section
      //used to demonstrate the use of stop()
      unsigned long start = millis();
      while( millis() - start < 5000 ) 
      {
        rtttl::play();
      }
      rtttl::stop();
      
    }
    else if (songIndex == 1)
    {
      rtttl::begin(BUZZER_PIN, arkanoid);
      songIndex++; //ready for next song
    }
    else if (songIndex == 2)
    {
      rtttl::begin(BUZZER_PIN, tetris);
      songIndex++; //ready for next song
    }
  }
  else
  {
    rtttl::play();
  }
}
```


## Other samples ##

See the library examples for more details:

* [rtttl_blocking.ino](examples/rtttl_blocking/rtttl_blocking.ino)
* [rtttl_demo.ino](examples/rtttl_demo/rtttl_demo.ino)




# Building #

Please refer to file [INSTALL.md](INSTALL.md) for details on how installing/building the application.




# Platforms #

NonBlockingRTTTL has been tested with the following platform:

  * Linux x86/x64
  * Windows x86/x64




# Versioning #

We use [Semantic Versioning 2.0.0](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/end2endzone/NonBlockingRTTTL/tags).




# Authors #

* **Antoine Beauchamp** - *Initial work* - [end2endzone](https://github.com/end2endzone)

See also the list of [contributors](https://github.com/end2endzone/NonBlockingRTTTL/blob/master/AUTHORS) who participated in this project.




# License #

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
