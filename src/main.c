/* Code: */
#include <stdio.h>
#include <string.h>
#include "internodeAPI.h"
#include "xmlparsing.h"
#define BASEXML "tmp/nodeservice.xml"
/* sample XML file */
/* <internode> */
/* <api> */
/* <services count="1"> */
/*      <service type="Personal_ADSL" href="/api/v1.5/ID">ID_changed</service> */
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

    char baseurl[80] = "https://customer-webtools-api.internode.on.net/api/v1.5/";
/* get the first xml for the internode userid */

    getNodeXml(baseurl, BASEXML); // this function takes url and saves the xml file to the path given using libcurl defined in internodeAPI.h 
    char * serviceID = getElementContent(BASEXML, "service");
    printf("%s\n", serviceID ); // i get ID_changed printed
    strcat(baseurl, serviceID);

    char history[80];
    strcpy(history, baseurl);
    strcat(history,"/history/");

    char usage[80];
    strcpy(usage, baseurl);
    strcat(usage,"/usage/");

    printf("%s\n",baseurl );    /* all of these work */
    printf("%s\n",history );
    printf("%s\n",usage );

    getNodeXml(usage, USAGEXML); /* download the files from Iternode */
    getNodeXml(history, HISTORYXML);

    char * traffic = getElementContent(HISTORYXML, "traffic");

    printf("%s\n", traffic);	/* segmentation fault */

    free(traffic);
    return 0;
}


/* main.c ends here */
