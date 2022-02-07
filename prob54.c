#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
typedef struct {
  char carta [3];
} cartaJogada;

typedef struct {
  int cartaNum; /*int cartaNum: 2 a 10 cartas normais, Valete 11, Dama 12, Rei 13, As 14 */
  int naipe; /* int naipe: H - copas (0), S - espadas (1), D - ouros (2), C - pais (3) */
} cartasNumerico;

/* lê as 5 cartas jogadas para vector de 5 cartas jogadas criadas dinamicamente,
se não conseguir ler ou houver algum problema, retorna NULL */
cartaJogada* leituraJogada (FILE *f);

/* para cada vector de cartas Jogadas, em string, converte para um vector numerico
de cartas, para poder ser tratado numericamente, devolve o vector ou NULL em
caso de erro */
cartasNumerico* converteStringCartasNumerico (cartaJogada* jogador);

/* ordena o vector por ordem decrescente de cartaNum, desde As ate ao 2,
e retorna no fim*/
void ordenaCartasPorValorNumericoDecrescente (cartasNumerico *jogador1NumV, cartasNumerico *jogador2NumV);

/* testa a existencia de um RoyalFlush, retorna 1 se ocorreu um RoyalFlush ou 0 se não */
int testaRoyalFlush (cartasNumerico *jogador);

/* testa a existencia de um straightFlush, retorna 1 se ocorreu um straightFlush ou 0 se não */
int testaStraightFlush (cartasNumerico *jogador);

/* testa a existencia de um 4ofAkind, retorna 1 se ocorreu um 4 of a kind ou 0 se não */
/* devolve por referencia o valor do carta num do conjunto de 4 cartas */
int testaFourOfaKind (cartasNumerico *jogador, int *num4Kind);

/* testa a existencia de um FullHouse, retorna 1 se ocorreu um Full House ou 0 se não */
/* devolve por referencia o valor numerico de trioNum */
int testaFullHouse (cartasNumerico *jogador, int *trioNum);

/* verifica se já temos um vencedor, se o vencedor for o jogador 1, actualiza o
numero de vitorias. Devolve 1 se ja tiver chegado a um vencedor ou 0 se ainda não */
int verificaBooleanos (int booleanoJogador1, int booleanoJogador2, cartasNumerico *jogador1NumV, cartasNumerico *jogador2NumV, int *nJogadas1ganhas);

/* devolve o numero de pares de uma jogada, assim como por referencia o nPar1Valor
e o nPar2Valor se existirem */
int numeroParesVerifica (cartasNumerico *jogador, int *nPar1Valor, int *nPar2Valor);

/* devolve 1 se houver 1 trio, assim como o valor do trioNumVal por referencia,
senão devolve 0, tenho uma flag a informar qual a posicao do trio,
imediatamente a frente */
int testaThreeOfaKind (cartasNumerico *jogador, int *trioNumVal, int *posTrio);

/* testa a existencia de um Flush, retorna 1 se ocorreu um Flush ou 0 se não */
int testaFlush (cartasNumerico *jogador);

/*desempata através das cartas mais elevadas,
devolve -1 se jogador 1 ganha, 1 se jogador 2 ganha ou 0 se ha empate */
int desempatePorCartasMaisAltas (cartasNumerico *jogador1NumV, cartasNumerico *jogador2NumV);

/* testa a existencia de straight, retorna 1 se ocorrer straight ou 0 se não */
int testaStraight (cartasNumerico *jogador);

/* verifica a existencia de 2 pares, retorna 1 se existem 2 pares ou 0 se não.
Se existir devolve o par maximo no par1 e o par minimo no par2 */
int testa2Pares (cartasNumerico *jogador, int *par1, int *par2);

/* verifica a existencia de 1 par, retorna 1 se existir 1 pares ou 0 se não.
Se existir devolve o par no par1, tenho uma flaga a informar se tenho algum trio,
e a sua posição imediatamente a frente, se não houver trio é -1 */
int testa1Par (cartasNumerico *jogador, int *par1, int posTrio);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();

/* tarefa a verificar */
char nomeFicheiro [15] = "poker.txt";
FILE *f;
cartaJogada *jogador1, *jogador2;
cartasNumerico *jogador1NumV, *jogador2NumV;
int i, nJogadas1ganhas = 0, booleanoJogador1, booleanoJogador2, booleano, num4Kind1, num4Kind2;
int trioNum1, trioNum2, par1Jog1, par2Jog1, par1Jog2, par2Jog2, posTrio, nJogadas = 0;

