/***************************************************************
 * Radix Tree (Compressed Trie) with:
 * - Insert
 * - Search
 * - Prefix check
 * - Autocomplete
 * - Deletion
 * - Print all words
 * - Interactive menu
 * ALGORITHM comments above each function
 * Plain English comments above every line of code
 ***************************************************************/

#include <stdio.h>    // For input/output (printf, scanf)
#include <stdlib.h>   // For malloc, realloc, free, exit
#include <string.h>   // For strlen, strcpy, strncpy, strncmp, memcpy
#include <stdbool.h>  // For bool, true, false

/* ================================================================
   DATA STRUCTURES
   ------------------------------------------------
   RadixNode:
     - key: edge label (substring) representing the characters on
            the path from parent to this node (compressed).
     - is_end: marks if a complete word ends exactly at this node.
     - children: dynamic array of pointers to child nodes.
     - child_count: how many children currently exist.
   The root holds an empty key "".
   ================================================================ */

// Define the RadixNode structure
typedef struct RadixNode {
    char *key;                 // Substring (edge label) for this node
    bool is_end;               // True if a word terminates here
    struct RadixNode **children; // Dynamic array of child node pointers
    int child_count;           // Number of children entries used
} RadixNode;

/* ================================================================
   HELPER STRUCT FOR DELETION
   ------------------------------------------------
   We want to know:
     removed: did we actually remove (find) the word?
     can_free: after processing, is this node now redundant
               (no children, not end) and safe for parent to free?
   ================================================================ */
typedef struct DeleteResult {
    bool removed;   // Whether the target word was found and removed
    bool can_free;  // Whether the current node can be freed by parent
} DeleteResult;

/* ================================================================
   FUNCTION: dup_string
   PURPOSE:
     Duplicate a C string into a freshly allocated buffer.
   ALGORITHM:
     1. Measure length.
     2. Allocate length + 1.
     3. Copy bytes including terminator.
     4. Return pointer (or NULL on failure).
   ================================================================ */
// Duplicate a string (safe wrapper)
static char *dup_string(const char *s) {
    // Measure the length of the source string (not counting terminator)
    size_t len = strlen(s);
    // Allocate memory for the duplicate including null terminator
    char *copy = (char *)malloc(len + 1);
    // Check allocation success
    if (!copy) return NULL;
    // Copy the original string bytes (including null)
    memcpy(copy, s, len + 1);
    // Return the pointer to the duplicated string
    return copy;
}

/* ================================================================
   FUNCTION: longest_common_prefix
   PURPOSE:
     Find number of matching starting characters between two strings.
   ALGORITHM:
     1. Start i=0.
     2. While both strings have characters and they match, increment i.
     3. Return i.
   ================================================================ */
// Compute the longest common prefix length between two strings
static int longest_common_prefix(const char *a, const char *b) {
    // Start at index 0
    int i = 0;
    // Loop while characters exist and are equal
    while (a[i] && b[i] && a[i] == b[i]) {
        // Move to the next position
        i++;
    }
    // Return how many matched
    return i;
}

/* ================================================================
   FUNCTION: create_node
   PURPOSE:
     Allocate and initialize a new RadixNode with a given key.
   ALGORITHM:
     1. Allocate node.
     2. Duplicate key (or use "").
     3. Initialize is_end=false, children=NULL, child_count=0.
     4. Return node or NULL on failure.
   ================================================================ */
// Create a new node with a specified key substring
static RadixNode *create_node(const char *key) {
    // Allocate memory for a new node
    RadixNode *node = (RadixNode *)malloc(sizeof(RadixNode));
    // Check if allocation failed
    if (!node) {
        // Report memory error
        printf("Memory allocation failed for node.\n");
        // Return NULL to caller
        return NULL;
    }
    // Duplicate the provided key or empty string if NULL
    node->key = dup_string(key ? key : "");
    // Check duplication success
    if (!node->key) {
        // Free the node memory
        free(node);
        // Report error
        printf("Memory allocation failed for key.\n");
        // Return NULL
        return NULL;
    }
    // Initialize as NOT the end of a word
    node->is_end = false;
    // Initialize children pointer to NULL (no children yet)
    node->children = NULL;
    // Initialize child count to 0
    node->child_count = 0;
    // Return new node pointer
    return node;
}

