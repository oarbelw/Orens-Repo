// CS2211b 2023
// Assignment number 5
// Oren Arbel-Wood
// 251251876
// oarbelwo
// April 5, 2023

typedef int* Data;

typedef struct {
    char *str1; 
    char *str2;
} Key_struct;

typedef Key_struct* Key;

//for Key
Key key_ini(void);
void key_set(Key key, char *str1, char *str2);
int key_comp(Key key1, Key key2);
void key_print(Key key);
void key_free(Key key);
char * string_dup(char *str);

//for Data
Data data_ini(void);
void data_set(Data data, int intdata);
void data_print(Data data);
void data_free(Data data);