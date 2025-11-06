#include <iostream>
#include <string>

using namespace std;

//constantes que definem o maximo de alunos e cursos
#define M_CURSOS 3
#define M_ALUNOS 300

//structs
struct Curso {
    string nome;
    int codigo;
    int cargaHoraria;
    int vagasTotais;
};

struct Aluno {
    string nome;
    int matricula;
    int idade;
    int codigoCurso;
};

//variaveis globais ("Curso" é a struct, "vetCurso" é o nome do array, "banco de dados")
//M_CURSOS é o tamanho do vetor, que definimos no #define lá em cima
//tudo isso cria um armario na memoria chamado vetCursos com o tamanho correspondente a cada vetor, com cada espaço podendo guardar um curso, vale tmabém pra Alunos
Curso vetCursos[M_CURSOS];
Aluno vetAlunos[M_ALUNOS];
//variaveis globais de contagem que guarda quabtos cadastros já existem em cada variavel
int posCurso = 0;
int posAluno = 0;

//função que busca em qual posição do vetor vetCursos está o curso com determinado código
//se ela encontrar o código, retorna o i, que será a posição na qual o código está, se não encontrar retorna o -1
int buscarIdCurso(int codigo) {
    for (int i = 0; i < posCurso; i++) {
        if (vetCursos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

//Menu
void mostrarMenu() {
    cout << "\n Menu \n";
    cout << "1. para cadastrar Curso\n";
    cout << "2. para cadastrar Aluno\n";
    cout << "3. para listar Cursos\n";
    cout << "4. para listar Alunos\n";
    cout << "5. para mostrar os alunos por Curso\n";
    cout << "6. Relatorio\n";
    cout << "7. Sair\n";
}

// procedimento para cadastrar curso (opção 1 do menu)
void cadastrarCurso() {
    //verifica se o numero maximo de cursos cadastrados já foi atingido, se foi, exibe a mensagem
    if (posCurso >= M_CURSOS) {
        cout << "Numero maximo de cursos atingido!\n";
        return;
    }

    //pede ao usuario o codigo do novo curso e guarda na variavel novoCurso, que é temporária, ela armazena os valores antes de guardar na memoria do vetCursos
    Curso novoCurso;
    cout << "Digite o nome do curso: ";
    cin.ignore();
    getline(cin, novoCurso.nome);
    cout << "Digite o codigo do curso: ";
    cin >> novoCurso.codigo;
    //verifica se o codigo ja foi usado no cadastro de outro curso, se foi, exibe a mensagem
    // o .codigo indica que nao quer a variavel inteira, mas sim só o codigo
    if (buscarIdCurso(novoCurso.codigo) != -1) {
        cout << "Codigo do curso ja existe! Tente novamente.\n";
        return;
    }
    cout << "Digite a carga horaria: ";
    cin >> novoCurso.cargaHoraria;
    cout << "Digite o total de vagas: ";
    cin >> novoCurso.vagasTotais;

    //o computador le que a posCurso é igual a novoCurso (variavel temporaria) e grava no primeiro local vago da variavel global vetCursos
    vetCursos[posCurso] = novoCurso;
    posCurso++;
    cout << "Novo curso cadastrado com sucesso!\n";
}

//procedimento para cadastrar aluno (opcao 2 do menu)
void cadastrarAluno() {
    if (posAluno >= M_ALUNOS) {
        cout << "Numero maximo de alunos atingido.\n";
        return;
    }
    if (posCurso == 0) {
        cout << "Nenhum curso cadastrado. Tente a opcao 1 do menu.\n";
        return;
    }

    //preciso fazer a parte que não deixa repetir no numero da matricula

    Aluno novoAluno;
    cout << "Digite o nome completo do aluno: ";
    cin.ignore();
    getline(cin, novoAluno.nome);
    cout << "Digite o matricula do aluno: ";
    cin >> novoAluno.matricula;
    cout << "Digite a idade do aluno: ";
    cin >> novoAluno.idade;

    cout << "Digite o codigo do curso: ";
    //codigo curso desejado é uma variavel local temporaria pra guardar temporariamente o codigo do usuario pra verificar se ele já existe
    int codigoCursotemp;
    cin >> codigoCursotemp;
    int idCurso = buscarIdCurso(codigoCursotemp);

    //se o codigo não existir, exibe a mensagem
    if (idCurso == -1) {
        cout << "Curso nao encontrado. Tente novamente\n";
        return;
    }

    // se tudo isso estiver correto, o aluno é cadastrado
    novoAluno.codigoCurso = codigoCursotemp;
    vetAlunos[posAluno] = novoAluno;
    posAluno++;
    cout << "Aluno cadastrado com sucesso!\n";
}

//procedimento para listar cursos (opcao 3 do menu)
void listarCursos() {
    //verifica se a posicao do vetor no contador é 0, se for não há cursos cadastrados e o programa sai da funcao
    if (posCurso == 0) {
        cout << "Nenhum curso cadastrado.\n";
        return;
    }

    //caso haja cursos, o loop anda por todos os espacos preenchidos e so para quando i for menor que o tanto de cursos que ja existem
    for (int i = 0; i < posCurso; i++) {
        cout << "................................\n";
        cout << "Curso: " << vetCursos[i].nome; // CORREÇÃO: Usa .nome (consistente com a struct)
        cout << " Codigo: " << vetCursos[i].codigo << "\n";
        cout << " Carga: " << vetCursos[i].cargaHoraria << "h \n";
        cout << " Vagas: " << vetCursos[i].vagasTotais << "\n";
    }
}

//procedimento para listar alunos (opcao 4 do menu)
void listarAlunos() {
    if (posAluno == 0) {
        cout << "Nenhum aluno cadastrado.\n";
        return;
    }

    for(int i; i<posAluno; i++){

        cout << "..................................\n";
        cout << "Aluno: " << vetAlunos[i].nome << "\n";
    }
}

// 5. Buscar Alunos por Curso
void buscarAlunosPorCurso() {
    cout << "Digite o codigo do curso: ";
    int codigoBusca;
    cin >> codigoBusca;
    int indiceCurso = buscarIdCurso(codigoBusca);

    if (indiceCurso == -1) {
        cout << "Erro: Curso nao encontrado.\n";
        return;
    }

    cout << "\n--- Alunos em: " << vetCursos[indiceCurso].nome << " ---\n"; // CORREÇÃO: Usa .nome
    int alunosEncontrados = 0;
    for (int i = 0; i < posAluno; i++) {
        if (vetAlunos[i].codigoCurso == codigoBusca) {
            cout << "  - " << vetAlunos[i].nome << " (Mat: " << vetAlunos[i].matricula << ")\n";
            alunosEncontrados++;
        }
    }
    if (alunosEncontrados == 0) {
        cout << "Nenhum aluno neste curso.\n";
    }
}

// 6. Relatório Geral
void relatorioGeral() {
    if (posCurso == 0) {
        cout << "Nenhum curso cadastrado.\n";
        return;
    }

    cout << "\n--- Relatorio Geral (Alunos por Curso) ---\n";
    for (int i = 0; i < posCurso; i++) {
        Curso c = vetCursos[i];
        int alunosNoCurso = 0;
        for (int j = 0; j < posAluno; j++) {
            if (vetAlunos[j].codigoCurso == c.codigo) {
                alunosNoCurso++;
            }
        }
        cout << c.nome << ": " << alunosNoCurso << " de " << c.vagasTotais << " vagas.\n";
    }
}

int main() {
    int opcao;

    do {
        mostrarMenu();
        cout << "Digite sua opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 1:
                cadastrarCurso();
                break;
            case 2:
                cadastrarAluno();
                break;
            case 3:
                listarCursos();
                break;
            case 4:
                listarAlunos();
                break;
            case 5:
                buscarAlunosPorCurso();
                break;
            case 6:
                relatorioGeral();
                break;
            case 7: cout << "Encerrando...\n"; break;
            default: cout << "Opcao invalida.\n"; break;
        }

    } while (opcao != 7);

    return 0;
}