/* ================================================================
   FUNCTION: add_child
   PURPOSE:
     Append a child pointer to a node's dynamic children array.
   ALGORITHM:
     1. Reallocate array to size child_count + 1.
     2. Store new child at new last index.
     3. Increment child_count.
   ================================================================ */
// Append a child node pointer to parent->children
static void add_child(RadixNode *parent, RadixNode *child) {
    // Reallocate the array to hold one more child pointer
    parent->children = (RadixNode **)realloc(
        parent->children,
        sizeof(RadixNode *) * (parent->child_count + 1)
    );
    // Check if reallocation failed
    if (!parent->children) {
        // Report fatal error
        printf("Fatal: realloc failed while adding child.\n");
        // Exit process (simplified error handling)
        exit(EXIT_FAILURE);
    }
    // Store the new child pointer in the last position
    parent->children[parent->child_count] = child;
    // Increment the number of children
    parent->child_count++;
}

/* ================================================================
   FUNCTION: radix_insert
   PURPOSE:
     Insert a lowercase word into the radix tree, creating
     and splitting nodes as needed.
   ALGORITHM:
     1. Start at root with remaining=word.
     2. For each child: compute longest common prefix with remaining.
         a. If LCP=0: ignore child, continue.
         b. If 0<LCP<child_key_len: split child into prefix + suffix node.
         c. Consume LCP characters from remaining.
         d. If remaining becomes empty: mark child.is_end=true, done.
         e. Else descend into child; repeat.
     3. If no child has LCP>0: create new child with entire remaining;
        mark it is_end; done.
   ================================================================ */
// Insert a word into the radix tree
static void radix_insert(RadixNode *root, const char *word) {
    // Keep a pointer to current traversal node
    RadixNode *current = root;
    // Track the unprocessed portion of the word
    const char *remaining = word;
    // Loop until we return upon successful insertion
    while (1) {
        // Flag to record whether we matched any child this round
        bool matched_child = false;
        // Iterate over each existing child of current node
        for (int i = 0; i < current->child_count; i++) {
            // Get the child pointer
            RadixNode *child = current->children[i];
            // Compute longest common prefix length with child's key
            int lcp = longest_common_prefix(child->key, remaining);
            // If no common prefix, try next child
            if (lcp == 0) {
                continue;
            }
            // Mark that we matched something
            matched_child = true;
            // If we matched only part of the child's key (need to split)
            if (lcp < (int)strlen(child->key)) {
                // Create a new node for the child's suffix
                RadixNode *suffix = create_node(child->key + lcp);
                // Check memory allocation success
                if (!suffix) {
                    // Report fatal error
                    printf("Fatal: cannot create suffix node.\n");
                    // Exit because continuing is unsafe
                    exit(EXIT_FAILURE);
                }
                // Move child's existing children to suffix
                suffix->children = child->children;
                suffix->child_count = child->child_count;
                // Preserve original child's end-of-word flag in suffix
                suffix->is_end = child->is_end;
                // Allocate memory for the new truncated key
                char *new_key = (char *)malloc(lcp + 1);
                // Check allocation
                if (!new_key) {
                    printf("Fatal: cannot allocate prefix truncation.\n");
                    exit(EXIT_FAILURE);
                }
                // Copy only the prefix part into new_key
                memcpy(new_key, child->key, lcp);
                // Null terminate the truncated string
                new_key[lcp] = '\0';
                // Free old child key
                free(child->key);
                // Assign truncated key back to child
                child->key = new_key;
                // Reset child's children so we can attach suffix only
                child->children = NULL;
                child->child_count = 0;
                // Attach the suffix as a single child of the newly truncated node
                add_child(child, suffix);
                // Now the truncated node no longer directly marks a word end
                child->is_end = false;
            }
            // If the LCP exactly consumes the entire remaining portion
            if (lcp == (int)strlen(remaining)) {
                // Mark the child node as ending the full word
                child->is_end = true;
                // Insertion complete; return
                return;
            }
            // Otherwise we still have leftover characters below this child
            // Advance remaining pointer by the lcp amount
            remaining += lcp;
            // Descend into the child to continue processing leftover
            current = child;
            // Break out of the child loop to restart outer while with new current
            break;
        }
        // If no child had any matching prefix
        if (!matched_child) {
            // Create a new node taking the entire remaining substring
            RadixNode *new_child = create_node(remaining);
            // Check allocation success
            if (!new_child) {
                printf("Fatal: cannot allocate new child for insertion.\n");
                exit(EXIT_FAILURE);
            }
            // Mark this new node as the end of the word
            new_child->is_end = true;
            // Attach this node to current
            add_child(current, new_child);
            // Insertion complete; return
            return;
        }
        // Loop repeats if matched_child was true and leftover remains
    }
}