f = fopen (nomeFicheiro, "r");
if (f == NULL) {
  printf ("\nErro na leitura do ficheiro.");
  return 0;
}

while (1) {
  jogador1 = leituraJogada (f);
  jogador2 = leituraJogada (f);
  if (jogador1 == NULL || jogador2 == NULL) {
    break;
  }

  jogador1NumV = converteStringCartasNumerico (jogador1);

  jogador2NumV = converteStringCartasNumerico (jogador2);
  free (jogador1);
  free (jogador2);
  if (jogador1NumV == NULL || jogador2NumV == NULL) {
    printf ("\nOcorreu um erro na função vector numérico.");
    return 0;
  }

  ordenaCartasPorValorNumericoDecrescente (jogador1NumV, jogador2NumV);
  /* teste a RoyalFlush */
  booleanoJogador1 = testaRoyalFlush (jogador1NumV);
  booleanoJogador2 = testaRoyalFlush (jogador2NumV);
  booleano = verificaBooleanos (booleanoJogador1, booleanoJogador2, jogador1NumV, jogador2NumV, &nJogadas1ganhas);
  if (booleano == 1) {
    continue;
  }
  if (booleanoJogador1 == 1 && booleanoJogador2 == 1) {
    /* não há desempate possivel neste caso */
    free (jogador1NumV);
    free (jogador2NumV);
    continue;
  }

  /* teste a straightFlush */
  booleanoJogador1 = testaStraightFlush (jogador1NumV);
  booleanoJogador2 = testaStraightFlush (jogador2NumV);
  booleano = verificaBooleanos (booleanoJogador1, booleanoJogador2, jogador1NumV, jogador2NumV, &nJogadas1ganhas);
  if (booleano == 1) {
    continue;
  }
  if (booleanoJogador1 == 1 && booleanoJogador2 == 1) {
    if (jogador1NumV[0].cartaNum > jogador2NumV[0].cartaNum) {
      /* jogador 1 tem um straight com valor superior */
      nJogadas1ganhas++;
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    } else if (jogador1NumV[0].cartaNum < jogador2NumV[0].cartaNum) {
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    } else {
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    }
  }

  /* teste a Four of a King */
  booleanoJogador1 = testaFourOfaKind (jogador1NumV, &num4Kind1);
  booleanoJogador2 = testaFourOfaKind (jogador2NumV, &num4Kind2);
  booleano = verificaBooleanos (booleanoJogador1, booleanoJogador2, jogador1NumV, jogador2NumV, &nJogadas1ganhas);
  if (booleano == 1) {
    continue;
  }
  /* revolver empate */
  if (booleanoJogador1 == 1 && booleanoJogador2 == 1) {
    if (num4Kind1 > num4Kind2) {
      nJogadas1ganhas++;
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    } else if (num4Kind1 < num4Kind2){
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    }
  }

  /* testa um full house */
  booleanoJogador1 = testaFullHouse (jogador1NumV, &trioNum1);
  booleanoJogador2 = testaFullHouse (jogador2NumV, &trioNum2);
  booleano = verificaBooleanos (booleanoJogador1, booleanoJogador2, jogador1NumV, jogador2NumV, &nJogadas1ganhas);
  if (booleano == 1) {
    continue;
  }
  if (booleanoJogador1 == 1 && booleanoJogador2 == 1) {
      if (trioNum1 > trioNum2) {
        nJogadas1ganhas++;
        free (jogador1NumV);
        free (jogador2NumV);
        continue;
      } else {
        free (jogador1NumV);
        free (jogador2NumV);
        continue;
      }
  }


  /* testa Flush */
  booleanoJogador1 = testaFlush (jogador1NumV);
  booleanoJogador2 = testaFlush (jogador2NumV);
  booleano = verificaBooleanos (booleanoJogador1, booleanoJogador2, jogador1NumV, jogador2NumV, &nJogadas1ganhas);
  if (booleano == 1) {
    continue;
  }
  if (booleanoJogador1 == 1 && booleanoJogador2 == 1) {
    /* desempate por cartas mais elevadas */
    /* devolve -1 se jogador 1 ganha, 1 se jogador 2 ganha ou 0 se ha empate */
      booleano = desempatePorCartasMaisAltas (jogador1NumV, jogador2NumV);
      free (jogador1NumV);
      free (jogador2NumV);
      if (booleano == 0) {
      } else if (booleano == 1) {
        /*ganha jogador 2*/
        continue;
      } else {
        /* ganhou o jogador 1 */
        nJogadas1ganhas++;
        continue;
      }
  }

  /* testa straight */
  booleanoJogador1 = testaStraight (jogador1NumV);
  booleanoJogador2 = testaStraight (jogador2NumV);
  booleano = verificaBooleanos (booleanoJogador1, booleanoJogador2, jogador1NumV, jogador2NumV, &nJogadas1ganhas);
  if (booleano == 1) {
    continue;
  }
  if (booleanoJogador1 == 1 && booleanoJogador2 == 1) {
    /* desempate por cartas mais elevadas */
    /* devolve -1 se jogador 1 ganha, 1 se jogador 2 ganha ou 0 se ha empate */
      booleano = desempatePorCartasMaisAltas (jogador1NumV, jogador2NumV);
      free (jogador1NumV);
      free (jogador2NumV);
      if (booleano == 0 || booleano == 1) {
        /* empate ou ganha jogador 2*/
        continue;
      } else {
        /* ganhou o jogador 1 */
        nJogadas1ganhas++;
        continue;
      }
  }

  /* testa ThreeOfaKind */
  booleanoJogador1 = testaThreeOfaKind (jogador1NumV, &trioNum1, &posTrio);
  booleanoJogador2 = testaThreeOfaKind (jogador2NumV, &trioNum2, &posTrio);
  booleano = verificaBooleanos (booleanoJogador1, booleanoJogador2, jogador1NumV, jogador2NumV, &nJogadas1ganhas);
  if (booleano == 1) {
    continue;
  }

  if (booleanoJogador1 == 1 && booleanoJogador2 == 1) {
    /* desempate por trios mais altos*/
    if (trioNum1 > trioNum2) {
      nJogadas1ganhas++;
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    } else if (trioNum1 < trioNum2) {
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    } else {
      /* como não ha full house então o desempate e por cartas mais altas */
      /* desempate por cartas mais elevadas */
      /* devolve -1 se jogador 1 ganha, 1 se jogador 2 ganha ou 0 se ha empate */
        booleano = desempatePorCartasMaisAltas (jogador1NumV, jogador2NumV);
        free (jogador1NumV);
        free (jogador2NumV);
        if (booleano == 0 || booleano == 1) {
          /* empate ou ganha jogador 2*/
          continue;
        } else {
          /* ganhou o jogador 1 */
          nJogadas1ganhas++;
          continue;
        }
    }
  }

  /* testa 2 pares */
  booleanoJogador1 = testa2Pares (jogador1NumV, &par1Jog1, &par2Jog1);
  booleanoJogador2 = testa2Pares (jogador2NumV, &par1Jog2, &par2Jog2);
  booleano = verificaBooleanos (booleanoJogador1, booleanoJogador2, jogador1NumV, jogador2NumV, &nJogadas1ganhas);
  if (booleano == 1) {
    continue;
  }
  if (booleanoJogador1 == 1 && booleanoJogador2 == 1) {
  /* desempate por pares mais altos */
  if (par1Jog1 > par1Jog2) {
    /* ganha o jogador 1 */
    nJogadas1ganhas++;
    free (jogador1NumV);
    free (jogador2NumV);
    continue;
  } else if (par1Jog1 < par1Jog2) {
    /* ganha o jogador 2 */
    free (jogador1NumV);
    free (jogador2NumV);
    continue;
  } else {
    /* par mais elevado empata */
    if (par2Jog1 > par2Jog2) {
      /* ganha o jogador 1 */
      nJogadas1ganhas++;
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    } else if (par2Jog1 < par2Jog2) {
      /* ganha o jogador 2 */
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    } else {
      /* o desempate tem de ser pela carta mais elevada */
      /* devolve -1 se jogador 1 ganha, 1 se jogador 2 ganha ou 0 se ha empate */
        booleano = desempatePorCartasMaisAltas (jogador1NumV, jogador2NumV);
        free (jogador1NumV);
        free (jogador2NumV);
        if (booleano == 0 || booleano == 1) {
          /* empate ou ganha jogador 2*/
          continue;
        } else {
          /* ganhou o jogador 1 */
          nJogadas1ganhas++;
          continue;
        }
      }
    }
  }
    /* testa 1 par */
    booleanoJogador1 = testaThreeOfaKind (jogador1NumV, &trioNum1, &posTrio);
    booleanoJogador1 = testa1Par (jogador1NumV, &par1Jog1, posTrio);

    booleanoJogador2 = testaThreeOfaKind (jogador2NumV, &trioNum2, &posTrio);
    booleanoJogador2 = testa1Par (jogador2NumV, &par1Jog2, posTrio);

    booleano = verificaBooleanos (booleanoJogador1, booleanoJogador2, jogador1NumV, jogador2NumV, &nJogadas1ganhas);
    if (booleano == 1) {
      continue;
    }
    if (booleanoJogador1 == 1 && booleanoJogador2 == 1) {
    /* desempate por pares mais altos */
    if (par1Jog1 > par1Jog2) {
      /* ganha o jogador 1 */
      nJogadas1ganhas++;
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    } else if (par1Jog1 < par1Jog2) {
      /* ganha o jogador 2 */
      free (jogador1NumV);
      free (jogador2NumV);
      continue;
    } else {
        /* o desempate tem de ser pela carta mais elevada */
        /* devolve -1 se jogador 1 ganha, 1 se jogador 2 ganha ou 0 se ha empate */
          booleano = desempatePorCartasMaisAltas (jogador1NumV, jogador2NumV);
          free (jogador1NumV);
          free (jogador2NumV);
          if (booleano == 0 || booleano == 1) {
            /* empate ou ganha jogador 2*/
            continue;
          } else {
            /* ganhou o jogador 1 */
            nJogadas1ganhas++;
            continue;
          }
      }
    }

  /* desempate por cartas mais elevadas */
  booleano = desempatePorCartasMaisAltas (jogador1NumV, jogador2NumV);
  free (jogador1NumV);
  free (jogador2NumV);
  if (booleano == 0 || booleano == 1) {
    /* empate ou ganha jogador 2*/
    continue;
  } else {
    /* ganhou o jogador 1 */
    nJogadas1ganhas++;
    continue;
  }

}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
printf ("\nO jogador 1 ganhou %d vezes.", nJogadas1ganhas);
printf ("\n");
return 0;
}

