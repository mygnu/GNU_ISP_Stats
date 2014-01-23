/* main.c --- main.c
 *
 * Filename: main.c
 * Description:
 * Author: mygnu
 * Maintainer:
 * Created: Sun Jan 19 20:16:55 2014 (+1030)
 * Version:
 * Package-Requires: ()
 * Last-Updated: Fri Jan 24 09:13:18 2014 (+1030)
 *           By: mygnu
 *     Update #: 46
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
#include <stdio.h>
#include "credentials.h"
#include "internodeAPI.h"
#include "xmlparsing.h"

int
main(int argc, char *argv[])
{
    char uname[50], secret[50];

    getCredentials( uname, secret);

    printf("%s %s\n", uname, secret );


char * baseurl = "https://customer-webtools-api.internode.on.net/api/v1.5/";
char * xmlfile = "tmp/nodeservice.xml";
/* get the first xml for the internode userid */

getNodeXml(baseurl, xmlfile);
    return 0;
}


/* main.c ends here */