/* ================================================================
   FUNCTION: radix_search
   PURPOSE:
     Determine if a full word is stored in the tree.
   ALGORITHM:
     1. Start at root with remaining=word.
     2. While remaining not empty:
         a. For each child: if child->key matches prefix of remaining,
            consume its length, descend.
         b. If no child matches, return false.
     3. After consuming all characters, return current->is_end.
   ================================================================ */
// Search the radix tree for an exact full word
static bool radix_search(const RadixNode *root, const char *word) {
    // Start at the root node
    const RadixNode *current = root;
    // Keep pointer to remaining portion of the word
    const char *remaining = word;
    // Loop until we either finish or fail
    while (*remaining) {
        // Flag to record if we matched a child
        bool found = false;
        // Iterate through each child of current
        for (int i = 0; i < current->child_count; i++) {
            // Get child pointer
            const RadixNode *child = current->children[i];
            // Determine length of child's key
            int klen = (int)strlen(child->key);
            // Compare child's key with the start of remaining
            if (strncmp(remaining, child->key, klen) == 0) {
                // If match, consume that portion
                remaining += klen;
                // Descend to that child
                current = child;
                // Mark found
                found = true;
                // Break out of child loop
                break;
            }
        }
        // If no child matched, the word is absent
        if (!found) return false;
    }
    // Return true only if current node marks a word end
    return current->is_end;
}

/* ================================================================
   FUNCTION: radix_starts_with
   PURPOSE:
     Check whether ANY stored word begins with the given prefix.
   ALGORITHM:
     1. Start at root with remaining=prefix.
     2. While remaining not empty:
         a. For each child compute if its key matches prefix segment.
         b. If remaining length ≤ child->key length and the prefix matches,
            return true (prefix fully covered).
         c. Else consume child->key length, descend.
         d. If no child matches -> return false.
     3. If loop ends normally, prefix exists.
   ================================================================ */
// Check if there exists any word beginning with the given prefix
static bool radix_starts_with(const RadixNode *root, const char *prefix) {
    // Begin at root
    const RadixNode *current = root;
    // Track unmatched prefix portion
    const char *remaining = prefix;
    // Continue while we have characters left in prefix
    while (*remaining) {
        // Track if a child matched this step
        bool found = false;
        // Examine all children
        for (int i = 0; i < current->child_count; i++) {
            // Access child
            const RadixNode *child = current->children[i];
            // Length of child's key
            int klen = (int)strlen(child->key);
            // Determine compare length (minimum of remaining length and child key length)
            int rem_len = (int)strlen(remaining);
            int cmp_len = rem_len < klen ? rem_len : klen;
            // Compare that many characters
            if (strncmp(remaining, child->key, cmp_len) == 0) {
                // If the remaining prefix fits entirely within this child key
                if (rem_len <= klen) {
                    // We have matched entire prefix
                    return true;
                }
                // Otherwise consume full child key from remaining
                remaining += klen;
                // Descend to child node
                current = child;
                // Mark match
                found = true;
                // Break out to continue with next portion
                break;
            }
        }
        // If no child matched, prefix is absent
        if (!found) return false;
    }
    // If we consumed entire prefix we succeeded
    return true;
}

/* ================================================================
   FUNCTION: collect_words
   PURPOSE:
     DFS helper to gather and print all words below a node.
   ALGORITHM:
     1. Append node->key to buffer.
     2. If node->is_end: terminate buffer and print word.
     3. For each child: recurse with updated depth.
   ================================================================ */