/******************************************************************************/

cartaJogada* leituraJogada (FILE *f) {
/* lê as 5 cartas jogadas para vector de 5 cartas jogadas criadas dinamicamente,
se não conseguir ler ou houver algum problema, retorna NULL */

if (f == NULL) {
  return NULL;
}

cartaJogada* cartas;

cartas = (cartaJogada*) calloc (5, sizeof (cartaJogada));
if (cartas == NULL) {
  return NULL;
}

if ((fscanf (f, "%s %s %s %s %s", cartas[0].carta, cartas[1].carta, cartas[2].carta, cartas[3].carta, cartas[4].carta)) == 5) {
  return cartas;
} else {
  free (cartas);
  return NULL;
}

}

/******************************************************************************/

cartasNumerico* converteStringCartasNumerico (cartaJogada* jogador) {
/* para cada vector de cartas Jogadas, em string, converte para um vector numerico
de cartas, para poder ser tratado numericamente, devolve o vector ou NULL em
caso de erro */

/*int cartaNum: 2 a 10 cartas normais, Valete 11, Dama 12, Rei 13, As 14 */
/* int naipe: H - copas (0), S - espadas (1), D - ouros (2), C - pais (3) */
if (jogador == NULL) {
  return NULL;
}

cartasNumerico *jogadorV;
char carta[2];
int i;

jogadorV = (cartasNumerico*) calloc (5, sizeof (cartasNumerico));
if (jogadorV == NULL) {
  return NULL;
}

for (i = 0; i < 5; i++) {
  /* primeiro vou preencher os dados de cartaNum */
  if (jogador[i].carta[0] == 'A') {
    jogadorV[i].cartaNum = 14;
  } else if (jogador[i].carta[0] == 'K') {
    jogadorV[i].cartaNum = 13;
  } else if (jogador[i].carta[0] == 'Q') {
    jogadorV[i].cartaNum = 12;
  } else if (jogador[i].carta[0] == 'J') {
    jogadorV[i].cartaNum = 11;
  } else if (jogador[i].carta[0] == 'T') {
      jogadorV[i].cartaNum = 10;
  } else {
    carta[0] = jogador[i].carta[0];
    carta[1] = '\0';
    jogadorV[i].cartaNum = atoi (carta);
  }

  /* agora vou preencher os dados dos naipes */
  /* int naipe: H - copas (0), S - espadas (1), D - ouros (2), C - pais (3) */
  if (jogador[i].carta[1] == 'H') {
    jogadorV[i].naipe = 0;
  } else if (jogador[i].carta[1] == 'S') {
    jogadorV[i].naipe = 1;
  } else if (jogador[i].carta[1] == 'D') {
    jogadorV[i].naipe = 2;
  } else if (jogador[i].carta[1] == 'C') {
    jogadorV[i].naipe = 3;
  }
}

return jogadorV;
}

