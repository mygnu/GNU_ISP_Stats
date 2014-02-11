/* Code: */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "internodeAPI.h"
#include "xmlparsing.h"




int
main(int argc, char *argv[])
{

    internodeInit("2014-02-09" , NULL, NULL);
    
 
    
    double totalusage = get_usage(HISTORYXML, "traffic", "total");
    printf("total usage %f MB\n",totalusage);
    char *rollover = get_attrib_val(USAGEXML, "traffic", "rollover");
    double quota = atof((char *) get_attrib_val(USAGEXML, "traffic", "quota"));
    double current_usage = atof((char *) get_element_content(USAGEXML, "traffic"));
    printf("total Quota: %0.2lf GB\n" ,quota/MBITS/MTOGB);
    printf("Current usage: %0.2lf\n" ,current_usage/MBITS/MTOGB);
    printf("Rollover Date: %s\n" ,rollover);
    
    return 0;
}


/* main.c ends here */




















