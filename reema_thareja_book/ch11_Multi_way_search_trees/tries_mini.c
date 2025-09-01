// Include stdio so we can print output
#include <stdio.h>
// Include stdlib so we can allocate and free memory
#include <stdlib.h>
// Include stdbool so we can use the bool type (true/false)
#include <stdbool.h>
// Include string.h so we can use strlen
#include <string.h>

// Define how many possible children each trie node has (26 letters a-z)
#define ALPHABET_SIZE 26

// Define a structure for one trie node
typedef struct TrieNode {
    // This array holds pointers to child nodes (one slot per letter)
    struct TrieNode *children[ALPHABET_SIZE];
    // This flag tells us if a complete word ends at this node
    bool is_end;
} TrieNode;

// This function creates a new empty trie node
static TrieNode *create_node(void) {
    // Allocate memory for one trie node
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    // Check if allocation failed
    if (!node) {
        // Print an error message if allocation failed
        printf("Memory allocation failed for TrieNode.\n");
        // Return NULL to show something went wrong
        return NULL;
    }
    // Set the end-of-word flag to false at the start
    node->is_end = false;
    // Loop through all children slots to initialize them
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        // Set each child pointer to NULL because there are no children yet
        node->children[i] = NULL;
    }
    // Return the newly created and initialized node
    return node;
}

// This function inserts a word (made of lowercase letters) into the trie
static void trie_insert(TrieNode *root, const char *word) {
    // Start from the root node
    TrieNode *cur = root;
    // Loop over each character in the input word
    for (int i = 0; word[i] != '\0'; i++) {
        // Get the current character
        char c = word[i];
        // Convert character to an index 0..25 (assumes a-z)
        int idx = c - 'a';
        // Check if character is outside 'a'..'z'
        if (idx < 0 || idx >= ALPHABET_SIZE) {
            // Warn the user and skip this word if invalid character found
            printf("Skipping word \"%s\" (invalid character '%c').\n", word, c);
            // Stop inserting this word because it contains invalid data
            return;
        }
        // If the child for this letter does not exist yet
        if (cur->children[idx] == NULL) {
            // Create a new node for this letter
            cur->children[idx] = create_node();
            // If creation failed, stop inserting
            if (!cur->children[idx]) {
                // Report failure and stop
                printf("Failed to create node while inserting \"%s\".\n", word);
                return;
            }
        }
        // Move down into the child node for the next character
        cur = cur->children[idx];
    }
    // After processing all characters, mark this node as the end of a word
    cur->is_end = true;
}

// This function searches for a full word in the trie (returns true if found exactly)
static bool trie_search(const TrieNode *root, const char *word) {
    // Start from the root
    const TrieNode *cur = root;
    // Loop through each character in the word
    for (int i = 0; word[i] != '\0'; i++) {
        // Get the current character
        char c = word[i];
        // Convert it to an index 0..25
        int idx = c - 'a';
        // If character is invalid, the word cannot exist here
        if (idx < 0 || idx >= ALPHABET_SIZE) {
            // Return false because of invalid character
            return false;
        }
        // If the needed child node does not exist, the word is not present
        if (cur->children[idx] == NULL) {
            // Return false because path breaks
            return false;
        }
        // Move down to the next node
        cur = cur->children[idx];
    }
    // After consuming all letters, return whether this node marks the end of a word
    return cur->is_end;
}

// This function checks whether any stored word starts with the given prefix
static bool trie_starts_with(const TrieNode *root, const char *prefix) {
    // Start at the root
    const TrieNode *cur = root;
    // Loop through each character in the prefix
    for (int i = 0; prefix[i] != '\0'; i++) {
        // Get the current character
        char c = prefix[i];
        // Convert it to an index 0..25
        int idx = c - 'a';
        // If character is invalid, no word can have this prefix (in our limited alphabet)
        if (idx < 0 || idx >= ALPHABET_SIZE) {
            // Return false because of invalid character
            return false;
        }
        // If the path does not exist, then no word has this prefix
        if (cur->children[idx] == NULL) {
            // Return false since prefix breaks
            return false;
        }
        // Move to the corresponding child node
        cur = cur->children[idx];
    }
    // If we successfully walked the whole prefix, it exists
    return true;
}

// This helper recursively prints all words from a given node
static void trie_print_dfs(const TrieNode *node, char *buffer, int depth) {
    // If the node pointer is NULL, there is nothing to do
    if (!node) {
        return;
    }
    // If this node marks the end of a complete word
    if (node->is_end) {
        // Add a string terminator at the current depth position
        buffer[depth] = '\0';
        // Print the accumulated characters as a word
        printf("%s\n", buffer);
    }
    // Loop through each possible child (a to z)
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        // If this child exists
        if (node->children[i]) {
            // Store the character corresponding to this child
            buffer[depth] = (char)('a' + i);
            // Recurse deeper with depth + 1
            trie_print_dfs(node->children[i], buffer, depth + 1);
        }
    }
}

