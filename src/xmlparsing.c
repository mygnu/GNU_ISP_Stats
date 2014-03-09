/* xmlparsing.c --- xml parsing of the internode return data
 *
 * Filename: xmlparsing.c
 * Description:
 * Created: Tue Jan 21 22:44:20 2014 (+1030)
 * Last-Updated: Fri Mar  7 23:46:12 2014 (+1030)
 *           By: mygnu
 *     Update #: 76
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
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

/* takes two pointers to string as name of the document and element */
char *
get_element_content(char *docname, char *elementName)
{
    char  element[50] = "//";       /* needs // prefix for some reason */
    strcat(element, elementName);

    xmlChar *xpath = (xmlChar*) element; /* is the name of the element */
    xmlDocPtr doc = getdoc(docname); /* xmlDocPtr to the document */

    xmlXPathObjectPtr result = getnodeset (doc, xpath);
    xmlNodeSetPtr nodeset;
    xmlChar *keyword = (xmlChar*)malloc(sizeof(xmlChar) * 64); 

    if (result)                 /* if not NULL */
    {
        nodeset = result->nodesetval;
        keyword = xmlNodeListGetString
            (doc, nodeset->nodeTab[0]->xmlChildrenNode, 1);
        xmlXPathFreeObject (result);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return (char*)keyword;
    }
    xmlXPathFreeObject (result);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return NULL;
}

char*
get_attrib_val(char *docname, char *elementName , char *attribName)
{
    char  element[50] = "//";       /* needs // prefix for some reason */
    strcat(element, elementName);
    xmlChar *xpath = (xmlChar*) element; /* is the name of the element */
    xmlDocPtr doc = getdoc(docname); /* xmlDocPtr to the document */
    xmlXPathObjectPtr result = getnodeset (doc, xpath);
    xmlNodeSetPtr nodeset;
    
    if (result)                 /* if not NULL */
    {
        nodeset = result->nodesetval;
        xmlChar *prop = (xmlChar*)malloc(sizeof(xmlChar) * 64);
        prop = xmlGetProp(nodeset->nodeTab[0], (xmlChar *)attribName);
        xmlXPathFreeObject (result);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return (char*)prop;
    }
    xmlXPathFreeObject (result);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return NULL;

}



double
get_usage(char *docname, char *elementName, char *type)
{
    char *attrib;
    if ((!strcmp(type, "up")) || (!strcmp(type, "down")))
    {
        attrib = "direction";
    }
    else if (!strcmp(type, "total"))
    {
        attrib = "name";
    }
    else
    {
        printf("please use 'up' 'down' or 'total' as usage type\n");
        return 0;
    }


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

    if (result) /* if not NULL */
    {
        nodeset = result->nodesetval;
        for (int i=0; i < nodeset->nodeNr; i++)
        {

            element_content = xmlNodeListGetString
                (doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);
            xmlChar *prop = (xmlChar*)malloc(64);
            prop = xmlGetProp(nodeset->nodeTab[i],(xmlChar*)attrib) ;

            if(xmlStrEqual(prop,(xmlChar *)type))
            {
		total = total + (atof((char *)element_content) / MBITS);
            }
            free(prop);
            xmlFree(element_content);
        }
        xmlXPathFreeObject (result);
    }
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return total;
}



/* xmlparsing.c ends here */




