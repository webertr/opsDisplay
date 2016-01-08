/*  genSub code for writing bits via word access to the modicon 	*/
/*  8-29-2007	ddr	started...take indivivual bits and stuff them	*/
/*  			into a waveform record, per Mark Rivers 	*/
/*			suggestion					*/
/*  9-06-2007   ddr     working...now adding more write bits		*/
/*  03-21-2011  sb      convert genSub to aSub                          */


#include        <sys/types.h>
#include        <dbCommon.h>
#include        <recSup.h>

#include <stdio.h>

#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
#include <registryFunction.h>
#include <subRecord.h>
#include <aSubRecord.h>
#include <epicsExport.h>
#include <string.h>

#define NAME_SIZE 40
#define BUFLEN 80

int mySubDebug = 1;
char *waveOutRecord = "MOD1:CnOutWArray";

char *bitRecord00 = "MOD1:bit00.VAL";
char *bitRecord01 = "MOD1:bit01.VAL";
char *bitRecord02 = "MOD1:bit02.VAL";
char *bitRecord03 = "MOD1:bit03.VAL";
char *bitRecord04 = "MOD1:bit04.VAL";
char *bitRecord05 = "MOD1:bit05.VAL";
char *bitRecord06 = "MOD1:bit06.VAL";
char *bitRecord07 = "MOD1:bit07.VAL";
char *bitRecord08 = "MOD1:bit08.VAL";
char *bitRecord09 = "MOD1:bit09.VAL";
char *bitRecord10 = "MOD1:bit10.VAL";
char *bitRecord11 = "MOD1:bit11.VAL";
char *bitRecord12 = "MOD1:bit12.VAL";
char *bitRecord13 = "MOD1:bit13.VAL";
char *bitRecord14 = "MOD1:bit14.VAL";
char *bitRecord15 = "MOD1:bit15.VAL";
char *bitRecord16 = "MOD1:bit16.VAL";
char *bitRecord17 = "MOD1:bit17.VAL";
char *bitRecord18 = "MOD1:bit18.VAL";
char *bitRecord19 = "MOD1:bit19.VAL";
char *bitRecord20 = "MOD1:bit20.VAL";
char *bitRecord21 = "MOD1:bit21.VAL";
char *bitRecord22 = "MOD1:bit22.VAL";
char *bitRecord23 = "MOD1:bit23.VAL";
char *bitRecord24 = "MOD1:bit24.VAL";
char *bitRecord25 = "MOD1:bit25.VAL";
char *bitRecord26 = "MOD1:bit26.VAL";
char *bitRecord27 = "MOD1:bit27.VAL";
char *bitRecord28 = "MOD1:bit28.VAL";
char *bitRecord29 = "MOD1:bit29.VAL";
char *bitRecord30 = "MOD1:bit30.VAL";
char *bitRecord31 = "MOD1:bit31.VAL";
char *bitRecord32 = "MOD1:bit32.VAL";
char *bitRecord33 = "MOD1:bit33.VAL";
char *bitRecord34 = "MOD1:bit34.VAL";
char *bitRecord35 = "MOD1:bit35.VAL";
char *bitRecord36 = "MOD1:bit36.VAL";
char *bitRecord37 = "MOD1:bit37.VAL";
char *bitRecord38 = "MOD1:bit38.VAL";
char *bitRecord39 = "MOD1:bit39.VAL";
char *bitRecord40 = "MOD1:bit40.VAL";
char *bitRecord41 = "MOD1:bit41.VAL";
char *bitRecord42 = "MOD1:bit42.VAL";
char *bitRecord43 = "MOD1:bit43.VAL";
char *bitRecord44 = "MOD1:bit44.VAL";
char *bitRecord45 = "MOD1:bit45.VAL";
char *bitRecord46 = "MOD1:bit46.VAL";
char *bitRecord47 = "MOD1:bit47.VAL";
char *bitRecord48 = "MOD1:bit48.VAL";
char *bitRecord49 = "MOD1:bit49.VAL";
char *bitRecord50 = "MOD1:bit50.VAL";
char *bitRecord51 = "MOD1:bit51.VAL";
char *bitRecord52 = "MOD1:bit52.VAL";
char *bitRecord53 = "MOD1:bit53.VAL";
char *bitRecord54 = "MOD1:bit54.VAL";
char *bitRecord55 = "MOD1:bit55.VAL";
char *bitRecord56 = "MOD1:bit56.VAL";
char *bitRecord57 = "MOD1:bit57.VAL";
char *bitRecord58 = "MOD1:bit58.VAL";
char *bitRecord59 = "MOD1:bit59.VAL";
char *bitRecord60 = "MOD1:bit60.VAL";
char *bitRecord61 = "MOD1:bit61.VAL";
char *bitRecord62 = "MOD1:bit62.VAL";
char *bitRecord63 = "MOD1:bit63.VAL";
char *bitRecord64 = "MOD1:bit64.VAL";
char *bitRecord65 = "MOD1:bit65.VAL";
char *bitRecord66 = "MOD1:bit66.VAL";
char *bitRecord67 = "MOD1:bit67.VAL";
char *bitRecord68 = "MOD1:bit68.VAL";
char *bitRecord69 = "MOD1:bit69.VAL";
char *bitRecord70 = "MOD1:bit70.VAL";
char *bitRecord71 = "MOD1:bit71.VAL";
char *bitRecord72 = "MOD1:bit72.VAL";
char *bitRecord73 = "MOD1:bit73.VAL";
char *bitRecord74 = "MOD1:bit74.VAL";
char *bitRecord75 = "MOD1:bit75.VAL";
char *bitRecord76 = "MOD1:bit76.VAL";
char *bitRecord77 = "MOD1:bit77.VAL";
char *bitRecord78 = "MOD1:bit78.VAL";
char *bitRecord79 = "MOD1:bit79.VAL";
char *bitRecord80 = "MOD1:bit80.VAL";
char *bitRecord81 = "MOD1:bit81.VAL";
char *bitRecord82 = "MOD1:bit82.VAL";
char *bitRecord83 = "MOD1:bit83.VAL";
char *bitRecord84 = "MOD1:bit84.VAL";
char *bitRecord85 = "MOD1:bit85.VAL";
char *bitRecord86 = "MOD1:bit86.VAL";
char *bitRecord87 = "MOD1:bit87.VAL";
char *bitRecord88 = "MOD1:bit88.VAL";
char *bitRecord89 = "MOD1:bit89.VAL";
char *bitRecord90 = "MOD1:bit90.VAL";
char *bitRecord91 = "MOD1:bit91.VAL";
char *bitRecord92 = "MOD1:bit92.VAL";
char *bitRecord93 = "MOD1:bit93.VAL";
char *bitRecord94 = "MOD1:bit94.VAL";
char *bitRecord95 = "MOD1:bit95.VAL";
char *bitRecord96 = "MOD1:bit96.VAL";
char *bitRecord97 = "MOD1:bit97.VAL";
char *bitRecord98 = "MOD1:bit98.VAL";
char *bitRecord99 = "MOD1:bit99.VAL";
char *bitRecord100 = "MOD1:bit100.VAL";
char *bitRecord101 = "MOD1:bit101.VAL";
char *bitRecord102 = "MOD1:bit102.VAL";
char *bitRecord103 = "MOD1:bit103.VAL";
char *bitRecord104 = "MOD1:bit104.VAL";
char *bitRecord105 = "MOD1:bit105.VAL";
char *bitRecord106 = "MOD1:bit106.VAL";
char *bitRecord107 = "MOD1:bit107.VAL";
char *bitRecord108 = "MOD1:bit108.VAL";
char *bitRecord109 = "MOD1:bit109.VAL";
char *bitRecord110 = "MOD1:bit110.VAL";
char *bitRecord111 = "MOD1:bit111.VAL";
char *bitRecord112 = "MOD1:bit112.VAL";
char *bitRecord113 = "MOD1:bit113.VAL";
char *bitRecord114 = "MOD1:bit114.VAL";
char *bitRecord115 = "MOD1:bit115.VAL";
char *bitRecord116 = "MOD1:bit116.VAL";
char *bitRecord117 = "MOD1:bit117.VAL";
char *bitRecord118 = "MOD1:bit118.VAL";
char *bitRecord119 = "MOD1:bit119.VAL";
char *bitRecord120 = "MOD1:bit120.VAL";

