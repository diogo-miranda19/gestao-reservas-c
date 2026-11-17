# Gestão de Reservas de Restaurante

Programa em C, feito na consola, para gerir as reservas de um restaurante.  
Trabalho académico em duplas da unidade curricular de Laboratório de Programação (Engenharia Informática, UPB).

---

## O que faz
- Adicionar, remover e mudar reservas
- Listar todas as reservas
- Guardar as reservas num ficheiro binário e ler de novo
- Ordenar as reservas por data
- Pesquisar reservas pelo nome do cliente
- Calcular a ocupação do restaurante numa data e hora

> **Regra principal:** À mesma data e hora não podem estar mais de 10 pessoas (`CAPACIDADE_MAXIMA`). Se uma reserva fizer passar esse limite, é recusada. O programa guarda no máximo 10 reservas (`MAX_RESERVAS`).

---

## Conceitos de C usados
- `struct` com `typedef`
- Arrays e passagem de parâmetros por endereço (pointers)
- Ficheiros binários (`fopen`, `fwrite`, `fread`)
- Funções de strings (`strcmp`, `strcpy`) e `scanf` / `sscanf`
- Ordenação com *bubble sort*

---

## Como compilar e executar

**Com o `gcc`:**
```bash
gcc -Wall -Wextra main.c -o reservas
./reservas
```

**Com o Visual Studio:**  
Abrir o ficheiro da solução (`.sln`) e carregar em `Ctrl + F5`.

---

## Como usar

O programa mostra um menu e escolhes uma opção:

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

**Formatos:** data `dd/mm/aaaa` (ex.: `12/12/2026`) e hora `hh:mm` (ex.: `13:00`).  
Usa sempre o mesmo formato, porque a data e a hora são comparadas como texto.

### Exemplo de execução
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

## Limitações conhecidas
- Os nomes só podem ter uma palavra (o `scanf("%s")` para no espaço).
- A data e a hora não são validadas (por exemplo, `31/02/2025` é aceite).
- Não é validado se o número de pessoas é positivo.
- Reservas a horas diferentes (`13:00` e `13:30`) contam como horas separadas.

## Possíveis melhorias
- Ler texto com `fgets` para aceitar nomes com espaços.
- Validar datas, horas e número de pessoas.
- Usar memória dinâmica (`malloc`) em vez de um limite fixo de reservas.