// Depth-first helper that prints every word in the subtree
static void collect_words(const RadixNode *node, char *buffer, int depth) {
    // Copy this node's key into buffer at current depth position
    strcpy(buffer + depth, node->key);
    // Advance depth by length of added key
    depth += (int)strlen(node->key);
    // If node marks end-of-word, terminate and print
    if (node->is_end) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }
    // Recurse for each child
    for (int i = 0; i < node->child_count; i++) {
        collect_words(node->children[i], buffer, depth);
    }
}

/* ================================================================
   FUNCTION: autocomplete
   PURPOSE:
     Print all stored words that begin with a given prefix.
   ALGORITHM:
     1. Traverse down matching prefix just like prefix search.
     2. Build prefix into a buffer as we go.
     3. Once prefix is fully matched:
         - Perform DFS (collect_words) from that node.
   EDGE CASE:
     If prefix ends in middle of an edge: we still collect from that node
     because we appended the full matched prefix.
   ================================================================ */
// Print all words that start with the given prefix
static void autocomplete(const RadixNode *root, const char *prefix) {
    // Start at root
    const RadixNode *current = root;
    // Remaining portion of prefix
    const char *remaining = prefix;
    // Buffer to accumulate prefix+suffix words
    char buffer[512] = "";
    // Continue while we have unmatched prefix characters
    while (*remaining) {
        // Whether we matched a child
        bool found = false;
        // For each child of current
        for (int i = 0; i < current->child_count; i++) {
            // Child pointer
            const RadixNode *child = current->children[i];
            // Child key length
            int klen = (int)strlen(child->key);
            // Remaining length
            int rem_len = (int)strlen(remaining);
            // Compare length = smaller of two
            int cmp_len = rem_len < klen ? rem_len : klen;
            // Compare that many characters
            if (strncmp(remaining, child->key, cmp_len) == 0) {
                // Append matched portion to buffer
                strncat(buffer, remaining, cmp_len);
                // If prefix ends within this child key
                if (rem_len <= klen) {
                    // Collect all completions below this child
                    collect_words(child, buffer, (int)strlen(buffer));
                    // Done with autocomplete
                    return;
                }
                // Else consume full child key from remaining
                remaining += klen;
                // Descend
                current = child;
                // Mark found
                found = true;
                // Break to attempt next segment
                break;
            }
        }
        // If no child matched, there are no completions
        if (!found) {
            printf("No completions for prefix: %s\n", prefix);
            return;
        }
    }
    // If we consumed entire prefix exactly at a node boundary
    collect_words(current, buffer, (int)strlen(buffer));
}

/* ================================================================
   FUNCTION: radix_delete_recursive (PRIVATE)
   PURPOSE:
     Recursively delete a word and report both removal success
     and whether the current node can be freed.
   ALGORITHM:
     1. If word part is empty:
         a. If node not marking word, removed=false, can_free=false.
         b. Else unset is_end.
         c. If node now has no children -> can_free=true else false.
     2. Else for each child:
         a. If child key matches prefix of remaining word (full key match required at this level).
         b. Recurse with word advanced by child key length.
         c. If child can be freed: free it and compact children array.
     3. After recursion:
         a. Determine if current can be freed (no children & !is_end).
         b. Propagate removed flag upward unchanged if already true.
     4. If no matching child: removed=false, can_free=false.
   NOTE:
     This simplified deletion does NOT recombine (compress) linear
     chains after partial deletions; only prunes empty leaves.
   ================================================================ */
