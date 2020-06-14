/* Destobj.c -- destroy WPS object
   Usage:
      DESTOBJ objid
   By Ned Konz 3/14/92
*/

#include <stdio.h>

#define INCL_WINWORKPLACE
#include <os2.h>

/*
HOBJECT APIENTRY WinCreateObject(PSZ pszClassName,
                                PSZ pszTitle,
                                PSZ pszSetupString,
                                PSZ pszLocation,
                                ULONG ulFlags );
#define CO_FAILIFEXISTS     1
#define CO_REPLACEIFEXISTS  2
#define CO_UPDATEIFEXISTS   4

BOOL APIENTRY WinSetObjectData(HOBJECT hObject,
                                PSZ pszSetupString);

BOOL APIENTRY WinDestroyObject(HOBJECT hObject);

HOBJECT APIENTRY WinQueryObject(PSZ pszObjectID);
*/

int main( int argc, char *argv[] )
{
    HOBJECT hObject;

    if (argc != 2) {
        fputs("Usage: ", stderr);
        fputs(argv[0], stderr);
        fputs(" objid\n", stderr);
        return 1;
    }

    hObject = WinQueryObject((PSZ)argv[1]);
    if (hObject) {
        return !WinDestroyObject(hObject);
    } else {
        fputs("Object ", stderr);
        fputs(argv[1], stderr);
        fputs(" Not found!\n", stderr);
        return 2;
    }
}
