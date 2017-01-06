/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 * 
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // init scope
    Node * scope = root;
    
    // loop through each character in word
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // get character index
        int ct = dict_charIndex(word[i]);
        
        // find child node of current scope using character index
        scope = dict_getChild(scope, ct);
        if (scope == NULL)
        {
            // the child doesn't exist thus the word doesn't exist
            return false;
        }
        
        // check if last letter 
        if (i == len -1)
        {
            // check if the node identifies itself as a word
            // and return this boolean
            return dict_isWord(scope);
        }
 
    }
    
    // fallback
    return false;
}




/**
 * Loads dictionary into memory.  Returns true if successful else false.
 * 
 * @param Char* dictionary
 * @return Bool
 */
bool load(const char* dictionary)
{
    // set fp & check the file opened and is not null
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return 1;
    }
    
    // if file is loaded
    if (fp)
    {
        // init root dictionary node
        root = (Node*)malloc(sizeof(Node));
        dict_nodeInit(root);
        
        // init dict_count
        dict_count = 0;

        int c = 0;
        while (c != EOF)
        {
            // set strut back to root node for this new word
            Node * scope = root;
            
            
            // for each character until EOR or new line
            for (c = fgetc(fp); c != EOF && c != 10; c = fgetc(fp))
            {
                // get character index
                int ct = dict_charIndex(c);
                
                // create scope if not exists and update scope to this
                scope = dict_add(scope, ct);
            }
            
            // end of word set current strut to word = true
            // increment dict_count
            dict_wordTrue(scope);
            dict_count++;
        }

        // close file and return true
        fclose(fp);
        return true;
    }

    // fallback
    return false;
}




/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 * 
 * @return Int
 */
unsigned int size(void)
{
    return dict_count -1;
}



/**
 * destroys all Node's child elements recersively
 * and finally destroys self node
 * 
 * @param Node n
 * @return Void
 */
void dict_destroy(struct Node *n)
{
    // iterate through each child where pointer isn't null
    for (int i = 1; i <= 27; i++)
    {
        // for each child where pointer is not null
        if (n->children[i] != NULL)
        {
            // destroy node & any children
            dict_destroy(n->children[i]);
            n->children[i] = NULL;
        }
    }
    
    // destroy self after all node's children are destroyed
    free(n);
    n = NULL;
}



/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 * 
 * @return Bool
 */
bool unload(void)
{
    // destroy root recersively
    dict_destroy(root);
    root = NULL;
    return true;
}



/**
 * Returns the index for a character from A-Z & a-z or '
 * also converts uppercase to lowercase.
 * 
 * @param Char c
 * @return Int
 */
int dict_charIndex(int c)
{
    // check if lowercase
    if (c >= 97 && c <= 122 )
    {
        // convert to 0-26 index of alphabet
        c = c - 96;
    }
    // check if uppercase
    else if (c >= 65 && c <= 90 )
    {
        // convert from uppercase to 0-26 index of alphabet
        c = c - 64;
    }
    // check if apostrope
    else if (c == 39)
    {
        c = 27;
    }
    // non valid character return null
    else
    {
        c = 0;
    }
    
    // return c character index
    return c;
}


/**
 * Checks if child doesn't exist and creates. Then 
 * returns the existing/new pointer to this node.
 * 
 * @param Node n
 * @param Int c
 * @return Node*
 */
Node *dict_add(struct Node *n, int c)
{
    // validate c is <= 27 && not 0
    if (c > 27 || c == 0)
    {
        return 0;
    }
    
    // check if child isn't null
    if (n->children[c] != NULL)
    {
        return n->children[c];
    }
    // create new node
    else 
    {
        Node *newNode = malloc(sizeof(Node));
        // init default variables
        dict_nodeInit(newNode);
        
        n->children[c] = newNode;
        return newNode;
    }

}



/**
 * sets a dict node's is_word value to true
 * 
 * @param Node n
 * @return Void
 */
void dict_wordTrue(struct Node *n)
{
    n->is_word = true;
}



/**
 * Checks if the current node is a word
 * 
 * @param Node n
 * @return Bool
 */
bool dict_isWord(struct Node *n)
{
    if (n->is_word == true)
    {
        return true;
    }
    
    // fallback
    return false;
}



/**
 * Checks if child struct exist based on child character
 * and returns struct address, else returns 0
 * 
 * @param Node n
 * @param Char c
 * @return Node n
 */
Node *dict_getChild(struct Node *n, int c)
{
    // check c is <= 27 && not 0
    if (c > 27 || c == 0)
    {
        return 0;
    }
    
    // check if child isn't null
    if (n->children[c] != NULL)
    {
        return n->children[c];
    }
    
    // no children found
    return 0;
}

/**
 * Initialises a node's variables
 * 
 * @param Node n
 * @return void
 */
void dict_nodeInit(struct Node *n)
{
    // set is_word to default false
    n->is_word = false;
    
    // iterate through children setting them to NULL
    for (int i = 0; i < 28; i++)
    {
        n->children[i] = NULL;
    }
}