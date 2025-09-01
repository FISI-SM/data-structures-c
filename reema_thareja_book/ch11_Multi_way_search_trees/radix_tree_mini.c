// Include stdio so we can print to the console and read user input
#include <stdio.h>
// Include stdlib so we can allocate and free dynamic memory
#include <stdlib.h>
// Include string.h so we can copy and compare strings
#include <string.h>
// Include stdbool so we can use true and false
#include <stdbool.h>

// --------------------------- DATA STRUCTURES ---------------------------

// Define a structure for a single Radix Tree node (compressed trie node)
typedef struct RadixNode {
    // Store the substring (edge label) that this node represents
    char *key;
    // Mark whether a complete word ends exactly at this node
    bool is_end;
    // Dynamic array of pointers to child nodes (can grow)
    struct RadixNode **children;
    // Number of children currently stored in the array
    int child_count;
} RadixNode;

// --------------------------- UTILITY HELPERS ---------------------------

// Provide a safe duplicate string function (wrapper for strdup portability)
static char *dup_string(const char *s) {
    // Get length of source string
    size_t len = strlen(s);
    // Allocate length + 1 for null terminator
    char *copy = (char *)malloc(len + 1);
    // If allocation failed return NULL
    if (!copy) return NULL;
    // Copy bytes from original into new buffer
    memcpy(copy, s, len + 1);
    // Return the new duplicated string
    return copy;
}

// Compute the length of the longest common prefix between two C strings
static int longest_common_prefix(const char *a, const char *b) {
    // Start an index at zero
    int i = 0;
    // Loop while both strings still have characters and they match
    while (a[i] && b[i] && a[i] == b[i]) {
        // Move to next character
        i++;
    }
    // Return how many characters matched
    return i;
}

// --------------------------- NODE CREATION ---------------------------

// Create a new Radix Tree node given a substring (can be empty "")
static RadixNode *create_node(const char *key) {
    // Allocate memory for one RadixNode structure
    RadixNode *node = (RadixNode *)malloc(sizeof(RadixNode));
    // Check allocation success
    if (!node) {
        // Report error if allocation failed
        printf("Memory allocation failed for RadixNode.\n");
        // Return NULL to caller
        return NULL;
    }
    // Duplicate the key (or empty if NULL was passed)
    node->key = key ? dup_string(key) : dup_string("");
    // If duplication failed free node and return NULL
    if (!node->key) {
        // Free node structure
        free(node);
        // Report failure
        printf("Memory allocation failed for key string.\n");
        // Return NULL
        return NULL;
    }
    // Initially this node does not mark the end of a word
    node->is_end = false;
    // Start with no children (NULL pointer)
    node->children = NULL;
    // Child count starts at zero
    node->child_count = 0;
    // Return the fully initialized node
    return node;
}

// --------------------------- CHILD MANAGEMENT ---------------------------

// Add a child node pointer to a parent by reallocating the array
static void add_child(RadixNode *parent, RadixNode *child) {
    // Reallocate the children array to hold one more pointer
    parent->children = (RadixNode **)realloc(
        parent->children,
        sizeof(RadixNode *) * (parent->child_count + 1)
    );
    // If reallocation failed report and exit (simplify error handling)
    if (!parent->children) {
        // Report fatal error
        printf("Fatal: realloc failed while adding child.\n");
        // Exit because continuing would cause crashes
        exit(EXIT_FAILURE);
    }
    // Store the new child pointer in the last slot
    parent->children[parent->child_count] = child;
    // Increase the child count
    parent->child_count++;
}

// --------------------------- INSERT LOGIC ---------------------------

