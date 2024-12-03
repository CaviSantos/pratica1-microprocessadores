#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Função para converter as instruções em binário
uint8_t instrucoes_para_binario(const char* instrucao) {
    if (strcmp(instrucao, "add") == 0) return 0x01;  // 0001 em binário
    else if (strcmp(instrucao, "sub") == 0) return 0x02; // 0010 em binário
    else return 0x00;  // Caso a instrução não seja add ou sub
}

// Função para converter uma string binária em um byte (uint8_t)
void string_para_binario(const char* buffer, uint8_t *byte) {
    uint8_t len = strlen(buffer);
    *byte = 0;  // Inicializamos o byte como 0
    
    // Convertemos a string binária para o byte correspondente
    for (uint8_t i = 0; i < len; i++) {
        if (buffer[i] == '1') {
            *byte |= (1 << (len - 1 - i));  // Definimos o bit correspondente
        }
    }
}

int main() {
    FILE *arquivotexto, *arquivobinario;  // Ponteiros para arquivos

    // Abrir o arquivo de texto para escrita
    arquivotexto = fopen("arquivo.txt", "w");
    if (arquivotexto == NULL) {
        return 1;
    }

    // Escrever instruções e números binários no arquivo de texto
    fprintf(arquivotexto, "%s", "add\n");  // ADD
    fprintf(arquivotexto, "%s", "1111\n");
    fprintf(arquivotexto, "%s", "1100\n");

    fprintf(arquivotexto, "%s", "sub\n");  // SUB
    fprintf(arquivotexto, "%s", "0101\n");
    fprintf(arquivotexto, "%s", "0110\n");

    fclose(arquivotexto); // Fechar o arquivo de texto

    // Abrir o arquivo binário para escrita
    arquivobinario = fopen("arquivo.bin", "wb");
    if (arquivobinario == NULL) {
        return 1;
    }

    char linha[256];  // Buffer para armazenar cada linha lida do arquivo de texto
    uint8_t binario;  // Variável para armazenar o valor binário correspondente à linha
    
    // Abrir o arquivo de texto para leitura
    arquivotexto = fopen("arquivo.txt", "r");

    // Processa cada linha do arquivo de texto
    while (fgets(linha, sizeof(linha), arquivotexto) != NULL) {
        linha[strcspn(linha, "\n")] = 0;  // Remover a quebra de linha do final da string

        // Verificar se a linha é uma instrução e converter para binário
        if (strcmp(linha, "add") == 0 || strcmp(linha, "sub") == 0) {
            binario = instrucoes_para_binario(linha);  // Converter instrução para binário
        } else {
            string_para_binario(linha, &binario);  // Converter string binária para byte
        }

        // Escrever o byte no arquivo binário
        fwrite(&binario, sizeof(uint8_t), 1, arquivobinario);
    }

    fclose(arquivobinario);  // Fechar o arquivo binário
    fclose(arquivotexto);    // Fechar o arquivo de texto

    return 0;
}
