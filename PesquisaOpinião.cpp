#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    HANDLE arquivo;
    DWORD bytesEscritos, bytesLidos;
    char buffer[256];

    // 1. Criar o arquivo
    arquivo = CreateFile(
        "opiniao.txt",              // nome do arquivo
        GENERIC_WRITE | GENERIC_READ, // leitura e escrita
        0,                          // sem compartilhamento
        NULL,                       // segurança padrão
        CREATE_ALWAYS,              // cria novo ou sobrescreve
        FILE_ATTRIBUTE_NORMAL,      // atributos
        NULL                        // sem template
    );

    if (arquivo == INVALID_HANDLE_VALUE) {
        cout << "Erro ao criar o arquivo (" << GetLastError() << ")." << endl;
        return 1;
    }

    // 2. Pergunta da pesquisa
    cout << "=== Sistema de Pesquisa de Opiniao ===" << endl;
    cout << "Pergunta: Voce acredita que pesquisas de opiniao ajudam a melhorar a sociedade?" << endl;
    cout << "Digite sua resposta: ";
    cin.getline(buffer, sizeof(buffer));

    // 3. Escrever no arquivo
    if (!WriteFile(arquivo, buffer, strlen(buffer), &bytesEscritos, NULL)) {
        cout << "Erro ao escrever no arquivo (" << GetLastError() << ")." << endl;
        CloseHandle(arquivo);
        return 1;
    }

    // 4. Voltar ponteiro para o início
    SetFilePointer(arquivo, 0, NULL, FILE_BEGIN);

    // 5. Ler o conteúdo do arquivo
    if (!ReadFile(arquivo, buffer, sizeof(buffer)-1, &bytesLidos, NULL)) {
        cout << "Erro ao ler o arquivo (" << GetLastError() << ")." << endl;
        CloseHandle(arquivo);
        return 1;
    }
    buffer[bytesLidos] = '\0';

    // 6. Mostrar na tela
    cout << "\nConteudo gravado no arquivo:" << endl;
    cout << buffer << endl;

    // 7. Fechar o arquivo
    CloseHandle(arquivo);
    
	return 0;
}