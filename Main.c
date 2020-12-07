#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
  int indice;
  char nome[20];
  int crm;
  char especialidade[50];

} Medico; // Criando uma struct( Objeto ) para o médico.

typedef struct{
  char usuario[20];
  char senha[20];
} Login; // Criando uma struct( Objeto ) para o usuário que deseja logar.

typedef struct
{
  int numero_consulta;
  char nome_paciente[20];
  char data[10];
  int crm_medico;
  char anotacoes[100];

} Consulta; // Criando uma struct( Objeto ) para a estrutura Consulta.

typedef struct Node {
  Medico medico; // Uma lista encadeada possui um espaço para inserir informações( podem ser objetos, inteiros, bytes entre outros...)
  struct node* next; // Uma referência para o próximo node
} Node; // Criando um NODE para ligar as structs de Médicos através de uma lista encadeada simples

typedef struct Node_Consulta {
  Consulta consulta; // Struct Consulta
  struct node* next; // Referência para o próximo
} Node_Consulta; // Criando um NODE para ligar as structs de Consultas através de uma lista encadeada simples

typedef struct list {
  int size; // Tamanho
  Node* head; // Cabeçalho ( Inicio )
} List; // Criando a estrutura da lista encadeada da lista dinâmica de Médicos

typedef struct List_Consulta {
  int size;
  Node_Consulta* head; // Guardando a posição do Node seguinte
} List_Consultas; // Criando a estrutura da lista encadeada da lista dinâmica de Consultas

List* createList(){
  List* list = (List *) malloc(sizeof(List)); // Malloc utilizado para toda vez que for adicionado alguma informação, criar um novo endereço na memória e guardar.
  list -> size = 0; // Iniciando com tamanho 0
  list -> head = NULL; // Iniciando com a informação do Node seguinte como NULL, pois,o médico que é inserido será o novo cabeçalho da lista.

  return list;
} // Criando a lista encadeada simples para guardar os dados do Médico através de alocação dinâmica

List_Consultas* createList_Consultas(){
  List_Consultas* list = (List_Consultas *) malloc(sizeof(List_Consultas));
  list -> size = 0;
  list -> head = NULL;

  return list;
} // Mesma coisa sobre a lista de Médicos, porém, com o objeto de Consulta.


int validCRM(List* lista, int crm){ // Função para validar o CRM
  Node* point = lista -> head; // Pega a cabeça (inicio) da lista

  while(point != NULL){ // Se a próxima posição do Node for Null quer dizer que ele alcançou o final da lista.
    if( point -> medico.crm == crm ){ // Comparação para achar um CRM válido
      return 1;
    }else{
      point = point -> next; // Caso não encontre ele prossegue ao próximo Node
    }
  }
}

void add(List* lista, Medico medico) { // Função para adicionar uma struct Médico na Lista
  Node* node = (Node*) (malloc(sizeof(Node))); // Criando um espaço para a struct
  node -> medico = medico; // Relacionando o objeto passado por parâmetro ao Node criado
  node -> next = lista -> head; // Relacionando o próximo ao cabeçalho da lista
  lista -> head = node; // Alocando a cabeça ao node
  lista -> size++; // Aumentando o tamanho da lista
}

void add_consulta(List_Consultas* lista, Consulta consulta) {
  Node_Consulta* node = (Node_Consulta*) (malloc(sizeof(Node_Consulta))); // Mesma coisa da função add(List* lista, Medico medico) acima
  node -> consulta = consulta;
  node -> next = lista -> head;
  lista -> head = node;
  lista -> size++;
}

void print(List* lista){ // Função para mostrar todos os médicos cadastrados
    Node* point = lista -> head; // Começando pela cabeça da lista
    
    if (isEmpty(lista) == 0) printf("Lista vazia!\n"); // Verificar se a lista está vazia
    
    while(point != NULL){ // Enquanto Fim da Lista ( posição do próximo Node == NULL )
      printf("\nMédico\n\tNome: %s\n\tCRM: %i\n\tEspecialidade: %s\n",point -> medico.nome, point -> medico.crm, point -> medico.especialidade);
      point = point -> next; // Próximo Node
    }
    printf("\n");
}

void print_(List_Consultas* lista){ // Mesma coisa dos médicos cadastrados, porém, com as consultas cadastradadas.
    Node_Consulta* point = lista -> head;
    
    if (isEmpty_lista(lista) == 0) printf("Lista vazia!\n");
    
    while(point != NULL){
      printf("\nConsulta\n\tNúmero: %i\n\tPaciente: %s\n\tData: %s\n\tCRM(Médico): %i\n\tAnotações: %s\n",point -> consulta.numero_consulta, point -> consulta.nome_paciente, point -> consulta.data, point -> consulta.crm_medico, point -> consulta.anotacoes);
      point = point -> next;
    }
    printf("\n");
}

int isEmpty(List* lista){ // Auxiliar a função de retornar tamanho da lista de médicos
  return (lista -> size);
}

int isEmpty_lista(List_Consultas* lista){ // Auxiliar a função de retornar tamanho da lista de consultas
  return (lista -> size);
}