// Insert a word (lowercase letters) into the Radix Tree
static void radix_insert(RadixNode *root, const char *word) {
    // Maintain a pointer to the current node while traversing or splitting
    RadixNode *current = root;
    // Keep track of the remaining part of the word we still need to insert
    const char *remaining = word;

    // Loop indefinitely until we return after inserting
    while (1) {
        // Flag to remember if we matched at least one child this round
        bool matched_child = false;
        // Loop over each existing child of the current node
        for (int i = 0; i < current->child_count; i++) {
            // Get pointer to this child
            RadixNode *child = current->children[i];
            // Access the child's key substring
            const char *ckey = child->key;
            // Compute the length of the longest common prefix
            int lcp = longest_common_prefix(ckey, remaining);
            // If no shared prefix move to next child
            if (lcp == 0) {
                continue;
            }
            // Mark that we found some overlap with this child
            matched_child = true;

            // Case 1: Shared prefix is smaller than child's key length
            if (lcp < (int)strlen(ckey)) {
                // We need to split the child node into prefix and suffix
                // Create a new node for the suffix part of the child's key
                RadixNode *suffix = create_node(ckey + lcp);
                // If creation failed abort
                if (!suffix) {
                    printf("Fatal: cannot create suffix node.\n");
                    exit(EXIT_FAILURE);
                }
                // Move over the child's children to the new suffix node
                suffix->children = child->children;
                suffix->child_count = child->child_count;
                // Copy the end-of-word marker from original child
                suffix->is_end = child->is_end;

                // Truncate the original child's key to only the prefix
                char *new_key = (char *)malloc(lcp + 1);
                if (!new_key) {
                    printf("Fatal: cannot allocate prefix truncation.\n");
                    exit(EXIT_FAILURE);
                }
                memcpy(new_key, ckey, lcp);
                new_key[lcp] = '\0';
                free(child->key);
                child->key = new_key;

                // Reset the original child to have only one child (the suffix)
                child->children = NULL;
                child->child_count = 0;
                add_child(child, suffix);
                // Since we split, the original node no longer ends a word unless the prefix itself was a word
                child->is_end = false;
            }

            // After possible split we recompute ckey pointer (still valid)
            // Check remaining length against lcp
            if (lcp == (int)strlen(remaining)) {
                // Entire remaining word consumed by prefix
                // Mark child as end of word
                child->is_end = true;
                // Insertion complete so return
                return;
            }

            // If we only consumed part of child's (already handled) and have leftover to insert deeper
            // Advance remaining pointer by the prefix length
            remaining += lcp;

            // Now move deeper into the child
            current = child;
            // Break out of child loop to continue outer while
            break;
        }

        // If no child matched any prefix at all
        if (!matched_child) {
            // Create a new child node with the entire remaining substring
            RadixNode *new_child = create_node(remaining);
            // If allocation failed abort
            if (!new_child) {
                printf("Fatal: cannot allocate new child for insertion.\n");
                exit(EXIT_FAILURE);
            }
            // Mark this new node as a complete word
            new_child->is_end = true;
            // Attach this new node to current
            add_child(current, new_child);
            // Done inserting so return
            return;
        }
        // Loop continues if we matched and still have characters to insert
    }
}

// --------------------------- SEARCH FULL WORD ---------------------------

// Search whether an exact word exists in the Radix Tree
static bool radix_search(const RadixNode *root, const char *word) {
    // Start at the root
    const RadixNode *current = root;
    // Pointer to remaining part of word to match
    const char *remaining = word;
    // Loop while we still have characters left to match
    while (*remaining) {
        // Flag to track matching child
        bool found = false;
        // Examine each child of current
        for (int i = 0; i < current->child_count; i++) {
            // Get candidate child
            const RadixNode *child = current->children[i];
            // Get length of child's key
            int klen = (int)strlen(child->key);
            // Check if the child's key matches the beginning of remaining
            if (strncmp(remaining, child->key, klen) == 0) {
                // Advance remaining beyond the child key
                remaining += klen;
                // Move current pointer into child
                current = child;
                // Mark found
                found = true;
                // Break to outer loop
                break;
            }
        }
        // If no child matched the next segment return false
        if (!found) return false;
    }
    // After consuming all characters, success only if current marks end of a word
    return current->is_end;
}

// --------------------------- PREFIX CHECK ---------------------------

// Check whether any word stored starts with the given prefix
static bool radix_starts_with(const RadixNode *root, const char *prefix) {
    // Start at root
    const RadixNode *current = root;
    // Pointer to remaining part of prefix to match
    const char *remaining = prefix;
    // Loop while there is still unmatched prefix
    while (*remaining) {
        // Track whether we matched a child segment
        bool found = false;
        // Loop through all children
        for (int i = 0; i < current->child_count; i++) {
            // Get child pointer
            const RadixNode *child = current->children[i];
            // Length of child's key
            int klen = (int)strlen(child->key);
            // Compute possible match length (prefix might be shorter)
            int cmp_len = klen;
            // If remaining is shorter, adjust compare length
            int rem_len = (int)strlen(remaining);
            if (rem_len < cmp_len) cmp_len = rem_len;
            // Check if the beginning matches
            if (strncmp(remaining, child->key, cmp_len) == 0) {
                // If prefix ends inside the child key we are done (prefix exists)
                if (rem_len <= klen) {
                    return true;
                }
                // Else consume entire child key and continue deeper
                remaining += klen;
                current = child;
                found = true;
                break;
            }
        }
        // If nothing matched the needed next part, prefix not present
        if (!found) return false;
    }
    // If entire prefix consumed we have a match
    return true;
}

// --------------------------- PRINT ALL WORDS ---------------------------

