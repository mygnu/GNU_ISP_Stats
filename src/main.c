/* Code: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "internodeAPI.h"
#include "xmlparsing.h"
#define BASEXML "tmp/nodeservice.xml"
#define USAGEXML "tmp/nodeusage.xml"
#define HISTORYXML "tmp/nodehistory.xml"



int
main(int argc, char *argv[])
{

    char baseurl[80] = "https://customer-webtools-api.internode.on.net\
/api/v1.5/";

/* get the first xml for the internode use rid */
    getNodeXml(baseurl, BASEXML);/* comment out if not compiling with
                                       internodeAPI.h */

    char serviceID[40];
    getElementContent(BASEXML, "service", serviceID);
    printf("serveice id in %s is %s\n",BASEXML, serviceID ); /* i get ID_changed printed */
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

    getNodeXml(usage, USAGEXML);     /* internodeAPI.h */
    getNodeXml(history, HISTORYXML); /* internodeAPI.h */

    free(usage);
    free(history);

    double totalusage = getUsage(HISTORYXML, "traffic", 0, -30);
    printf("totalUsage = %f MB\n", totalusage);
    return 0;
}


/* main.c ends here */




















