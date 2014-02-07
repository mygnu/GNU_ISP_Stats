/* Code: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "internodeAPI.h"
#include "xmlparsing.h"
#define BASEXML "tmp/nodeservice.xml"
/* sample XML file */
/* <internode> */
/* <api> */
/* <services count="1"> */
/*      <service type="Personal_ADSL" href="/api/v1.5/ID">ID_changed */
/*      </service> */
/*      </services> */
/* </api> */
/* </internode> */
#define USAGEXML "tmp/nodeusage.xml"
#define HISTORYXML "tmp/nodehistory.xml"
/* sample XML file */
/* <internode><api> */
/* <service type="Personal_ADSL" request="history">ID_changed</service> */
/*      <usagelist> */
/*      <usage day="2013-01-25"> */
/*      <traffic name="total" unit="bytes">2084408661</traffic> */
/*      </usage> */
/*      <usage day="2013-01-26"> */
/*      <traffic name="total" unit="bytes">3038963621</traffic> */
/*      </usage> */
/*      </usagelist> */
/* </api></internode> */



int
main(int argc, char *argv[])
{

    char baseurl[80] = "https://customer-webtools-api.internode.on.net\
/api/v1.5/";

/* get the first xml for the internode use rid */
    //    getNodeXml(baseurl, BASEXML);/* comment out if not compiling with
    //                                    internodeAPI.h */

    char * serviceID = getElementContent(BASEXML, "service");
    printf("%s\n", serviceID ); /* i get ID_changed printed */
    strcat(baseurl, serviceID);
    printf("%s\n",baseurl );    /* all of these work */

    char *history = malloc(sizeof(char) * 128);
    strcpy(history, baseurl);
    strcat(history,"/history/");
    printf("%s\n",history );

    char *usage = malloc(sizeof(char) * 128);
    strcpy(usage, baseurl);
    strcat(usage,"/usage/");
    printf("%s\n",usage );

    //    getNodeXml(usage, USAGEXML);     /* internodeAPI.h */
    //    getNodeXml(history, HISTORYXML); /* internodeAPI.h */

    free(usage);
    free(history);

    double totalusage = getUsage(HISTORYXML, "//traffic", 0, -30);
    printf("totalUsage = %f MB\n", totalusage);
    return 0;
}


/* main.c ends here */




















