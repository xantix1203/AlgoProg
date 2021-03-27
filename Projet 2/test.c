#include <stdio.h>

int main(){
  char* string = "abcd";
  while ((*string) != '\0')
  {
    printf("%s", string);
    string++;
  }
  return 0;
}
