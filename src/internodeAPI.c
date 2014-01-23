/* internodeAPI.c --- handle internode APIs
 *
 * Filename: internodeAPI.c
 * Description:
 * Author: mygnu
 * Maintainer:
 * Created: Sun Jan 19 23:40:19 2014 (+1030)
 * Version:
 * Package-Requires: ()
 * Last-Updated: Fri Jan 24 09:16:23 2014 (+1030)
 *           By: mygnu
 *     Update #: 31
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
#include <curl/curl.h>
#include "credentials.h"
#include "internodeAPI.h"


/* gets the page and writes the content to a file */
void getNodeXml( char *url, char *file_name)
{
    char uname[50];
    char passwd[50];
    /* get user name and password */
    getCredentials(uname, passwd);

    CURL *easyhandle = curl_easy_init(); /* initialize curl */

    if(easyhandle)              /* if initialized */
    {
        curl_easy_setopt(easyhandle, CURLOPT_URL, url); /* set url */

        /* if a site is redirected, tell lib curl to follow redirection */
        // curl_easy_setopt(easyhandle, CURLOPT_FOLLOWLOCATION, 1L);

/* set username and password options */
        curl_easy_setopt(easyhandle, CURLOPT_USERNAME, uname);
        curl_easy_setopt(easyhandle, CURLOPT_PASSWORD, passwd);

/* set to copy content to the file */
        FILE *file = fopen(file_name, "w");
        curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, file);

        curl_easy_perform(easyhandle); /* Perform the request */
        fclose(file);           /* close the file */

        curl_easy_cleanup(easyhandle); /* Libcurl cleanup */

    }

}




/* internodeAPI.c ends here */
