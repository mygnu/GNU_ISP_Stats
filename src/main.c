/* main.c --- main.c
 *
 * Filename: main.c
 * Description:
 * Created: Wed Feb 19 10:24:52 2014 (+1030)
 * Last-Updated:
 *           By:
 *     Update #: 7
 */ 

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 */

/* Code: */

/* define NOTAUSER here to compile withot internode account
 * make sure you have the following files in tmp folder
 * BASEXML "tmp/nodeservice.xml"
 * USAGEXML "tmp/nodeusage.xml"
 * HISTORYXML "tmp/nodehistory.xml"
 */

#define USER
#include <stdio.h>
#include <stdlib.h>
#include "xmlparsing.h"
#include "credentials.h"
#ifndef NOTAUSER
#include "internodeAPI.h"
#endif


int
main(int argc, char *argv[])
{
    char *days = "31";

#ifndef NOTAUSER
    internodeInit(NULL , NULL, days); /* gets xml files from internode ISP */
#endif
    confPaths *xmlfiles = pathFunc();
    double totalusage = get_usage(xmlfiles->historyxml, "traffic", "total");
    printf("total Usage for last %s days %0.2f GB\n",days, totalusage/MBTOGB);
    char *rollover = get_attrib_val(xmlfiles->usagexml, "traffic", "rollover");
    double quota = atof((char *)
                        get_attrib_val(xmlfiles->usagexml, "traffic", "quota"));
    double current_usage = atof((char *)
                                get_element_content(xmlfiles->usagexml, "traffic"));

    printf("Monthly Quota: %0.2lf GB\n" ,quota/MBITS/MBTOGB);
    printf("This month usage: %0.2lf GB\n" ,current_usage/MBITS/MBTOGB);
    printf("Rollover Date: %s\n" ,rollover);
    return 0;
}


/* main.c ends here */



