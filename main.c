#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define KEY_LENGTH 5
#define MSG_LENGTH 100

char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void duplicate_key(char msg[], char key[], char key_duplicated[]) {
    int msg_len = strlen(msg);
    int i, key_len = strlen(key);

    for (i=0; i<msg_len; i++) {
        key_duplicated[i] = key[i % key_len];
    }
    key_duplicated[i] = '\0';
}


void generate_vtable(char vtable[26][27]){
    int i, j;
    for (i=0; i<26; i++) {
        for (j=0; j<26; j++)
        {
            vtable[i][j] = tolower(alphabet[(i+j)%26]);
        }
        vtable[i][j] = '\0';
    }
}

void print_vtable(char vtable[26][27]) {
    printf("vtable is as follows:\n");
    for (int i=0; i<26; i++) {
        printf("%s\n", vtable[i]);
    }
}

void encode_text(char text[], char key[], char vtable[26][27], char encoded_text[]) {
    int i, j, k, text_len = strlen(text);
    for (i=0; i<text_len; i++)
    {
        j = key[i] - 'a';
        k = text[i] - 'a';
        encoded_text[i] = vtable[j][k];
    }
    encoded_text[i] = '\0';
}

void decode_text(char encoded_text[], char key[], char vtable[26][27], char text[]) {
    int i, j, k, text_len = strlen(text);
    for (i=0; i<text_len; i++)
    {
        j = key[i] - 'a';
        for (k=0; k<26; k++)
        {
            if (vtable[j][k] == encoded_text[i])
            {
                text[i] = tolower(alphabet[k]);
                break;
            }
        }
    }
    text[i] = '\0';
}


int main() {
    char msg[MSG_LENGTH] = "defensewinschampionships";
    char key[KEY_LENGTH+1] = "crypt";
    char key_duplicated[MSG_LENGTH];
    char vtable[26][27];
    char encoded_msg[MSG_LENGTH];

    printf("msg: %s (length=%d)\n", msg, strlen(msg));
    printf("key: %s (length=%d)\n", key, strlen(key));
    printf("\n");

    duplicate_key(msg, key, key_duplicated);
    printf("duplicated key: %s (length=%d)\n", key_duplicated, strlen(key_duplicated));
    printf("\n");

    generate_vtable(vtable);
    print_vtable(vtable);
    printf("\n");

    encode_text(msg, key_duplicated, vtable, encoded_msg);
    printf("encoded msg: %s\n", encoded_msg);
    printf("\n");

    decode_text(encoded_msg, key_duplicated, vtable, msg);
    printf("decoded msg: %s\n", msg);

    return 0;
}
