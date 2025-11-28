#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#define N 5
#define MAX 5

using namespace std;

int posCliente = 0;
int posFilme = 0;
int posIndustriaCine = 0;


struct Cliente {
    int id;
    char nome [100];
    int telefone;
};

struct Filme {
    int codigo;
    char titulo [100];
    char genero [100];
    int ano;
    int idCliente;
};

struct IndustriaCine{
    char nomeIndustria [100];
    char local [100];
    int cnae;
};


bool clienteExiste(Cliente vetorC[], int id, int tam) {
    for (int i = 0; i < tam; i++) {
        if (vetorC[i].id == id)
            return true;
    }
    return false;
}


void menu() {
    cout << "\n------ MENU ------\n";
    cout << "1 - Cadastrar Cliente\n";
    cout << "2 - Cadastrar Filme\n";
    cout << "3 - Cadastrar Produtora\n";
    cout << "4 - Listar Clientes\n";
    cout << "5 - Listar Filmes\n";
    cout << "6 - Listar Produtora\n";
    cout << "7 - Buscar Filmes por Cliente\n";
    cout << "8 - Relatorio Geral\n";
    cout << "9 - Salvar Cliente\n";
    cout << "10 - Salvar Filme\n";
    cout << "11 - Salvar Produtora\n";
    cout << "12 - Carregar Cliente\n";
    cout << "13 - Carregar Filme\n";
    cout << "14 - Carregar Produtora\n";
    cout << "15 - Sair\n";
    cout << "Digite sua opcao: ";
}


void cadastrarCliente(Cliente *c, Cliente vetorC[]) {
    do {
        cout << "Digite o ID: ";
        cin >> c->id;
        if (clienteExiste(vetorC, c->id, posCliente))
            cout << "ID EXITENTE!!! Digite outro.\n";
    } while (clienteExiste(vetorC, c->id, posCliente));
    cin.ignore();
    cout << "Digite o Nome: ";
    cin.getline(c->nome, 100);
    cout << "Digite o Telefone: ";
    cin >> c->telefone;
}

void cadastrarFilme(Filme *f, Cliente vetorC[]) {
    cout << "Digite o Codigo do filme: ";
    cin >> f->codigo;
    cin.ignore();
    cout << "Digite o Titulo do Filme: ";
    cin.getline(f->titulo, 100);
    cout << "Digite o Genero do Filme: ";
    cin.getline(f->genero, 100);
    cout << "Digite o Ano: ";
    cin >> f->ano;
    cout << "Digite o ID do cliente que alugou (-1 se nenhum): ";
    cin >> f->idCliente;

    if (f->idCliente != -1 && !clienteExiste(vetorC, f->idCliente, posCliente)) {
        cout << "Cliente nao encontrado!\n";
        f->idCliente = -1;
    }
}

void cadastrarIndustria(IndustriaCine *i) {
    cin.ignore();
    cout << "Nome da Produtora: ";
    cin.getline(i->nomeIndustria, 100);
    cout << "Local: ";
    cin.getline(i->local, 100);
    cout << "CNAE: ";
    cin >> i->cnae;
}


void listarClientes(Cliente vetorC[]) {
    if (posCliente == 0) {
        cout << "Nenhum cliente cadastrado.\n";
        return;
    }

    cout << "\n--- LISTA DE CLIENTES ---\n";
    for (int i = 0; i < posCliente; i++) {
        cout << "ID: " << vetorC[i].id << endl;
        cout << "Nome: " << vetorC[i].nome << endl;
        cout << "Telefone: " << vetorC[i].telefone << endl;
        cout << "-----------------------------\n";
    }
}

