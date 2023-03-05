// Используется для сборки полученной строки и выполения всех комманд

#include <string.h>

void __puts(char StringLine[]){
    char OutputString[strlen(StringLine)];
    memset(OutputString,0,sizeof(OutputString));
    int index_output_string = 0;

    int activ_read = 0;

    for(int i = 0; i < strlen(StringLine); i++){
        if( (StringLine[i] == '"') && (activ_read == 0)){
            activ_read = 1;
            continue;
        }
        if( (StringLine[i] == '"') && (activ_read == 1)){
            activ_read = 0;
            break;
        }

        if(activ_read == 1){
            OutputString[index_output_string] = StringLine[i];
            index_output_string+=1;
        }
    }
    printf("%s\n",OutputString);

}
