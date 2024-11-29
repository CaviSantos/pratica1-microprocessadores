#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    FILE *arquivotexto, *arquivobinario;
    
    arquivotexto = fopen("arquivo.txt", "w");
    
    if(arquivotexto == NULL){
        return 1;
    }
    
    //o intuito de cada fprintf é ser cada um escrito em uma linha.
    //um abaixo do outro no arquivo.
    fprintf(arquivotexto, "%s","add\n");
    fprintf(arquivotexto,"%s","0001\n");
    fprintf(arquivotexto,"%s","sub\n");
    fprintf(arquivotexto,"%s","0010\n");
    
    fclose(arquivotexto);
    
    
    
    arquivobinario = fopen("arquivo.bin", "wb");
    
    if(arquivobinario == NULL){
        return 1;
    }
    
    char ch;
    
    arquivotexto = fopen("arquivo.txt", "r");

    while((ch = fgetc(arquivotexto))!= EOF ){
        
        fwrite(&ch, sizeof(ch), 1, arquivobinario);
    }
    
    
    fclose(arquivobinario);
    fclose(arquivotexto);
    
    return 0;
}