/******************************************************************************/

void ordenaCartasPorValorNumericoDecrescente (cartasNumerico *jogador1NumV, cartasNumerico *jogador2NumV) {
/* ordena o vector por ordem decrescente de cartaNum, desde As ate ao 2,
e retorna no fim*/

if (jogador1NumV == NULL || jogador2NumV == NULL) {
  printf ("\nErro na função ordenaCartasPorValorNumericoDecrescente, parâmetros nulos.");
  return;
}

int i, j, auxCartaNum, auxNaipe;

for (i = 0; i < 4; i++) {
  for (j = i+1; j < 5; j++) {
    /* jogador 1 */
    if (jogador1NumV[j].cartaNum > jogador1NumV[i].cartaNum) {
      /* aux = i */
      auxCartaNum = jogador1NumV[i].cartaNum;
      auxNaipe = jogador1NumV[i].naipe;
      /* i = j */
      jogador1NumV[i].cartaNum = jogador1NumV[j].cartaNum;
      jogador1NumV[i].naipe = jogador1NumV[j].naipe;
      /* j = aux */
      jogador1NumV[j].cartaNum = auxCartaNum;
      jogador1NumV[j].naipe = auxNaipe;
    }

    /* jogador 2 */
    if (jogador2NumV[j].cartaNum > jogador2NumV[i].cartaNum) {
      /* aux = i */
      auxCartaNum = jogador2NumV[i].cartaNum;
      auxNaipe = jogador2NumV[i].naipe;
      /* i = j */
      jogador2NumV[i].cartaNum = jogador2NumV[j].cartaNum;
      jogador2NumV[i].naipe = jogador2NumV[j].naipe;
      /* j = aux */
      jogador2NumV[j].cartaNum = auxCartaNum;
      jogador2NumV[j].naipe = auxNaipe;
    }
  }
}

}

