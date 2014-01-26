/* xmlparsing.c --- xml parsing of the internode return data
 *
 * Filename: xmlparsing.c
 * Description:
 * Author: mygnu
 * Maintainer:
 * Created: Tue Jan 21 22:44:20 2014 (+1030)
 * Version:
 * Package-Requires: ()
 * Last-Updated: Sun Jan 26 15:19:14 2014 (+1030)
 *           By: mygnu
 *     Update #: 17
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
#include "xmlparsing.h"
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <stdio.h>
#include <string.h>


static xmlDocPtr
getdoc (char *docname);

static xmlXPathObjectPtr
getnodeset (xmlDocPtr doc, xmlChar *xpath);


/* takes two pointers to string as name of the document and element */
char *
getElementContent(char * docname, char * elementname)
{
    char  element[50] = "//"; 	/* needs // prefix for some reason */
    strcat(element, elementname);
    
    xmlDocPtr doc = getdoc(docname); /* xmlDocPtr to the document */
    xmlChar *xpath = (xmlChar*) element; /* is the name of the element */

    xmlXPathObjectPtr result = getnodeset (doc, xpath);
    xmlNodeSetPtr nodeset;
    int i;
    xmlChar *keyword; 		/* could possibly use malloc() */

    if (result)                 /* if not NULL */
    {
        nodeset = result->nodesetval;
        for (i=0; i < nodeset->nodeNr; i++)
        {
            keyword = xmlNodeListGetString
                (doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);

            return (char *)keyword;
            xmlFree(keyword);
        }
        xmlXPathFreeObject (result);
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return NULL;
}



/* takes pointer to a string of the name of the document */
static xmlDocPtr
getdoc (char *docname)
{
    xmlDocPtr doc;
    doc = xmlParseFile(docname);

    if (doc == NULL ) {
        fprintf(stderr,"Document not parsed successfully. \n");
        return NULL;
    }

    return doc;
}


/* takes a xmlDocPtr to the xml document and a xmlChar string pointer as
 an element name */
static xmlXPathObjectPtr
getnodeset (xmlDocPtr doc, xmlChar *xpath)
{

    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;

    context = xmlXPathNewContext(doc); /* initialize the context */
    if (context == NULL)               /* test if null */
    {
        printf("Error in xmlXPathNewContext\n");
        return NULL;
    }
    result = xmlXPathEvalExpression(xpath, context); /* evaluates XPath location
                                                        in the given context */
    xmlXPathFreeContext(context); /* free the context memory */
    if (result == NULL)
    {
        printf("Error in xmlXPathEvalExpression\n");
        return NULL;
    }
    if(xmlXPathNodeSetIsEmpty(result->nodesetval))
    {
        xmlXPathFreeObject(result);
        printf("There is no element of this name \n");
        return NULL;
    }
    return result;
}



/* xmlparsing.c ends here */