// This function prints all words stored in the trie
static void trie_print_all(const TrieNode *root) {
    // Allocate a buffer large enough to hold typical test words (adjust if needed)
    char buffer[256];
    // Start depth-first printing from root with depth 0
    trie_print_dfs(root, buffer, 0);
}

// This helper tries to delete a word and returns whether the current node can be freed
static bool trie_delete_recursive(TrieNode *node, const char *word, int depth) {
    // If node is NULL, nothing to delete; return false (cannot free something that is already absent)
    if (!node) {
        return false;
    }
    // If we reached the end of the word string
    if (word[depth] == '\0') {
        // If this node was marking a word end, unmark it
        if (node->is_end) {
            node->is_end = false;
        }
        // Check if this node has any children
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != NULL) {
                // If a child exists, we cannot free this node
                return false;
            }
        }
        // If no children and not end of any other word, signal it can be freed
        return true;
    }
    // Convert current character to index
    int idx = word[depth] - 'a';
    // If invalid character, we do not support deleting it; stop
    if (idx < 0 || idx >= ALPHABET_SIZE) {
        // Cannot proceed with invalid character
        return false;
    }
    // Recurse on the child node for that character
    if (trie_delete_recursive(node->children[idx], word, depth + 1)) {
        // If child can be freed, free it and clear that pointer
        free(node->children[idx]);
        node->children[idx] = NULL;
        // After freeing the child, check if current becomes free-able
        if (!node->is_end) {
            // Look for any remaining children
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (node->children[i] != NULL) {
                    // Found another child, so we cannot free this node
                    return false;
                }
            }
            // No children and not an end of word, so this node can be freed
            return true;
        }
    }
    // Default: do not free this node
    return false;
}

// This function deletes a word from the trie (only if it exists)
static void trie_delete_word(TrieNode *root, const char *word) {
    // Call the recursive delete helper starting at depth 0
    if (trie_delete_recursive(root, word, 0)) {
        // If the helper says root can be freed (should almost never happen unless tree empties)
        // We will not free root here to keep the trie usable, but you could if desired
        // Print a note about potential root emptiness
        // (We choose not to free root to allow further operations)
        ;
    }
}

// This function frees every node in the trie
static void trie_free_all(TrieNode *node) {
    // If the node is NULL there is nothing to do
    if (!node) {
        return;
    }
    // Loop over all children
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        // Recursively free each child
        trie_free_all(node->children[i]);
    }
    // Free this node after its children
    free(node);
}

// The main function demonstrates usage of the trie
int main(void) {
    // Create the root node of the trie (empty root)
    TrieNode *root = create_node();
    // If creation failed, exit with error code
    if (!root) {
        return 1;
    }
    // Print a banner to show the demo started
    printf("=== Mini Trie Demo ===\n");
    // Define a small list of words to insert
    const char *words[] = {"apple", "app", "ape", "bat", "bad", "bar", "bark", "zoo"};
    // Compute how many words we have
    int count = (int)(sizeof(words) / sizeof(words[0]));
    // Insert each word into the trie
    for (int i = 0; i < count; i++) {
        trie_insert(root, words[i]);
    }
    // Print a header before listing all stored words
    printf("\nAll words in the trie:\n");
    // Print every word stored in the trie
    trie_print_all(root);
    // Demonstrate full word search for an existing word
    printf("\nSearch \"apple\": %s\n", trie_search(root, "apple") ? "FOUND" : "NOT FOUND");
    // Demonstrate search for a word that is only a prefix
    printf("Search \"ap\": %s\n", trie_search(root, "ap") ? "FOUND" : "NOT FOUND");
    // Demonstrate search for a non-existing word
    printf("Search \"apply\": %s\n", trie_search(root, "apply") ? "FOUND" : "NOT FOUND");
    // Demonstrate prefix check for a present prefix
    printf("\nStarts with \"ap\": %s\n", trie_starts_with(root, "ap") ? "YES" : "NO");
    // Demonstrate prefix check for a non-existing prefix
    printf("Starts with \"za\": %s\n", trie_starts_with(root, "za") ? "YES" : "NO");
    // Delete a word and show effect
    printf("\nDeleting word \"bad\"...\n");
    trie_delete_word(root, "bad");
    // Show that "bad" no longer matches
    printf("Search \"bad\": %s\n", trie_search(root, "bad") ? "FOUND" : "NOT FOUND");
    // But its sibling word "bat" should still exist
    printf("Search \"bat\": %s\n", trie_search(root, "bat") ? "FOUND" : "NOT FOUND");
    // Print all words again after deletion
    printf("\nAll words after deleting \"bad\":\n");
    trie_print_all(root);
    // Free the entire trie structure from memory
    trie_free_all(root);
    // Return success code
    return 0;
}

