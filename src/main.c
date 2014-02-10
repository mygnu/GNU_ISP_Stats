/* Code: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "internodeAPI.h"
#include "xmlparsing.h"




int
main(int argc, char *argv[])
{

    internodeInit("2014-01-01", "2014-02-01");
    
 

    double totalusage = getUsage(HISTORYXML, "traffic", 0, -30);
    printf("totalUsage = %f MB\n", totalusage);

    char *attrib = malloc(sizeof(char) * 50);
    //    getAttrib(USAGEXML, "traffic", "quota", attrib);
    printf("%s\n", attrib);
    return 0;
}


/* main.c ends here */




















