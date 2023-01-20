#include "kvs.h"

int put(kvs_t* kvs, const char* key, const char* value)
{
	printf("put: %s, %s\n", key, value);
	/* do program here */
	node_t* tmpnode = kvs->db;

	while (tmpnode->next != NULL)
		tmpnode = tmpnode->next;
	
	node_t* node = (node_t*) malloc (sizeof(node_t));
	strcpy(node->key, key);
	node->value = value;
	node->next = NULL;

	tmpnode->next = node;

	return 0;
}