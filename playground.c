#include <stdio.h>

int main(void)
{
    int array[] = {1, 2, 3};
    int array_size = sizeof (array);
    int element_size = sizeof (array[0]);
    printf("The array size is %i bytes. Each element is %i bytes. So the array has %i elements!", array_size, element_size, array_size / element_size);
}