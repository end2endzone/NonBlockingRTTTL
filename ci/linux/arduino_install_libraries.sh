# Any commands which fail will cause the shell script to exit immediately
set -e

# Set PRODUCT_SOURCE_DIR root directory
if [ "$PRODUCT_SOURCE_DIR" = "" ]; then
  RESTORE_DIRECTORY="$PWD"
  cd "$(dirname "$0")"
  cd ../..
  export PRODUCT_SOURCE_DIR="$PWD"
  echo "PRODUCT_SOURCE_DIR set to '$PRODUCT_SOURCE_DIR'."
  cd "$RESTORE_DIRECTORY"
  unset RESTORE_DIRECTORY
fi

# Check Arduino CLI installation
echo Expecting Arduino IDE installed in directory: $ARDUINO_CLI_INSTALL_DIR
echo Searching for arduino cli executable...
export PATH=$PATH:$ARDUINO_CLI_INSTALL_DIR
which arduino-cli
echo

echo ==========================================================================================================
echo Installing arduino library dependencies
echo ==========================================================================================================

echo BitReader...
arduino-cli lib install BitReader
echo

cd "$(dirname "$0")"
