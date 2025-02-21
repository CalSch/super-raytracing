#!/bin/bash

# script made by chatgpt so be warned
# we doin this bc arduino ide is goofy

# Define source and destination directories
INCLUDE_SRC="../base/include"
SRC_SRC="../base/src"
DST_DIR="./rtx"

# Create destination directory if it doesn't exist
mkdir -p "$DST_DIR"

# Copy all files from INCLUDE_SRC and SRC_SRC to DST_DIR
cp -r "$INCLUDE_SRC"/* "$DST_DIR"
cp -r "$SRC_SRC"/* "$DST_DIR"

# Change file extensions from .c or .cpp to .ino in the destination directory
find "$DST_DIR" -type f \( -iname "*.c" -o -iname "*.cpp" \) | while read -r file; do
    # Generate new file name with .ino extension
    new_file="${file%.*}.ino"
    
    # Rename the file
    mv -v "$file" "$new_file"
    
    echo "Renamed $file to $new_file"
done

echo "All files copied and renamed successfully!"
