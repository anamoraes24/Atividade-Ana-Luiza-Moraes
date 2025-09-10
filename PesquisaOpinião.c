#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE arquivo;
    DWORD bytesEscritos, bytesLidos;
    char buffer[256];

    // 1. Criar o arquivo
    arquivo = CreateFile(
        "opiniao.txt",              // nome do arquivo
        GENERIC_WRITE | GENERIC_READ, // modo de acesso
        0,                          // sem compartilhamento
        NULL,                       // segurança padrão
        CREATE_ALWAYS,              // cria novo ou sobrescreve
        FILE_ATTRIBUTE_NORMAL,      // atributos
        NULL                        // sem template
    );

    if (arquivo == INVALID_HANDLE_VALUE) {
        printf("Erro ao criar o arquivo (%lu).\n", GetLastError());
        return 1;
    }

    // 2. Pergunta da pesquisa
    printf("=== Sistema de Pesquisa de Opiniao ===\n");
    printf("Pergunta: Voce acha que a tecnologia melhora a qualidade de vida?\n");
    printf("Digite sua resposta: ");
    fgets(buffer, sizeof(buffer), stdin);

    // 3. Escrever no arquivo
    if (!WriteFile(arquivo, buffer, strlen(buffer), &bytesEscritos, NULL)) {
        printf("Erro ao escrever no arquivo (%lu).\n", GetLastError());
        CloseHandle(arquivo);
        return 1;
    }

    // 4. Voltar ponteiro para o início
    SetFilePointer(arquivo, 0, NULL, FILE_BEGIN);

    // 5. Ler do arquivo
    if (!ReadFile(arquivo, buffer, sizeof(buffer)-1, &bytesLidos, NULL)) {
        printf("Erro ao ler o arquivo (%lu).\n", GetLastError());
        CloseHandle(arquivo);
        return 1;
    }
    buffer[bytesLidos] = '\0';

    // 6. Mostrar conteúdo
    printf("\nConteudo gravado no arquivo:\n%s\n", buffer);

    // 7. Fechar o arquivo
    CloseHandle(arquivo);
    
	return 0;
}