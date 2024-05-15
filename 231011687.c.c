/******************************************************************************
Aluno(a): Luiz Felipe Bessa Santos
Matrícula: 231011687
Declaro que eu sou o(a) autor(a) deste trabalho e que o código não foi copiado 
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.
*******************************************************************************/

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <ctype.h>
    #include <locale.h>
    #include <conio.h>


    //Definições para opção selecionada
    #define CONSULTAR_MINIUSINA 1
    #define CONSULTAR_CONSUMIDOR 2
    #define LISTAR_MU_CADASTRADA 3
    #define LISTAR_MU_OP_DECRE_CAP 4  
    #define LISTAR_RA_DECRE_QNT_MU 5
    #define LISTAR_RA_CRE_CONTR 6
    #define LISTAR_RA_DECRE_CAP_GER 7
    #define LISTAR_RA_DECRE_PERCENT_ENERG_DISP 8
    #define SAIR 9

    //Limitação de tamanho 
    #define TAM_MAX_CNPJ 19
    #define TAM_MAX_CPF 15
    #define TAM_MAX_NOME 100
    #define TAM_MAX_STATUS 11
    #define TAM_MAX_CAPTOT 8
    #define TAM_MAX_CNPJ_TEST 14
    #define TAM_MAX_DATA 11
    #define TAM_MAX_ENERGIA_CONTR 7
    #define TAM_MAX_CPFNUMBER 12
    #define TAM_MAX_DESCRESCENTE 15

    //Definição da struct
    struct miniusina{
        char cnpj[TAM_MAX_CNPJ];
        char id[TAM_MAX_CNPJ];
        char nome[TAM_MAX_NOME];
        float cap_tot;
        int ra;
        char status_us[TAM_MAX_STATUS];
        };
        
    struct contrato{
        char id_contrato[2];
        char id_consumidor[TAM_MAX_CNPJ];
        char cnpj_miniusina[TAM_MAX_CNPJ];
        char data_início_contrato[TAM_MAX_DATA];
        char energia_contr[TAM_MAX_ENERGIA_CONTR];

    };

    //Procedimento para consultar as miniusinas com base no cnpj informado e válido
    void consultar_miniusina(char cnpj_consultado[TAM_MAX_CNPJ]){
        //Declaração de variáveis
        FILE *arquivo_miniusinas;
        struct miniusina miniusina_cadastrada;
        int miniusina_encontrada=0;

        //Abrir o arquivo
        arquivo_miniusinas = fopen("miniusinas.csv", "r");

        //Verificar se conseguiu abrir o arquivo
        if(arquivo_miniusinas != NULL){

            //Ignorar a primeira linha do arquivo
            char primeira_linha [1000];
            fscanf(arquivo_miniusinas,"%[^\n]\n",primeira_linha);

            //Ler uma linha do arquivo, e organiza-la
            while(!feof(arquivo_miniusinas)){
                fscanf(arquivo_miniusinas,"%[^;];%[^;];%f;%d;%[^\n]\n",
                    miniusina_cadastrada.cnpj,
                    miniusina_cadastrada.nome,
                    &miniusina_cadastrada.cap_tot,
                    &miniusina_cadastrada.ra,
                    miniusina_cadastrada.status_us);

                    if(strcmp(cnpj_consultado, miniusina_cadastrada.cnpj)==0){
                        miniusina_encontrada++;
                        printf("CNPJ: %s\n", miniusina_cadastrada.cnpj);
                        printf("Nome: %s\n", miniusina_cadastrada.nome);
                        printf("Capacidade Total: %.1f\n", miniusina_cadastrada.cap_tot);
                        printf("RA: %d\n", miniusina_cadastrada.ra);
                        printf("Status Usina: %s\n", miniusina_cadastrada.status_us);
                        printf("Miniusinas encontradas com esse CNPJ: %d\n", miniusina_encontrada);
                        printf("\n");
                    }
            }

        } else{
            printf("Erro. Não consegui abrir o arquivo de miniusinas.\n");
        }

    }

    //Procedimento para consultar os contratos relacionados ao cnpj informado
    void consultar_contratos(char cnpj_consultado[TAM_MAX_CNPJ]){
        //Declaração de varoáveis
        FILE *arquivo_contratos;
        struct contrato contrato_cadastrado;
        int contratos_encontrados=0;

        //Abrir o arquivo
        arquivo_contratos = fopen("contratos.csv","r");

        //Verificar se conseguiu abrir o arquivo
        if(arquivo_contratos!= NULL){

            //Ignorar a primeira linha do arquivo
            char primeira_linha[1000];
            fscanf(arquivo_contratos,"%[^\n]\n",primeira_linha);

            //Ler uma linha do arquivo, e organiza-la
            while(!feof(arquivo_contratos)){
                fscanf(arquivo_contratos,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                contrato_cadastrado.id_contrato,
                contrato_cadastrado.id_consumidor,
                contrato_cadastrado.cnpj_miniusina,
                contrato_cadastrado.data_início_contrato,
                contrato_cadastrado.energia_contr);

                if(strcmp(cnpj_consultado, contrato_cadastrado.cnpj_miniusina) ==0){
                    printf("Contratos vinculados ao CNPJ informado:\n");
                    printf("Id Contrato: %s\n", contrato_cadastrado.id_contrato);
                    printf("Id Consumidor: %s\n",contrato_cadastrado.id_consumidor);
                    printf("CNPJ da Miniusina: %s\n",contrato_cadastrado.cnpj_miniusina);
                    printf("Data de início de contrato: %s\n",contrato_cadastrado.data_início_contrato);
                    printf("Quantidade de energia contratada: %s\n",contrato_cadastrado.energia_contr);
                    printf("\n");
                    contratos_encontrados++;
                }
            }
            if(contratos_encontrados==0){
                printf("Nenhum contrato vinculado ao CNPJ informado.\n");
                printf("\n");
            }

        } else{
            printf("Erro. Não foi possivel abrir o arquivo de contratos\n");
            printf("\n");
        }

    }

    //Procedimento para buscar e monstrar miniusinas que estão cadastradas 3)
    void listarmu() {
        //Declaração de variáveis
        FILE *arquivo_miniusinas;//variável que representa o arquivo
        struct miniusina miniusina_lida;//struct que armazena temp a mu

        //1) Abrir o arquivo
        arquivo_miniusinas = fopen("miniusinas.csv", "r");


        //2 Verificar se foi possível abrir o arquivo
        if(arquivo_miniusinas == NULL){
            printf("Erro. Não foi possível abrir o arquivo com os dados das miniusinas");
            return;
        }
            
            //Descartar a primeira linha
            char primeira_linha[1000];
            fscanf(arquivo_miniusinas, "%[^\n]\n",primeira_linha);

            //Ler e exibir os dados das miniusinas
            while(!feof(arquivo_miniusinas)){
                //Ler uma linha do arquivo colocando os dados na struct
                fscanf(arquivo_miniusinas,"%[^;];%[^;];%f;%d;%[^\n]\n",
                    miniusina_lida.cnpj,
                    miniusina_lida.nome,
                    &miniusina_lida.cap_tot,
                    &miniusina_lida.ra,
                    miniusina_lida.status_us);

                    //Mostrar na tela cada informação lida
                printf("CNPJ: %s\n", miniusina_lida.cnpj);
                printf("Nome: %s\n", miniusina_lida.nome);
                printf("Capacidade Total: %.1f\n", miniusina_lida.cap_tot);
                printf("RA: %d\n", miniusina_lida.ra);
                printf("Status Usina: %s\n", miniusina_lida.status_us);
                printf("\n");                       
            }
        
        //Fechar o arquivo
        fclose(arquivo_miniusinas);
        }


    //Função que imprime o menu
    void menu(){
        printf("****** Menu de Opções ******\n");
        printf("\n");
        printf("Digite a opção do que se deseja:\n");
        printf("1) Consultar miniusina cadastrada\n");
        printf("2) Consultar consumidor cadastrado\n");
        printf("3) Listar as miniusinas cadastradas\n");
        printf("4) Listar as miniusinas em operação por ordem decrescente de capacidade de geração de energia\n");
        printf("5) Listar as RAs por ordem decrescente de quantidade de miniusinas\n");
        printf("6) Listar as RAs por ordem crescente de número de contratos\n");
        printf("7) Listar as RAs por ordem decrescente de capacidade de geração\n");
        printf("8) Listar as RAs por ordem decrescente de percentual de energia disponível\n");
        printf("9) Sair do programa\n");}


    //Função que valide o cnpj
    int cnpj_ver(char cnpj[TAM_MAX_CNPJ]){

        //declaração de variáveis
            int i;
            int j;
            int somatorio=0;
            int somatorio2=0;
            int digito1=0;
            int digito2=0;
            char cnpj_teste[TAM_MAX_CNPJ_TEST];
            int contador_teste=0;
            char digitoverificador;
            char digitoverificador2;

        //retira os caracteres especiais e deixa somente os números, armazenando-os em uma nova variavel
        for(i=0;i<TAM_MAX_CNPJ;i++){
            if(cnpj[i]>=48 && cnpj[i]<=57){
                cnpj_teste[contador_teste]=cnpj[i];
                contador_teste++;
            }
        }
        //verificar o tamanho do cnpj
        if (strlen(cnpj_teste) != TAM_MAX_CNPJ_TEST){
            return 0;
            } else if((strcmp(cnpj_teste,"00000000000000")==0) || (strcmp(cnpj_teste,"11111111111111")==0) || (strcmp(cnpj_teste,"22222222222222")==0)
            || (strcmp(cnpj_teste,"33333333333333")==0) || (strcmp(cnpj_teste,"44444444444444")==0) || (strcmp(cnpj_teste,"55555555555555")==0)
            || (strcmp(cnpj_teste,"66666666666666")==0)  || (strcmp(cnpj_teste,"77777777777777")==0) || (strcmp(cnpj_teste,"88888888888888")==0)
            || (strcmp(cnpj_teste,"99999999999999")==0)){
                return 0;
            } else{
                for(i=0,j=5;i<TAM_MAX_CNPJ_TEST-2;i++,j--){
                    if(j==1){
                        j=9;               
                    }
                    digito1=(cnpj_teste[i]-48)*j;
                    somatorio+=digito1;
                }
                    if(somatorio % 11 == 0 || somatorio % 11 == 1){
                        digitoverificador='0';
                }   else{
                        digitoverificador=(11-(somatorio%11))+48;
                }
                    if (digitoverificador!=cnpj_teste[12]){
                        return 0;
                    }
            {
                for(i=0,j=6;i<TAM_MAX_CNPJ_TEST-1;i++,j--){
                    if(j==1){
                        j=9;
                    }
                    digito2=(cnpj_teste[i]-48)*j;
                    somatorio2+=digito2;
                }
                    if(somatorio2 % 11 ==0 || somatorio2 % 11 == 1){
                        digitoverificador2='0';
                    } else{
                        digitoverificador2=(11-(somatorio2%11))+48;
                    }
                    if(digitoverificador2!=cnpj_teste[13]){
                        return 0;
                    }
        }
    }
            return 1;
    }

