#include "config.h"

XMLConfigLoader::XMLConfigLoader( const std::string& xmlPath, const std::string& schemaPath )
    : doc( nullptr )
    , schema( nullptr )
    , schemaValidCtxt( nullptr )
    , xmlFilePath( xmlPath )
    , schemaFilePath( schemaPath )
    , isLoadedAndValid( false )
{
    xmlInitParser();
    LIBXML_TEST_VERSION
}

XMLConfigLoader::~XMLConfigLoader()
{
    if( schemaValidCtxt ) {
        xmlSchemaFreeValidCtxt( schemaValidCtxt );
    }
    if( schema ) {
        xmlSchemaFree( schema );
    }
    if( doc ) {
        xmlFreeDoc( doc );
    }
    xmlCleanupParser();
}

bool XMLConfigLoader::loadAndValidate()
{
    doc = xmlReadFile( xmlFilePath.c_str(), nullptr, 0 );
    if( doc == nullptr ) {
        std::cerr << "Error: could not parse file " << xmlFilePath << "\n";
        return false;
    }

    xmlSchemaParserCtxtPtr schemaParserCtxt = xmlSchemaNewParserCtxt( schemaFilePath.c_str() );
    schema = xmlSchemaParse( schemaParserCtxt );
    xmlSchemaFreeParserCtxt( schemaParserCtxt );

    if( schema == nullptr ) {
        std::cerr << "Error: could not parse schema\n";
        return false;
    }

    schemaValidCtxt = xmlSchemaNewValidCtxt( schema );
    if( xmlSchemaValidateDoc( schemaValidCtxt, doc ) != 0 ) {
        std::cerr << "Error: XML does not conform to the schema\n";
        return false;
    }

    isLoadedAndValid = true;
    return true;
}

std::string XMLConfigLoader::getAppName( const std::string& xpathExpr )
{
    if( !isLoadedAndValid ) {
        std::cerr << "Error: XML file not loaded or not valid\n";
        return "";
    }

    xmlXPathContextPtr xpathCtx = xmlXPathNewContext( doc );
    if( xpathCtx == nullptr ) {
        std::cerr << "Error: unable to create new XPath context\n";
        return "";
    }

    xmlXPathObjectPtr xpathObj = xmlXPathEvalExpression( (const xmlChar*)xpathExpr.c_str(), xpathCtx );
    if( xpathObj == nullptr ) {
        std::cerr << "Error: unable to evaluate XPath expression\n";
        xmlXPathFreeContext( xpathCtx );
        return "";
    }

    std::string appName;
    xmlNodeSetPtr nodes = xpathObj->nodesetval;

    if( nodes != nullptr && nodes->nodeNr > 0 ) {
        xmlNodePtr node = nodes->nodeTab[0];
        appName = (const char*)xmlNodeGetContent( node );
    }
    else {
        std::cerr << "Error: app name not found\n";
    }

    xmlXPathFreeObject( xpathObj );
    xmlXPathFreeContext( xpathCtx );
    return appName;
}
