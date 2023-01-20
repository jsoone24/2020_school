#include "kvs.h"

int main()
{
	kvs_t *kvs = open();

	if (!kvs)
	{
		printf("Failed to open kvs\n");
		return -1;
	}

	// KVS created.
	FILE *file = fopen("student.dat", "r");
	if (NULL != file) //파일 열기에 성공
	{
		node_t *node = (node_t *)malloc(sizeof(node_t));
		kvs->db = node;
		kvs->db->next = NULL;
		while (!feof(file))
		{
			char key[100];
			char *value = (char *)malloc(sizeof(char) * 300);

			fscanf(file, "%s %s", key, value);

			if (put(kvs, key, value) < 0)
			{
				printf("Failed to put data\n");
				exit(-1);
			}

			kvs->items++;
		}
	}
	fclose(file);

	file = fopen("student.dat", "r");
	if (NULL != file) //파일 열기에 성공
	{
		while (!feof(file))
		{
			char key[100];
			char *value = (char *)malloc(sizeof(char) * 300);
			char *rvalue;

			fscanf(file, "%s %s", key, value);

			if (!(rvalue = get(kvs, key)))
			{
				printf("Failed to get data\n");
				exit(-1);
			}

			printf("get: %s, %s\n", key, rvalue);
		}
	}
	fclose(file);

	close(kvs);
	
	return 0;
}
