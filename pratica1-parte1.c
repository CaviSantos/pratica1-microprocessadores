#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char* instrucoes_para_binario(const char* instrucao){
    if(strcmp(instrucao, "add") == 0 ) return "0001";
    else if(strcmp(instrucao, "sub") ==0) return "0010";
    else return NULL;
    
}

int main()
{
    FILE *arquivotexto, *arquivobinario; // ponteiro para arquivos.
    
    
    arquivotexto = fopen("arquivo.txt", "w"); // abre o arquivo de texto na função write
    
    if(arquivotexto == NULL){ // se o arquivo não abrir ele retorna 1.
        return 1;
    }
    
    //o intuito de cada fprintf é ser cada um escrito em uma linha.
    //um abaixo do outro no arquivo.
    fprintf(arquivotexto, "%s","add\n"); //0001
    fprintf(arquivotexto,"%s","1111\n");
    fprintf(arquivotexto,"%s","1100\n");
    
    
    fprintf(arquivotexto,"%s","sub\n"); //0010
    fprintf(arquivotexto,"%s","0101\n");
    fprintf(arquivotexto,"%s","0110\n");

    
    fclose(arquivotexto); // fecha o arquivo txt.
    
    
    
    arquivobinario = fopen("arquivo.bin", "wb"); // abre o arquivo binario.
    
    if(arquivobinario == NULL){ // verifica se abriu, se não retorna 1.
        return 1;
    }
    
    char linha[256]; //ponteiro para char, para alocar as linhas dinamicamente.
    
    
    arquivotexto = fopen("arquivo.txt", "r"); // abre novamente o arquivo txt.

    while(fgets(linha,sizeof(linha),arquivotexto)!= NULL ){ // converte as cada linha do arquivo txt para binario.
        linha[strcspn(linha, "\n")] = 0;
        
        const char *bin = instrucoes_para_binario(linha);
        
        if(bin !=NULL){
            fwrite(bin,sizeof(char),4,arquivobinario);
        }
        else{
            fwrite(linha, sizeof(linha),strlen(linha),arquivobinario);
        }
        
    }
    
    
    fclose(arquivobinario);
    fclose(arquivotexto);
    
    return 0;
}
