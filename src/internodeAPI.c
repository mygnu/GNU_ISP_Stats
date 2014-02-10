/* internodeAPI.c --- handle internode APIs
 *
 * Filename: internodeAPI.c
 * Description:
 * Author: mygnu
 * Maintainer:
 * Created: Sun Jan 19 23:40:19 2014 (+1030)
 * Version:
 * Package-Requires: ()
 * Last-Updated: Mon Feb 10 18:11:15 2014 (+1030)
 *           By: mygnu
 *     Update #: 64
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
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>
#include "credentials.h"
#include "internodeAPI.h"
#include "xmlparsing.h"

void
internodeInit(char *startDate, char *stopDate)
{
    char baseurl[80] = "https://customer-webtools-api.internode.on.net\
/api/v1.5/";
    char baseopts[80] = "start=";
/* get the first xml for the internode use rid */
    getNodeXml(baseurl, BASEXML, NULL);

    char serviceID[40];
    getElementContent(BASEXML, "service", serviceID);
    strcat(baseurl, serviceID);

    char *history = (char*)malloc(sizeof(char) * 128);
    strcpy(history, baseurl);
    strcat(history,"/history/");

    char *usage = (char*)malloc(sizeof(char) * 128);
    strcpy(usage, baseurl);
    strcat(usage,"/usage/");

    strcat(baseopts,startDate);
    strcat(baseopts,"&stop=");
    strcat(baseopts,stopDate);
    strcat(baseopts, "&verbose=1"); /*"start=2014-01-01&stop=2014-02-01&verbose=1"*/

    getNodeXml(usage, USAGEXML, NULL); 
    getNodeXml(history, HISTORYXML, baseopts); 

    free(usage);
    free(history);

}

static int
chkFileTime(char *file_name)
{
    time_t curtime;/* long int time format represents no
                      of seconds since 00:00:00 Jan 1 1970*/
    struct stat filestat;/* a system struct that is defined to store
                            information about files. It is used in
                            several system calls, including fstat, lstat,
                            and stat. */
    if(access(file_name, F_OK) == 0) /* file exists */
    {
        bzero(&filestat,sizeof(filestat));
        if(stat(file_name,&filestat) != 0)/* stat is a system call to
                                             determine information about
                                             a file based on its file path.*/
        {
            printf("stat() failed with errno %d\n", errno);
            exit(-1);
        }
        time(&curtime);/* current time in seconds */
        /* difference between current time and file modification time */
        double timetest = difftime(curtime, filestat.st_mtime);

        if (timetest < 86400)   /* if less than a day old return false */
            return 0;
    }
    return 1;
}

/* gets the page and writes the content to a file */
void getNodeXml( char *url, char *file_name, char *extra_opts)
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
        if (extra_opts != NULL)
        {
            curl_easy_setopt(easyhandle, CURLOPT_POSTFIELDS, extra_opts);
        }


        /* set to copy content to the file */
        if(chkFileTime(file_name)) /* if file doesn't exist or more than
                                      a day old*/
        {
            FILE *file = fopen(file_name, "w");
            curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, file);

            curl_easy_perform(easyhandle); /* Perform the request */
            fclose(file);           /* close the file */
        }
    }
    curl_easy_cleanup(easyhandle); /* Libcurl cleanup */

}



/* internodeAPI.c ends here */
