/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Define typedef for node & set global scope for root instance of Node
 */
typedef struct Node
{
    bool is_word;
    struct Node* children[27];
} Node;
extern Node *root;
Node *root;

/**
 * Set global variable to hold dict_count int
 * @var Int dict_count
 */
int dict_count;


/**
 * Returns the index for a character from A-Z & a-z or '
 * also converts uppercase to lowercase.
 * 
 * @param Char c
 * @return Int
 */
int dict_charIndex(int c);


/**
 * Checks if child doesn't exist and creates. Then 
 * returns the existing/new pointer to this node.
 * 
 * @param Node n
 * @param Int c
 * @return Node*
 */
Node *dict_add(struct Node *n, int c);

/**
 * sets a dict node's is_word value to true
 * 
 * @param Node n
 * @return Void
 */
void dict_wordTrue(struct Node *n);

/**
 * Checks if the current node is a word
 * 
 * @param Node n
 * @return Bool
 */
bool dict_isWord(struct Node *n);

/**
 * Checks if child struct exist based on child character
 * and returns struct address, else returns 0
 * 
 * @param Node n
 * @param Char c
 * @return Node n
 */
Node *dict_getChild(struct Node *n, int c);

/**
 * destroys all Node's child elements recersively
 * and finally destroys self node
 * 
 * @param Node n
 * @return Void
 */
void dict_destroy(struct Node *n);

/**
 * Initialises a node's variables
 * 
 * @param Node n
 * @return void
 */
void dict_nodeInit(struct Node *n);

#endif // DICTIONARY_H
