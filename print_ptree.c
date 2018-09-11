#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ptree.h"


int main(int argc, char **argv) {
    // TODO: Update error checking and add support for the optional -d flag
    // printf("Usage:\n\tptree [-d N] PID\n");

    // NOTE: This only works if no -d option is provided and does not
    // error check the provided argument or generate_ptree. Fix this!
    if(argc == 2) {
	struct TreeNode *root = NULL;
        if(generate_ptree(&root, strtol(argv[1], NULL, 10))==0) {
            print_ptree(root, 0);
            return 0;}
	if(generate_ptree(&root, strtol(argv[1], NULL, 10))==1) {
            return 2;}}
    if(argc == 4) {
	struct TreeNode *root = NULL;
	getopt(argc, argv, "d:");
	int level = strtol(optarg, NULL, 10);
	if(generate_ptree(&root, strtol(argv[1], NULL, 10)) == 0) {
	    print_ptree(root, level);}
	if(generate_ptree(&root, strtol(argv[1], NULL, 10)) == 1) {
	    return 2;}}
    if(argc < 2){
	fprintf(stderr, "Too few arguments provided.\n");
	return 1;}
    if(argc == 3){
	fprintf(stderr, "Incorrect number of arguments provided.\n");
	return 1;}
    if(argc > 4) {
	fprintf(stderr, "Too many arguments provided.\n");
	return 1;}

}

