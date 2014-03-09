/* credentials.h --- header file for defs and other includes
 * 
 * Filename: credentials.h
 * Created: Sun Jan 19 20:03:12 2014 (+1030)
 * Last-Updated: Sun Mar  9 22:08:10 2014 (+1030)
 *           By: mygnu
 *     Update #: 25
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 */

/* Code: */
typedef struct
{
    char conf[64];
    char basexml[64];
    char usagexml[64];
    char historyxml[64];
    
}confPaths;

confPaths *pathFunc();

int getCredentials(char *uname, char *secret);

/* get the credentials from the keyboard */

/* credentials.h ends here */













