/* This module is a leical analizer for the
 * programming language  >>Cluty<<
 * IKIGAI Corparation 2023 year
 * v1.0 Beta
 */
#include <string.h>
#include "__token.h"
#include "__parser.h"

void WriteSymbolToken(char ResultDefinitionToken[][100], char Symbol, int KToken, int SymbolInTokens[]);
void WriteStringToken(char ResultDefinitionToken[][100], char String[], int KToken, int SymbolInString, int SymbolInTokens[]);

// Процедура для получения всех токенов в строке
// TokenInLine - исходная строка
// ResultDefinitionToken - полученный список токенов в строке
// KToken - количесвто найденных токенов;
void GetTokenInLine(char StringLine[], char ResultDefinitionToken[][100], int *KToken, int SymbolInTokens[]){
    *KToken = 0;
    // Перемененная для тестовой строки в которую записывается токен
    char TestString[100];
    // Переменная для индекса тестовой строки в которую записывается токен
    int IndexTestString = 0;
    // Переменная для символьного токена
    char TestSymbol;

    for(int index_line = 0; index_line < strlen(StringLine); index_line++){

        // Ищем токены исключая пробелы
        if(StringLine[index_line] != ' '){
            TestString[IndexTestString] = StringLine[index_line];
            IndexTestString++;
            TestSymbol = StringLine[index_line];
        }
        for(int index_token = 0; index_token < (sizeof(AllToken)/sizeof(AllToken[0])); index_token++){

            // Для токенов больше 1 символа
            if( (strlen(AllToken[index_token].token) > 1) &&  (strcmp(TestString, AllToken[index_token].token) == 0) ){

                WriteStringToken(ResultDefinitionToken, TestString, *KToken, IndexTestString, SymbolInTokens);

                memset(TestString,0,sizeof(TestString));
                IndexTestString = 0;
                *KToken += 1;

                break;
            }
            // Для токенов в один симовл
            if( (strlen(AllToken[index_token].token) == 1) && (AllToken[index_token].token[0] == TestSymbol) ){

                WriteSymbolToken(ResultDefinitionToken, TestSymbol, *KToken, SymbolInTokens);

                memset(TestString,0,sizeof(TestString));
                IndexTestString = 0;
                *KToken += 1;

                break;
            }
        }
    }
}

// Записываем токен симовла в общий пул
void WriteSymbolToken(char ResultDefinitionToken[][100], char Symbol, int KToken, int SymbolInTokens[]){
    SymbolInTokens[KToken] = 1;
    ResultDefinitionToken[KToken][0] = Symbol;
}
// Записываем токен строки в общий пул
void WriteStringToken(char ResultDefinitionToken[][100], char String[], int KToken, int SymbolInString, int SymbolInTokens[]){
    SymbolInTokens[KToken] = SymbolInString;
    for(int index = 0; index < SymbolInString; index++){
        ResultDefinitionToken[KToken][index] =  String[index];
    }
}

// Процедура для определения главного токена в строке
void DefinitionToken(char ResultDefinitionToken[][100], int KToken, int SymbolInTokens[], char StringLine[]){
    char TestToken[100];
    int IndexInTestToken = 0;

    for(int index_token = 0; index_token < KToken; index_token++){
        for(int symbol_index = 0; symbol_index < SymbolInTokens[index_token]; symbol_index++){

            TestToken[IndexInTestToken] = ResultDefinitionToken[index_token][symbol_index];
            IndexInTestToken+=1;

            // Поиск главного токена
            for(int main_index = 0; main_index < (sizeof(MainToken)/sizeof(MainToken[0])); main_index++){
                if(strcmp(TestToken, MainToken[main_index].token) == 0){

                    // Проверяем по id_token какой главныйтокен был найден и инициализируем его
                    switch (MainToken[main_index].id_token){
                        case 1:
                            InitializationPuts(ResultDefinitionToken, KToken, SymbolInTokens, StringLine);
                            break;
                    }
                }
            }
        }
    }
}

// Инициализация комманды === puts ===, проверка на ошибки синтаксиса
void InitializationPuts(char ResultDefinitionToken[][100], int KToken, int SymbolInTokens[], char StringLine[]){
    char TestToken[100];

    // Индекс для перебора токенов комманды === puts ===
    int IndexPuts = 0;
    // Для ошибок
    char ErrPuts[10];

    for(int index_token = 0; index_token < KToken; index_token++){
        for(int symbol_index = 0; symbol_index < SymbolInTokens[index_token]; symbol_index++){
            TestToken[symbol_index] = ResultDefinitionToken[index_token][symbol_index];
        }

        if(strcmp(TestToken, constuct_puts[IndexPuts].token) == 0){
            memset(TestToken,0,sizeof(IndexPuts));
            IndexPuts+=1;
        }else{
            ErrPuts[index_token] = '1';
        }
    }


    if(KToken < (sizeof(constuct_puts)/sizeof(constuct_puts[0]))){
        printf("Error!\n");
    }else{
        printf("KToken:%d; core:%d\n",KToken , (sizeof(constuct_puts)/sizeof(constuct_puts[0])));
        __puts(StringLine);
    }
}
