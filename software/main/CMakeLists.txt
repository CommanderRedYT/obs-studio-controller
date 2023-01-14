file(
    GLOB files
        *.h
        */*.h
        *.cpp
        */*.cpp
)

set(dependencies
    freertos nvs_flash esp_http_server esp_https_ota mdns app_update esp_system esp_websocket_client driver esp_adc
    arduino-esp32 ArduinoJson esp-nimble-cpp FastLED-idf TFT_eSPI QRCode-esp32
    cpputils cxx-ring-buffer date
    espasynchttpreq espasyncota espchrono espcpputils espconfiglib esp-gui-lib esphttpdutils espwifistack expected fmt
)

idf_component_register(
    SRCS
        ${files}
    INCLUDE_DIRS
        .
    REQUIRES
        ${dependencies}
)

execute_process(COMMAND git rev-parse HEAD
        OUTPUT_VARIABLE GIT_REV ERROR_QUIET
)
execute_process(
        COMMAND git log -1 --pretty=%B
        OUTPUT_VARIABLE GIT_MESSAGE ERROR_QUIET
)
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        OUTPUT_VARIABLE GIT_BRANCH
)
execute_process(
        COMMAND git status --short
        OUTPUT_VARIABLE GIT_STATUS
)

string(STRIP "${GIT_REV}" GIT_REV)
string(SUBSTRING "${GIT_REV}" 1 7 GIT_SHORT_REV)
string(STRIP "${GIT_MESSAGE}" GIT_MESSAGE)
string(REPLACE "\n" " " GIT_MESSAGE "${GIT_MESSAGE}")
string(REPLACE "\"" "\\\"" GIT_MESSAGE "${GIT_MESSAGE}")
string(SUBSTRING "${GIT_MESSAGE}" 0 100 GIT_MESSAGE)
string(STRIP "${GIT_BRANCH}" GIT_BRANCH)

message(WARNING "Git revision: ${GIT_REV}")
message(WARNING "Git short revision: ${GIT_SHORT_REV}")
message(WARNING "Git message: ${GIT_MESSAGE}")
message(WARNING "Git branch: ${GIT_BRANCH}")
message(WARNING "Git status: ${GIT_STATUS}")

target_compile_options(${COMPONENT_TARGET}
    PRIVATE
        -fstack-reuse=all
        -fstack-protector-all
        -fdiagnostics-color=always
        -Wno-unused-function
        -Wno-deprecated-declarations
        -Wno-missing-field-initializers
        -Wno-parentheses
        -DGIT_REV="${GIT_REV}"
        -DGIT_SHORT_REV="${GIT_SHORT_REV}"
        -DGIT_MESSAGE="${GIT_MESSAGE}"
        -DGIT_BRANCH="${GIT_BRANCH}"
        ${CUSTOM_BUILDFLAGS}
)