// Depth-first traversal to print all full words (accumulating path)
static void radix_print_dfs(const RadixNode *node, char *buffer, int depth) {
    // Copy this node's key into the buffer at current depth
    strcpy(buffer + depth, node->key);
    // Advance depth by the length of this node's key
    depth += (int)strlen(node->key);
    // If this node marks a completed word, terminate buffer and print
    if (node->is_end) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }
    // Recurse for each child
    for (int i = 0; i < node->child_count; i++) {
        radix_print_dfs(node->children[i], buffer, depth);
    }
}

// Public function to print all stored words
static void radix_print_all(const RadixNode *root) {
    // Allocate a buffer to hold the longest possible path (adjust size if needed)
    char buffer[512];
    // For each child of root start a DFS
    for (int i = 0; i < root->child_count; i++) {
        radix_print_dfs(root->children[i], buffer, 0);
    }
}

// --------------------------- MEMORY CLEANUP ---------------------------

// Recursively free all nodes in the Radix Tree
static void radix_free(RadixNode *node) {
    // For each child free recursively first
    for (int i = 0; i < node->child_count; i++) {
        radix_free(node->children[i]);
    }
    // Free the dynamic children array
    free(node->children);
    // Free the key substring
    free(node->key);
    // Free the node itself
    free(node);
}

// --------------------------- INTERACTIVE MENU ---------------------------

// Show the menu options to the user
static void show_menu(void) {
    // Print a blank line for readability
    printf("\n");
    // Print menu title
    printf("=== Radix Tree Menu ===\n");
    // Print option 1
    printf("1. Insert word\n");
    // Print option 2
    printf("2. Search full word\n");
    // Print option 3
    printf("3. Check prefix\n");
    // Print option 4
    printf("4. Print all words\n");
    // Print option 5
    printf("5. Quit\n");
    // Prompt user for a choice
    printf("Enter choice: ");
}

// Run an interactive loop letting the user manipulate the tree
static void interactive_loop(RadixNode *root) {
    // Variable to hold the user's numeric menu choice
    int choice;
    // Buffer to store user-input words or prefixes
    char input[256];
    // Loop forever until user chooses to quit
    while (1) {
        // Show menu each iteration
        show_menu();
        // Read the choice; if invalid input, clear and continue
        if (scanf("%d", &choice) != 1) {
            // Clear invalid characters from input buffer
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            // Tell user input was invalid
            printf("Invalid input. Try again.\n");
            // Restart loop
            continue;
        }
        // Switch based on the choice
        if (choice == 1) {
            // Prompt for the word to insert
            printf("Enter word to insert (lowercase a-z): ");
            // Read the word
            if (scanf("%255s", input) == 1) {
                // Insert the word
                radix_insert(root, input);
                // Confirm insertion (even if it existed; this simple version does not check duplicates explicitly)
                printf("Inserted: %s\n", input);
            } else {
                // Handle bad input
                printf("Invalid word input.\n");
            }
        } else if (choice == 2) {
            // Prompt for search word
            printf("Enter full word to search: ");
            // Read the word
            if (scanf("%255s", input) == 1) {
                // Perform search
                bool found = radix_search(root, input);
                // Report result
                printf("Word \"%s\" %s.\n", input, found ? "FOUND" : "NOT FOUND");
            } else {
                // Handle bad input
                printf("Invalid word input.\n");
            }
        } else if (choice == 3) {
            // Prompt for prefix
            printf("Enter prefix to check: ");
            // Read the prefix
            if (scanf("%255s", input) == 1) {
                // Test prefix existence
                bool present = radix_starts_with(root, input);
                // Report result
                printf("Prefix \"%s\" %s present.\n", input, present ? "IS" : "is NOT");
            } else {
                // Handle bad input
                printf("Invalid prefix input.\n");
            }
        } else if (choice == 4) {
            // Print all stored words
            printf("--- All Words ---\n");
            radix_print_all(root);
        } else if (choice == 5) {
            // Announce exit
            printf("Exiting menu...\n");
            // Break out of the loop
            break;
        } else {
            // Handle an unsupported menu number
            printf("Unknown choice. Try again.\n");
        }
    }
}

// --------------------------- MAIN DEMO ---------------------------

// Entry point of the program
int main(void) {
    // Create the root node with an empty key
    RadixNode *root = create_node("");
    // If root creation failed terminate program
    if (!root) {
        return 1;
    }
    // Insert a few sample words before menu starts
    radix_insert(root, "apple");
    radix_insert(root, "app");
    radix_insert(root, "ape");
    radix_insert(root, "bat");
    radix_insert(root, "bar");
    radix_insert(root, "bark");
    // Print a banner letting the user know initial data was inserted
    printf("Initial sample words inserted (apple, app, ape, bat, bar, bark).\n");
    // Enter the interactive menu loop
    interactive_loop(root);
    // After menu ends free all allocated memory
    radix_free(root);
    // Return success code
    return 0;
}