/******************************************************************************/

int testaRoyalFlush (cartasNumerico *jogador) {
/* testa a existencia de um RoyalFlush, retorna 1 se ocorreu um RoyalFlush ou 0 se não */

int naipeRef, i, somaCartas = 0;
naipeRef = jogador[0].naipe;


for (i = 0; i < 5; i++) {
  if (jogador[i].naipe != naipeRef) {
    return 0;
  }
  somaCartas = somaCartas + jogador[i].cartaNum;
}

if (somaCartas == 50) {
  return 1;
} else {
  return 0;
}

}

/******************************************************************************/

int testaStraightFlush (cartasNumerico *jogador) {
/* testa a existencia de um straightFlush, retorna 1 se ocorreu um straightFlush ou 0 se não */

int naipeRef, i, subtracao;
naipeRef = jogador[0].naipe;

/* como as cartas estão por ordem decrescente, a sutracçao tem de dar 1 */

for (i = 0; i < 4; i++) {
  if (jogador[i].naipe != naipeRef) {
    return 0;
  }
  subtracao = jogador[i].cartaNum - jogador[i+1].cartaNum;
  if (subtracao != 1) {
    return 0;
  }
}

/* se chega aqui e porque e um straight flush */
return 1;
}

/******************************************************************************/

int verificaBooleanos (int booleanoJogador1, int booleanoJogador2, cartasNumerico *jogador1NumV, cartasNumerico *jogador2NumV, int *nJogadas1ganhas) {
/* verifica se já temos um vencedor, se o vencedor for o jogador, actualiza o
numero de vitorias. Devolve 1 se ja tiver chegado a um vencedor ou 0 se ainda não */

if (booleanoJogador1 == 1 && booleanoJogador2 == 0) {
  *nJogadas1ganhas = *nJogadas1ganhas+1;
  free (jogador1NumV);
  free (jogador2NumV);
  return 1;
} else if (booleanoJogador1 == 0 && booleanoJogador2 == 1) {
  free (jogador1NumV);
  free (jogador2NumV);
  return 1;
} else if (booleanoJogador1 == 1 && booleanoJogador2 == 1) {
  return 0;
}

/* se chega aqui e porque ainda não temos vencedor */
return 0;

}