int size(List* lista){ // Retorna o tamanho da lista de médicos
  printf("%d",isEmpty(lista));
  return isEmpty(lista);
}

int size_lista(List_Consultas* lista){ // Retorna o tamanho da lista de médicos
  return isEmpty_lista(lista);
}


void writeFile(Medico medico){ // Função para escrever a struct Médico no arquivo
  FILE *f = fopen("medicos.bin","ab");

  fwrite(&medico, sizeof(Medico),1,f);

  fclose(f);
}

void writeFile_(Consulta consulta){ // Função para escrever a struct Consulta no arquivo
  FILE *f = fopen("consultas.bin","ab");

  fwrite(&consulta, sizeof(Consulta),1,f);

  fclose(f);
}

void printPacient_Order(List_Consultas* lista, Consulta consulta){
  Node_Consulta* point = lista -> head;
  Consulta consultas[size_lista(lista)]; // Criando uma lista auxiliar para as structs Consulta
  FILE *file = fopen("consultas.bin","rb"); 
  
  int cont = 0,i=0,j=0,z=0,r=0;
  char aux[80];
 
  while(fread(&consulta,sizeof(Consulta),1,file) == 1){ // Lendo o arquivo
    consultas[cont] = consulta; // Salvando todos os dados do arquivo na array de Consultas
    point = point -> next; // Próximo node
    cont++; // Contador da Array
  }
    
  for (i = 0; i < size_lista(lista); i++) // Ordenando as consultas por ordem alfabética
  {
    for (j = i+1; j < size_lista(lista); j++)
    {
      r = strcmp(consultas[i].nome_paciente,consultas[j].nome_paciente); // Comparando o atual com o próximo
      if(r > 0){ // Caso retorne 0 quer dizer que o nome atual vem depois do próximo ( No caso da ordem alfabética )
        strcpy(aux,consultas[i].nome_paciente); // Fazendo a cópia do atual
        strcpy(consultas[i].nome_paciente,consultas[j].nome_paciente); // Trocando de posições
        strcpy(consultas[j].nome_paciente,aux); // Ajustando a posição atual
      }
    }
    
  }
  
  for (z = 0; z < size_lista(lista); z++) // Printando todas as consultas com o novo resultado da ordem
  {
    printf("\nConsulta\n\tPaciente: %s\n\tData: %s\n\tCRM(Médico): %i\n\tAnotações: %s\n",consultas[z].nome_paciente,consultas[z].data,consultas[z].crm_medico,consultas[z].anotacoes);
  }
  fclose(file);

  
}

void printPacient(List_Consultas* lista, char nome[30]){ // Parâmetro Nome
  Node_Consulta* point = lista -> head; // Cabeça da lista

  while(point != NULL){
    if(strcmp(point -> consulta.nome_paciente,nome) == 0){ // Se o Node atual com o nome do paciente for o mesmo que o inserido pelo usuário, a função retorna 0
      printf("\nConsulta\n\tNúmero: %i\n\tPaciente: %s\n\tData: %s\n\tCRM(Médico): %i\n\tAnotações: %s\n",point -> consulta.numero_consulta, point -> consulta.nome_paciente, point -> consulta.data, point -> consulta.crm_medico, point -> consulta.anotacoes);
      point = point -> next;
    }else{
      point = point -> next; // Caso contrário, próximo Node é chamado
    }
  }
}

int login(Login logon){ // Função de login, através de um arquivo salvo
    FILE *file = fopen("registros.txt", "r");
    char usuario[30];
    char senha[30];

    if(!file){ // Caso o arquivo não exista ele cria um, com o usuário e senha digitados pela primeira vez no programa
      fclose(file);
      FILE *f = fopen("registros.txt", "w+");
      fprintf(f,"%s\n%s",logon.usuario,logon.senha);
      fclose(f);
      return 1; // Retorna 1( true ) para o usuário automaticamente logado.
    }else { // Caso o arquivo já exista, ele só pega os dados do arquivo e faz uma comparação.
        fscanf(file,"%s\n%s",usuario,senha);
        if(strcmp(usuario,logon.usuario) == 0 && strcmp(senha,logon.senha) == 0){
          return 1; // Retorna 1( true ) para o usuário logado.
        }
      return 0;// Caso o usuário e senha inseridos pelo usuário estejam incorretos.
    }
}

void loadDocs(List* lista ,Medico medico){ // Função para carregar os arquivos de médicos.
  FILE *f = fopen("medicos.bin","rb"); 
  if(!f){ // Caso não exista, ele cria um automaticamente
    FILE *g = fopen("medicos.bin","ab");
    printf("\nArquivo criado com sucesso!\n");
    fclose(g);
  }else{
    while(fread(&medico,sizeof(Medico),1,f)){ // Caso já exista, ele lê todos os dados do arquivo
      add(lista,medico); // Adiciona a lista de médicos
      }
    }
  fclose(f);
}