//Função que valide o CPF
    int cpf_ver(char cpf[TAM_MAX_CPF]){

    //declaração de variáveis
            int i;
            int j;
            char cpf_number[TAM_MAX_CPFNUMBER];
            int contador_teste=0;
            int todos_iguais=1;
            int digito1=0;
            int somatorio1=0;
            char digitoverificador1;
            int digito2=0;
            int somatorio2=0;
            char digitoverificador2;

        for(i=0;i<TAM_MAX_CPF;i++){
            if(cpf[i]>=48 && cpf[i]<=57){
                cpf_number[contador_teste]=cpf[i];
                contador_teste++;
            }
        }
        //verificar o tamanho do cpf
        if(strlen(cpf_number)!= TAM_MAX_CPFNUMBER-1){
            return 0;
        }

        //checar se todos os dígitos são iguais
        for(i=1;i<11;i++){
            if(cpf_number[i]!= cpf_number[0]){
                todos_iguais=0;
                break;
            }
        }
        //se todos_iguais for verdadeiro (=1), significa que todos os digitos do cpf são os mesmos
        if(todos_iguais){
            return 0;
        }
        //cálculo digito1 verificador
        for(i=0,j=10;i<TAM_MAX_CPFNUMBER-3;i++,j--){
            digito1=(cpf_number[i]-48)*j;
            somatorio1+=digito1;
        }
        if(somatorio1 % 11 == 0 ||somatorio1 % 11 == 1){
            digitoverificador1= '0';
        } else{
            digitoverificador1=(11-(somatorio1 % 11))+48;
        }
        if(digitoverificador1!= cpf_number[9]){
            return 0;
        }


        //cálculo do digito2 verificador
        for(i=0,j=11;i<TAM_MAX_CPFNUMBER-2;i++,j--){
            digito2=(cpf_number[i]-48)*j;
            somatorio2+=digito2;
        }
        if(somatorio2 % 11 == 0 || somatorio2 % 11 == 1){
            digitoverificador2= '0';
        } else {
            digitoverificador2=(11-(somatorio2 % 11))+48;
        }
        if(digitoverificador2 != cpf_number[10]){
            return 0;
        }
    return 1;
    }

    //Procedimento para consultar os contratos relacionados ao cnpj informado, do consumidor
    void consultar_contratos_consumidor_CNPJ(char cnpj_consultado[TAM_MAX_CNPJ]){
        //Declaração de varoáveis
        FILE *arquivo_contratos;
        struct contrato contrato_cadastrado;
        int contratos_encontrados=0;

        //Abrir o arquivo
        arquivo_contratos = fopen("contratos.csv","r");

        //Verificar se conseguiu abrir o arquivo
        if(arquivo_contratos!= NULL){

            //Ignorar a primeira linha do arquivo
            char primeira_linha[1000];
            fscanf(arquivo_contratos,"%[^\n]\n",primeira_linha);

            //Ler uma linha do arquivo, e organiza-la
            while(!feof(arquivo_contratos)){
                fscanf(arquivo_contratos,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                contrato_cadastrado.id_contrato,
                contrato_cadastrado.id_consumidor,
                contrato_cadastrado.cnpj_miniusina,
                contrato_cadastrado.data_início_contrato,
                contrato_cadastrado.energia_contr);

                if(strcmp(cnpj_consultado, contrato_cadastrado.id_consumidor) ==0){
                    printf("Contratos vinculados ao CNPJ informado:\n");
                    printf("Id Contrato: %s\n", contrato_cadastrado.id_contrato);
                    printf("Id Consumidor: %s\n",contrato_cadastrado.id_consumidor);
                    printf("CNPJ da Miniusina: %s\n",contrato_cadastrado.cnpj_miniusina);
                    printf("Data de início de contrato: %s\n",contrato_cadastrado.data_início_contrato);
                    printf("Quantidade de energia contratada: %s\n",contrato_cadastrado.energia_contr);
                    printf("\n");
                    contratos_encontrados++;
                }
            }
            if(contratos_encontrados==0){
                printf("Nenhum contrato vinculado ao CNPJ informado.\n");
                printf("\n");
            }

        } else{
            printf("Erro. Não foi possivel abrir o arquivo de contratos\n");
            printf("\n");
        }

    }

