/* internodeAPI.c --- handle internode APIs
 *
 * Filename: internodeAPI.c
 * Description:
 * Author: mygnu
 * Maintainer:
 * Created: Sun Jan 19 23:40:19 2014 (+1030)
 * Last-Updated: Sun Mar  9 22:03:40 2014 (+1030)
 *           By: mygnu
 *     Update #: 76
 *
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
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

#ifndef NOTAUSER

void
internodeInit(char *start_date, char *stop_date, char *days_count)
{
    char baseurl[80] = "https://customer-webtools-api.internode.on.net\
/api/v1.5/";
    char usage_opts[128] = "verbose=1";
    if (start_date != NULL)
    {
        strcat(usage_opts,"&start=");
        strcat(usage_opts,start_date);
    }
    if (stop_date != NULL)
    {
	strcat(usage_opts,"&stop=");
	strcat(usage_opts,stop_date);
    }
    if (days_count != NULL)
    {
	strcat(usage_opts,"&count=");
	strcat(usage_opts,days_count);
    }

    /*"start=2014-01-01&stop=2014-02-01&verbose=1"*/

/* get the xml files the internode */
    confPaths *xmlfiles = pathFunc(); 
    getNodeXml(baseurl, xmlfiles->basexml, NULL);

    char *service_id = get_element_content(xmlfiles->basexml, "service");
    strcat(baseurl, service_id);

    char *history = (char*)malloc(sizeof(char) * 128);
    strcpy(history, baseurl);
    strcat(history,"/history/");

    char *usage = (char*)malloc(sizeof(char) * 128);
    strcpy(usage, baseurl);
    strcat(usage,"/usage/");


    getNodeXml(usage, xmlfiles->usagexml, "verbose=1");
    getNodeXml(history, xmlfiles->historyxml, usage_opts);

    free(service_id);
    free(usage);
    free(history);
    free(xmlfiles);

}

static int
chkFileDir(char *file_name)
{
    mkdir("tmp",0777);
    
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
    if (!getCredentials(uname, passwd))
	exit(0);

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
        /* if(chkFileDir(file_name)) */ /* if file doesn't exist or more than
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

#endif


/* internodeAPI.c ends here */

