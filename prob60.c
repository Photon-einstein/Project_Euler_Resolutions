#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAXPRIME 10000
#define SIZE MAXPRIME/2

typedef struct {
  int primo;
  int dim;
  int nAlg;
} primeV;

/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */
int primeTeste (int nTeste);

/* calcula dim do contador e devolve também o nAlg do contador */
int dimCalc (int contador, int *nAlg);

/* efectua as rotações de acordo com os indices do vector, e depois, confirma se
são primos ou não, se forem então retorna a soma dos 5 primos, senão retorna 0*/
int booleanoTestaPrimePair (primeV *v, int *indices);

/* efectua as rotações de acordo com os indices do vector, e depois, confirma se
são primos ou não, se forem então retorna a soma dos 5 primos, senão retorna 0*/
int booleanoTestaPrimePair01Pares (primeV *v, int *indices);

/* efectua as rotações de acordo com os indices do vector, e depois, confirma se
são primos ou não, se forem então retorna a soma dos 5 primos, senão retorna 0*/
int booleanoTestaPrimePair12Pares (primeV *v, int *indices);


/* efectua as rotações de acordo com os indices do vector, e depois, confirma se
são primos ou não, se forem então retorna a soma dos 5 primos, senão retorna 0*/
int booleanoTestaPrimePair23Pares (primeV *v, int *indices);

/* efectua as rotações de acordo com os indices do vector, e depois, confirma se
são primos ou não, se forem então retorna a soma dos 5 primos, senão retorna 0*/
int booleanoTestaPrimePair34Pares (primeV *v, int *indices);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();
/* tarefa a verificar */
int nTeste, nPrimos = 0, mult = 1, booleano, dimVector, i, indices[5] = {0}, sum, sumMin = 10000000, found = 0;
primeV *prVec;

dimVector = SIZE*mult;
prVec = (primeV*) calloc (dimVector, sizeof (primeV));
if (prVec == NULL) {
  return 0;
}

for (nTeste = 3; nTeste < MAXPRIME+1; nTeste = nTeste+2) {
  if (nTeste == 5) {
    continue;
  }
  booleano = primeTeste (nTeste);

  if (booleano == 1) {
    if (nPrimos == dimVector) {
      mult++;
      dimVector = SIZE*mult;
      prVec = (primeV*) realloc (prVec ,dimVector*sizeof(primeV));
      if (prVec == NULL) {
        printf ("\nErro na realocação de prVec.");
        return 0;
      }
    }
    prVec[nPrimos].primo = nTeste;
    prVec[nPrimos].dim = dimCalc (nTeste, &prVec[nPrimos].nAlg);
    nPrimos++;
  }
}

prVec = (primeV*) realloc (prVec, nPrimos*sizeof (primeV));
if (prVec == NULL) {
  printf ("\nOcorreu uma falha na realocação.");
  return 0;
}

printf ("\nExistem %d primos até %d.", nPrimos, MAXPRIME);