DBADDR *waveOutAddr = (DBADDR *)NULL;

DBADDR *bitAddr00 = (DBADDR *)NULL;
DBADDR *bitAddr01 = (DBADDR *)NULL;
DBADDR *bitAddr02 = (DBADDR *)NULL;
DBADDR *bitAddr03 = (DBADDR *)NULL;
DBADDR *bitAddr04 = (DBADDR *)NULL;
DBADDR *bitAddr05 = (DBADDR *)NULL;
DBADDR *bitAddr06 = (DBADDR *)NULL;
DBADDR *bitAddr07 = (DBADDR *)NULL;
DBADDR *bitAddr08 = (DBADDR *)NULL;
DBADDR *bitAddr09 = (DBADDR *)NULL;
DBADDR *bitAddr10 = (DBADDR *)NULL;
DBADDR *bitAddr11 = (DBADDR *)NULL;
DBADDR *bitAddr12 = (DBADDR *)NULL;
DBADDR *bitAddr13 = (DBADDR *)NULL;
DBADDR *bitAddr14 = (DBADDR *)NULL;
DBADDR *bitAddr15 = (DBADDR *)NULL;
DBADDR *bitAddr16 = (DBADDR *)NULL;
DBADDR *bitAddr17 = (DBADDR *)NULL;
DBADDR *bitAddr18 = (DBADDR *)NULL;
DBADDR *bitAddr19 = (DBADDR *)NULL;
DBADDR *bitAddr20 = (DBADDR *)NULL;
DBADDR *bitAddr21 = (DBADDR *)NULL;
DBADDR *bitAddr22 = (DBADDR *)NULL;
DBADDR *bitAddr23 = (DBADDR *)NULL;
DBADDR *bitAddr24 = (DBADDR *)NULL;
DBADDR *bitAddr25 = (DBADDR *)NULL;
DBADDR *bitAddr26 = (DBADDR *)NULL;
DBADDR *bitAddr27 = (DBADDR *)NULL;
DBADDR *bitAddr28 = (DBADDR *)NULL;
DBADDR *bitAddr29 = (DBADDR *)NULL;
DBADDR *bitAddr30 = (DBADDR *)NULL;
DBADDR *bitAddr31 = (DBADDR *)NULL;
DBADDR *bitAddr32 = (DBADDR *)NULL;
DBADDR *bitAddr33 = (DBADDR *)NULL;
DBADDR *bitAddr34 = (DBADDR *)NULL;
DBADDR *bitAddr35 = (DBADDR *)NULL;
DBADDR *bitAddr36 = (DBADDR *)NULL;
DBADDR *bitAddr37 = (DBADDR *)NULL;
DBADDR *bitAddr38 = (DBADDR *)NULL;
DBADDR *bitAddr39 = (DBADDR *)NULL;
DBADDR *bitAddr40 = (DBADDR *)NULL;
DBADDR *bitAddr41 = (DBADDR *)NULL;
DBADDR *bitAddr42 = (DBADDR *)NULL;
DBADDR *bitAddr43 = (DBADDR *)NULL;
DBADDR *bitAddr44 = (DBADDR *)NULL;
DBADDR *bitAddr45 = (DBADDR *)NULL;
DBADDR *bitAddr46 = (DBADDR *)NULL;
DBADDR *bitAddr47 = (DBADDR *)NULL;
DBADDR *bitAddr48 = (DBADDR *)NULL;
DBADDR *bitAddr49 = (DBADDR *)NULL;
DBADDR *bitAddr50 = (DBADDR *)NULL;
DBADDR *bitAddr51 = (DBADDR *)NULL;
DBADDR *bitAddr52 = (DBADDR *)NULL;
DBADDR *bitAddr53 = (DBADDR *)NULL;
DBADDR *bitAddr54 = (DBADDR *)NULL;
DBADDR *bitAddr55 = (DBADDR *)NULL;
DBADDR *bitAddr56 = (DBADDR *)NULL;
DBADDR *bitAddr57 = (DBADDR *)NULL;
DBADDR *bitAddr58 = (DBADDR *)NULL;
DBADDR *bitAddr59 = (DBADDR *)NULL;
DBADDR *bitAddr60 = (DBADDR *)NULL;
DBADDR *bitAddr61 = (DBADDR *)NULL;
DBADDR *bitAddr62 = (DBADDR *)NULL;
DBADDR *bitAddr63 = (DBADDR *)NULL;
DBADDR *bitAddr64 = (DBADDR *)NULL;
DBADDR *bitAddr65 = (DBADDR *)NULL;
DBADDR *bitAddr66 = (DBADDR *)NULL;
DBADDR *bitAddr67 = (DBADDR *)NULL;
DBADDR *bitAddr68 = (DBADDR *)NULL;
DBADDR *bitAddr69 = (DBADDR *)NULL;
DBADDR *bitAddr70 = (DBADDR *)NULL;
DBADDR *bitAddr71 = (DBADDR *)NULL;
DBADDR *bitAddr72 = (DBADDR *)NULL;
DBADDR *bitAddr73 = (DBADDR *)NULL;
DBADDR *bitAddr74 = (DBADDR *)NULL;
DBADDR *bitAddr75 = (DBADDR *)NULL;
DBADDR *bitAddr76 = (DBADDR *)NULL;
DBADDR *bitAddr77 = (DBADDR *)NULL;
DBADDR *bitAddr78 = (DBADDR *)NULL;
DBADDR *bitAddr79 = (DBADDR *)NULL;
DBADDR *bitAddr80 = (DBADDR *)NULL;
DBADDR *bitAddr81 = (DBADDR *)NULL;
DBADDR *bitAddr82 = (DBADDR *)NULL;
DBADDR *bitAddr83 = (DBADDR *)NULL;
DBADDR *bitAddr84 = (DBADDR *)NULL;
DBADDR *bitAddr85 = (DBADDR *)NULL;
DBADDR *bitAddr86 = (DBADDR *)NULL;
DBADDR *bitAddr87 = (DBADDR *)NULL;
DBADDR *bitAddr88 = (DBADDR *)NULL;
DBADDR *bitAddr89 = (DBADDR *)NULL;
DBADDR *bitAddr90 = (DBADDR *)NULL;
DBADDR *bitAddr91 = (DBADDR *)NULL;
DBADDR *bitAddr92 = (DBADDR *)NULL;
DBADDR *bitAddr93 = (DBADDR *)NULL;
DBADDR *bitAddr94 = (DBADDR *)NULL;
DBADDR *bitAddr95 = (DBADDR *)NULL;
DBADDR *bitAddr96 = (DBADDR *)NULL;
DBADDR *bitAddr97 = (DBADDR *)NULL;
DBADDR *bitAddr98 = (DBADDR *)NULL;
DBADDR *bitAddr99 = (DBADDR *)NULL;
DBADDR *bitAddr100 = (DBADDR *)NULL;
DBADDR *bitAddr101 = (DBADDR *)NULL;
DBADDR *bitAddr102 = (DBADDR *)NULL;
DBADDR *bitAddr103 = (DBADDR *)NULL;
DBADDR *bitAddr104 = (DBADDR *)NULL;
DBADDR *bitAddr105 = (DBADDR *)NULL;
DBADDR *bitAddr106 = (DBADDR *)NULL;
DBADDR *bitAddr107 = (DBADDR *)NULL;
DBADDR *bitAddr108 = (DBADDR *)NULL;
DBADDR *bitAddr109 = (DBADDR *)NULL;
DBADDR *bitAddr110 = (DBADDR *)NULL;
DBADDR *bitAddr111 = (DBADDR *)NULL;
DBADDR *bitAddr112 = (DBADDR *)NULL;
DBADDR *bitAddr113 = (DBADDR *)NULL;
DBADDR *bitAddr114 = (DBADDR *)NULL;
DBADDR *bitAddr115 = (DBADDR *)NULL;
DBADDR *bitAddr116 = (DBADDR *)NULL;
DBADDR *bitAddr117 = (DBADDR *)NULL;
DBADDR *bitAddr118 = (DBADDR *)NULL;
DBADDR *bitAddr119 = (DBADDR *)NULL;
DBADDR *bitAddr120 = (DBADDR *)NULL;

