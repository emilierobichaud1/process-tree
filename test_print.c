#include <stdio.h>
#include <stdlib.h>

#include "ptree.h"


int main(int argc, char *argv[]) {
    // Creates a ptree to test printing
    struct TreeNode root, child_one, child_two, child_three, grandchild, greatgrandchild, grandchild2, greatgrandchild2;
    root.child_procs = &child_one;
    root.next_sibling = NULL;
    root.pid = 1;
    root.name = NULL;

    child_one.name = "first child";
    child_one.child_procs = &grandchild;
    child_one.next_sibling = &child_two;
    child_one.pid = 2;

    child_two.name = "second child";
    child_two.child_procs = NULL;
    child_two.next_sibling = &child_three;
    child_two.pid = 7;

    child_three.name = "third child";
    child_three.child_procs = NULL;
    child_three.next_sibling = NULL;
    child_three.pid = 8;

    grandchild.name = "grandchild";
    grandchild.child_procs = &greatgrandchild;
    grandchild.next_sibling = &grandchild2;
    grandchild.pid = 3;

    grandchild2.name = "grandchild 2";
    grandchild2.child_procs = NULL;
    grandchild2.next_sibling = NULL;
    grandchild2.pid = 6;


    greatgrandchild.name = "great grandchild";
    greatgrandchild.child_procs = NULL;
    greatgrandchild.next_sibling = &greatgrandchild2;
    greatgrandchild.pid = 4;
    
    greatgrandchild2.name = "great grandchild";
    greatgrandchild2.child_procs = NULL;
    greatgrandchild2.next_sibling = NULL;
    greatgrandchild2.pid = 5;


    print_ptree(&root, 0);

    return 0;
}