for (indices[0] = 0; indices[0] < nPrimos-4; indices[0]++) {
  printf ("\ni = %d", indices[0]);
  if (found == 1) {
    printf (" SumMin = %d", sumMin);
  }
  fflush (stdout);
  for (indices[1] = indices[0]+1; indices[1] < nPrimos-3; indices[1]++) {
    sum = booleanoTestaPrimePair01Pares (prVec, indices);
    if (sum == 0) {
      continue;
    }
    for (indices[2] = indices[1]+1; indices[2] < nPrimos-2; indices[2]++) {
      sum = booleanoTestaPrimePair12Pares (prVec, indices);
      if (sum == 0) {
        continue;
      }
      for (indices[3] = indices[2]+1; indices[3] < nPrimos-1; indices[3]++) {
        sum = booleanoTestaPrimePair23Pares (prVec, indices);
        if (sum == 0) {
          continue;
        }
        for (indices[4] = indices[3]+1; indices[4] < nPrimos; indices[4]++) {
          sum = booleanoTestaPrimePair34Pares (prVec, indices);
          if (sum == 0) {
            continue;
          }
          sum = booleanoTestaPrimePair (prVec, indices);
          if (sum == 0) {
            continue;
          } else if (sum < sumMin) {
            sumMin = sum;
            found = 1;
            printf ("\nSolução: %d %d %d %d %d", prVec[indices[0]].primo, prVec[indices[1]].primo, prVec[indices[2]].primo, prVec[indices[3]].primo, prVec[indices[4]].primo);
            break;
          }
        }
        if (found == 1) {
          break;
        }
      }
      if (found == 1) {
        break;
      }
    }
    if (found == 1) {
      break;
    }
  }
  if (found == 1) {
    break;
  }
}
/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
if (sumMin == 10000000) {
  printf ("\nNão foi encontrado o prime pair para 5 números.");
} else {
  printf ("\nA soma menor para 5 prime pairs é de: %d.", sumMin);
}
printf ("\n");
return 0;
}
/******************************************************************************/
int primeTeste (int nTeste) {
/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */

int i;

if (nTeste <= 1) {
	return 0;
}
if (nTeste  == 2) {
	return 1;
} else if (nTeste % 2 == 0) {
	return 0;
}
for (i = 3; i < sqrt(nTeste+1); i = i+2) {
	if (nTeste % i == 0) {
		return 0;
	}
}
/* se chega aqui é porque é um número primo */
return 1;
}
/******************************************************************************/
int dimCalc (int contador, int *nAlg) {
/* calcula dim do contador e devolve também o nAlg do contador */

int dim = 1;
int res, nAlgarismos = 1;

res = contador / dim;

while (res > 9) {
  dim = dim * 10;
  nAlgarismos++;
  res = contador / dim;
}

*nAlg = nAlgarismos;
return dim;
}
/******************************************************************************/
int booleanoTestaPrimePair (primeV *v, int *indices) {
/* efectua as rotações de acordo com os indices do vector, e depois, confirma se
são primos ou não, se forem então retorna a soma dos 5 primos, senão retorna 0*/

int i, j, numero, avanco, booleano, sum = 0;
int esquerda, direita, n, diff;

/* numero i a direita e o numero j a esquerda */
for (i = 0; i < 5; i++) {
  for (j = 0; j < 5; j++) {
    if (i == j) {
      continue;
    }
    diff = abs (i-j);
    if (diff == 1) {
      continue;
    }
    esquerda = indices[i];
    direita = indices[j];

    avanco = pow (10, v[direita].nAlg);
    numero = v[esquerda].primo*avanco+v[direita].primo;
    /* se o pos e null então ainda não existe em nenhum deles, vou testar se e primo*/
    booleano = primeTeste (numero);
    if (booleano == 0) {
      /* neste caso não e primo*/
      return 0;
    }
  }
}


/* se chega aqui é porque está tudo ok, vou somar os números */
for (i = 0; i < 5; i++) {
  n = indices[i];
  sum = sum + v[n].primo;
}
/* se chega aqui é porque estamos perante um prime pair */
return sum;
}
/******************************************************************************/
int booleanoTestaPrimePair01Pares (primeV *v, int *indices) {
  /* efectua as rotações de acordo com os indices do vector, e depois, confirma se
  são primos ou não, se forem então retorna a soma dos 2 primos, senão retorna 0*/

int i, j, numero, avanco, booleano, sum = 0;
int esquerda, direita, n;

/* numero i a direita e o numero j a esquerda */
for (i = 0; i < 2; i++) {
  for (j = 0; j < 2; j++) {
    if (i == j) {
      continue;
    }
    esquerda = indices[i];
    direita = indices[j];

    avanco = pow (10, v[direita].nAlg);
    numero = v[esquerda].primo*avanco+v[direita].primo;
    /* se o pos e null então ainda não existe em nenhum deles, vou testar se e primo*/
    booleano = primeTeste (numero);
    if (booleano == 0) {
      /* neste caso não e primo*/
      return 0;
    }
  }
}

return 1;
}
/******************************************************************************/
int booleanoTestaPrimePair12Pares (primeV *v, int *indices) {
  /* efectua as rotações de acordo com os indices do vector, e depois, confirma se
  são primos ou não, se forem então retorna a soma dos 2 primos, senão retorna 0*/

int i, j, numero, avanco, booleano, sum = 0;
int esquerda, direita, n;

/* numero i a direita e o numero j a esquerda */
for (i = 1; i < 3; i++) {
  for (j = 1; j < 3; j++) {
    if (i == j) {
      continue;
    }
    esquerda = indices[i];
    direita = indices[j];

    avanco = pow (10, v[direita].nAlg);
    numero = v[esquerda].primo*avanco+v[direita].primo;
    /* se o pos e null então ainda não existe em nenhum deles, vou testar se e primo*/
    booleano = primeTeste (numero);
    if (booleano == 0) {
      /* neste caso não e primo*/
      return 0;
    }
  }
}

return 1;
}
/******************************************************************************/
int booleanoTestaPrimePair23Pares (primeV *v, int *indices) {
  /* efectua as rotações de acordo com os indices do vector, e depois, confirma se
  são primos ou não, se forem então retorna a soma dos 2 primos, senão retorna 0*/

int i, j, numero, avanco, booleano, sum = 0;
int esquerda, direita, n;

/* numero i a direita e o numero j a esquerda */
for (i = 2; i < 4; i++) {
  for (j = 2; j < 4; j++) {
    if (i == j) {
      continue;
    }
    esquerda = indices[i];
    direita = indices[j];

    avanco = pow (10, v[direita].nAlg);
    numero = v[esquerda].primo*avanco+v[direita].primo;
    /* se o pos e null então ainda não existe em nenhum deles, vou testar se e primo*/
    booleano = primeTeste (numero);
    if (booleano == 0) {
      /* neste caso não e primo*/
      return 0;
    }
  }
}

return 1;
}
/******************************************************************************/
int booleanoTestaPrimePair34Pares (primeV *v, int *indices) {
/* efectua as rotações de acordo com os indices do vector, e depois, confirma se
são primos ou não, se forem então retorna a soma dos 5 primos, senão retorna 0*/
int i, j, numero, avanco, booleano, sum = 0;
int esquerda, direita, n;

/* numero i a direita e o numero j a esquerda */
for (i = 3; i < 5; i++) {
  for (j = 3; j < 5; j++) {
    if (i == j) {
      continue;
    }
    esquerda = indices[i];
    direita = indices[j];

    avanco = pow (10, v[direita].nAlg);
    numero = v[esquerda].primo*avanco+v[direita].primo;
    /* se o pos e null então ainda não existe em nenhum deles, vou testar se e primo*/
    booleano = primeTeste (numero);
    if (booleano == 0) {
      /* neste caso não e primo*/
      return 0;
    }
  }
}

return 1;
}
/******************************************************************************/
