/* xmlparsing.h --- 
 * 
 * Filename: xmlparsing.h
 * Description: 
 * Author: mygnu
 * Maintainer: 
 * Created: Wed Jan 22 10:16:40 2014 (+1030)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Tue Feb 11 15:11:48 2014 (+1030)
 *           By: mygnu
 *     Update #: 36
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
/* takes pointer to a string of the name of the document */

/* takes two pointers to string as name of the document and element
 returns char * content */
#define MBITS 1000000
#define MTOGB 1000
char *
get_attrib_val(char *docname, char *elementName , char *attribName);

double
get_usage(char *docname, char *elementName, char *direction);

char *
get_element_content(char *docname, char *elementName);
/* xmlparsing.h ends here */















