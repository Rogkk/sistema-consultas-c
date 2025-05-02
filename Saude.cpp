#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

int menu();
void cadastro_Paciente(struct Paciente *p, int total_pacientes);
void cadastro_Medico(struct Medico *m, int total_medicos);
void agendar_Consulta(struct Consulta *c, int total_consultas);
void salvar_Totais(int pacientes, int medicos, int consultas);
void carregar_Totais(int *pacientes, int *medicos, int *consultas);
void relatorio_consultas();
void relatorio_Pacientes();
void relatorio_Medicos();

struct Paciente {
	int pk;
	char nome[30];
	char sexo;
	int idade;
	char end[100];
};

struct Medico {
	int pk;
	char nome[30];
	char sexo;
	int idade;
	char end[100];
	char especialidade[50];
};

struct Consulta {
	int pk;
	char data[11];
	char hora[6];
	char especialidade[50];
	int paciente;
	int medico; 
};

int main() {
	int op;
	int total_pacientes = 0, total_medicos = 0, total_consultas = 0;
	
	struct Paciente pacientes[100];
	struct Medico medicos[20];
	struct Consulta consultas[100];
	
	carregar_Totais(&total_pacientes, &total_medicos, &total_consultas);

	while(1) {
		system("cls");
		op = menu();
		if(op == 0) {
			break;
		} else if(op == 1) {
			cadastro_Paciente(&pacientes[total_pacientes], total_pacientes);
			total_pacientes++;
		} else if(op == 2) {
			cadastro_Medico(&medicos[total_medicos], total_medicos);
			total_medicos++;
		} else if(op == 3) {
			agendar_Consulta(&consultas[total_consultas], total_consultas);
			total_consultas++;
		} else if(op == 4) {
			relatorio_consultas();
		} else if(op == 5) {
			relatorio_Pacientes();
		} else if(op == 6) {
			relatorio_Medicos();
		}
	}
	
	salvar_Totais(total_pacientes, total_medicos, total_consultas);
	
	return 0;
}

int menu() {
	int op;
	printf("=== SISTEMA DE SAUDE ===\n\n");
	printf("1 - Cadastro de Pacientes\n");
	printf("2 - Cadastro de Medicos\n");
	printf("3 - Agendar Consulta\n");
	printf("4 - Consultas Agendadas\n");
	printf("5 - Relatorio de Pacientes\n");
	printf("6 - Relatorio de Medicos\n");
	printf("0 - Sair\n");
	printf("\nEscolha uma opcao: ");	
	scanf("%d", &op);
	return op;
};

void cadastro_Paciente(struct Paciente *p, int total_pacientes) {
	FILE* arquivo = fopen("pacientes.txt", "a");
	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		system("pause");
        return;
	}
	
	
	system("cls");

	p->pk = total_pacientes + 1;

	printf("Nome: ");
	fflush(stdin);
	fgets(p->nome, sizeof(p->nome), stdin);

	printf("Sexo (M/F): ");
	scanf(" %c", &p->sexo);

	printf("Idade: ");
	scanf("%d", &p->idade);

	printf("Endereco: ");
	fflush(stdin);
	fgets(p->end, sizeof(p->end), stdin);
	
	fprintf(arquivo, "%d\n", p->pk);
	fprintf(arquivo, "%s", p->nome);
	fprintf(arquivo, "%c\n", p->sexo);
	fprintf(arquivo, "%d\n", p->idade);
	fprintf(arquivo, "%s\n", p->end);
	
	fclose(arquivo);

	printf("\nPaciente cadastrado com sucesso!\n");
	system("pause");
}

void cadastro_Medico(struct Medico *m, int total_medicos) {
	FILE* arquivo = fopen("medicos.txt", "a");
	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		system("pause");
        return;
	}
	
	system("cls");

	m->pk = total_medicos + 1;

	printf("Nome: ");
	fflush(stdin);
	fgets(m->nome, sizeof(m->nome), stdin);

	printf("Sexo (M/F): ");
	scanf(" %c", &m->sexo);

	printf("Idade: ");
	scanf("%d", &m->idade);

	printf("Endereco: ");
	fflush(stdin);
	fgets(m->end, sizeof(m->end), stdin);
	
	printf("Especialidade: ");
	fflush(stdin);
	fgets(m->especialidade, sizeof(m->especialidade), stdin);
	
	fprintf(arquivo, "%d\n", m->pk);
	fprintf(arquivo, "%s", m->nome);
	fprintf(arquivo, "%c\n", m->sexo);
	fprintf(arquivo, "%d\n", m->idade);
	fprintf(arquivo, "%s", m->end);
	fprintf(arquivo, "%s\n", m->especialidade);
	
	fclose(arquivo);

	printf("\nMedico cadastrado com sucesso!\n");
	system("pause");
}

