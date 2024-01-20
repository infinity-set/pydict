typedef struct dict_node
{
    char *key;              // Key of the node
    int key_length;         // Length of the key
    int key_alloc;          // Allocated memory for the key
    char *value;            // Value associated with the key
    int value_length;       // Length of the value
    int value_alloc;        // Allocated memory for the value
    struct dict_node *next; // Pointer to the next node in the dictionary
} dict_node;

// Define a structure to represent a dictionary
typedef struct pydict
{
    dict_node *head; // Pointer to the first node in the dictionary
    dict_node *tail; // Pointer to the last node in the dictionary
    int count;       // Number of nodes in the dictionary
} pydict;

// Function to create a new dictionary
pydict *pydict_new();

// Function to put or update a key-value pair in the dictionary
pydict *pydict_put(pydict *self, const char *key_string, const char *value_string);

// Function to append a new key-value pair to the dictionary
pydict *pydct_append(pydict *self, const char *key_string, const char *value_string);

// Function to create a new key-value node in the dictionary
dict_node *pydict_new_key_value_node(pydict *self);

// Function to find a node in the dictionary based on the key
dict_node *pydict_find(pydict *self, const char *key_string);

// Function to get the value associated with a key in the dictionary
const char *pydict_get(pydict *self, const char *key_string);

// Function to get the length of the dictionary
int pydict_len(pydict *self);

// Function to print the contents of the dictionary
void pydict_print(pydict *self);

// Function to delete the entire dictionary and free memory
pydict *pydict_del(pydict *self);

#include <stdio.h>
#include <stdlib.h>

// Main function demonstrating the usage of the dictionary
int main()
{
    // Create a new dictionary
    pydict *dct = pydict_new();
    // Print the empty dictionary
    pydict_print(dct);
    // Add key-value pairs to the dictionary
    pydict_put(dct, "Hello", "World");
    pydict_print(dct);
    pydict_put(dct, "key_2", "value_2");
    pydict_print(dct);
    pydict_put(dct, "key_3", "value_3");
    pydict_print(dct);
    // Replace a former key-value pair in the dictionary with a new value
    pydict_put(dct, "Hello", "Replace Value");
    pydict_print(dct);
    // Print the length of the dictionary
    printf("\nLength = %d\n", pydict_len(dct));
    // Print the value associated with a specific key
    printf("\nValue of Key 'Hello': %s\n", pydict_get(dct, "Hello"));
    printf("\nValue of Key 'key_3': %s\n", pydict_get(dct, "key_3"));
    // Try to get the value of a nonexistent key
    printf("\nValue of Key 'Nonexistent': %s\n", pydict_get(dct, "Nonexistent"));
    // Delete the dictionary and free memory
    dct = pydict_del(dct);
    // Print the empty dictionary
    pydict_print(dct);
    return 0;
}

// Function to create a new dictionary
pydict *pydict_new()
{
    // Allocate memory for the dictionary
    pydict *dictionary = (pydict *)malloc(sizeof(pydict));
    // Check if memory allocation was successful
    if (dictionary == NULL)
    {
        printf("Unable to allocate memory!");
        return dictionary;
    }
    // Initialize the dictionary properties
    dictionary->head = NULL;
    dictionary->tail = NULL;
    dictionary->count = 0;
    return dictionary;
}

// Function to get the length of the dictionary
int pydict_len(pydict *self)
{
    return self->count;
}

// Function to delete the entire dictionary and free memory
pydict *pydict_del(pydict *self)
{
    dict_node *current, *next;
    // Start from the head of the dictionary
    current = self->head;
    // Iterate through each node in the dictionary
    while (current)
    {
        // Free memory allocated for key and value
        free(current->key);
        free(current->value);
        // Move to the next node
        next = current->next;
        // Free memory allocated for the current node
        free(current);
        current = next;
    }
    // Free memory allocated for the dictionary structure
    free(self);
    // Return NULL to indicate that the dictionary is deleted
    return NULL;
}