long status = 0;
long pbuffer = 0x01;
long nRequest = 16;
int i;
int j;

/* Holder for array waveform 	*/
long waveform[120];

typedef long (*writeWaveFormMethod)(aSubRecord *writewaveformrecord);

static long writeWaveFormInit(aSubRecord *writewaveform, writeWaveFormMethod process)
{
    printf("Record %s called writeWaveFormInit(%p, %p)\n", writewaveform->name, (void*) writewaveform, (void*) process);

/*  get the paddr for the waveform record */
    waveOutAddr = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(waveOutRecord, waveOutAddr) != 0)
        printf("Error:  Cannot find waveform Record %s\n", waveOutRecord);

/*  Not get all the paddr info the the output bits */
    bitAddr00 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord00, bitAddr00) != 0)
    {
        printf("Error:  Cannot find bit00 Record %s\n", bitRecord00);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord00);
    }

    bitAddr01 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord01, bitAddr01) != 0)
    {
        printf("Error:  Cannot find bit01 Record %s\n", bitRecord01);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord01);
    }

    bitAddr02 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord02, bitAddr02) != 0)
    {
        printf("Error:  Cannot find bit02 Record %s\n", bitRecord02);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord02);
    }

    bitAddr03 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord03, bitAddr03) != 0)
    {
        printf("Error:  Cannot find bit03 Record %s\n", bitRecord03);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord03);
    }

    bitAddr04 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord04, bitAddr04) != 0)
    {
        printf("Error:  Cannot find bit04 Record %s\n", bitRecord04);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord04);
    }

    bitAddr05 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord05, bitAddr05) != 0)
    {
        printf("Error:  Cannot find bit05 Record %s\n", bitRecord05);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord05);
    }

    bitAddr06 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord06, bitAddr06) != 0)
    {
        printf("Error:  Cannot find bit06 Record %s\n", bitRecord06);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord06);
    }

    bitAddr07 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord07, bitAddr07) != 0)
    {
        printf("Error:  Cannot find bit07 Record %s\n", bitRecord07);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord07);
    }

    bitAddr08 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord08, bitAddr08) != 0)
    {
        printf("Error:  Cannot find bit08 Record %s\n", bitRecord08);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord08);
    }

    bitAddr09 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord09, bitAddr09) != 0)
    {
        printf("Error:  Cannot find bit09 Record %s\n", bitRecord09);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord09);
    }

    bitAddr10 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord10, bitAddr10) != 0)
    {
        printf("Error:  Cannot find bit10 Record %s\n", bitRecord10);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord10);
    }

    bitAddr11 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord11, bitAddr11) != 0)
    {
        printf("Error:  Cannot find bit11 Record %s\n", bitRecord11);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord11);
    }

    bitAddr12 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord12, bitAddr12) != 0)
    {
        printf("Error:  Cannot find bit12 Record %s\n", bitRecord12);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord12);
    }

    bitAddr13 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord13, bitAddr13) != 0)
    {
        printf("Error:  Cannot find bit13 Record %s\n", bitRecord13);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord13);
    }

    bitAddr14 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord14, bitAddr14) != 0)
    {
        printf("Error:  Cannot find bit14 Record %s\n", bitRecord14);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord14);
    }

    bitAddr15 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord15, bitAddr15) != 0)
    {
        printf("Error:  Cannot find bit15 Record %s\n", bitRecord15);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord15);
    }

    bitAddr16 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord16, bitAddr16) != 0)
    {
        printf("Error:  Cannot find bit16 Record %s\n", bitRecord16);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord16);
    }

    bitAddr17 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord17, bitAddr17) != 0)
    {
        printf("Error:  Cannot find bit17 Record %s\n", bitRecord17);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord17);
    }

    bitAddr18 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord18, bitAddr18) != 0)
    {
        printf("Error:  Cannot find bit18 Record %s\n", bitRecord18);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord18);
    }

    bitAddr19 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord19, bitAddr19) != 0)
    {
        printf("Error:  Cannot find bit19 Record %s\n", bitRecord19);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord19);
    }

    bitAddr20 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord20, bitAddr20) != 0)
    {
        printf("Error:  Cannot find bit20 Record %s\n", bitRecord20);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord20);
    }

    bitAddr21 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord21, bitAddr21) != 0)
    {
        printf("Error:  Cannot find bit21 Record %s\n", bitRecord21);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord21);
    }

    bitAddr22 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord22, bitAddr22) != 0)
    {
        printf("Error:  Cannot find bit22 Record %s\n", bitRecord22);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord22);
    }

    bitAddr23 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord23, bitAddr23) != 0)
    {
        printf("Error:  Cannot find bit23 Record %s\n", bitRecord23);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord23);
    }

    bitAddr24 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord24, bitAddr24) != 0)
    {
        printf("Error:  Cannot find bit24 Record %s\n", bitRecord24);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord24);
    }

    bitAddr25 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord25, bitAddr25) != 0)
    {
        printf("Error:  Cannot find bit25 Record %s\n", bitRecord25);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord25);
    }

    bitAddr26 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord26, bitAddr26) != 0)
    {
        printf("Error:  Cannot find bit26 Record %s\n", bitRecord26);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord26);
    }

    bitAddr27 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord27, bitAddr27) != 0)
    {
        printf("Error:  Cannot find bit27 Record %s\n", bitRecord27);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord27);
    }

    bitAddr28 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord28, bitAddr28) != 0)
    {
        printf("Error:  Cannot find bit28 Record %s\n", bitRecord28);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord28);
    }

    bitAddr29 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord29, bitAddr29) != 0)
    {
        printf("Error:  Cannot find bit29 Record %s\n", bitRecord29);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord29);
    }

    bitAddr30 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord30, bitAddr30) != 0)
    {
        printf("Error:  Cannot find bit30 Record %s\n", bitRecord30);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord30);
    }

    bitAddr31 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord31, bitAddr31) != 0)
    {
        printf("Error:  Cannot find bit31 Record %s\n", bitRecord31);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord31);
    }

    bitAddr32 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord32, bitAddr32) != 0)
    {
        printf("Error:  Cannot find bit32 Record %s\n", bitRecord32);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord32);
    }

    bitAddr33 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord33, bitAddr33) != 0)
    {
        printf("Error:  Cannot find bit33 Record %s\n", bitRecord33);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord33);
    }

    bitAddr34 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord34, bitAddr34) != 0)
    {
        printf("Error:  Cannot find bit34 Record %s\n", bitRecord34);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord34);
    }

    bitAddr35 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord35, bitAddr35) != 0)
    {
        printf("Error:  Cannot find bit35 Record %s\n", bitRecord35);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord35);
    }

    bitAddr36 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord36, bitAddr36) != 0)
    {
        printf("Error:  Cannot find bit36 Record %s\n", bitRecord36);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord36);
    }

    bitAddr37 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord37, bitAddr37) != 0)
    {
        printf("Error:  Cannot find bit37 Record %s\n", bitRecord37);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord37);
    }

    bitAddr38 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord38, bitAddr38) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord38);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord38);
    }

    bitAddr39 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord39, bitAddr39) != 0)
    {
        printf("Error:  Cannot find bit39 Record %s\n", bitRecord39);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord39);
    }

    bitAddr40 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord40, bitAddr40) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord40);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord40);
    }

    bitAddr41 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord41, bitAddr41) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord41);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord41);
    }

    bitAddr42 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord42, bitAddr42) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord42);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord42);
    }

    bitAddr43 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord43, bitAddr43) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord43);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord43);
    }

    bitAddr44 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord44, bitAddr44) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord44);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord44);
    }

    bitAddr45 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord45, bitAddr45) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord45);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord45);
    }

    bitAddr46 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord46, bitAddr46) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord46);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord46);
    }

    bitAddr47 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord47, bitAddr47) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord47);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord47);
    }

    bitAddr48 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord48, bitAddr48) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord48);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord48);
    }

    bitAddr49 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord49, bitAddr49) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord49);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord49);
    }

    bitAddr50 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord50, bitAddr50) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord50);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord50);
    }

    bitAddr51 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord51, bitAddr51) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord51);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord51);
    }

    bitAddr52 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord52, bitAddr52) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord52);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord52);
    }

    bitAddr53 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord53, bitAddr53) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord53);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord53);
    }

    bitAddr54 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord54, bitAddr54) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord54);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord54);
    }

    bitAddr55 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord55, bitAddr55) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord55);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord55);
    }

    bitAddr56 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord56, bitAddr56) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord56);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord56);
    }

    bitAddr57 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord57, bitAddr57) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord57);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord57);
    }

    bitAddr58 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord58, bitAddr58) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord58);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord58);
    }

    bitAddr59 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord59, bitAddr59) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord59);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord59);
    }

    bitAddr60 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord60, bitAddr60) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord60);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord60);
    }

    bitAddr61 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord61, bitAddr61) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord61);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord61);
    }

    bitAddr62 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord62, bitAddr62) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord62);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord62);
    }

    bitAddr63 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord63, bitAddr63) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord63);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord63);
    }

    bitAddr64 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord64, bitAddr64) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord64);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord64);
    }

    bitAddr65 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord65, bitAddr65) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord65);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord65);
    }

    bitAddr66 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord66, bitAddr66) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord66);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord66);
    }

    bitAddr67 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord67, bitAddr67) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord67);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord67);
    }

    bitAddr68 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord68, bitAddr68) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord68);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord68);
    }

    bitAddr69 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord69, bitAddr69) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord69);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord69);
    }

    bitAddr70 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord70, bitAddr70) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord70);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord70);
    }

    bitAddr71 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord71, bitAddr71) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord71);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord71);
    }

    bitAddr72 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord72, bitAddr72) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord72);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord72);
    }

    bitAddr73 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord73, bitAddr73) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord73);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord73);
    }

    bitAddr74 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord74, bitAddr74) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord74);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord74);
    }

    bitAddr75 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord75, bitAddr75) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord75);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord75);
    }

    bitAddr76 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord76, bitAddr76) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord76);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord76);
    }

    bitAddr77 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord77, bitAddr77) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord77);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord77);
    }

    bitAddr78 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord78, bitAddr78) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord78);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord78);
    }

    bitAddr79 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord79, bitAddr79) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord79);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord79);
    }

    bitAddr80 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord80, bitAddr80) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord80);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord80);
    }

    bitAddr81 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord81, bitAddr81) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord81);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord81);
    }

    bitAddr82 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord82, bitAddr82) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord82);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord82);
    }

    bitAddr83 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord83, bitAddr83) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord83);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord83);
    }

    bitAddr84 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord84, bitAddr84) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord84);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord84);
    }

    bitAddr85 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord85, bitAddr85) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord85);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord85);
    }

    bitAddr86 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord86, bitAddr86) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord86);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord86);
    }

    bitAddr87 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord87, bitAddr87) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord87);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord87);
    }

    bitAddr88 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord88, bitAddr88) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord88);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord88);
    }

    bitAddr89 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord89, bitAddr89) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord89);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord89);
    }

    bitAddr90 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord90, bitAddr90) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord90);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord90);
    }

    bitAddr91 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord91, bitAddr91) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord91);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord91);
    }

    bitAddr92 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord92, bitAddr92) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord92);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord92);
    }

    bitAddr93 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord93, bitAddr93) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord93);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord93);
    }

    bitAddr94 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord94, bitAddr94) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord94);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord94);
    }

    bitAddr95 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord95, bitAddr95) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord95);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord95);
    }

    bitAddr96 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord96, bitAddr96) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord96);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord96);
    }

    bitAddr97 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord97, bitAddr97) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord97);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord97);
    }

    bitAddr98 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord98, bitAddr98) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord98);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord98);
    }

    bitAddr99 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord99, bitAddr99) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord99);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord99);
    }

    bitAddr100 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord100, bitAddr100) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord100);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord100);
    }

    bitAddr101 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord101, bitAddr101) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord101);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord101);
    }

    bitAddr102 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord102, bitAddr102) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord102);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord102);
    }

    bitAddr103 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord103, bitAddr103) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord103);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord103);
    }

    bitAddr104 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord104, bitAddr104) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord104);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord104);
    }

    bitAddr105 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord105, bitAddr105) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord105);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord105);
    }

    bitAddr106 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord106, bitAddr106) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord106);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord106);
    }

    bitAddr107 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord107, bitAddr107) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord107);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord107);
    }

    bitAddr108 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord108, bitAddr108) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord108);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord108);
    }

    bitAddr109 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord109, bitAddr109) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord109);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord109);
    }

    bitAddr110 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord110, bitAddr110) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord110);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord110);
    }

    bitAddr111 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord111, bitAddr111) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord111);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord111);
    }

    bitAddr112 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord112, bitAddr112) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord112);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord112);
    }

    bitAddr113 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord113, bitAddr113) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord113);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord113);
    }

    bitAddr114 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord114, bitAddr114) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord114);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord114);
    }

    bitAddr115 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord115, bitAddr115) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord115);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord115);
    }

    bitAddr116 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord116, bitAddr116) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord116);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord116);
    }

    bitAddr117 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord117, bitAddr117) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord117);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord117);
    }

    bitAddr118 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord118, bitAddr118) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord118);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord118);
    }

    bitAddr119 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord119, bitAddr119) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord119);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord119);
    }

    bitAddr120 = (DBADDR *)calloc(1, sizeof(DBADDR));
    if (dbNameToAddr(bitRecord120, bitAddr120) != 0)
    {
        printf("Error:  Cannot find bit Record %s\n", bitRecord120);
    }
    else
    {
        printf("dbNameToAddr(%s) OK.\n", bitRecord120);
    }

    return(0);
}