// Recursive helper for deletion
static DeleteResult radix_delete_recursive(RadixNode *node, const char *word) {
    // If we reached the end of the word characters
    if (*word == '\0') {
        // If this node does not mark a word end, nothing to remove
        if (!node->is_end) {
            // Return removed=false, can_free=false
            return (DeleteResult){ false, false };
        }
        // Otherwise remove the terminal mark
        node->is_end = false;
        // If node has no children now, we can free it
        bool free_now = (node->child_count == 0);
        // Return success status and free suggestion
        return (DeleteResult){ true, free_now };
    }
    // Iterate over children to find matching path
    for (int i = 0; i < node->child_count; i++) {
        // Access child
        RadixNode *child = node->children[i];
        // Determine child's key length
        int klen = (int)strlen(child->key);
        // Check if word segment starts with child's key
        if (strncmp(word, child->key, klen) == 0) {
            // Recurse into child beyond its key
            DeleteResult child_res = radix_delete_recursive(child, word + klen);
            // If child was removed and can be freed
            if (child_res.can_free) {
                // Free child's key
                free(child->key);
                // Free child's children array
                free(child->children);
                // Free child itself
                free(child);
                // Shift remaining children left to fill gap
                for (int j = i; j < node->child_count - 1; j++) {
                    node->children[j] = node->children[j + 1];
                }
                // Decrement child count
                node->child_count--;
                // If no children left allocate pointer cleanup
                if (node->child_count == 0) {
                    // Free the array (was reallocated) to avoid dangling memory
                    free(node->children);
                    // Set pointer to NULL for safety
                    node->children = NULL;
                }
            }
            // Decide if current node can now be freed
            bool can_free_now = (!node->is_end && node->child_count == 0);
            // Return removed flag from child plus current free status
            return (DeleteResult){ child_res.removed, can_free_now };
        }
    }
    // If no child matched prefix, the word is not present
    return (DeleteResult){ false, false };
}

/* ================================================================
   FUNCTION: radix_delete
   PURPOSE:
     Public interface to delete a word and report success.
   ALGORITHM:
     1. Call recursive helper on root.
     2. Ignore root's can_free (we keep root).
     3. Return removed flag.
   ================================================================ */
// Delete a word from the tree, returning whether it was removed
static bool radix_delete(RadixNode *root, const char *word) {
    // Call recursive helper on root
    DeleteResult res = radix_delete_recursive(root, word);
    // Always keep the root (even if empty)
    // Return whether deletion succeeded
    return res.removed;
}

/* ================================================================
   FUNCTION: radix_free
   PURPOSE:
     Recursively free entire tree from a given node downward.
   ALGORITHM:
     1. For each child: recurse free.
     2. Free children array.
     3. Free key string.
     4. Free node.
   ================================================================ */
// Free an entire subtree rooted at 'node'
static void radix_free(RadixNode *node) {
    // Loop through each child and free recursively
    for (int i = 0; i < node->child_count; i++) {
        radix_free(node->children[i]);
    }
    // Free the child pointer array
    free(node->children);
    // Free the key substring memory
    free(node->key);
    // Free the node itself
    free(node);
}

/* ================================================================
   FUNCTION: radix_print_all
   PURPOSE:
     Print every stored word (lexicographic traversal order
     depends on insertion order since children are unsorted).
   ALGORITHM:
     1. For each root child: run collect_words with buffer.
   ================================================================ */
// Print all words in the tree
static void radix_print_all(const RadixNode *root) {
    // Allocate a reusable buffer for word accumulation
    char buffer[512];
    // For each child of root call DFS collector
    for (int i = 0; i < root->child_count; i++) {
        collect_words(root->children[i], buffer, 0);
    }
}

/* ================================================================
   FUNCTION: show_menu
   PURPOSE:
     Display the interactive menu options.
   ALGORITHM:
     1. Print menu header and numbered options.
   ================================================================ */
// Show the menu options to the user
static void show_menu(void) {
    // Print a blank line for readability
    printf("\n");
    // Print menu title
    printf("=== Radix Tree Menu ===\n");
    // Print each numbered option
    printf("1. Insert Word\n");
    printf("2. Search Word\n");
    printf("3. Check Prefix\n");
    printf("4. Autocomplete Prefix\n");
    printf("5. Delete Word\n");
    printf("6. Print All Words\n");
    printf("7. Quit\n");
    // Prompt for user choice input
    printf("Enter choice: ");
}

/* ================================================================
   FUNCTION: interactive_loop
   PURPOSE:
     Repeatedly read user choices and perform operations.
   ALGORITHM:
     LOOP:
       1. Show menu.
       2. Read choice (handle invalid input).
       3. Switch based on choice:
          a. Insert: read word, call radix_insert.
          b. Search: read word, call radix_search.
          c. Prefix: read prefix, call radix_starts_with.
          d. Autocomplete: read prefix, call autocomplete.
          e. Delete: read word, call radix_delete, report result.
          f. Print all: call radix_print_all.
          g. Quit: break loop.
       4. Repeat until quit.
   ================================================================ */
