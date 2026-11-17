# Sistema de Gestão de Reservas de Restaurante - Linguagens de Programação (C)

> Projeto académico desenvolvido no âmbito da unidade curricular de **Laboratório de Programação (LP)** em duplas da Licenciatura em Engenharia Informática no **UPB (Universidade Politécnica de Bragança)**.

---

## Sobre o Projeto
Esta aplicação de consola, desenvolvida em linguagem **C**, simula a gestão de reservas de mesas simples num restaurante. O principal objetivo do projeto é aplicar os conceitos fundamentais de programação estruturada — manipulação de estruturas (`struct`), passagem de parâmetros por endereço (pointers), algoritmos de ordenação e persistência de dados em ficheiros binários.

> **Regra de Negócio Principal:** À mesma data e hora não podem estar mais de **10 pessoas** (`CAPACIDADE_MAXIMA`). Se uma nova reserva fizer ultrapassar esse limite, é automaticamente recusada. O sistema suporta até um máximo de **10 reservas** (`MAX_RESERVAS`).

---

## Funcionalidades e Conceitos Aplicados

O programa foi implementado de forma modular em `main.c`, cobrindo as seguintes operações e técnicas:

- **Gestão Completa de Reservas:** Adicionar, listar, editar e remover reservas associadas a clientes, número de lugares, data e hora.
- **Controlo de Capacidade e Pesquisa:** Cálculo da ocupação total do restaurante para uma determinada data/hora e pesquisa de reservas por nome do cliente.
- **Ordenação Cronológica:** Organização das reservas por data utilizando o algoritmo *bubble sort*.
- **Persistência em Ficheiro Binário :** Gravação e leitura direta dos registos no ficheiro `reservas_restaurante.dat` através de `fopen`, `fwrite` e `fread`.
- **Estruturas e Ponteiros:** Modelação de dados com `struct` e `typedef`, passagem por referência e manipulação de *strings* (`strcmp`, `strcpy`, `scanf`, `sscanf`).

---

## Como Compilar e Executar

### Opção 1: Via Terminal (`gcc`)
1. Clona ou descarrega este repositório.
2. Compila e executa o programa no terminal:
   ```bash
   gcc -Wall -Wextra main.c -o reservas
   ./reservas
   ```

### Opção 2: Visual Studio Community (Windows)
1. Abre o ficheiro de solução **`Project2.sln`** no **Visual Studio Community**.
2. Define a configuração de compilação para **Debug** (`x64`).
3. Prime **`Ctrl + F5`** (ou vai a **Depurar** > **Iniciar Sem Depurar**) para compilar e executar.

---

## Como Usar

Ao iniciar, o programa apresenta um menu interativo na consola:

```text
MENU
[1] Adicionar Reserva
[2] Remover Reserva
[3] Mudar Reserva
[4] Listar Reservas
[5] Guardar Reservas no Ficheiro
[6] Ler do Ficheiro e Listar Todas as Reservas
[7] Ordenar por Data e Listar
[8] Pesquisar Reservas por Nome do Cliente
[9] Calcular Ocupacao do Restaurante
[0] Sair
```

**Formatos aceites:** Data no formato `dd/mm/aaaa` (ex.: `12/12/2026`) e hora no formato `hh:mm` (ex.: `13:00`). Utiliza sempre o mesmo formato, uma vez que a comparação é efetuada textualmente.

### Exemplo de Execução
```text
Escolha uma opcao: 1
Nome do cliente: bruno
Numero de pessoas: 8
Data da reserva (dd/mm/aaaa): 12/12/2026
Hora da reserva (hh:mm): 13:00
Reserva adicionada com sucesso.

Escolha uma opcao: 1
Nome do cliente: diogo
Numero de pessoas: 3
Data da reserva (dd/mm/aaaa): 12/12/2026
Hora da reserva (hh:mm): 13:00
Nao ha lugares suficientes. Ja ha 8 pessoas nessa data e hora (capacidade 10).
Reserva nao adicionada.
```

---

## Estrutura de Pastas
```text
gestao-reservas-c/
├── main.c                      # Código-fonte principal e lógica do menu
├── reservas_restaurante.dat    # Ficheiro binário de persistência das reservas
├── Project2.sln                
├── Project2.vcxproj            
├── Project2.vcxproj.filters    
├── .gitignore                  
└── README.md                   
```

---

## Limitações Conhecidas e Melhorias Futuras

### Limitações Conhecidas
- Os nomes dos clientes aceitam apenas uma palavra (devido ao comportamento do `scanf("%s")` nos espaços).
- Não existe validação semântica de calendário para datas e horas inseridas (ex.: `31/02/2025` é aceite) nem verificação de números negativos.
- Reservas em horários próximos (ex.: `13:00` e `13:30`) são contabilizadas como blocos horários independentes.

### Possíveis Melhorias
- Substituir `scanf("%s")` por `fgets` para suportar nomes completos com espaços.
- Implementar validação rigorosa de datas, horários e valores positivos.
- Utilizar alocação dinâmica de memória (`malloc` / `realloc`) para remover o limite estático de 10 reservas.
