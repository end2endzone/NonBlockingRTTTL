# Installing

The library does not provide an automatic installer package. It is deployed using a zip archive which only contains the source code. It can be installed on the system by following the same steps as with other Arduino library.

The following steps show how to install the library on your system:

## Download the library .zip file

The latest version of the library can be found in the project's [release page](http://github.com/end2endzone/NonBlockingRTTTL/releases/latest).

Each released version of the library contains 3 files:
* The archive installer in .zip format (identified as `NonBlockingRtttl.vX.Y.Z.zip`)
* The project source code and documentation in .zip format (identified as `Source code (zip)`)
* The project source code and documentation in tar.gz (identified as `Source code (tar.gz)`)

Download the `library archive installer` from an existing tags and extract the content to a local directory (for example `c:\my_arduino_libraries`).

## Import the .zip library

The library can be installed on the system by following the same steps as other Arduino library.

Refer to the official Arduino guide on how [importing a .zip library](http://www.arduino.cc/en/Guide/Libraries#toc4) for details.

### Error `Zip doesn't contain a library`

When importing a library in the Arduino IDE, you may get the `Zip doesn't contain a library` error message.

This is probably because you tried to install the `project source code` instead of the `archive installer in .zip format`. Follow the instructions of the Download section.

# Building

N/A.

The library does not require building before usage.