void listarFilmes(Filme vetorF[], int tamF, Cliente vetorC[], int tamC) {
    if (tamF == 0) {
        cout << "Nenhum filme cadastrado.\n";

    }

    cout << "\n--- LISTA DE FILMES ---\n";
    for (int i = 0; i < tamF; i++) {
        cout << "Codigo: " << vetorF[i].codigo << endl;
        cout << "Titulo: " << vetorF[i].titulo << endl;
        cout << "Genero: " << vetorF[i].genero << endl;
        cout << "Ano: " << vetorF[i].ano << endl;

        if (vetorF[i].idCliente != -1) {
            for (int j = 0; j < tamC; j++) {
                if (vetorC[j].id == vetorF[i].idCliente)
                    cout << "Alugado por: " << vetorC[j].nome << endl;
            }
        } else {
            cout << "Dispon�vel\n";
        }
        cout << "-----------------------------\n";
    }
}

void listarProdutora(IndustriaCine vetorI[]) {
    cout << "\n--- LISTA DAS PRODUTORAS ---\n";
    for (int i = 0; i < posIndustriaCine; i++) {
        cout << "Nome da Produtora: " << vetorI[i].nomeIndustria << endl;
        cout << "Local " << vetorI[i].local << endl;
        cout << "CNAE: " << vetorI[i].cnae << endl;
        cout << "-----------------------------\n";
    }

}

void buscarFilmesPorCliente(Filme vetorF[], int tamF, Cliente vetorC[], int tamC) {
    int idBusca;
    cout << "Digite o ID do cliente: ";
    cin >> idBusca;

    bool achouCliente = false;
    string nomeCliente;
    for (int i = 0; i < tamC; i++) {
        if (vetorC[i].id == idBusca) {
            achouCliente = true;
            nomeCliente = vetorC[i].nome;
            break;
        }
    }
    if (!achouCliente) {
        cout << "Cliente n�o encontrado.\n";
    }
    cout << "\nFilmes alugados por " << nomeCliente << ":\n";
    bool achouFilme = false;
    for (int i = 0; i < tamF; i++) {
        if (vetorF[i].idCliente == idBusca) {
            cout << "- " << vetorF[i].titulo << " (" << vetorF[i].ano << ")\n";
            achouFilme = true;
        }
    }
    if (!achouFilme)
        cout << "Nenhum filme alugado.\n";
}

void relatorioGeral(Filme vetorF[], int tamF, Cliente vetorC[], int tamC) {
    cout << "\n--- RELATORIO GERAL ---\n";
    for (int i = 0; i < tamC; i++) {
        int cont = 0;
        for (int j = 0; j < tamF; j++) {
            if (vetorF[j].idCliente == vetorC[i].id)
                cont++;
        }
        cout << vetorC[i].nome << " alugou " << cont << " filme(s)\n";
    }
}

void adicionarCliente(Cliente vetorC[], Cliente c) {
    if (posCliente < N)
        vetorC[posCliente++] = c;
    else
        cout << "Lista de clientes cheia.\n";
}

void adicionarFilme(Filme vetorF[], Filme f) {
    if (posFilme < N)
        vetorF[posFilme++] = f;
    else
        cout << "Lista de filmes cheia.\n";
}

void adicionarIndustria(IndustriaCine vetorI[], IndustriaCine i) {
    if (posIndustriaCine < N)
        vetorI[posIndustriaCine++] = i;
    else
        cout << "Lista de produtora cheia.\n";
}

void salvarCliente (Cliente vet[]){
    fstream meuArquivo;

    meuArquivo.open("cliente.bin", ios::out | ios::binary);

        if(meuArquivo.is_open()) {
        meuArquivo.write((char *) &posCliente, sizeof(int));
        meuArquivo.write((char *) vet, sizeof(Cliente) * posCliente);
        meuArquivo.close();
        cout << "Informacoes salvas com sucesso!!\n";
    }
    else {
        cout << "Falha ao gravar informacoes.\n";
    }
}

void salvarFilme (Filme vetf[], int n){
    fstream meuArquivo;

    meuArquivo.open("filme.bin", ios::out | ios::binary);

     if(meuArquivo.is_open()) {
        meuArquivo.write((char *) &posFilme, sizeof(int));
        meuArquivo.write((char *) vetf, sizeof(Filme) * posFilme);
        meuArquivo.close();
        cout << "Informacoes salvas com sucesso!!\n";
    }
    else {
        cout << "Falha ao gravar informacoes.\n";
    }
}

