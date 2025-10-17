# Any commands which fail will cause the shell script to exit immediately
set -e

# Validate GitHub CI environment
if [ "$GITHUB_WORKSPACE" = "" ]; then
  echo "Please define 'GITHUB_WORKSPACE' environment variable.";
  exit 1;
fi

# Call matching script for linux
# and execute the script under the current shell instead of loading another one
this_filename=`basename "$0"`
. $GITHUB_WORKSPACE/ci/linux/$this_filename

# Remember installation directory
echo Remember ARDUINO_CLI_INSTALL_DIR as $ARDUINO_CLI_INSTALL_DIR in $GITHUB_ENV
echo ARDUINO_CLI_INSTALL_DIR=$ARDUINO_CLI_INSTALL_DIR>> $GITHUB_ENV