// Function to put or update a key-value pair in the dictionary
pydict *pydict_put(pydict *self, const char *key_string, const char *value_string)
{
    // Check if the dictionary is empty
    if (self->head == NULL)
    {
        // If empty, create a new key-value node
        dict_node *new_node = pydict_new_key_value_node(self);
        // Check if memory allocation was successful
        if (new_node == NULL)
        {
            printf("\nCould not allocate memory!\n");
            // Delete the dictionary and return NULL
            pydict_del(self);
            return NULL;
        }
        // Set the head and tail of the dictionary to the new node
        self->head = new_node;
        self->tail = new_node;
        // Append the key-value pair to the node
        pydct_append(self, key_string, value_string);
    }
    else
    {
        // If not empty, find the node with the specified key
        dict_node *old = pydict_find(self, key_string);
        // If the key is not found, create a new key-value node
        if (old == NULL)
        {
            dict_node *new_node = pydict_new_key_value_node(self);
            // Check if memory allocation was successful
            if (new_node == NULL)
            {
                printf("\nCould not allocate memory!\n");
                // Delete the dictionary and return NULL
                pydict_del(self);
                return NULL;
            }
            // Start from the head of the dictionary
            dict_node *ptr = self->head;
            // Set the tail of the dictionary to the new node
            self->tail = new_node;
            // Append the key-value pair to the new node
            pydct_append(self, key_string, value_string);
            // Iterate to the last node in the dictionary
            for (int i = 1; i < self->count - 1; i++)
            {
                ptr = ptr->next;
            }
            // Set the next pointer of the last node to the new node
            ptr->next = new_node;
        }
        else
        {
            // If the key is found, update the value of the existing node
            free(old->value);
            old->value_alloc = 10;
            old->value_length = 0;
            old->value = (char *)calloc(old->value_alloc, sizeof(char));
            // Check if memory allocation was successful
            if (old->value == NULL)
            {
                printf("\nCould not allocate memory!\n");
                // Delete the dictionary and return NULL
                pydict_del(self);
                return NULL;
            }
            // Copy the characters from the new value string to the node's value
            for (int i = 0; value_string[i] != '\0'; i++)
            {
                if (old->value_length < (old->value_alloc - 1))
                {
                    old->value[old->value_length + 1] = old->value[old->value_length];
                    old->value[old->value_length] = value_string[i];
                    old->value_length++;
                }
                else
                {
                    // If the allocated memory is not enough, reallocate with additional space
                    old->value = (char *)realloc(old->value, old->value_alloc + 10);
                    // Check if memory allocation was successful
                    if (old->value == NULL)
                    {
                        printf("\nCould not allocate memory!\n");
                        // Delete the dictionary and return NULL
                        pydict_del(self);
                        return NULL;
                    }
                    old->value_alloc += 10;
                    old->value[old->value_length + 1] = old->value[old->value_length];
                    old->value[old->value_length] = value_string[i];
                    old->value_length++;
                }
            }
        }
    }
    // Return the updated dictionary
    return self;
}

// Function to get the value associated with a key in the dictionary
const char *pydict_get(pydict *self, const char *key_string)
{
    // Find the node with the specified key
    dict_node *value = pydict_find(self, key_string);
    // If the key is not found, print a message and return NULL
    if (value == NULL)
    {
        printf("\n**The key '%s' does not exist**\n", key_string);
        key_string = NULL;
        return key_string;
    }
    else
    {
        // Return the value associated with the key
        return value->value;
    }
}

// Function to find a node in the dictionary based on the key
dict_node *pydict_find(pydict *self, const char *key_string)
{
    // Start from the head of the dictionary
    dict_node *ptr = self->head;
    // Iterate through each node in the dictionary
    while (ptr)
    {
        // Check if the current node is not NULL and has valid data
        if (ptr->key[0] != '\0' && ptr != NULL)
        {
            int i;
            // Iterate through the characters of both the input string and the node's key
            for (i = 0; key_string[i] && ptr->key[i]; i++)
            {
                // If characters don't match, break the loop
                if (key_string[i] != ptr->key[i])
                {
                    break;
                }
            }
            // If both strings match until the end, return the pointer to the node
            if (key_string[i] == '\0' && ptr->key[i] == '\0')
            {
                return ptr;
            }
        }
        // Move to the next node in the dictionary
        ptr = ptr->next;
    }
    // Return NULL if the key is not found
    return NULL;
}

