#include <stdio.h>
#include <stdlib.h>

#include "CONF/__lexer.h"


#define smile ">)"
#define true 1
#define false 0

void InitializationInterpretator();
void PrintToken(char ResultDefinitionToken[][100], int KToken, int SymbolInTokens[]);

void main(void){
    InitializationInterpretator();
}

void InitializationInterpretator(){
    int activ_core = 1;
    char StringLine[100];

    char ResultDefinitionToken[100][100];
    int KToken;
    int SymbolInTokens[100];

    system("cls");
    while(activ_core){
        printf("%s ",smile);
        gets(StringLine);

        if(strcmp(StringLine, "end")==0){
            activ_core = false;
        }

        GetTokenInLine(StringLine, ResultDefinitionToken, &KToken, SymbolInTokens);
        DefinitionToken(ResultDefinitionToken, KToken, SymbolInTokens, StringLine);

        //PrintToken(ResultDefinitionToken, KToken, SymbolInTokens);
    }
}

// Вывод всех токенов
void PrintToken(char ResultDefinitionToken[][100], int KToken, int SymbolInTokens[]){
    for(int index_token = 0; index_token < KToken; index_token++){
        for(int symbol_index = 0; symbol_index < SymbolInTokens[index_token]; symbol_index++){
            printf("%c",ResultDefinitionToken[index_token][symbol_index]);
        }
        printf("\n");
    }
}
