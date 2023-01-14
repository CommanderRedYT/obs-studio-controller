set(APP_NAME obs-studio-controller)

add_definitions(
  -DUSER_SETUP_LOADED=1
  -fdiagnostics-color=always
)

set(CUSTOM_BUILDFLAGS
    -DBOARD_REVISION_V1
)