void salvarProdutora (IndustriaCine veti[], int n){
    fstream meuArquivo;

    meuArquivo.open("prod.bin", ios::out | ios::binary);

    if(meuArquivo.is_open()) {
        meuArquivo.write((char *) &posIndustriaCine, sizeof(int));
        meuArquivo.write((char *) veti, sizeof(IndustriaCine) * posIndustriaCine);
        meuArquivo.close();
        cout << "Informacoes salvas com sucesso!!\n";
    }
    else {
        cout << "Falha ao gravar informacoes.\n";
    }
}

void carregarCliente(Cliente vet[]){
    fstream meuArquivo;

    meuArquivo.open("cliente.bin", ios::in | ios::binary);

    if(meuArquivo.is_open()) {
        meuArquivo.read((char *) &posCliente, sizeof(int));
        meuArquivo.read((char *) vet, sizeof(Cliente)* posCliente);

        meuArquivo.close();
        cout << "Clientes carregados com sucesso!\n";
    }
    else {
        cout << "Falha ao carregar informacoes.\n";
    }
}

void carregarFilme(Filme vetf[], int *n){
    fstream meuArquivo;

    meuArquivo.open("filme.bin", ios::in | ios::binary);

    if(meuArquivo.is_open()) {
        meuArquivo.read((char *) &posFilme, sizeof(int));
        meuArquivo.read((char *) vetf, sizeof(Filme)* posFilme);

        meuArquivo.close();
        cout << "Filmes carregados com sucesso!\n";
    }
    else {
        cout << "Falha ao carregar informacoes.\n";
    }
}

void carregarProdutora(IndustriaCine veti[], int *n){
    fstream meuArquivo;

    meuArquivo.open("prod.bin", ios::in | ios::binary);

     if(meuArquivo.is_open()) {
        meuArquivo.read((char *) &posIndustriaCine, sizeof(int));
        meuArquivo.read((char *) veti, sizeof(IndustriaCine)* posIndustriaCine);

        meuArquivo.close();
        cout << "Produtoras carregadas com sucesso!\n";
    }
    else {
        cout << "Falha ao carregar informacoes.\n";
    }
}




int main() {
    Cliente vetorC[N];
    Filme vetorF[N];
    IndustriaCine vetorI[N];
    Cliente c;
    Filme f;
    IndustriaCine i;
    int escolha;

    do {
        menu();
        cin >> escolha;

        switch (escolha) {
            case 1:
                cadastrarCliente(&c, vetorC);
                adicionarCliente(vetorC, c);
                break;
            case 2:
                cadastrarFilme(&f, vetorC);
                adicionarFilme(vetorF, f);
                break;
            case 3:
                cadastrarIndustria(&i);
                adicionarIndustria(vetorI, i);
                break;
             case 4:
            listarClientes(vetorC);
            break;

        case 5:
            listarFilmes(vetorF, posFilme, vetorC, posCliente);
            break;

        case 6:
            listarProdutora(vetorI);
            break;

        case 7:
            buscarFilmesPorCliente(vetorF, posFilme, vetorC, posCliente);
            break;

        case 8:
            relatorioGeral(vetorF, posFilme, vetorC, posCliente);
            break;

        case 9:
            salvarCliente(vetorC);
            break;

        case 10:
            salvarFilme(vetorF, posFilme);
            break;

        case 11:
            salvarProdutora(vetorI, posIndustriaCine);
            break;

        case 12:
            carregarCliente(vetorC);
            break;

        case 13:
            carregarFilme(vetorF, &posFilme);
            break;

        case 14:
            carregarProdutora(vetorI, &posIndustriaCine);
            break;

        case 15:
            cout << "Saindo do sistema...\n";
            break;

        default:
            cout << "Opcao invalida.\n";
    }

} while (escolha != 15);

    return 0;
}
