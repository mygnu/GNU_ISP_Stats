/* credentials.c --- functions to get user credentials and save it in a text file
 *
 * Filename: credentials.c
 * Description:
 * Created: Sun Jan 19 19:57:52 2014 (+1030)
 * Last-Updated: Sun Mar  9 22:20:53 2014 (+1030)
 *           By: mygnu
 *     Update #: 53
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 */

/* Code: */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <confuse.h>
#include "credentials.h"
#define SUCCESS 1
#define ERROR 0

#define CONFDIR "/.gisps.d/"
#define CONFFILE "gisps.conf"
#define BASEXML "nodeservice.xml"
#define USAGEXML "nodeusage.xml"
#define HISTORYXML "nodehistory.xml"

#define INITCONFIG "\
/* This is the Sample Configuration file for gisps  *\n\
 * Please enter your internode username and pasword *\n\
 * ________________________________________________ */\n\n\
user=     \t\"username\"\n\
password= \t\"Password\"\n"


static int dirExists(const char *path)
{
    struct stat info;
    if (stat(path, &info) !=0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;

}

confPaths *pathFunc()
{
    confPaths *path = malloc(sizeof(confPaths));
    /* path->conf = malloc(sizeof(char) * 64); */
    /* path->basexml = malloc(sizeof(char) * 64); */
    /* path->usagexml = malloc(sizeof(char) * 64); */
    /* path->historyxml = malloc(sizeof(char) * 64); */
    /* getting the home dir path */
    if (!strcpy(path->conf, getenv("HOME"))) /* if copying stirng returns NULL */
    {
        struct passwd* pwd = getpwuid(getuid());
        if (pwd){
            strcpy(path->conf, pwd->pw_dir);
        }
        else {
            free(path);
            return NULL;
        }
    }
    strcpy(path->basexml, path->conf);
    strcpy(path->usagexml, path->conf);
    strcpy(path->historyxml, path->conf);

    /* concating the cony dir to the path */
    strcat(path->conf, CONFDIR);
    strcat(path->basexml, CONFDIR);
    strcat(path->usagexml, CONFDIR);
    strcat(path->historyxml, CONFDIR);

    if(!dirExists(path->conf))
    {
        if (mkdir(path->conf,0760) == -1)
        {
            fprintf(stderr, "Could not create %s\n" ,path->conf);
            free(path);
            return NULL;
        }
    }
    strcat(path->conf, CONFFILE);
    strcat(path->basexml, BASEXML);
    strcat(path->usagexml, USAGEXML);
    strcat(path->historyxml, HISTORYXML);

    return path;
}




static int chkConfFile()
{
    /* must be freed when finished using */

    /* add the config dir to it */
    confPaths *confPath = pathFunc(); /* free it in the end */


    /* if file doesn't exist */
    if(access(confPath->conf, F_OK) != -1) /* if file exists */
    {
        free(confPath);
        return SUCCESS;
    }
    else
    {
        FILE *crFile;
        if((crFile = fopen(confPath->conf,"w")) != NULL)
        {
            //            fprintf(crFile, INITCONFIG); /* write the header of the config file */
            fclose(crFile);         /* close file */
            free(confPath);
            return SUCCESS;
        }
        else
        {
            fclose(crFile);
            fprintf(stderr,"Could not create file %s\n", confPath->conf);
            free(confPath);
            return ERROR;
        }
    }

    free(confPath);
    return ERROR;

}

static void fromKeboard(char *uname, char *secret)
/* gets username and password from user input as strings */
{
    printf("Enter your Internode Username: ");
    scanf("%s", uname);
    printf("Enter your Inetrnode Password: ");
    scanf("%s", secret);
}


int  getCredentials(char *uname, char *password)
{
    confPaths *configPath = pathFunc();
    if((!configPath->conf) && !chkConfFile())
    {
        fprintf(stderr,"config file pathFunc error.");
        return ERROR;
    }

    cfg_opt_t opts[] =
        { 
            CFG_STR("user", "test", CFGF_NONE ),
            CFG_STR("password", "test", CFGF_NONE ),
            CFG_END()
        };
    cfg_t *cfg;
    cfg = cfg_init(opts, CFGF_NONE);
    if (cfg_parse(cfg, configPath->conf) == CFG_PARSE_ERROR)
        return ERROR;

    if (!(strcmp(cfg_getstr(cfg, "user"), "test")) || /* if default value */
        !(strcmp(cfg_getstr(cfg, "password"), "test")))
    {
        fromKeboard(uname, password);
        cfg_setstr(cfg,"user", uname);
        cfg_setstr(cfg,"password",password);
        FILE *fp = fopen(configPath->conf, "w");
        cfg_print(cfg, fp);
        fclose(fp);
    }


    strcpy(uname, cfg_getstr(cfg, "user"));
    strcpy(password, cfg_getstr(cfg, "password"));

    cfg_free(cfg);
    free(configPath);           /* don't forget to free the heap */
    return SUCCESS;

}

/* credentials.c ends here */
