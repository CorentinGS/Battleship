# Add a trailing newline at the end of every file ending with .c or .h in the directory and its subdirectories.
# Usage: ./newline.sh

find . -name "*.c" -o -name "*.h" | while read file; do
    if [ -f "$file" ]; then
        if [ "$(tail -c 1 "$file")" != "" ]; then
            echo >> "$file"
        fi
    fi
done
