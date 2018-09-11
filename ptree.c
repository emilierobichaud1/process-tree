#include <stdio.h>
#include <sys/stat.h>
// Add your system includes here.
#include <stdlib.h>
#include "ptree.h"
// Defining the constants described in ptree.h
const unsigned int MAX_PATH_LENGTH = 1024;

// If TEST is defined (see the Makefile), will look in the tests 
// directory for PIDs, instead of /proc.
#ifdef TEST
    const char *PROC_ROOT = "tests";
#else
    const char *PROC_ROOT = "/proc";
#endif


/*
 * Creates a PTree rooted at the process pid. The root of the tree is
 * placed in root. The function returns 0 if the tree was created 
 * successfully and 1 if the tree could not be created or if at least
 * one PID was encountered that could not be found or was not an 
 * executing process.1
 */

struct TreeNode* createnode(int pid) {
    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    FILE* fp;
    node->pid = pid;
    char procfile[MAX_PATH_LENGTH + 1];
    char* name = malloc(sizeof(char) * MAX_PATH_LENGTH);
    sprintf(procfile, "%s/%d/cmdline", PROC_ROOT, pid);
    fp = fopen(procfile, "r");
    fscanf(fp, "%s",name);
    if(name==NULL) {
	node->name = NULL;}
    if(name!=NULL) {
    node->name = name;}
    fclose(fp);
    return node;}

void helper(struct TreeNode* parentnode) {
    FILE* fp;
    char procfile[MAX_PATH_LENGTH+1];
    int pid = parentnode->pid;
    sprintf(procfile, "%s/%d/task/%d/children", PROC_ROOT, pid, pid);
    fp = fopen(procfile, "r");
    int child_pid;
    fscanf(fp, "%dNULL", &child_pid);
    parentnode->child_procs = createnode(child_pid);
    struct TreeNode* newnode = parentnode->child_procs;
    while(fscanf(fp, "%d ", &child_pid) != EOF) {
	newnode->next_sibling = createnode(child_pid);
	newnode = newnode->next_sibling;}
    fclose(fp);
    struct TreeNode* newernode = parentnode->child_procs;
    while(newernode != NULL) {
	int new_pid = newernode->pid;
	sprintf(procfile, "%s/%d/task/%d/children", PROC_ROOT, new_pid, new_pid);
	fp = fopen(procfile, "r");
        int otherpid;
	if(fscanf(fp, " %d", &otherpid)!=EOF) {
		helper(newernode);}
	newernode = newernode->next_sibling;}}    

int generate_ptree(struct TreeNode **root, pid_t pid) {
    char procfile[MAX_PATH_LENGTH + 1];
    struct stat *restrict buf = malloc(sizeof(struct stat));
    sprintf(procfile, "%s/%d/exe", PROC_ROOT, pid);
    if (lstat(procfile, buf) != 0) {
        return 1;
    }
    sprintf(procfile, "%s/%d", PROC_ROOT, pid);
    if (lstat(procfile, buf) != 0) {
        return 1;
    }
    (*root) = malloc(sizeof(struct TreeNode));
    (*root)->pid = pid;
    (*root)->next_sibling = NULL;
    FILE* fp;
    char* name = malloc(sizeof(char) * MAX_PATH_LENGTH);
    (*root)->name = name;
    sprintf(procfile, "%s/%d/cmdline", PROC_ROOT, pid);
    fp = fopen(procfile, "r");
    fscanf(fp, "%s", name);
    helper(*root);
    fclose(fp);
    return 0;
}


/* Prints the TreeNodes encountered on a preorder traversal of an PTree
iprocfiltruct TreeNode* node, FILE* fp, int pid, char procfile[MAX_PATH_LENGTH + 1])
 * 2) to a specified maximum depth. If the maximum depth is 0, then the 
 * entire tree is printed.
 */
void print_ptree(struct TreeNode *root, int max_depth) {
    static int space = 0;
    if((root != NULL) && (max_depth != space || max_depth==0)) {
	printf("%*s", space * 2, "");
	if(root->name != NULL) {
        	printf("%d: %s\n", root->pid, root->name);}
        if(root->name == NULL) {
		printf("%d\n", root->pid);}
	if(root->child_procs != NULL) {
		space+=1;
		print_ptree(root->child_procs, max_depth);
		space-=1;}
	if(root->next_sibling != NULL) {
		print_ptree(root->next_sibling, max_depth);}
}}