//Procedimento para consultar os contratos relacionados ao CPF informado, do consumidor
    void consultar_contratos_consumidor_CPF(char cpf_consultado[TAM_MAX_CPF]){
        //Declaração de variáveis
        FILE *arquivo_contratos;
        struct contrato contrato_cadastrado;
        int contratos_encontrados=0;

        //Abrir o arquivo
        arquivo_contratos = fopen("contratos.csv","r");

        //Verificar se conseguiu abrir o arquivo
        if(arquivo_contratos!= NULL){

            //Ignorar a primeira linha do arquivo
            char primeira_linha[1000];
            fscanf(arquivo_contratos,"%[^\n]\n",primeira_linha);

            //Ler uma linha do arquivo, e organiza-la
            while(!feof(arquivo_contratos)){
                fscanf(arquivo_contratos,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                contrato_cadastrado.id_contrato,
                contrato_cadastrado.id_consumidor,
                contrato_cadastrado.cnpj_miniusina,
                contrato_cadastrado.data_início_contrato,
                contrato_cadastrado.energia_contr);

                if(strcmp(cpf_consultado, contrato_cadastrado.id_consumidor) ==0){
                    printf("Contratos vinculados ao CPF informado:\n");
                    printf("Id Contrato: %s\n", contrato_cadastrado.id_contrato);
                    printf("Id Consumidor: %s\n",contrato_cadastrado.id_consumidor);
                    printf("CNPJ da Miniusina: %s\n",contrato_cadastrado.cnpj_miniusina);
                    printf("Data de início de contrato: %s\n",contrato_cadastrado.data_início_contrato);
                    printf("Quantidade de energia contratada: %s\n",contrato_cadastrado.energia_contr);
                    printf("\n");
                    contratos_encontrados++;
                }
            }
            if(contratos_encontrados==0){
                printf("Nenhum contrato vinculado ao CPF informado.\n");
                printf("\n");
            }

        } else{
            printf("Erro. Não foi possivel abrir o arquivo de contratos\n");
            printf("\n");
        }

    }

    void listar_mu_cap_decre(){
        //Declaração de variáveis
        FILE *arquivo_miniusinas;//Variavel que representa o arquivo
        struct miniusina miniusina_lida[15];//struct que armazena temp a mu
        int contador=0;

        //1)Abrir o arquivo
        arquivo_miniusinas= fopen("miniusinas.csv", "r");

        //2)Verificar se foi possível abrir o arquivo
        if(arquivo_miniusinas==NULL){
            printf("Erro. Não foi possível abrir o arquivo com os dados da miniusina.");
            return;
        }

        //decarte da primeira linha
        char primeira_linha[1000];
        fscanf(arquivo_miniusinas,"%[^\n]\n",primeira_linha);

        //ler, organizar e printar os dados das miniusinas
        while(!feof(arquivo_miniusinas)){
            //Ler uma linha do arquivo colocando os dados na struct
            fscanf(arquivo_miniusinas,"%[^;];%[^;];%f;%d;%[^\n]\n",
                    miniusina_lida[contador].cnpj,
                    miniusina_lida[contador].nome,
                    &miniusina_lida[contador].cap_tot,
                    &miniusina_lida[contador].ra,
                    miniusina_lida[contador].status_us);
                    contador++;
        }

        fclose(arquivo_miniusinas);

        //Ordenar as miniusinas por capacidade de geração em ordem descrescente
        int i,j;
        struct miniusina temp;

        for(i=0;i<contador-1;i++){

            //encontra o índice da miniusina com maior capacidade de geração
            for(j=i+1;j<contador;j++){
                if (miniusina_lida[j].cap_tot > miniusina_lida[i].cap_tot)
                {
                    temp=miniusina_lida[i];
                    miniusina_lida[i]=miniusina_lida[j];
                    miniusina_lida[j]=temp;
                }
                
            }

        }

        for(i=0;i<contador;i++){
            //Mostrar na tela cada informação lida
            printf("CNPJ: %s\n",miniusina_lida[i].cnpj);
            printf("RA: %d\n",miniusina_lida[i].ra);
            printf("Capacidade total de geração: %.1f\n",miniusina_lida[i].cap_tot);
            printf("\n");
        }
    }

    void listar_ra_decre_qnt_mu(){
        printf("em desenvolvimento.");
    }

    /*void limpar_buffer(){
        char ch;
        while((ch=getchar())!= '\n' && ch != EOF);
    }*/

    void voltar_menu(){
        printf("Aperte qualquer tecla para retornar ao menu...\n");
        getch();               
    }

    /*void limpar_tela(){
        #if defined(linux) || defined(unix) || defined(APPLE)
            system("clear");
        #endif

        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #endif
    }*/

    //Função principal
    int main(){
        //Caracteres especiais língua portuguesa
        setlocale(LC_CTYPE, "Portuguese");
        //declaração de variáveis
        int opcao;
        char cnpj[TAM_MAX_CNPJ];
        char id[TAM_MAX_CNPJ];


        //laço de repetição do menu e opcoes
        while(1){
            menu();
        
            scanf("%d",&opcao);

            if(opcao == 1){
                printf("Digite o CNPJ:\n");
                scanf("%s", cnpj);
                int resultado = cnpj_ver(cnpj);
                    if(resultado==0){
                        printf("CNPJ Inválido\n");
                    } 
                    else {printf("CNPJ Válido\n");
                        consultar_miniusina(cnpj);
                        consultar_contratos(cnpj);
                    }
                    voltar_menu();

                } else if (opcao == 2){
                printf("Digite o CNPJ ou CPF:\n");
                scanf("%s", id);

                //cpf
                if(strlen(id)<=14){
                    int resultado = cpf_ver(id);
                        if(resultado == 0){
                            printf("CPF Inválido\n");
                        } else{
                            printf("CPF Válido\n");
                            consultar_contratos_consumidor_CPF(id);
                        }

                    //cnpj
                } else if(strlen(id)>14){
                    int resultado = cnpj_ver(id);
                        if(resultado==0){
                            printf("CNPJ Inválido\n");
                        } else{
                            printf("CNPJ Válido\n");
                            consultar_contratos_consumidor_CNPJ(id);
                        }
                }
                voltar_menu();
            } else if (opcao == 3){
                listarmu();
                voltar_menu();
            }  else if (opcao == 4){
                listar_mu_cap_decre();
                voltar_menu();
            }  else if (opcao == 5){
                printf("Opção 5 em desenvolvimento\n");
            }  else if (opcao == 6){
                printf("Opção 6 em desenvolvimento\n");
            } else if (opcao == 7){
                printf("Opção 7 em desenvolvimento\n");
            } else if (opcao == 8){
                printf("Opção 8 em desenvolvimento\n");
            } else if (opcao == 9){
                break;
            }
            }
            return 0;
    }

