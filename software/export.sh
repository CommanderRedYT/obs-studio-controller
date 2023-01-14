PROJECT_ROOT="$(dirname "$BASH_SOURCE")"

if [[ ! -f "${PROJECT_ROOT}/esp-idf/export.sh" ]]
then
    echo "esp-idf is missing, please check out all needed submodules!"
    echo "git submodule update --init --recursive"
    return
fi

. ${PROJECT_ROOT}/esp-idf/export.sh

complete -W "$(./switchconf.sh --list)" ./switchconf.sh
complete -W "$(./switchconf.sh --list)" switchconf

PROJECT_INIT_FAILED=

if [[ -e "build" ]] && [[ ! -L "build" ]]
then
    echo "ERROR: build folder exists but is not a symlink!"
    PROJECT_INIT_FAILED=1
fi

if [[ -e "sdkconfig" ]]
then
    if [[ ! -L "sdkconfig" ]]
    then
        echo "ERROR: sdkconfig exists but is not a symlink!"
        PROJECT_INIT_FAILED=1
    fi
else
    echo "ERROR: sdkconfig does not exist"
    PROJECT_INIT_FAILED=1
fi

if [[ -e "config.cmake" ]]
then
    if [[ ! -L "config.cmake" ]]
    then
        echo "ERROR: config.cmake exists but is not a symlink!"
        PROJECT_INIT_FAILED=1
    fi
else
    echo "ERROR: config.cmake does not exist"
    PROJECT_INIT_FAILED=1
fi

if [[ ! -z "$PROJECT_INIT_FAILED" ]]
then
    echo "run ./switchconf.sh to fix all listed issues"
    return
fi

export PATH=$PATH:$(pwd)/tools
alias switchconf="./switchconf.sh"
