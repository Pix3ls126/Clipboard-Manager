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

int main()
{
    // Set up the console control handler to catch Ctrl+C
    if (!SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
        fprintf(stderr, "Error setting control handler.\n");
        return 1;
    }

    initializeClipboardHistory(); // Initialize clipboard history

    printf("Clipboard Manager started. Press Ctrl+C to exit.\n");

    monitorClipboard(); // Start monitoring the clipboard

    clearClipboardHistory;

    return 1; // Exit successfully
}

void initializeClipboardHistory()
{
    for (int i = 0; i < MAX_CLIPBOARD_ENTRIES; i++)
    {
        clipboardHistory[i].content = NULL;
        clipboardHistory[i].timestamp = NULL;
    }

    CloseClipboard();

    printf("Clipboard Manager initialized.\n");
}

/*
Clears the clipboard history by freeing allocated memory for each entry.
*/
void clearClipboardHistory()
{
    for (int i = 0; i < clipCount; i++)
    {
        free(clipboardHistory[i].content);
        free(clipboardHistory[i].timestamp);
        clipboardHistory[i].content = NULL;
        clipboardHistory[i].timestamp = NULL;
    }
    clipCount = 0; // Reset the count
    printf("Clipboard history cleared.\n");
}

char *getCurrentTimeStamp()
{
    char *buffer = (char *)malloc(20 * sizeof(char)); // Allocate memory for timestamp
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed for timestamp.\n");
        return NULL;
    }

    SYSTEMTIME st;
    GetLocalTime(&st); // Get the current local time
    sprintf(buffer, "%02d-%02d-%04d %02d:%02d:%02d", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
    return buffer; // Return the timestamp string
}

void setClipboardText(const char *text)
{
    if (text == NULL || strlen(text) == 0)
    {
        fprintf(stderr, "Cannot set empty text to clipboard.\n");
        return;
    }
    if (!OpenClipboard(NULL)) // Open the clipboard
    {
        printf(stderr, "Failed to open clipboard.\n");
        return;
    }

    EmptyClipboard(); // Clear the clipboard

    size_t textLength = strlen(text) + 1;
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, textLength); // Allocate global memory
    if (hGlobal == NULL)
    {
        printf("Failed to allocate memory for clipboard text.\n");
        return;
    }
    char *memPtr = (char *)GlobalLock(hGlobal); // Lock the memory
    if (memPtr == NULL)
    {
        printf("Failed to lock global memory for clipboard text.\n");
        GlobalFree(hGlobal); // Free the allocated memory
        CloseClipboard();
        return;
    }

    memcpy(memPtr, text, textLength); // Copy the text to the memory
    GlobalUnlock(hGlobal);            // Unlock the memory

    if (SetClipboardData(CF_TEXT, hGlobal) == NULL) // Set the clipboard data
    {
        printf("Failed to set clipboard data.\n");
        GlobalFree(hGlobal); // Free the allocated memory
    }

    CloseClipboard(); // Close the clipboard
}

void addClipboardEntry(const char *text)
{
    if (text == NULL || strlen(text) == 0)
    {
        fprintf(stderr, "Cannot add empty text to clipboard history.\n");
        return;
    }

    if (clipCount > 0 && clipboardHistory[0].content != NULL &&
        strcmp(clipboardHistory[0].content, text) == 0)
    {
        printf("Text is already the latest entry in clipboard history.\n");
        return; // Do not add duplicate entries
    }

    if (clipCount >= MAX_CLIPBOARD_ENTRIES)
    {
        free(clipboardHistory[MAX_CLIPBOARD_ENTRIES - 1].content);
        free(clipboardHistory[MAX_CLIPBOARD_ENTRIES - 1].timestamp);

        for (int i = MAX_CLIPBOARD_ENTRIES - 1; i > 0; i--)
        {
            clipboardHistory[i] = clipboardHistory[i - 1]; // Shift entries
        }
    }
    else
    {
        for (int i = clipCount; i > 0; i--)
        {
            clipboardHistory[i] = clipboardHistory[i - 1]; // Shift entries
        }
        clipCount++; // Increment the count
    }

    printf("Adding new entry to clipboard history.\n");
}

void displayClipboardHistory() {}

void monitorClipboard() {}
