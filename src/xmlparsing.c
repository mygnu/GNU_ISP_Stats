/* xmlparsing.c --- xml parsing of the internode return data
 *
 * Filename: xmlparsing.c
 * Description:
 * Author: mygnu
 * Maintainer:
 * Created: Tue Jan 21 22:44:20 2014 (+1030)
 * Version:
 * Package-Requires: ()
 * Last-Updated: Sat Feb  8 16:06:45 2014 (+1030)
 *           By: mygnu
 *     Update #: 48
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
#define MBITS 1000000

static xmlDocPtr
getdoc (char *docname);

static xmlXPathObjectPtr
getnodeset (xmlDocPtr doc, xmlChar *xpath);


/* takes two pointers to string as name of the document and element */
void
getElementContent(char *docname, char *elementName , char * retStr)
{
    char  element[50] = "//";       /* needs // prefix for some reason */
    strcat(element, elementName);

    xmlDocPtr doc = getdoc(docname); /* xmlDocPtr to the document */
    xmlChar *xpath = (xmlChar*) element; /* is the name of the element */

    xmlXPathObjectPtr result = getnodeset (doc, xpath);
    xmlNodeSetPtr nodeset;
    xmlChar *keyword;               /* could possibly use malloc() */

    if (result)                 /* if not NULL */
    {
        nodeset = result->nodesetval;
        keyword = xmlNodeListGetString
            (doc, nodeset->nodeTab[0]->xmlChildrenNode, 1);

        xmlXPathFreeObject (result);
	strcpy(retStr, (char *)keyword);
        xmlFree(keyword);
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

double getUsage(char *docname, char *elementName, int startDay, int endDay)
{

     char  element[50] = "//";       /* needs // prefix for some reason */
    strcat(element, elementName);

    xmlDocPtr doc = getdoc(docname); /* xmlDocPtr to the document */
    xmlChar *xpath = (xmlChar*) element; /* is the name of the element */

    xmlXPathObjectPtr result = getnodeset (doc, xpath);
    xmlNodeSetPtr nodeset;
    xmlChar *element_content;

    doc = getdoc(docname);
    result = getnodeset (doc, xpath); /* xmlXpathObPtr in the given document */
    double total = 0;
    startDay = (startDay + 365);
    endDay = (endDay + 365);
    if (result) /* if not NULL */
    {
        nodeset = result->nodesetval;
        for (int i=0; i < nodeset->nodeNr; i++)
        {

            element_content = xmlNodeListGetString
                (doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);

            if(i<=startDay && i>=endDay)
            {
                printf("usage of the day %d element: %s\n", i, element_content);
                total = total + (atof((char *)element_content) / MBITS);
            }
            xmlFree(element_content);
        }
        xmlXPathFreeObject (result);
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return total;
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
