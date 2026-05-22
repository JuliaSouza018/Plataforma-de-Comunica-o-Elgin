# Plataforma de Comunicação Elgin

Projeto educacional em linguagem C para integração com impressoras térmicas Elgin via DLL (`E1_Impressora01.dll`). O programa oferece um menu interativo no terminal que permite configurar a conexão, imprimir textos, QR Codes, códigos de barras, XMLs do SAT e controlar periféricos como gaveta e sinal sonoro.

---

## Estrutura do Projeto

```
Plataforma-de-Comunica-o-Elgin-main/
├── C Aluno/
│   ├── projeto.c              # Código-fonte principal (C)
│   ├── projeto.exe            # Executável compilado (Windows)
│   ├── E1_Impressora01.dll    # DLL da Elgin (necessária em tempo de execução)
│   ├── XMLSAT.xml             # XML de exemplo para impressão SAT
│   ├── NFCe.xml               # XML de exemplo NFC-e
│   ├── NFCeCancelamento.xml   # XML de exemplo cancelamento NFC-e
│   └── CANC_SAT.xml           # XML de exemplo cancelamento SAT
└── README.md
```

---

## Pré-requisitos

- **Sistema operacional:** Windows (a integração usa `windows.h`, `LoadLibrary` e `GetProcAddress`)
- **Compilador:** GCC (MinGW/MSYS2) ou MSVC com suporte a C99
- **DLL:** `E1_Impressora01.dll` deve estar no mesmo diretório do executável
- **Hardware:** Impressora térmica Elgin compatível (i7, i7 Plus, i8, i9, ix, Fitpos, BK-T681, MP-4200, MP-4200 HS, MK, MP-2800)

---

## Como Compilar

Com GCC (MinGW):

```bash
gcc projeto.c -o projeto.exe
```

> O executável compilado (`projeto.exe`) já está incluso na pasta `C Aluno/` para facilitar os testes.

---

## Como Executar

1. Certifique-se de que `E1_Impressora01.dll` está na mesma pasta do executável.
2. Execute o programa:

```bash
./projeto.exe
```

3. O menu interativo será exibido no terminal.

---

## Menu de Funcionalidades

| Opção | Descrição |
|-------|-----------|
| `1` | Configurar conexão (tipo, modelo, endereço/porta) |
| `2` | Abrir conexão com a impressora |
| `3` | Impressão de texto |
| `4` | Impressão de QR Code |
| `5` | Impressão de código de barras |
| `6` | Impressão de XML SAT |
| `7` | Impressão de XML Cancelamento SAT |
| `8` | Abrir gaveta (padrão Elgin) |
| `9` | Abrir gaveta (genérica) |
| `10` | Emitir sinal sonoro |
| `0` | Fechar conexão e sair |

---

## Tipos de Conexão Suportados

| Valor | Tipo |
|-------|------|
| 1 | USB |
| 2 | RS232 (Serial) |
| 3 | TCP/IP |
| 4 | Bluetooth |
| 5 | Impressoras acopladas (Android) |

---

## Funções da DLL

O projeto carrega dinamicamente as seguintes funções da `E1_Impressora01.dll`:

| Função | Descrição |
|--------|-----------|
| `AbreConexaoImpressora` | Abre a conexão com a impressora |
| `FechaConexaoImpressora` | Fecha a conexão |
| `InicializaImpressora` | Inicializa o dispositivo |
| `ImpressaoTexto` | Imprime texto simples |
| `ImpressaoQRCode` | Imprime QR Code |
| `ImpressaoCodigoBarras` | Imprime código de barras |
| `ImprimeXMLSAT` | Imprime cupom fiscal SAT a partir de XML |
| `ImprimeXMLCancelamentoSAT` | Imprime cancelamento SAT |
| `AvancaPapel` | Avança o papel |
| `Corte` | Aciona o corte do papel |
| `AbreGavetaElgin` | Abre gaveta (protocolo Elgin) |
| `AbreGaveta` | Abre gaveta (protocolo genérico) |
| `SinalSonoro` | Emite sinal sonoro |

---

## Contexto Educacional

Este projeto é um exercício prático de programação em C com foco em:

- Carregamento dinâmico de bibliotecas (`LoadLibrary` / `GetProcAddress`)
- Uso de ponteiros de função com convenção de chamada `__stdcall` (WINAPI)
- Leitura e envio de arquivos XML para dispositivos fiscais
- Estruturação de menus interativos via terminal

Várias funções contêm comentários `// TODO:` indicando onde os alunos devem implementar a lógica correspondente.

---

## Observações

- O arquivo `E1_Impressora01.dll` é fornecido pela Elgin e **não deve ser redistribuído** sem autorização.
- Os XMLs de exemplo (`XMLSAT.xml`, `NFCe.xml`, etc.) são apenas para fins de teste.
- A assinatura digital usada no cancelamento SAT (`imprimirXMLCancelamentoSAT`) é um exemplo fictício.
