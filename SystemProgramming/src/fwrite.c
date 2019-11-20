#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person
{
    char name[20];
    int age;
};

// View created file command
// '''hexdump people'''
// add option [-C] is ASCII

static int write_to_file(void)
{
    FILE *fp = NULL;
    struct person kim = {
	.name = "kim",
	.age = 20
    };
    struct person lee = {
	.name = "lee",
	.age = 30
    };

    if(!(fp = fopen("people","w"))){
	return -1; 
    }

// size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    if(fwrite(&kim, sizeof(struct person), 1, fp) != 1){
	goto err;
    };
    if(fwrite(&lee, sizeof(struct person), 1, fp) != 1){
	goto err;
    };

    fclose(fp); 
    return 0;

err:
    if(fp) {
	fclose(fp);
    }
    return -1;
}

static int read_from_file(void)
{
    FILE *fp;
    int i;
    struct person people[2];
    
    if(!(fp = fopen("people","r"))){
	return -1; 
    }

    if(fread(people, sizeof(struct person), 2, fp) != 2){
	fclose(fp);
	return -1;
    };

    fclose(fp);

    for(i=0; i<2; i++){
	printf("name : %s, age : %d\n", people[i].name, people[i].age);
    }

    return 0;
}

int main (int argc, char *argv[])
{
    if (write_to_file()){
	printf("write fail\n");
	return -1;
    };

    if (read_from_file()){
	printf("write fail\n");
	return -1;
    };    

    return 0;
}
