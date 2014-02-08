/* credentials.c --- functions to get user credentials and save it in a text file
 *
 * Filename: credentials.c
 * Description:
 * Author: mygnu
 * Maintainer:
 * Created: Sun Jan 19 19:57:52 2014 (+1030)
 * Version: 0.001
 * Package-Requires: ()
 * Last-Updated: Sat Feb  8 15:20:56 2014 (+1030)
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
#include <stdio.h>
#include <unistd.h>
#include "credentials.h"


void getCredentials( char *uname, char *secret)
/* gets credentials from file if exists.
 or calls fromKeboard and writes to the file*/
{
    FILE *crFile;
    char filename[] = "tmp/unamepwd";
    if (access(filename, F_OK) != -1)
    {   /* file exists */
        if((crFile = fopen(filename,"r")) != NULL)
        {
            fscanf(crFile, "%s %s", uname, secret); /* read username and
						     password to the variables*/
            fclose(crFile);         /* close file */
	}
        else                    /* if not able to open the file print error */
            fprintf(stderr, "Not able to open the credential file %s\n", filename);
    }

    else
    {				/* if file doesn't exist */
        if((crFile = fopen(filename,"w")) != NULL)
        {
            fromKeboard(uname, secret); /* get the credential from the keyboard */

            fprintf(crFile, "%s %s",uname, secret); /* write the username and
                                                        password to the file*/
            fclose(crFile);         /* close file */
        }
	else                    /* if not able to open the file print error */
            fprintf(stderr, "Not able to open the credential file %s\n", filename);
    }
}


void fromKeboard(char *uname, char *secret)
/* gets username and password from user input as strings */
{
    printf("Enter your Internode Username: ");
    scanf("%s", uname);
    printf("Enter your Inetrnode Password: ");
    scanf("%s", secret);
}

/* credentials.c ends here */
