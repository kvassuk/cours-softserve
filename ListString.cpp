#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef const char* String;

/* Initializes list */
void StringListInit (char*** list);
/* Destroy list and set pointer to NULL. */
void StringListDestroy (char*** list);

/* Inserts value at the end of the list. */
void StringListAdd (char** list, String str);
/* Removes all occurrences of str in the list. */
void StringListRemove (char** list, String str);

/* Returns the number of items in the list. */
int StringListSize (char** list);
/* Returns the index position of the first occurrence of str in the list. */
int StringListIndexOf (char** list, char* str);

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates (char** list);
/* Replaces every occurrence of the before, in each of the string lists's
 * strings, with after. */
void StringListReplaceInStrings (char** list, char* before, char* after);
/* Sorts the list of strings in ascending order */
void StringListSort (char** list);
/* Print strings of the list*/
void StringListPrint (char** list);

int main ()
{
	printf ("Hello World!\n");
	char** list = NULL;

	StringListInit (&list);

	printf ("List containe  %i string(s)\n", StringListSize (list));
	StringListAdd (list, "Hello");
	StringListAdd (list, "Abrakadabra");
	StringListAdd (list, "Killer");
	StringListAdd (list, "Killer");
	StringListAdd (list, "Hello");
	StringListAdd (list, "Barbara");
	StringListAdd (list, "Abrakadabra");
	StringListAdd (list, "Hello");
	StringListAdd (list, "Barbara");
	StringListAdd (list, "Barbara");
	printf ("List containe  %i string(s)\n", StringListSize (list));
	StringListPrint (list);
	printf ("--------sort-----------------\n");
	StringListSort (list);
	StringListPrint (list);
	printf ("--------sort-----------------\n");
	char str1[] = "Killer";
	char str2[] = "Hello";
	char str3[] = "GoodBay";
	StringListPrint (list);
	printf ("--------replaces-----------------\n");
	printf ("List containe  %i string(s)\n", StringListSize (list));
	StringListReplaceInStrings (list, str2, str3);
	StringListPrint (list);
	printf ("Index of \"%s\" string is  %i string(s)\n", str1, StringListIndexOf (list, str1));
	printf ("-------------------------\n");
	StringListRemoveDuplicates (list);
	StringListPrint (list);
	printf ("-------------------------\n");
	StringListRemove (list, "Killer");
	StringListRemove (list, "Abrakadabra");
	printf ("List containe  %i string(s)\n", StringListSize (list));
	StringListPrint (list);
	printf ("-------------------------\n");
	StringListDestroy (&list);
	StringListPrint (list);
	_CrtDumpMemoryLeaks ();
	return 0;
}
void StringListInit (char*** list)
{
	if (!*list)
	{
		*list = (char**)calloc (2, sizeof (char*));

		if (*list == NULL)
		{
			printf ("Memory allocation ERROR");
			exit (0);
		}
	}
	else
	{
		printf ("List is already initialized\n");
	}
}

void StringListAdd (char** list, String str)
{
	if (str[0] == '\0' || list == NULL)
	{
		printf ("ERROR to Add string\n");
		return;
	}
	if (*list == NULL)
	{
		*list = (char*)calloc (1, strlen (str) + 1);
		strcpy (list[0], str);
	}
	else
	{
		char** node = (char**)calloc (2, sizeof (char*));
		if (node)
		{
			*node = (char*)calloc (1, strlen (str) + 1);
			strcpy (*node, str);
		}
		char** current = list;
		while (*(current + 1) != NULL)
		{
			current = (char**)*(current + 1);
		}
		*(current + 1) = (char*)node;
	}
}

void StringListPrint (char** list)
{
	if (list == NULL || *list == NULL)
	{
		printf ("String list is empty.\n");

		return;
	}

	char** current = list;
	while (current != NULL)
	{
		printf ("%s\n", *current);
		current = (char**)*(current + 1);
	}
}
void StringListDestroy (char*** list)
{
	if (!*list)
		return;

	while (*list != NULL)
	{
		char** temp = (char**)*(*list + 1);
		free (*(*list));
		free (*list);
		*list = temp;
	}
	*list = NULL;
}
void StringListRemove (char** list, String str)
{
	if (str[0] == '\0' || list == NULL)
	{
		printf ("ERROR to Remove string\n");
		return;
	}


	char** current = list;
	char** previous = NULL;
	while (current)
	{

		if (strcmp (*current, str) == 0)
		{
			if (current == list)
			{
				char** nextnode = (char**)*(current + 1);
				free (*current);
				*current = NULL;
				if (nextnode)
				{
					*current = *nextnode;
					*(current + 1) = *(nextnode + 1);
					free (nextnode);
				}
				else
				{
					*current = NULL;
					current = NULL;
				}

				continue;
			}
			else
			{
				free (*current);
				*current = NULL;
				*(previous + 1) = *(current + 1);
				free (current);
				current = (char**)*(previous + 1);
				continue;
			}
		}
		if (current)
			previous = current;
		current = (char**)*(current + 1);
	}


}

int StringListSize (char** list)
{
	int count = 0;
	if (list == NULL || *list == NULL)
	{
		printf ("String list is empty.\n");
		return count;
	}


	char** current = list;
	while (current != NULL)
	{
		count++;
		current = (char**)*(current + 1);
	}
	return count;
}

int StringListIndexOf (char** list, char* str)
{
	if (list == NULL || str[0] == '\0')
	{
		printf ("String list is empty.\n");
	}
	int index = 0;
	char** current = list;
	while (current != NULL)
	{
		if (strcmp (*current, str) == 0)
		{
			return index;
		}
		index++;
		current = (char**)*(current + 1);
	}
	return -1;
}

void StringListRemoveDuplicates (char** list) //TODO:
{
	if (list == NULL || *list == NULL)
	{
		printf ("String list is empty.\n");
		return;
	}
	char** current = list;
	char** previous = current;
	char** next = (char**)*(current + 1);

	while (current)
	{
		while (next)
		{
			if (strcmp (*current, *next) == 0)
			{
				*(previous + 1) = *(next + 1);
				free (*next);
				*next = NULL;
				*(next + 1) = NULL;
				free (next);
				next = NULL;

				next = (char**)*(previous + 1);
				continue;
			}
			if (next)
				previous = next;
			next = (char**)*(next + 1);
		}

		current = (char**)*(current + 1);
		if (current)
			next = (char**)*(current + 1);
		previous = current;
	}


}

void StringListReplaceInStrings (char** list, char* before, char* after)
{
	if (!list && before[0] == '\0' && after[0] == '\0')
		printf ("Error to replace strings\n");

	char** current = list;
	while (current)
	{
		if (strcmp (*current, before) == 0)
		{
			if (*current != NULL)
			{
				*current = (char*)realloc (*current, strlen (after) + 1);
				if (*current)
					strcpy (*current, after);
			}

		}
		current = (char**)*(current + 1);
	}

}

void StringListSort (char** list)
{
	bool sorted = false;
	while (!sorted)
	{
		char** current = list;
		char** next = (char**)*(current + 1);
		sorted = true;
		while (next)
		{

			if (strcmp (*current, *next) > 0)
			{
				char* temp = NULL;
				temp = *current;
				*current = *next;
				*next = temp;
				sorted = false;
			}
			current = (char**)*(current + 1);
			if (current)
				next = (char**)*(next + 1);
		}

	}
}
