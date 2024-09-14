#include <stdio.h>
#include<cs50.h>

int main(void)
{
    // Gets users name
    string name = get_string("What's your name? ");
    // Says hello, user name
    printf("hello, %s\n", name);
}