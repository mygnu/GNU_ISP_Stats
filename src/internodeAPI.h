/* internodeAPI.h --- 
 * 
 * Filename: internodeAPI.h
 * Description: 
 * Author: mygnu
 * Maintainer: 
 * Created: Sun Jan 19 23:44:02 2014 (+1030)
 * Version: 
 * Package-Requires: ()
 * Last-Updated: Tue Feb 11 14:23:57 2014 (+1030)
 *           By: mygnu
 *     Update #: 24
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
#define BASEXML "tmp/nodeservice.xml"
#define USAGEXML "tmp/nodeusage.xml"
#define HISTORYXML "tmp/nodehistory.xml"

void
internodeInit(char *startDate, char *stopDate, char *days_count);

void
getNodeXml( char *url, char *file_name, char *extra_opts);

/* gets the page and writes the content to a file */
    

/* internodeAPI.h ends here */








