#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char * arg1, char * arg2) {
  char tmp = *arg1;
  *arg1 = *arg2;
  *arg2 = tmp;
}

void reverse(char * str) {
  //WRITE ME!
  if (str == NULL)
    return;

  char * lptr = str;
  size_t len = 0;
  while (*lptr != '\0') {
    len++;
    lptr++;
  }  // lptr now points at \0

  // remove \0 count
  lptr--;

  while (len > 1) {
    swap(str, lptr);
    len = len - 2;
    str++;
    lptr--;
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
