/* main.c --- main.c
 *
 * Filename: main.c
 * Description:
 * Author:
 * Maintainer:
 * Created: Wed Feb 19 10:24:52 2014 (+1030)
 * Version:
 * Package-Requires: ()
 * Last-Updated:
 *           By:
 *     Update #: 0
 * URL:
 * Doc URL:
 * Keywords:
 * Compatibility:
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change Log:
 *
 *
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
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

#ifndef NOTAUSER
#include "internodeAPI.h"
#endif


int
main(int argc, char *argv[])
{
    char *days = "2000";

#ifndef NOTAUSER
    internodeInit(NULL , NULL, days); /* gets xml files from internode ISP */
#endif

    double totalusage = get_usage(HISTORYXML, "traffic", "total");
    printf("total Usage for last %s days %0.2f GB\n",days, totalusage/MTOGB);
    char *rollover = get_attrib_val(USAGEXML, "traffic", "rollover");
    double quota = atof((char *)
                        get_attrib_val(USAGEXML, "traffic", "quota"));
    double current_usage = atof((char *)
                                get_element_content(USAGEXML, "traffic"));


    printf("Monthly Quota: %0.2lf GB\n" ,quota/MBITS/MTOGB);
    printf("This month usage: %0.2lf GB\n" ,current_usage/MBITS/MTOGB);
    printf("Rollover Date: %s\n" ,rollover);
    return 0;
}


/* main.c ends here */
