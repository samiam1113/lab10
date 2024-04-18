#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
	int occurrence;
    struct Trie* next[26];
};

//prototypes
void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);
struct Trie *createTrie();
int readDictionary(char *filename, char **pInWords);

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	struct Trie* current = pTrie;
    for (int i = 0; word[i]; ++i) {
        int index = word[i] - 'a'; 
        if (current->next[index] == NULL) {
            current->next[index] = createTrie();
        }
        current = current->next[index];
    }
    //counts occurrence of inserted word
    current->occurrence++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    
    struct Trie* current = pTrie;
    for (int i = 0; word[i]; ++i) {
        int index = word[i] - 'a';

        //word not found return 0;
        if (current->next[index] == NULL) {
            return 0; 
        }

        current = current->next[index]; //traverse
    }
    
    //returns occurrence count
    return current->occurrence;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
        return NULL;

    for (int i = 0; i < 26; i++)
        deallocateTrie(pTrie->next[i]);

    free(pTrie);
    return NULL;
}

// initializes a trie structure
struct Trie *createTrie()
{
	struct Trie* myTree = (struct Trie*)malloc(sizeof(struct Trie));

    for (int i=0; i<26; i++)
        myTree->next[i] = NULL;

    //initializes to 0
    myTree->occurrence = 0;
    
    return myTree;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    int count = 0;
    int numLines;

    //scan number of lines
    fscanf(file, "%d", &numLines);
    
    //scans words
    for(int i = 0; i<numLines; i++) {
        
        pInWords[i] = (char*)malloc(256 * sizeof(char));
        fscanf(file, "%s", pInWords[i]);
        
    }

    fclose(file);
    return numLines;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");

    
	return 0;
}
