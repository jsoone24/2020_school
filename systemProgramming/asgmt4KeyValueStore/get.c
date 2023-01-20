#include "kvs.h"

char* get(kvs_t* kvs, const char* key)
{
	/* do program here */
	
	char* value = (char*)malloc(sizeof(char)*300);

	if(!value){
		printf("Failed to malloc\n");
		return NULL;
	}

	node_t* tmpnode = kvs->db;

	while ((tmpnode->next != NULL) && strcmp(tmpnode->key,key))
		tmpnode = tmpnode->next;

	value = tmpnode->value;

	return value;
}