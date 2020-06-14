/* Makeobj.c -- create WPS object
    usage:
        MAKEOBJ Classname Title Location [setupstring]
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
    HOBJECT hobject;

    if (argc < 4) {
        fputs("Usage: ", stderr);
        fputs(argv[0], stderr);
        fputs(" Classname Title Location [setupstring]\n", stderr);
        return 1;
    }

    hobject = WinCreateObject((PSZ)argv[1],
                              (PSZ)argv[2],
                              (PSZ)((argc > 4) ? argv[4] : NULL),
                              (PSZ)argv[3],
                              CO_FAILIFEXISTS );

    if (! hobject)
		fputs("WinCreateObject failed\n", stderr);

	return !hobject;
}
