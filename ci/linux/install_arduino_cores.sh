# Any commands which fail will cause the shell script to exit immediately
set -e

# Set current directory to local script
cd "$(dirname "$0")"

# Check Arduino CLI installation
echo Expecting Arduino IDE installed in directory: $ARDUINO_CLI_INSTALL_DIR
echo Searching for arduino-cli executable...
export PATH=$PATH:$ARDUINO_CLI_INSTALL_DIR
which arduino-cli
echo

echo Searching for yaml-merge executable...
export PATH=$PATH:~/.local/bin
which yaml-merge
echo

# Set arduino-cli config file path
export ARDUINO_CONFIG_FILE_PATH="/home/$USER/.arduino15/arduino-cli.yaml"
echo ARDUINO_CONFIG_FILE_PATH set to '$ARDUINO_CONFIG_FILE_PATH'
cat "$ARDUINO_CONFIG_FILE_PATH"
echo
echo

export YAML_MERGE_FILE="../arduinocli-core-esp8266.yaml"
echo Adding $YAML_MERGE_FILE to arduino-cli config...
yaml-merge --nostdin "$YAML_MERGE_FILE" "$ARDUINO_CONFIG_FILE_PATH" --overwrite="$ARDUINO_CONFIG_FILE_PATH"
cat "$ARDUINO_CONFIG_FILE_PATH"
echo
echo

export YAML_MERGE_FILE="../arduinocli-core-esp32.yaml"
echo Adding $YAML_MERGE_FILE to arduino-cli config...
yaml-merge --nostdin "$YAML_MERGE_FILE" "$ARDUINO_CONFIG_FILE_PATH" --overwrite="$ARDUINO_CONFIG_FILE_PATH"
cat "$ARDUINO_CONFIG_FILE_PATH"
echo
echo

echo arduino update-index...
arduino-cli core update-index
echo
echo

echo Installing "arduino:avr" core...
arduino-cli core install "arduino:avr"
echo
echo

echo Installing "esp8266:esp8266" core...
arduino-cli core install "esp8266:esp8266"
echo
echo

echo Installing "esp32:esp32" core...
arduino-cli core install "esp32:esp32"
echo
echo

echo Listing all installed cores...
arduino-cli core list
echo
echo