void loadConsults(List_Consultas* lista ,Consulta consulta){ // Mesma coisa do loadDocs, porém, ele carrega os dados das consultas.
  FILE *f = fopen("consultas.bin","rb"); 
  if(!f){
    FILE *g = fopen("consultas.bin","ab");
    printf("\nArquivo criado com sucesso!\n");
    fclose(g);
  }else{
    while(fread(&consulta,sizeof(Consulta),1,f)){
      add_consulta(lista,consulta);
      }
    }
  fclose(f);
}

int main(void){ // Principal
  //Declaração de Variáveis
  List* lista = createList(); // Cria a lista de médicos
  List_Consultas* lista_consultas = createList_Consultas(); // Cria a lista de consultas
  
  char usuario[20]; 
  char senha[20];

  Consulta consulta; //
  Medico medico;     // Criação de structs para relacionar com os objetos
  Login user;        //

  loadDocs(lista,medico); // Carregando os médicos
  loadConsults(lista_consultas,consulta); // Carregando as consultas

  char nome_paciente[20];

  FILE * arq;
  int menu = -1;
  int logon = 0;
  //

  //Autenticação do usuário ao sistema
  printf("Login\nUsuário: ");
  scanf("%s", user.usuario);
  printf("Senha: ");
  scanf("%s", user.senha);
  
  logon = login(user);
  system("clear");
  //

  //Caso o login retorne 1, o usuário estará devidamente autenticado
  if(logon == 1){
    printf("Autenticação concluída!\n\n");
    
      do { // Menu principal
        printf("Menu\n1) Adicionar médico\n2) Visualizar médicos\n3) Adicionar consulta\n4) Visualizar consultas\n5) Consultar paciente\n6) Atendimentos (Ordem Alfabética)\n7) Sair\nOpcao: ");
        scanf("%i", &menu);
        switch (menu)
        {
        case 1:
          system("clear");
          printf("Digite o CRM do Médico: "); 
          scanf("%i", &medico.crm); // Perguntando o CRM, para não existir a possibilidade de duplicidade dentro do arquivo
          if(validCRM(lista,medico.crm) == 1){ // Caso retorne 1, é porque o CRM já está cadastrado
            system("clear");
            printf("CRM cadastrado!\n");
            break; 
          }
          // Caso não esteja cadastrado, os outros dados são perguntados ao usuário para completar o cadastro do médico
          printf("\nDigite o nome: ");
          scanf("%s",medico.nome); // medico.nome, chamando o objeto medico e atribuindo ao mesmo o dado de nome.
          
          printf("Digite a especialidade: ");
          scanf("%s",medico.especialidade); // medico.especialidade, chamando o objeto medico e atribuindo ao mesmo o dado de especialidade.
          
          medico.indice = size(lista); // Indice do médico sempre vai ser o tamanho da lista
          add(lista,medico);// Adicionando o médico a lista de médicos
          writeFile(medico); // Escrevendo no arquivo o médico
          
          system("clear");
          printf("\nMedico cadastrado com sucesso!\n");

          break;
        
        case 2:
          system("clear");  
          print(lista); // Listar todos os médicos cadastrados.
          break;
        case 3:
          system("clear");

          printf("Digite o CRM do médico: "); // Para cadastrar uma consulta, o usuário deve validar o CRM do médico para não existir consulta sem um médico cadastrado
          scanf("%i", &consulta.crm_medico);

          if(validCRM(lista,consulta.crm_medico) == 0){
            system("clear");
            printf("CRM não cadastrado!\n");
            break;
          }

          printf("Digite o nome do Paciente: ");
          scanf("%s", consulta.nome_paciente); // Atribuindo valor ao objeto consulta

          printf("Digite a data do atendimento: ");
          scanf("%s", consulta.data); // Atribuindo valor ao objeto consulta

          printf("Anotações: ");
          scanf("%s",consulta.anotacoes); // Atribuindo valor ao objeto consulta

          consulta.numero_consulta = size_lista(lista_consultas); // Indice do médico sempre vai ser o tamanho da lista

          add_consulta(lista_consultas,consulta); // Adicionando a consulta a lista

          writeFile_(consulta); // Escrevendo a consulta no arquivo

          system("clear");
          printf("\nConsulta cadastrada com sucesso!\n");
          
          break;
        case 4:
          system("clear");
          print_(lista_consultas); // Visualizar consultas cadastradas, não em ordem alfabética
          break;
        case 5:
          system("clear");
          printf("Digite o nome do paciente: ");
          scanf("%s",nome_paciente); // Perguntando o nome requisitado pelo usuário, para descobrir as consultas do paciente

          printPacient(lista_consultas,nome_paciente); // Função para listar as consultas de um certo paciente
          break;
        case 6:
          system("clear");
          printPacient_Order(lista_consultas,consulta); // Listar em ordem alfabética as consultas
          break;
        case 7:
          system("clear"); // Sair do sistema
          exit(0);
          break;

        default:
          system("clear");
          printf("\n Opcao invalida!"); // Opção default caso o usuário não escolha o que está no menu
          break;
        }
      } while(menu != 7);
      } else {
        printf("\nUsuário ou senha incorretos!\n"); // Caso o usuário erre o login e senha
        exit(0);
      }
}