void agendar_Consulta(struct Consulta *c, int total_consultas) {
	FILE* arquivo = fopen("consultas.txt", "a");
	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		system("pause");
        return;
	}
	
	system("cls");

	c->pk = total_consultas + 1;
	
	fflush(stdin);
	printf("Data (dd/mm/aaaa): ");
	fgets(c->data, sizeof(c->data), stdin);

	fflush(stdin);
	printf("Hora (hh:mm): ");
	fgets(c->hora, sizeof(c->hora), stdin);

	fflush(stdin);
	printf("PK do Medico: ");
	scanf("%d", &c->medico);
	
	fflush(stdin);
	printf("PK do Paciente: ");
	scanf("%d", &c->paciente);
	
	fflush(stdin);
	printf("Especialidade: ");
	fgets(c->especialidade, sizeof(c->especialidade), stdin);

    fprintf(arquivo, "%d\n", c->pk);
    fprintf(arquivo, "%s\n", c->data);
    fprintf(arquivo, "%s\n", c->hora);
    fprintf(arquivo, "%s", c->especialidade);
    fprintf(arquivo, "%d\n", c->medico);
    fprintf(arquivo, "%d\n\n", c->paciente);

    fclose(arquivo);

	printf("\nConsulta cadastrada com sucesso!\n");
	system("pause");
}

void salvar_Totais(int pacientes, int medicos, int consultas) {
	FILE* arquivo = fopen("totais.txt", "w");
	if(arquivo != NULL) {
		fprintf(arquivo, "%d %d %d", pacientes, medicos, consultas);
		fclose(arquivo);
	}
}

void carregar_Totais(int *pacientes, int *medicos, int *consultas) {
	FILE* arquivo = fopen("totais.txt", "r");
	if(arquivo != NULL) {
		fscanf(arquivo, "%d %d %d", pacientes, medicos, consultas);
		fclose(arquivo);
	} else {
		*pacientes = 0;
		*medicos = 0;
		*consultas = 0;
	}
}

void relatorio_consultas() {
	FILE* arquivo = fopen("consultas.txt", "r");
	if(arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		return;
	}

	system("cls");

	char linha[100];
	int i = 0;
	int id, paciente_id, medico_id;
	char data[20], hora[10], especialidade[50];

	printf("RELATORIO DE CONSULTAS\n");
    printf("=======================\n");

	while(fgets(linha, sizeof(linha), arquivo)) {

		if(i == 0) {
			id = atoi(linha); 
		} else if(i == 1) {
			strcpy(data, linha);
		} else if(i == 2) {
			strcpy(hora, linha);
		} else if(i == 3) {
			strcpy(especialidade, linha);
		} else if(i == 4) {
			paciente_id = atoi(linha);
		} else if(i == 5) {
			medico_id = atoi(linha);
		} else if(i == 6) {
			printf("ID: %d\n", id);
            printf("Data: %s\n", data);
            printf("Hora: %s\n", hora);
            printf("Especialidade: %s\n", especialidade);
            printf("Paciente ID: %d\n", paciente_id);
            printf("Medico ID: %d\n", medico_id);
            printf("-------------------------\n");
		}

		i = (i+1) % 7;
	}
	printf("==> Total de Consultas: %d\n", id);
	fclose(arquivo);
	getch();
}

void relatorio_Pacientes() {
	FILE* arquivo = fopen("pacientes.txt", "r");
	if(arquivo == NULL) {
		printf("Erro ao abrir arquivo.\n");
		return;
	}

	system("cls");

	char linha[100];
	int i = 0;
	int id, idade;
	char nome[30], sexo, end[100];

	printf("RELATORIO DE PACIENTES\n");
    printf("=======================\n");

	while(fgets(linha, sizeof(linha), arquivo)) {

		if(i == 0) {
			id = atoi(linha); 
		} else if(i == 1) {
			strcpy(nome, linha);
		} else if(i == 2) {
			sexo = linha[0];
		} else if(i == 3) {
			idade = atoi(linha);
		} else if(i == 4) {
			strcpy(end, linha);
		} else if(i == 5) {
			printf("ID: %d\n", id);
            printf("Nome: %s\n", nome);
            printf("Sexo: %c\n", sexo);
            printf("Idade: %d\n", idade);
            printf("Endereco: %s\n", end);
            printf("-------------------------\n");
		}

		i = (i+1) % 6;
	}
	printf("==> Total de Pacientes: %d\n", id);
	fclose(arquivo);
	getch();
}

void relatorio_Medicos() {
	FILE* arquivo = fopen("medicos.txt", "r");
	if(arquivo == NULL) {
		printf("Erro ao abrir arquivo.\n");
		return;
	}

	system("cls");

	char linha[100];
	int i = 0;
	int id, idade;
	char nome[30], sexo, end[100], especialidade[100];

	printf("RELATORIO DE MEDICOS\n");
    printf("=======================\n");

	while(fgets(linha, sizeof(linha), arquivo)) {

		if(i == 0) {
			id = atoi(linha); 
		} else if(i == 1) {
			strcpy(nome, linha);
		} else if(i == 2) {
			sexo = linha[0];
		} else if(i == 3) {
			idade = atoi(linha);
		} else if(i == 4) {
			strcpy(end, linha);
		} else if(i == 5) {
			strcpy(especialidade, linha);
		} else if(i == 6) {
			printf("ID: %d\n", id);
            printf("Nome: %s\n", nome);
            printf("Sexo: %c\n", sexo);
            printf("Idade: %d\n", idade);
			printf("Especialidade: %s\n", especialidade);
            printf("Endereco: %s\n", end);
            printf("-------------------------\n");
		}

		i = (i+1) % 7;
	}
	printf("==> Total de Medicos: %d\n", id);
	fclose(arquivo);
	getch();	
}
