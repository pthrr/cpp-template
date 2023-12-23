#!/usr/bin/env sh

PRESET_INCLUDE_PATH="/path/to/optional/preset.json"
PROJECT_ROOT="/path/to/project/root"

# Copy the main CMakePresets.json to the project root
# cp "$PROJECT_ROOT/CMakePresets.json" "$PROJECT_ROOT/CMakePresets.json.bak"

if [ -f "$PRESET_INCLUDE_PATH" ]; then
    # Modify CMakePresets.json to include the additional presets
    jq '.include += ["'"$PRESET_INCLUDE_PATH"'"]' "$PROJECT_ROOT/CMakePresets.json" > "$PROJECT_ROOT/CMakePresets.json.modified"
    mv "$PROJECT_ROOT/CMakePresets.json.modified" "$PROJECT_ROOT/CMakePresets.json"
fi

# Run CMake with the desired preset
# cmake --preset your-preset

# Restore the original CMakePresets.json
mv "$PROJECT_ROOT/CMakePresets.json.bak" "$PROJECT_ROOT/CMakePresets.json"
