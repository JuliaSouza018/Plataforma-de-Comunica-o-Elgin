#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* ======================= Config DLL ======================= */
static HMODULE g_hDll = NULL;

/* Convenção de chamada (Windows): __stdcall */
#ifndef CALLCONV
#  define CALLCONV WINAPI
#endif

/* ======================= Assinaturas da DLL ======================= */
typedef int (CALLCONV *AbreConexaoImpressora_t)(int, const char *, const char *, int);
typedef int (CALLCONV *FechaConexaoImpressora_t)(void);
typedef int (CALLCONV *ImpressaoTexto_t)(const char *, int, int, int);
typedef int (CALLCONV *Corte_t)(int);
typedef int (CALLCONV *ImpressaoQRCode_t)(const char *, int, int);
typedef int (CALLCONV *ImpressaoCodigoBarras_t)(int, const char *, int, int, int);
typedef int (CALLCONV *AvancaPapel_t)(int);
typedef int (CALLCONV *AbreGavetaElgin_t)(int, int, int);
typedef int (CALLCONV *AbreGaveta_t)(int, int, int);
typedef int (CALLCONV *SinalSonoro_t)(int, int, int);
typedef int (CALLCONV *ImprimeXMLSAT_t)(const char *, int);
typedef int (CALLCONV *ImprimeXMLCancelamentoSAT_t)(const char *, const char *, int);
typedef int (CALLCONV *InicializaImpressora_t)(void);

/* ======================= Ponteiros ======================= */
static AbreConexaoImpressora_t        AbreConexaoImpressora        = NULL;
static FechaConexaoImpressora_t       FechaConexaoImpressora       = NULL;
static ImpressaoTexto_t               ImpressaoTexto               = NULL;
static Corte_t                        Corte                        = NULL;
static ImpressaoQRCode_t              ImpressaoQRCode              = NULL;
static ImpressaoCodigoBarras_t        ImpressaoCodigoBarras        = NULL;
static AvancaPapel_t                  AvancaPapel                  = NULL;
static AbreGavetaElgin_t              AbreGavetaElgin              = NULL;
static AbreGaveta_t                   AbreGaveta                   = NULL;
static SinalSonoro_t                  SinalSonoro                  = NULL;
static ImprimeXMLSAT_t                ImprimeXMLSAT                = NULL;
static ImprimeXMLCancelamentoSAT_t    ImprimeXMLCancelamentoSAT    = NULL;
static InicializaImpressora_t         InicializaImpressora         = NULL;

/* ======================= Configuração ======================= */
static int   g_tipo      = 1;
static char  g_modelo[64] = "i9";
static char  g_conexao[128] = "USB";
static int   g_parametro = 0;
static int   g_conectada = 0;

