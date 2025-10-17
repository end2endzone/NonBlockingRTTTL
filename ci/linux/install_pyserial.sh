# Any commands which fail will cause the shell script to exit immediately
set -e

# Install pyserial.

# Search for python
echo Validate if python is installed
which python
echo Found python interpreter
python --version
echo

# Search for pip
echo Validate if pip is installed
which pip
echo

# Installing pyserial.
echo Proceeding with instaling pyserial...
pip install pyserial
echo

echo pyserial was installed on the system without error.
echo
