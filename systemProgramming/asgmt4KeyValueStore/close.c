#include "kvs.h"

int close(kvs_t *kvs)
{
	/* do program */
	while (kvs->items)
	{
		node_t *tmpnode = kvs->db, *tmpnode2;

		while (tmpnode->next != NULL)
		{
			tmpnode2 = tmpnode;
			tmpnode = tmpnode->next;
		}

		free(tmpnode->value);
		free(tmpnode);
		tmpnode2->next = NULL;

		kvs->items--;
	}

	free(kvs->db);
	kvs->db = NULL;
	free(kvs);
	kvs = NULL;
	
	return 0;
}