/* ======================= Utilidades ======================= */
#define LOAD_FN(h, name)                                                         \
    do {                                                                         \
        name = (name##_t)GetProcAddress((HMODULE)(h), #name);                    \
        if (!(name)) {                                                           \
            fprintf(stderr, "Falha ao resolver símbolo %s (erro=%lu)\n",         \
                    #name, GetLastError());                                      \
            return 0;                                                            \
        }                                                                        \
    } while (0)

static void flush_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* ======================= Funções para manipular a DLL ======================= */
static int carregarFuncoes(void)
{
    g_hDll = LoadLibraryA("E1_Impressora01.dll");
    if (!g_hDll) {
        fprintf(stderr, "Erro ao carregar E1_Impressora01.dll (erro=%lu)\n", GetLastError());
        return 0;
    }

    LOAD_FN(g_hDll, AbreConexaoImpressora);
    LOAD_FN(g_hDll, FechaConexaoImpressora);
    LOAD_FN(g_hDll, ImpressaoTexto);
    LOAD_FN(g_hDll, Corte);
    LOAD_FN(g_hDll, ImpressaoQRCode);
    LOAD_FN(g_hDll, ImpressaoCodigoBarras);
    LOAD_FN(g_hDll, AvancaPapel);
    LOAD_FN(g_hDll, AbreGavetaElgin);
    LOAD_FN(g_hDll, AbreGaveta);
    LOAD_FN(g_hDll, SinalSonoro);
    LOAD_FN(g_hDll, ImprimeXMLSAT);
    LOAD_FN(g_hDll, ImprimeXMLCancelamentoSAT);
    LOAD_FN(g_hDll, InicializaImpressora);

    return 1;
}

static void liberarBiblioteca(void)
{
    if (g_hDll) {
        FreeLibrary(g_hDll);
        g_hDll = NULL;
    }
}

/* ======================= Funções a serem implementadas pelos alunos ======================= */

static int exibirMenu()
{
	
	int EscolhaOpcao;
	
	printf("========ESCOLHE UMA OPCAO========\n");
	printf("1 - Configurar Conexao\n");
	printf("2 - Abrir Conexao\n");
	printf("3 - Impressao Texto\n");
	printf("4 - Impressao QRCode\n");
	printf("5 - Impressao Cod Barras\n");
	printf("6 - Impressao XML SAT\n");
	printf("7 - Impressao XML Canc SAT\n");
	printf("8 - Abrir Gaveta Elgin\n");
	printf("9 - Abrir Gaveta\n");
	printf("10 - Sinal Sonoro\n");
	printf("0 - Fechar Conexao e Sair\n"); 
	scanf("%d" , &EscolhaOpcao);
	
	return EscolhaOpcao; 		 
	

	
  // TODO: implementar exibição do menu principal com as opções de impressão  
}

static void configurarConexao(void) {
    int tipo;
    const char *modelo;
    const char *conexao;
    int parametro;

    char PonteiroModelo[50];   // isso é poruqe o ponteiro nao é um espaço na memoria, mass sim um endereço, por isso criei esse buffers temporário
    char PonteiroConexao[100]; 

    printf("--------------------------------------------\n");
    printf("| Valor | Referencia                       |\n");
    printf("--------------------------------------------\n");
    printf("|   1   | USB                              |\n");
    printf("|   2   | RS232                            |\n");
    printf("|   3   | TCP/IP                           |\n");
    printf("|   4   | Bluetooth                        |\n");
    printf("|   5   | Impressoras acopladas (Android)  |\n");
    printf("--------------------------------------------\n");
    printf("Digite o valor: ");
    scanf("%d", &tipo);

    if (tipo < 1 || tipo > 5) {
        printf("Valor invalido!\n");
        return;
    }

    if (tipo != 5) {
        printf("-----------------------------------\n");
        printf("|              Modelos            |\n");
        printf("-----------------------------------\n");
        printf("| i7                              |\n");
        printf("| i7 Plus                         |\n");
        printf("| i8                              |\n");
        printf("| i9                              |\n");
        printf("| ix                              |\n");
        printf("| Fitpos                          |\n");
        printf("| BK-T681                         |\n");
        printf("| MP-4200 (Para modelos TH e ADV) |\n");
        printf("| MP-4200 HS                      |\n");
        printf("| MK                              |\n");
        printf("| MP-2800                         |\n");
        printf("-----------------------------------\n");
        printf("Digite o modelo: ");
        scanf(" %[^\n]", PonteiroModelo); //esse [^\n] faz a variavel ler o nome completo se fosse so o %s iria ver só o primeiro valor antes do espaço
        modelo = PonteiroModelo; // ai aqui eu estou fazendo o ponteiro q é um endereço nao um espaço na memoria virar um espaço na memoria. 
        printf("-   %s\n", modelo);
    } else {
        modelo = ""; 
    }

    switch (tipo) {
        case 1:
            conexao = "USB";
            break;
        case 2:
            conexao = "COM2";
            break;
        case 3:
            conexao = "192.168.0.20";
            break;
        case 4:
            conexao = "AA:BB:CC:DD:EE:FF";
            break;
        case 5:
            conexao = "";
            break;
    }

    printf("Conexao padrao: %s\n", conexao); 
    printf("Deseja alterar a conexao? (s/n): ");
    char resp;
    scanf(" %c", &resp);

    if (resp == 's' || resp == 'S') {
        printf("Digite o novo valor de conexao: ");
        scanf(" %[^\n]", PonteiroConexao); //ai aqui eu estou fazendo o ponteiro q é um endereço nao um espaço na memoria virar um espaço na memoria. 
        conexao = PonteiroConexao;
    }

    if (tipo == 2) {
        printf("Digite o baudrate: ");
        scanf("%d", &parametro);
    } else if (tipo == 3) {
        printf("Digite a porta TCP: ");
        scanf("%d", &parametro);
    } else {
        parametro = 0;
    }

    printf("\nResumo da configuracao:\n");
    printf("--------------------------------------------\n");
    printf("Tipo:       %d\n", tipo);
    printf("Modelo:     %s\n", modelo[0] ? modelo : "(vazio)");
    printf("Conexao:    %s\n", conexao[0] ? conexao : "(vazio)");
    printf("Parametro:  %d\n", parametro);
    printf("--------------------------------------------\n");


}




static void abrirConexao(void)
{
    // TODO: chamar AbreConexaoImpressora e validar retorno
}

static void fecharConexao(void)
{
    // TODO: chamar FechaConexaoImpressora e tratar retorno
}

static void imprimirTexto(void)
{
    // TODO: solicitar texto do usuário e chamar ImpressaoTexto
    // incluir AvancaPapel e Corte no final
}

static void imprimirQRCode(void)
{
    // TODO: solicitar conteúdo do QRCode e chamar ImpressaoQRCode(texto, 6, 4)
    // incluir AvancaPapel e Corte no final
}

static void imprimirCodigoBarras(void)
{
    // TODO: usar ImpressaoCodigoBarras(8, "{A012345678912", 100, 2, 3)
    // incluir AvancaPapel e Corte no final
}

static void imprimirXMLSAT(void)
{
    // TODO: ler o arquivo ./XMLSAT.xml e enviar via ImprimeXMLSAT
    // incluir AvancaPapel e Corte no final
}

static void imprimirXMLCancelamentoSAT(void)
{
    // TODO: ler o arquivo ./CANC_SAT.xml e chamar ImprimeXMLCancelamentoSAT
    // incluir AvancaPapel e Corte no final
    
	/*usar assinatura abaixo:
        "Q5DLkpdRijIRGY6YSSNsTWK1TztHL1vD0V1Jc4spo/CEUqICEb9SFy82ym8EhBRZ"
        "jbh3btsZhF+sjHqEMR159i4agru9x6KsepK/q0E2e5xlU5cv3m1woYfgHyOkWDNc"
        "SdMsS6bBh2Bpq6s89yJ9Q6qh/J8YHi306ce9Tqb/drKvN2XdE5noRSS32TAWuaQE"
        "Vd7u+TrvXlOQsE3fHR1D5f1saUwQLPSdIv01NF6Ny7jZwjCwv1uNDgGZONJdlTJ6"
        "p0ccqnZvuE70aHOI09elpjEO6Cd+orI7XHHrFCwhFhAcbalc+ZfO5b/+vkyAHS6C"
        "YVFCDtYR9Hi5qgdk31v23w==";
        */
}

static void abrirGavetaElginOpc(void)
{
    // TODO: chamar AbreGavetaElgin(1, 50, 50)
}

static void abrirGavetaOpc(void)
{
    // TODO: chamar AbreGaveta(1, 5, 10)
}

static void emitirSinalSonoro(void)
{
    // TODO: chamar SinalSonoro(4, 50, 5)
}

/* ======================= Função principal ======================= */
int main(void)
{
    if (!carregarFuncoes()) {
    	
    	printf("Erro!");
        return 1;
    }

    int opcao = 0;
    while (1) {
    	
    	opcao = exibirMenu();
    	
 	switch (opcao) {
        case 1:
        configurarConexao(); 
        break;

        case 2:
        abrirConexao(); 
        break;

        case 3:
        imprimirTexto(); 
        break;

    	case 4:
        imprimirQRCode(); 
        break;

        case 5:
        imprimirCodigoBarras(); 
        break;

        case 6:
        imprimirXMLSAT(); 
        break;

        case 7:
        imprimirXMLCancelamentoSAT(); 
        break;

        case 8:
        abrirGavetaElginOpc(); 
        break;

        case 9:
        abrirGavetaOpc(); 
        break;

        case 10:
        emitirSinalSonoro(); 
        break;

        case 0:
        fecharConexao();
        printf("Saindo do sistema...\n");
        return 0; 

        default:
        printf("Opcao Invalida!\n");
        break;
        }
    }

    return 0; 
}