// Run the interactive menu loop
static void interactive_loop(RadixNode *root) {
    // Variable storing user's numeric menu selection
    int choice;
    // Buffer for user-entered words or prefixes
    char input[256];
    // Infinite loop until user chooses to quit
    while (1) {
        // Display the menu
        show_menu();
        // Attempt to read an integer choice
        if (scanf("%d", &choice) != 1) {
            // Clear invalid characters from input buffer
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            // Inform user of invalid entry
            printf("Invalid input. Try again.\n");
            // Continue to next loop iteration
            continue;
        }
        // Handle choice for insertion
        if (choice == 1) {
            // Prompt for word to insert
            printf("Enter word: ");
            // Read word as string
            if (scanf("%255s", input) == 1) {
                // Insert the word
                radix_insert(root, input);
                // Acknowledge insertion
                printf("Inserted: %s\n", input);
            } else {
                // Handle bad input
                printf("Invalid word input.\n");
            }
        }
        // Handle choice for searching full word
        else if (choice == 2) {
            // Prompt for word to search
            printf("Enter word: ");
            // Read word
            if (scanf("%255s", input) == 1) {
                // Perform search
                bool found = radix_search(root, input);
                // Report result
                printf("Word \"%s\" %s.\n", input, found ? "FOUND" : "NOT FOUND");
            } else {
                // Handle invalid input
                printf("Invalid word input.\n");
            }
        }
        // Handle choice for prefix checking
        else if (choice == 3) {
            // Prompt for prefix
            printf("Enter prefix: ");
            // Read prefix
            if (scanf("%255s", input) == 1) {
                // Check prefix existence
                bool exists = radix_starts_with(root, input);
                // Report result
                printf("Prefix \"%s\" %s present.\n", input, exists ? "IS" : "is NOT");
            } else {
                // Handle invalid input
                printf("Invalid prefix input.\n");
            }
        }
        // Handle choice for autocomplete
        else if (choice == 4) {
            // Prompt for prefix
            printf("Enter prefix: ");
            // Read prefix
            if (scanf("%255s", input) == 1) {
                // Perform autocomplete
                autocomplete(root, input);
            } else {
                // Handle invalid input
                printf("Invalid prefix input.\n");
            }
        }
        // Handle choice for deletion
        else if (choice == 5) {
            // Prompt for word to delete
            printf("Enter word to delete: ");
            // Read word
            if (scanf("%255s", input) == 1) {
                // Attempt deletion
                bool removed = radix_delete(root, input);
                // Report outcome
                if (removed) {
                    printf("Deleted: %s\n", input);
                } else {
                    printf("Word \"%s\" not found.\n", input);
                }
            } else {
                // Handle invalid input
                printf("Invalid word input.\n");
            }
        }
        // Handle choice to print all words
        else if (choice == 6) {
            // Header line
            printf("--- All Words ---\n");
            // Print every stored word
            radix_print_all(root);
        }
        // Handle quit selection
        else if (choice == 7) {
            // Inform user of exiting
            printf("Exiting...\n");
            // Break out of loop
            break;
        }
        // Handle unknown menu numbers
        else {
            // Inform user of invalid choice
            printf("Invalid choice.\n");
        }
    }
}

/* ================================================================
   FUNCTION: main
   PURPOSE:
     Program entry point: builds root, inserts sample words,
     then starts interactive menu until user quits.
   ALGORITHM:
     1. Create root node.
     2. Insert sample words (demo).
     3. Print banner.
     4. Enter interactive loop.
     5. On exit free entire tree.
   ================================================================ */
// Entry point of the program
int main(void) {
    // Create the root node with empty key
    RadixNode *root = create_node("");
    // Check if root allocation failed
    if (!root) {
        // Return error code
        return 1;
    }
    // Insert some initial sample words for demonstration
    radix_insert(root, "apple");
    radix_insert(root, "app");
    radix_insert(root, "ape");
    radix_insert(root, "bat");
    radix_insert(root, "bar");
    radix_insert(root, "bark");
    // Print banner showing initial words are inserted
    printf("Sample words inserted: apple, app, ape, bat, bar, bark\n");
    // Run the interactive user menu
    interactive_loop(root);
    // Free all allocated memory in the radix tree
    radix_free(root);
    // Return success status
    return 0;
}

