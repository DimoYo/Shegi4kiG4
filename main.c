#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "Hashmap.h"

/**
 * insert: 1.622563
update: 8.451588
get: 8.621937
delete: 11.991240
get deleted: 30.035062

 */
char *rand_string_alloc(size_t size)
{
	char *str = malloc(size + 1);
	if (str)
	{
		const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK";
		if (size)
		{
			--size;
			for (size_t n = 0; n < size; n++)
			{
				int key = rand() % (int)(sizeof charset - 1);
				str[n] = charset[key];
			}
			str[size] = '\0';
		}
	}
	return str;
}
void deinit_hashmap(Hashmap* hashmap){
    free(hashmap->list);
    free(hashmap);
}
#define Lister 100000
int main()
{

    struct HashHead *hashmap = init();
    char* tester[Lister];
    clock_t begin,end;
    double time_spent;
    for(int i = 0;i<Lister;i++){
        tester[i] = rand_string_alloc(10);
    }
    begin = clock();
    for(int i =0;i<Lister;i++){
        if(insert(hashmap,tester[i],tester[i]) == Error_repeating){
            printf("2");
        }
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("insert: %f\n",time_spent);
    printf("size: %d\n", find_bit(hashmap));
    begin = clock();
    for(int i =0;i<Lister-1;i++){
        if(update(hashmap,tester[i],tester[i+1]) == Error){
            printf("2 ");
        }

    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("update: %f\n",time_spent);
    begin = clock();
    int m = 0;
    for(int i =0;i<Lister-1;i++){
        if(get(hashmap,tester[i]) != tester[i+1]){
              m++;
        }
    }
    if(get(hashmap,tester[Lister-1]) != tester[Lister-1]){
        m++;
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("get: %f\n",time_spent);
    begin = clock();
    for(int i =0;i<Lister-1;i++){
        if(delete(hashmap,tester[i]) ==Error){
            printf("2 ");
        }
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("delete: %f\n",time_spent);
    begin = clock();
    for(int i =0;i<Lister-1;i++){

        if(get(hashmap,tester[i]) != tester[i+1]){
            m++;
        }
    }
    if(get(hashmap,tester[Lister-1]) != tester[Lister-1]){
        m++;
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("get deleted: %f\n",time_spent);
    for(int i = 0;i<Lister;i++){
        free(tester[i]);
    }
    for(int i =0;i<Lister;i++){
        tester[i] = rand_string_alloc(10);
        if(insert(hashmap,tester[i],tester[i]) == Error_repeating){
            printf("2");
        }

    }
    for(int i =0;i<Lister-1;i++){
        if(update(hashmap,tester[i],tester[i+1]) == Error){
            printf("2 ");
        }

    }
    for(int i =0;i<Lister-1;i++){
        if(get(hashmap,tester[i]) != tester[i+1]){
            m++;
        }
    }
    if(get(hashmap,tester[Lister-1]) != tester[Lister-1]){
        m++;
    }
    for(int i = 0;i<Lister;i++){
        free(tester[i]);
    }
    printf("%lu, %lu",m,hashmap->size);
    deinit_hashmap(hashmap);
    return 0;
}
/*
 *
1.542028
0.639431
0.679939
1.003936
12.597597
 */