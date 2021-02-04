//
//  main.c
//  Algo prog
//
//  Created by COTTEN on 21/09/2020.
//  Copyright © 2020 Cotten. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* ex1(char* c1, char* c2);
char* palindrome(char* c);
int voyelles(char* c);
void conjug(char* c);
char* copy(char* c);
char* concat(char* c1, char* c2);
char* subchain(char* c, int fst, int lst);


int main(int argc, const char * argv[]) {
    char c1[15] = "tortue";
    char* c2 = "ninja";
    printf("%s\n", ex1(c1, c2));
    printf("%s\n", palindrome(c2));
    printf("%d voyelles dans %s\n", voyelles(c2), c2);
    conjug("chanter");
    printf("%s\n", copy("fenec"));
    printf("%s\n", concat("tortue ", "ninja"));
    printf("%s", subchain("coucou", 0, 2));
    return 0;
}

char* ex1(char* c1, char* c2){
    printf("length c1: %d, length c2: %d\n", (int) strlen(c1), (int) strlen(c2));
    int comp = strcmp(c1, c2);
    if (comp > 0)
        printf("c1 > c2\n");
    else if (comp < 0)
        printf("c1 < c2\n");
    else
        printf("c1 = c2\n");
    strcat((strcat(c1, " : ")), c2);
    return c1;
}

char* palindrome(char* c){
    int len = (int) strlen(c);
    for (int i = 0; i < (len / 2); i++)
        if (c[i] != c[len - i - 1])
            return "false";
    return "true";
}

int voyelles(char* c){
    int count = 0;
    for(int i = 0; i < (int) strlen(c); i++)
        switch (c[i]) {
            case 'a':
                count++;
                break;
            case 'e':
                count++;
                break;
            case 'i':
                count++;
                break;
            case 'o':
                count++;
                break;
            case 'u':
                count++;
                break;
            case 'y':
                count++;
                break;
            default:
                break;
        };
    return count;
}

void conjug(char* c){
    int len = (int) strlen(c);
    char* root = (char*) malloc((len - 2) * sizeof(char));
    strncpy(root, c, len - 2);
    printf("je %se\ntu %ses\nil %se\nnous %sons\nvous %sez\nils %sent\n", root, root, root, root, root, root);
}

char* copy(char* c){
    char* c_copy = (char*) malloc((strlen(c)) * sizeof(char));
    strcpy(c_copy, c);
    return c_copy;
}

char* concat(char* c1, char* c2){
    char* c_concat = (char*) malloc((strlen(c1) + strlen(c2)) * sizeof(char));
    strcpy(c_concat, c1);
    strcat(c_concat, c2);
    return c_concat;
}

char* subchain(char* c, int fst, int lst){
    char* c_sub = (char*) malloc((lst - fst + 1) * sizeof(char));
    for(int i = fst; i <= lst; i++)
        c_sub[i - fst] = c[i];
    return c_sub;
}
