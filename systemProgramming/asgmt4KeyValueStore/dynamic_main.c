#include "kvs.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    void *handle;
    char *error;
    kvs_t *(*open)();
    int (*put)(kvs_t * kvs, const char *key, const char *value);
    char *(*get)(kvs_t * kvs, const char *key);
    int (*close)(kvs_t * kvs);

    handle = dlopen("./libkvs.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    open = dlsym(handle, "open");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    put = dlsym(handle, "put");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    get = dlsym(handle, "get");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    close = dlsym(handle, "close");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

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

	/*Unload the shared library*/
	if(dlclose(handle)<0){
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	
    return 0;
}