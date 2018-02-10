// ---------------------------------------------------------------------------
// NonBlockingRtttl Library - v1.0 - 03/19/2016
//
// AUTHOR/LICENSE:
//  The following code was written by Antoine Beauchamp.
//  The code & updates for the library can be found on http://end2endzone.com
//  Project home: http://end2endzone.com
//  Original source code for the RTTL player: https://code.google.com/archive/p/rogue-code/wikis/ToneLibraryDocumentation.wiki
//  MIT License: http://www.opensource.org/licenses/mit-license.php
//
// DISCLAIMER:
//  This software is furnished "as is", without technical support, and with no 
//  warranty, express or implied, as to its usefulness for any purpose.
//
// PURPOSE:
//  Most code that can be found on the internet that allows you to "play" an RTTL string
//  is build the same way: sequential calls to the tone() function followed by a delay()
//  function. This type of implementation might be good for robots but not for realtime
//  application or projects that needs to monitor pins while the song is playing.
//  This library is non-blocking (https://en.wikipedia.org/wiki/Non-blocking_algorithm)
//  which make it suitable to be used by more advanced algorithm.
//  The NON-BLOCKING RTTTL library is a port of the RTTTL example from the Tone library.
//
// USAGE:
//  Call rtttl::begin() to setup the NON-BLOCKING RTTTL library. Then call 
//  rtttl::play() to update the library's state and play notes as required. Use
//  rtttl::done() or rtttl::isPlaying() to know if the library is done playing
//  the given song. Anytime playing one can call rtttl::stop() to stop playing
//  the current song.
//
//  Define RTTTL_NONBLOCKING_INFO to enable the debugging of the library
//  state on the serial port.
//
//  Use NONBLOCKINGRTTTL_VERSION to read the current version of the library.
//
// HISTORY:
// 03/19/2016 v1.0 - Initial release.
//
// ---------------------------------------------------------------------------


#ifndef NonBlockingRtttl_h
#define NonBlockingRtttl_h

#define NONBLOCKINGRTTTL_VERSION 1.0

#include "Arduino.h"

//if notes are not already defined
#ifndef NOTE_B0

#define NOTE_H   0
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//if notes are not already defined
#endif

//#define RTTTL_NONBLOCKING_DEBUG
//#define RTTTL_NONBLOCKING_INFO

namespace rtttl
{

/****************************************************************************
 * Description:
 *   begin() setups the NON-BLOCKING RTTTL library for
 *   decoding a new RTTTL song.
 * Parameters:
 *   iPin:        The pin which is connected to the piezo buffer.
 *   iSongBuffer: The string buffer of the RTTTL song.
 ****************************************************************************/
void begin(byte iPin, const char * iSongBuffer);

/****************************************************************************
 * Description:
 *   play() automatically plays a new note when required.
 *   This function must constantly be called within the loop() function.
 *   Warning: inserting too long delays within the loop function may
 *   disrupt the NON-BLOCKING RTTTL library from playing properly.
 ****************************************************************************/
void play();

/****************************************************************************
 * Description:
 *   stop() stops playing the current song.
 ****************************************************************************/
void stop();

/****************************************************************************
 * Description:
 *   isPlaying() return true when the library is playing
 *   the given RTTTL song.
 ****************************************************************************/
bool isPlaying();

/****************************************************************************
 * Description:
 *   done() return true when the library is done playing
 *   the given RTTTL song.
 ****************************************************************************/
bool done();

}; //namespace

//NonBlockingRtttl_h
#endif
