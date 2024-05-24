#include "graphh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Graphe* createGraph2(typed(json_array)* nodesIdArray, const typed(json_element) jsonContent, const char* fileName)
{
	Graphe* graph = (Graphe*)malloc(sizeof(Graphe));
	graph->order = (int)nodesIdArray->count;

	graph->arcsList = (ListSuccessor*)malloc(sizeof(ListSuccessor));
	graph->arcsList->size = 0;
	graph->arcsList->first = NULL;
	graph->arcsList->next = NULL;
	graph->arcsList->node = NULL;

	ListSuccessor *nodeList = graph->arcsList;
	for (int i = 0; i < graph->order; i++)
	{
		Arc* nodeCurrent = (Arc*)malloc(sizeof(Arc));
		typed(json_element) nodeId = nodesIdArray->elements[i];
		int nameLength = strlen(nodeId.value.as_string);
		nodeCurrent->id = (int)malloc(nameLength);
		strcpy(nodeCurrent->id, nodeId.value.as_string);
		//nodeCurrent->data = i * 10;
		nodeCurrent->x = -1;
		nodeCurrent->y = -1;
		nodeCurrent->adjacent = NULL;

		nodesList->node = nodeCurrent;
		nodesList->first = NULL;
		nodesList->size = 0;

		nodesList->next = (ListSuccessor*)malloc(sizeof(ListSuccessor));
		nodeList = nodesList->next;
		nodeList->node = NULL;
		nodeList->f = NULL;
		nodeList->size = 0;
		nodeList->next = NULL;
	}

	graph->name = (char*)malloc(strlen(fileName));
	typed(json_element) bOriented = getJsonElementFromName(jsonContent, "oriented");
	graph->oriented = bOriented.value.as_number.value.as_long;
	strcpy(graph->name, fileName);

	return graph;
}


Graphe* jsonCreateGraphFromFile2(const char* jsonFile)
{
	//json structure : 
	//nbNodes is an integer containing the number of nodes
	//oriented is a boolean containing if the graph is oriented or not
	//each node is a dictionary whose key is its id and its value contains its coordinates {x, y} and its adjencyList
	//The adjencyList is an n-element array of 2-elements array : first element is the id of the connected node and the second is the weight of the edge
	typed(json_element) jsonContent = interpretJSon(jsonFile);
	typed(json_element) nodesIds = getJsonElementFromName(jsonContent, "nodesIds");

	typed(json_array)* nodesIdArray = nodesIds.value.as_array;
	Graphe* graph = createGraph2(nodesIdArray, jsonContent, jsonFile);


	// Get the nodes from the graph and fill the information from the json file
	ListSuccessor* curNodeList = graph->arcsList;
	for (int i = 0; i < graph->order; i++)
	{
		//retrieve the node id
		//With its id, get the dictionary containing the node information
		typed(json_element) nodeId = nodesIdArray->elements[i];
		typed(json_element) nodeAsObject = getJsonElementFromName(jsonContent, nodeId.value.as_string);

		//From this dictionnary, get the x and y coordinates of the node
		Arc* curNode = curNodeList->node;
		curNode->x = -1;
		typed(json_element) nodeX = getJsonElementFromName(nodeAsObject, "x");
		curNode->x = (float)nodeX.value.as_number.value.as_double;

		curNode->y = -1;
		typed(json_element) nodeY = getJsonElementFromName(nodeAsObject, "y");
		curNode->y = (float)nodeY.value.as_number.value.as_double;

		//From this dictionnary, get the adjency list of the node
		if (hasElementWithName(nodeAsObject, "adjencyList"))
		{

			typed(json_element) connectedNodeIds = getJsonElementFromName(nodeAsObject, "adjencyList");

			typed(json_array)* values = connectedNodeIds.value.as_array;
			char** adjencents = malloc(sizeof(char*) * values->count);
			long* adjencentsWeight = malloc(sizeof(long) * values->count);
			//For each element of the adjency list, get the id of the connected node and the weight of the edge
			for (int j = 0; j < values->count; j++) {
				typed(json_element) element = values->elements[j];
				typed(json_array)* edgeInfos = element.value.as_array;
				if (edgeInfos != NULL)
				{
					if (edgeInfos->elements[0].value.as_number.value.as_long != -1) {
						adjencents[j] = (char*)malloc(strlen(edgeInfos->elements[0].value.as_string));
						strcpy(adjencents[j], edgeInfos->elements[0].value.as_string);
						adjencentsWeight[j] = edgeInfos->elements[1].value.as_number.value.as_long;
					}
				}
			}

			ListSuccessor* adjencyList = (ListSuccessor*)malloc(sizeof(ListSuccessor));
			curNode->adjacent = adjencyList;
			adjencyList->node = NULL;
			adjencyList->first = NULL;
			adjencyList->size = 0;
			adjencyList->next = NULL;
			createAdjacentList2(graph, adjencyList, adjencents, adjencentsWeight, (int)values->count);
		}
		curNodeList = curNodeList->next;

	}

	//json_print(&element, 2);
	//json_free(&element);
	return graph;
}

void createAdjacentList2(Graphe* graph,
	ListSuccessor* adjencyList,
	char* adjacents[],
	long adjacentsWeight[],
	int nbElement)
{
	//look in graphe for node 2, 3 and 4 because we have 
	// an edge between node 1 and 2, 3 and 4
	for (int i = 0; i < nbElement; i++)
	{
		ListSuccessor* tmp = graph->arcsList;
		//If vertexNode is not NULL, we have to create the next element of the list
		//and set this new element as the next of current adjacent element
		if (adjencyList->node != NULL)
		{
			adjencyList->next = (ListSuccessor*)malloc(sizeof(ListSuccessor));
			adjencyList = adjencyList->next;
			adjencyList->node = NULL;
			adjencyList->first = NULL;
			adjencyList->next = NULL;
		}

		//look for the node in the graph
		while (tmp != NULL)
		{
			if (tmp->node != NULL && strcmp(tmp->node->id, adjacents[i]) == 0)
			{
				adjencyList->node = tmp->node;
				adjencyList->node->weight = adjacentsWeight[i];
				break;
			}
			tmp = tmp->next;
		}
	}
}