// Function to append a new key-value pair to the dictionary
pydict *pydct_append(pydict *self, const char *key_string, const char *value_string)
{
    // Check if key and value strings are not NULL
    if (key_string != NULL && value_string != NULL)
    {
        // Allocate memory for the key in the last node
        self->tail->key = (char *)calloc(self->tail->key_alloc, sizeof(char));
        // Check if memory allocation was successful
        if (self->tail->key == NULL)
        {
            printf("\nCould not allocate memory!\n");
            // Delete the dictionary and return NULL
            pydict_del(self);
            return NULL;
        }
        // Copy characters from the input key string to the last node's key
        for (int i = 0; key_string[i] != '\0'; i++)
        {
            if (self->tail->key_length < (self->tail->key_alloc - 1))
            {
                self->tail->key[self->tail->key_length + 1] = self->tail->key[self->tail->key_length];
                self->tail->key[self->tail->key_length] = key_string[i];
                self->tail->key_length++;
            }
            else
            {
                // If the allocated memory is not enough, reallocate with additional space
                self->tail->key = (char *)realloc(self->tail->key, self->tail->key_alloc + 10);
                // Check if memory allocation was successful
                if (self->tail->key == NULL)
                {
                    printf("\nCould not allocate memory!\n");
                    // Delete the dictionary and return NULL
                    pydict_del(self);
                    return NULL;
                }
                self->tail->key_alloc += 10;
                self->tail->key[self->tail->key_length + 1] = self->tail->key[self->tail->key_length];
                self->tail->key[self->tail->key_length] = key_string[i];
                self->tail->key_length++;
            }
        }
        // Allocate memory for the value in the last node
        self->tail->value = (char *)calloc(self->tail->value_alloc, sizeof(char));
        // Check if memory allocation was successful
        if (self->tail->value == NULL)
        {
            printf("\nCould not allocate memory!\n");
            // Delete the dictionary and return NULL
            pydict_del(self);
            return NULL;
        }
        // Copy characters from the input value string to the last node's value
        for (int i = 0; value_string[i] != '\0'; i++)
        {
            if (self->tail->value_length < (self->tail->value_alloc - 1))
            {
                self->tail->value[self->tail->value_length + 1] = self->tail->value[self->tail->value_length];
                self->tail->value[self->tail->value_length] = value_string[i];
                self->tail->value_length++;
            }
            else
            {
                // If the allocated memory is not enough, reallocate with additional space
                self->tail->value = (char *)realloc(self->tail->value, self->tail->value_alloc + 10);
                // Check if memory allocation was successful
                if (self->tail->value == NULL)
                {
                    printf("\nCould not allocate memory!\n");
                    // Delete the dictionary and return NULL
                    pydict_del(self);
                    return NULL;
                }
                self->tail->value_alloc += 10;
                self->tail->value[self->tail->value_length + 1] = self->tail->value[self->tail->value_length];
                self->tail->value[self->tail->value_length] = value_string[i];
                self->tail->value_length++;
            }
        }
        // Increment the count of nodes in the dictionary
        self->count++;
        // Set the next pointer of the last node to NULL
        self->tail->next = NULL;
    }
    return self;
}

// Create a new key-value pair node for the dictionary
dict_node *pydict_new_key_value_node(pydict *self)
{
    // Allocate memory for the new node
    dict_node *new_node = (dict_node *)malloc(sizeof(dict_node));

    // Check if memory allocation was successful
    if (new_node == NULL)
    {
        printf("\nCould not allocate memory!\n");
        // Clean up and return NULL in case of failure
        pydict_del(self);
        return NULL;
    }

    // Initialize the new node's fields
    new_node->key = NULL;
    new_node->key_alloc = 10;
    new_node->key_length = 0;
    new_node->value = NULL;
    new_node->value_alloc = 10;
    new_node->value_length = 0;
    new_node->next = NULL;

    // Return the newly created node
    return new_node;
}

// Print the contents of the dictionary
void pydict_print(pydict *self)
{
    // Check if the dictionary or its head is NULL
    if (self == NULL || self->head == NULL)
    {
        printf("\n{}\n");
        return;
    }

    // Start printing the dictionary
    printf("\n{");

    // Initialize a pointer to iterate through the nodes
    dict_node *ptr = self->head;

    // Iterate through the nodes in the dictionary
    while (ptr)
    {
        // Check if the key and value are not NULL and not empty
        if (ptr->key != NULL && ptr->key[0] != '\0' && ptr->value != NULL)
        {
            // Print the key-value pair
            printf("'%s': '%s'", ptr->key, ptr->value);

            // Check if there is a next node, and if so, print a comma
            if (ptr->next != NULL)
            {
                printf(", ");
            }
        }

        // Move to the next node in the dictionary
        ptr = ptr->next;
    }

    // Finish printing the dictionary
    printf("}\n");
}
