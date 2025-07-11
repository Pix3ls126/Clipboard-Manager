#include <stdio.h>   // Standard input/output functions (printf, etc.)
#include <stdlib.h>  // Standard library (malloc, free, etc.)
#include <string.h>  // String handling functions (strcmp, strlen, etc.)
#include <windows.h> // Windows API functions for clipboard operations
#include <conio.h>   // Console input/output functions (getch, etc.)

#define MAX_TEXT_LENGTH 4096     // Max length of text to handle
#define MAX_CLIPBOARD_ENTRIES 10 // Max number of clipboard entries to store

/*
Define a structure to hold clipboard entries.
Each entry contains:
- text: The text copied to the clipboard
- timestamp: The time when the text was copied
eventually would like to add the ability to store images or other data types.
*/
typedef struct
{
    char *content;   // Pointer to the text content
    char *timestamp; // Pointer to the timestamp string
} ClipboardEntry;

ClipboardEntry clipboardHistory[MAX_CLIPBOARD_ENTRIES]; // Array to hold clipboard entries
int clipCount = 0;                                      // Current count of clipboard entries

/*
Function Declarations
*/

void initializeClipboardHistory();        // Sets up clipboard history
void clearClipboardHistory();             // Clears the clipboard history
void monitorClipboard();                  // Monitors the clipboard for changes
void displayClipboardHistory();           // Displays the current clipboard history
char *getCurrentTimeStamp();              // Gets the current timestamp as a string
void setClipboardText(const char *text);  // Sets the clipboard text
void addClipboardEntry(const char *text); // Add a new entry to the clipboard history

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    if (fdwCtrlType == CTRL_C_EVENT)
    {
        printf("\nExiting clipboard monitor...\n");
        clearClipboardHistory(); // Clear history on exit
        exit(0);                 // Exit the program
        return TRUE;             // Indicate that the event was handled
    }
    return FALSE; // Indicate that the event was not handled
}
