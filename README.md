# Clipboard-Manager

A simple clipboard manager application that allows you to store and recall multiple clipboard entries.

- Monitors the clipboard for changes
- Stores up to 10 recent clipboard entries
- Displays clipboard history with timestamps
- Allows you to restore previous clipboard entries

## Notes

- Currently only supports text content
- Each clipboard entry must not exceed 4096 characters.

## How to Build

1. Ensure you have a C compiler installed for windows.
2. Run 'build.bat' to compile the application

## How to Use

1. Run 'clipboard_manager.exe'
2. The program will now start managing your clipboard
3. Use the following commands
   - Press 'd' to display clipboard history
   - Press '1'- '9' to restore specific clipboard entries
   - Press 'c' to clear the clipboard history
   - Press 'q' to quit and close the application
