#pragma once

#include <iostream>
#include <string>

#include <libxml/parser.h>
#include <libxml/xmlschemas.h>
#include <libxml/xpath.h>

class XMLConfigLoader
{
public:
    XMLConfigLoader( const std::string& xmlPath, const std::string& schemaPath );
    ~XMLConfigLoader();

    bool loadAndValidate();
    std::string getAppName( const std::string& xpathExpr );

private:
    xmlDocPtr doc;
    xmlSchemaPtr schema;
    xmlSchemaValidCtxtPtr schemaValidCtxt;

    std::string xmlFilePath;
    std::string schemaFilePath;

    bool isLoadedAndValid;
};