/******************************************************************************/

int testaFourOfaKind (cartasNumerico *jogador, int *num4Kind) {
/* testa a existencia de um 4ofAkind, retorna 1 se ocorreu um 4 of a kind ou 0 se não */
/* devolve por referencia o valor do carta num do conjunto de 4 cartas */

int naipeRef, i;
naipeRef = jogador[0].naipe;

/* como as cartas estão ordenadas por ordem numerica, a carta diferente ou e maior
e esta a esquerda ou e menor e esta na outra ponta */

/* caso 1, esta à direita */
if (jogador[1].cartaNum == jogador[2].cartaNum) {
  if (jogador[1].cartaNum == jogador[3].cartaNum) {
    if (jogador[1].cartaNum == jogador[4].cartaNum) {
      /* se chega aqui e porque são todas do mesmo tipo */
      *num4Kind = jogador[1].cartaNum;
      return 1;
    }
  }
}

/* caso 2, a carta diferente esta à esquerda */
if (jogador[0].cartaNum == jogador[1].cartaNum) {
  if (jogador[0].cartaNum == jogador[2].cartaNum) {
    if (jogador[0].cartaNum == jogador[3].cartaNum) {
      /* se chega aqui e porque são todas do mesmo tipo */
      *num4Kind = jogador[0].cartaNum;
      return 1;
    }
  }
}

/* se chega aqui e porque não e um four of a kind */
return 0;
}

/******************************************************************************/

int testaFullHouse (cartasNumerico *jogador, int *trioNum) {
/* testa a existencia de um FullHouse, retorna 1 se ocorreu um Full House ou 0 se não */
/* devolve por referencia o valor numerico de trioNum */
int trioNumVal, booleano, par1, booleanoPar, posTrio;


booleano = testaThreeOfaKind (jogador, &trioNumVal, &posTrio);
if (booleano == 0) {
  return 0;
}

booleanoPar = testa1Par (jogador, &par1, posTrio);

if (booleanoPar == 1 && booleano == 1) {
  /* neste caso trata-se de um fullHouse */
  *trioNum = trioNumVal;
  return 1;
} else {
  return 0;
}

}

/******************************************************************************/

int testaFlush (cartasNumerico *jogador) {
/* testa a existencia de um Flush, retorna 1 se ocorreu um Flush ou 0 se não */

int naipeRef, i;
naipeRef = jogador[0].naipe;

for (i = 0; i < 5; i++) {
  if (jogador[i].naipe != naipeRef) {
    return 0;
  }
}

/* se chega aqui e porque e um flush */
return 1;
}

/******************************************************************************/

int testaThreeOfaKind (cartasNumerico *jogador, int *trioNumVal, int *posTrio) {
/* devolve 1 se houver 1 trio, assim como o valor do trioNumVal por referencia,
senão devolve 0 */
/* devolve 1 se houver 1 trio, assim como o valor do trioNumVal por referencia,
senão devolve 0, tenho uma flag a informar qual a posicao do trio,
imediatamente a frente */
/* como as cartas estão por ordem crescente, os 3 podem estar a esquerda, no meio,
ou a direita */

/* cartas a esquerda */
if (jogador[0].cartaNum == jogador[1].cartaNum) {
  if (jogador[0].cartaNum == jogador[2].cartaNum) {
    *trioNumVal = jogador[0].cartaNum;
    *posTrio = 3;
    return 1;
  }
}

/* cartas no meio */
if (jogador[1].cartaNum == jogador[2].cartaNum) {
  if (jogador[1].cartaNum == jogador[3].cartaNum) {
    *trioNumVal = jogador[1].cartaNum;
    *posTrio = 4;
    return 1;
  }
}

/* cartas à direita */
if (jogador[2].cartaNum == jogador[3].cartaNum) {
  if (jogador[2].cartaNum == jogador[4].cartaNum) {
    *trioNumVal = jogador[2].cartaNum;
    *posTrio = 5;
    return 1;
  }
}

/* se chega aqui é porque não há trio nenhum */
*posTrio = -1;
return 0;
}

