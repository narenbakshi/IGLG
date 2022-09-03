/**
 * @file configread.c
 * @brief File containing functionality to read configurations.
 *
 * This file is used to read configurations from the config path .
 * It read the xml file and creates a config structure.
 * 
 * @author Naren Bakshi
 */ 
#include "configread.h"


Config configReader(void)
{

	struct config re;
	
  xmlDoc *doc = NULL;
  xmlNode *root_element = NULL; 

	/*parse the file and get the DOM */
  doc = xmlReadFile(CONFIGPATH, NULL, 0);
	if (doc == NULL) {
    printf("Could not parse the XML file");
  }

	root_element = xmlDocGetRootElement(doc);
  xmlNode *cur_node = NULL;

 	for (cur_node = root_element->xmlChildrenNode; cur_node; cur_node = cur_node->next) {
  	if (cur_node->type == XML_ELEMENT_NODE) 
		{
			if(!xmlStrcmp(cur_node->name,"PID"))
			{
				re.pidr = xmlNodeGetContent(cur_node);
				
			}
			else if(!xmlStrcmp(cur_node->name,"PNAME"))
			{
				re.pname = xmlNodeGetContent(cur_node);	
			}
			else if(!xmlStrcmp(cur_node->name,"WINDOW_SIZE"))
			{
				re.windowsize = xmlNodeGetContent(cur_node);
			}
			else if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"DB_HOST")))
			{
				re.dbhost = xmlNodeGetContent(cur_node);
			}
			else if(!xmlStrcmp(cur_node->name,"BROKER_IP")) 
			{
				re.brokerip= xmlNodeGetContent(cur_node); 
			}
			else if(!xmlStrcmp(cur_node->name,"STORAGE_MODE"))
			{
				re.storagemode = xmlNodeGetContent(cur_node);
			}
			else if(!xmlStrcmp(cur_node->name,"LOGGINGLEVEL"))
			{
				re.logginglevel = xmlNodeGetContent(cur_node);
			}
			else if(!xmlStrcmp(cur_node->name,"MODULEOPTION"))
			{
				re.moduleoption = xmlNodeGetContent(cur_node);
			}
			else if(!xmlStrcmp(cur_node->name,"MIDDLEWARE"))
			{
				re.middleware = xmlNodeGetContent(cur_node);
			}
			else if(!xmlStrcmp(cur_node->name,"TRANSFER"))
			{
				re.transer = xmlNodeGetContent(cur_node);
			}
			else if(!xmlStrcmp(cur_node->name,"BENCHMARKING_TIME"))
			{
				re.benchmarkTime = xmlNodeGetContent(cur_node);
			}
		}
	}

	return re;
}