static long writeWaveFormProcess(aSubRecord *writewaveformrecord)
{

    long *vala = (long *)writewaveformrecord->vala;

/*  Now get the information for the 120 bits of binary outs to be written 	*/
/*  to the Modicon via the waveform record					*/

    status = dbGetField(bitAddr00, DBF_LONG, &waveform[0], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr01, DBF_LONG, &waveform[1], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr02, DBF_LONG, &waveform[2], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr03, DBF_LONG, &waveform[3], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr04, DBF_LONG, &waveform[4], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr05, DBF_LONG, &waveform[5], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr06, DBF_LONG, &waveform[6], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr07, DBF_LONG, &waveform[7], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr08, DBF_LONG, &waveform[8], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr09, DBF_LONG, &waveform[9], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr10, DBF_LONG, &waveform[10], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr11, DBF_LONG, &waveform[11], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr12, DBF_LONG, &waveform[12], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr13, DBF_LONG, &waveform[13], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr14, DBF_LONG, &waveform[14], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr15, DBF_LONG, &waveform[15], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr16, DBF_LONG, &waveform[16], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr17, DBF_LONG, &waveform[17], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr18, DBF_LONG, &waveform[18], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr19, DBF_LONG, &waveform[19], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr20, DBF_LONG, &waveform[20], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr21, DBF_LONG, &waveform[21], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr22, DBF_LONG, &waveform[22], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr23, DBF_LONG, &waveform[23], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr24, DBF_LONG, &waveform[24], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr25, DBF_LONG, &waveform[25], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr26, DBF_LONG, &waveform[26], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr27, DBF_LONG, &waveform[27], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr28, DBF_LONG, &waveform[28], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr29, DBF_LONG, &waveform[29], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr30, DBF_LONG, &waveform[30], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr31, DBF_LONG, &waveform[31], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr32, DBF_LONG, &waveform[32], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr33, DBF_LONG, &waveform[33], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr34, DBF_LONG, &waveform[34], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr35, DBF_LONG, &waveform[35], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr36, DBF_LONG, &waveform[36], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr37, DBF_LONG, &waveform[37], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr38, DBF_LONG, &waveform[38], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr39, DBF_LONG, &waveform[39], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr40, DBF_LONG, &waveform[40], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr41, DBF_LONG, &waveform[41], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr42, DBF_LONG, &waveform[42], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr43, DBF_LONG, &waveform[43], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr44, DBF_LONG, &waveform[44], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr45, DBF_LONG, &waveform[45], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr46, DBF_LONG, &waveform[46], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr47, DBF_LONG, &waveform[47], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr48, DBF_LONG, &waveform[48], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr49, DBF_LONG, &waveform[49], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr50, DBF_LONG, &waveform[50], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr51, DBF_LONG, &waveform[51], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr52, DBF_LONG, &waveform[52], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr53, DBF_LONG, &waveform[53], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr54, DBF_LONG, &waveform[54], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr55, DBF_LONG, &waveform[55], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr56, DBF_LONG, &waveform[56], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr57, DBF_LONG, &waveform[57], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr58, DBF_LONG, &waveform[58], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr59, DBF_LONG, &waveform[59], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr60, DBF_LONG, &waveform[60], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr61, DBF_LONG, &waveform[61], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr62, DBF_LONG, &waveform[62], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr63, DBF_LONG, &waveform[63], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr64, DBF_LONG, &waveform[64], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr65, DBF_LONG, &waveform[65], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr66, DBF_LONG, &waveform[66], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr67, DBF_LONG, &waveform[67], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr68, DBF_LONG, &waveform[68], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr69, DBF_LONG, &waveform[69], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr70, DBF_LONG, &waveform[70], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr71, DBF_LONG, &waveform[71], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr72, DBF_LONG, &waveform[72], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr73, DBF_LONG, &waveform[73], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr74, DBF_LONG, &waveform[74], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr75, DBF_LONG, &waveform[75], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr76, DBF_LONG, &waveform[76], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr77, DBF_LONG, &waveform[77], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr78, DBF_LONG, &waveform[78], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr79, DBF_LONG, &waveform[79], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr80, DBF_LONG, &waveform[80], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr81, DBF_LONG, &waveform[81], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr82, DBF_LONG, &waveform[82], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr83, DBF_LONG, &waveform[83], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr84, DBF_LONG, &waveform[84], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr85, DBF_LONG, &waveform[85], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr86, DBF_LONG, &waveform[86], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr87, DBF_LONG, &waveform[87], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr88, DBF_LONG, &waveform[88], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr89, DBF_LONG, &waveform[89], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr90, DBF_LONG, &waveform[90], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr91, DBF_LONG, &waveform[91], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr92, DBF_LONG, &waveform[92], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr93, DBF_LONG, &waveform[93], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr94, DBF_LONG, &waveform[94], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr95, DBF_LONG, &waveform[95], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr96, DBF_LONG, &waveform[96], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr97, DBF_LONG, &waveform[97], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr98, DBF_LONG, &waveform[98], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr99, DBF_LONG, &waveform[99], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr100, DBF_LONG, &waveform[100], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr101, DBF_LONG, &waveform[101], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr102, DBF_LONG, &waveform[102], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr103, DBF_LONG, &waveform[103], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr104, DBF_LONG, &waveform[104], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr105, DBF_LONG, &waveform[105], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr106, DBF_LONG, &waveform[106], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr107, DBF_LONG, &waveform[107], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr108, DBF_LONG, &waveform[108], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr109, DBF_LONG, &waveform[109], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr110, DBF_LONG, &waveform[110], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr111, DBF_LONG, &waveform[111], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr112, DBF_LONG, &waveform[112], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr113, DBF_LONG, &waveform[113], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr114, DBF_LONG, &waveform[114], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr115, DBF_LONG, &waveform[115], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr116, DBF_LONG, &waveform[116], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr117, DBF_LONG, &waveform[117], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr118, DBF_LONG, &waveform[118], NULL, &nRequest, NULL);
    status = dbGetField(bitAddr119, DBF_LONG, &waveform[119], NULL, &nRequest, NULL);

/* put the waveform array into the .VAL field of the 	*/
/* waveform record					*/

/*  Will put the waveform into the output of the genSub record, and then */
/*  the database will push it into the waveform record			 */

/*  check that it got there */
    for(j=0; j<=119; j++)
    {
  	vala[j] = waveform[j];    
    }

    return(0);
}

/* Register these symbols for use by IOC code: */

epicsExportAddress(int, mySubDebug);
epicsRegisterFunction(writeWaveFormInit);
epicsRegisterFunction(writeWaveFormProcess);
