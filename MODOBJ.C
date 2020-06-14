/* Modobj.c -- modify WPS object
    usage:
        modobj objid setupstring
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

    if (argc != 3) {
        fputs("Usage: ", stderr);
        fputs(argv[0], stderr);
        fputs(" objid setupstring\n", stderr);
        return 1;
    }

    hObject = WinQueryObject((PSZ)argv[1]);
    if (hObject) {
        return !WinSetObjectData(hObject, (PSZ)argv[2]);
    } else {
        fputs("Object ", stderr);
        fputs(argv[1], stderr);
        fputs(" Not found!\n", stderr);
        return 2;
    }
}

