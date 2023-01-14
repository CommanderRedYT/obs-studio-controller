# Software

## Compiling the firmware
1. Make sure you fully clone this repository with `git clone --recursive git@github.com:CommanderRedYT/obs-studio-controller.git
2. Install the esp-idf via ./esp-idf/install.sh
3. Source the environment via `source ./export.sh`
4. Switch to the correct build config via `switchconf.sh <config>`
5. Run `idf.py build` to build the firmware