/******************************************************************************/

int testa1Par (cartasNumerico *jogador, int *par1, int posTrio) {
/* verifica a existencia de 1 par, retorna 1 se existir 1 pares ou 0 se não.
Se existir devolve o par no par1 */

/* so chego aqui depois se saber ou que ha um trio ou depois de saber que não tenho
dois pares, se não houver trio é -1 */
/* posso ter um trio ou 3 cartas todas diferentes */

int i, j;

if (posTrio != -1) {
  /* valores possiveis para posTrio: 3, 4 ou 5 */
  if (posTrio == 4) {
    /* trio no meio das 5 cartas, logo não ha par nenhum */
    return 0;
  } else if (posTrio == 3) {
    if (jogador[3].cartaNum == jogador[4].cartaNum) {
      *par1 = jogador[3].cartaNum;
      return 1;
    } else {
      return 0;
    }
  } else {
    if (jogador[0].cartaNum == jogador[1].cartaNum) {
      *par1 = jogador[0].cartaNum;
      return 1;
    } else {
      return 0;
    }
  }
}

/* se chega aqui é porque não ha trios nem 2 pares */

for (i = 0; i < 4; i++) {
  for (j = i+1; j < 5; j++) {
    if (jogador[i].cartaNum == jogador[j].cartaNum) {
      *par1 = jogador[i].cartaNum;
      return 1;
    }
  }
}

/* se chega aqui é porque não ha nenhum par */
return 0;
}

/******************************************************************************/

int desempatePorCartasMaisAltas (cartasNumerico *jogador1NumV, cartasNumerico *jogador2NumV) {
/*desempata através das cartas mais elevadas,
devolve -1 se jogador 1 ganha, 1 se jogador 2 ganha ou 0 se ha empate */

int i;

for (i = 0; i < 5; i++) {
  if (jogador1NumV[i].cartaNum > jogador2NumV[i].cartaNum) {
    return -1;
  } else if (jogador1NumV[i].cartaNum < jogador2NumV[i].cartaNum) {
    return 1;
  }
}

/* se chega aqui é porque houve um empate */
return 0;
}

/******************************************************************************/

int testaStraight (cartasNumerico *jogador) {
/* testa a existencia de straight, retorna 1 se ocorrer straight ou 0 se não */

int naipeRef, i, subtracao;
naipeRef = jogador[0].naipe;

/* como as cartas estão por ordem decrescente, a sutracçao tem de dar 1 */

for (i = 0; i < 4; i++) {
  subtracao = jogador[i].cartaNum - jogador[i+1].cartaNum;
  if (subtracao != 1) {
    return 0;
  }
}

/* se chega aqui e porque e um straight*/
return 1;
}

/******************************************************************************/

int testa2Pares (cartasNumerico *jogador, int *par1, int *par2) {
/* verifica a existencia de 2 pares, retorna 1 se existem 2 pares ou 0 se não.
Se existir devolve o par maximo no par1 e o par minimo no par2 */

/* so podem existir 2 pares um em cada canto, dois do lado esquerdo ou 2 do lado
direito */
int i, dif, nPares = 0;
int par1N, par2N;

for (i = 0; i < 4; i++) {
  dif = jogador[i+1].cartaNum - jogador[i].cartaNum;
  if (dif != 0) {
    if (nPares == 0) {
      par1N = jogador[i].cartaNum;
    } else {
      par2N = jogador[i].cartaNum;
    }
    nPares++;
  }
}

if (nPares != 2) {
  return 0;
}

/* se chega aqui e porque temos 2 pares */
if (par1N > par2N) {
  *par1 = par1N;
  *par2 = par2N;
} else {
  *par1 = par2N;
  *par2 = par1N;
}

return 1;
}

/******************************************************************************/
