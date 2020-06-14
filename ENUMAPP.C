/*******************************************/
/* This call retrieves a string from the   */
/* specified profile.                      */
/*******************************************/

#define SPIT_DATA 0
#define DEBUG     0

#include <stdio.h>
#include <stdlib.h>

#define INCL_WINSHELLDATA   /* Or use INCL_WIN or INCL_PM */
#include <os2.h>

#define APP_BUFFER_SIZE     10000
#define KEY_BUFFER_SIZE     40000
#define VAL_BUFFER_SIZE     10000

int main(int argc, char *argv[])
{
    ULONG  pulLength;      /*String length returned */
    ULONG  max_length = 0UL;      /*String length returned */

    PSZ    appnames = malloc( APP_BUFFER_SIZE );
    PSZ    keynames = malloc( KEY_BUFFER_SIZE );
#if SPIT_DATA
    PSZ    values   = malloc( VAL_BUFFER_SIZE );
#endif
    PSZ    papp;
    ULONG  app_buffer_size = APP_BUFFER_SIZE;

    /* get all app names into appnames */
    app_buffer_size = APP_BUFFER_SIZE;
    pulLength = PrfQueryProfileData(HINI_PROFILE,
                    NULL, NULL, appnames, &app_buffer_size);

    for (papp = appnames; *papp; papp += strlen(papp)+1) {
        PSZ   pkey;
        ULONG length = KEY_BUFFER_SIZE;
        if (! PrfQueryProfileData(HINI_PROFILE,
                    papp, NULL, keynames, &length))
            break;

		if (length > max_length)
			max_length = length;

        for (pkey = keynames; *pkey;  pkey += strlen(pkey)+1) {
#if SPIT_DATA
            ULONG length = VAL_BUFFER_SIZE;
            if ( !PrfQueryProfileData(HINI_PROFILE,
                    papp, pkey, values, &length))
                        break;
			printf("%06lu\t",
                strlen(pkey) + strlen(papp) + 11 + (unsigned long)length);
#endif
            fputs(papp, stdout);
            fputs("\t", stdout);
            fputs(pkey, stdout);
            fputs("\t", stdout);

#if SPIT_DATA
            fwrite(values, 1, length, stdout);
#endif
            fputs("\n", stdout);
        }
    }

#if SPIT_DATA
    free(values);
#endif
    free(keynames);
    free(appnames);

#if DEBUG
	printf("%lu bytes of app names\n", (unsigned long) pulLength);
	printf("%lu bytes max of key names\n", (unsigned long) max_length);
#endif

    return 0;
}

