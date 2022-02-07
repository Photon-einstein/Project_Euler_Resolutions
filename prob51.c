#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX 1000000
#define CHECK 8

/* esta função verifica se o número nTeste é um primo, retorna 1 se primo ou 0 se não */
int primeTeste (int nTeste);

/* calcula dim do contador e devolve também o nAlg do contador */
int dimCalc (int contador, int *nAlg);

/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/
int *preencheVectorDigit (int contador, int dim, int nAlg);

/* devolve o numero com os digitos no vector, de de dimensão dim */
int geraNumero (int *vDigit, int dim, int nAlg);

/* subsitui um digito no vector digit e retorna o numero gerado */
int subsitui1Digito (int *vDigit, int dim, int nAlg, int pos, int numero);

/* subsitui dois digitos no vector digit e retorna o numero gerado */
int subsitui2Digito (int *vDigit, int dim, int nAlg, int pos1, int pos2, int numero);

/* subsitui três digitos no vector digit e retorna o numero gerado */
int subsitui3Digito (int *vDigit, int dim, int nAlg, int pos1, int pos2, int pos3, int numero);

/* subsitui quatro digitos no vector digit e retorna o numero gerado */
int subsitui4Digito (int *vDigit, int dim, int nAlg, int pos1, int pos2, int pos3, int pos4, int numero);

/* subsitui quatro digitos no vector digit e retorna o numero gerado */
int subsitui5Digito (int *vDigit, int dim, int nAlg, int pos1, int pos2, int pos3, int pos4, int pos5, int numero);

/* verifica qual o menor primo de entre um vector com n primos*/
int encontraMinimoPrimo (int *resposta, int nPrimosGerados);

int main () {

clock_t inicio, fim;
double tempo;
inicio = clock();

/* tarefa a verificar */
int nTeste, booleano, dim, nAlg, pos, numero, i, pos1, pos2, pos3, pos4, pos5;
int found = 0, *vDigit, numeroGerado, nPrimosGerados = 0, nPrimosGeradosMax = 0;
int *resposta, minimoPrimoGerado, minimoPrimoGeradoAbsoluto = 10000000;

/* agora vou testar todos os numeros desde 11 ate max-1 */

for (nTeste = 11; nTeste < (MAX-1); nTeste = nTeste + 2) {
  printf ("\nnTeste = %d", nTeste);
  fflush (stdout);
  if (found == 1) {
    break;
  }
  dim = dimCalc (nTeste, &nAlg);
  vDigit = preencheVectorDigit (nTeste, dim, nAlg);
  if (vDigit == NULL) {
    printf ("\nOcorreu uma falha na criação do vector digit.");
    return 0;
  }


  if (dim == 10) {
    /* reset dos contadores */
    nPrimosGerados = 0;
    resposta = (int*) calloc (10, sizeof (int));
    if (resposta == NULL) {
      printf ("\nFalha na alocação de memória do vector resposta.");
      return 0;
    }

    /* so posso substituir o digito da esquerda, 1 digito*/
    pos = 0;

    for (numero = 0; numero < 10; numero++) {
      if (pos == 0 && numero == 0) {
        continue;
      }
      numeroGerado = subsitui1Digito (vDigit, dim, nAlg, pos, numero);
      booleano = primeTeste (numeroGerado);

      if (booleano == 1) {
        resposta[nPrimosGerados] = numeroGerado;
          nPrimosGerados++;
          if (nPrimosGeradosMax < nPrimosGerados) {
            nPrimosGeradosMax = nPrimosGerados;
          }
      }
    }

    /* averiguação da resposta */
    /* averiguação se os valores vão ser substituidos */
    minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
    if (nPrimosGerados == CHECK) {
      found = 1;
      if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
        minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
      }
      break;
    }
    free (resposta);

  } else if (dim == 100) {

    /* posso substituir o digito da esquerta ou o do meio ou os 2, 1 ou 2 digitos*/

    /* primeiro apenas um digito a trocar */
    for (pos = 0; pos < nAlg-1; pos++) {

      /* reset dos contadores */
      nPrimosGerados = 0;
      resposta = (int*) calloc (10, sizeof (int));
      if (resposta == NULL) {
        printf ("\nFalha na alocação de memória do vector resposta.");
        return 0;
      }

      vDigit = preencheVectorDigit (nTeste, dim, nAlg);
      if (vDigit == NULL) {
        printf ("\nOcorreu uma falha na criação do vector digit.");
        return 0;
      }
      /******/

      for (numero = 0; numero < 10; numero++) {
        if (pos == 0 && numero == 0) {
          continue;
        }
        numeroGerado = subsitui1Digito (vDigit, dim, nAlg, pos, numero);
        booleano = primeTeste (numeroGerado);

        if (booleano == 1) {
          resposta[nPrimosGerados] = numeroGerado;
            nPrimosGerados++;
            if (nPrimosGeradosMax < nPrimosGerados) {
              nPrimosGeradosMax = nPrimosGerados;
            }
          }
        }
        /* averiguação da resposta */
        /* averiguação se os valores vão ser substituidos */
        minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
        if (nPrimosGerados == CHECK) {
          found = 1;
          if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
            minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
          }
          break;
        }
        free (resposta);
      }

      /* agora dois digitos a trocar */
      /* reset dos contadores */
      nPrimosGerados = 0;
      resposta = (int*) calloc (10, sizeof (int));
      if (resposta == NULL) {
        printf ("\nFalha na alocação de memória do vector resposta.");
        return 0;
      }
      vDigit = preencheVectorDigit (nTeste, dim, nAlg);
      if (vDigit == NULL) {
        printf ("\nOcorreu uma falha na criação do vector digit.");
        return 0;
      }
      /************/

      /* so posso substituir o digito da esquerda e o do meio, 2 digito a subsituir*/

      for (numero = 0; numero < 10; numero++) {
        if (numero == 0) {
          continue;
        }
        numeroGerado = subsitui2Digito (vDigit, dim, nAlg, 0, 1, numero);
        booleano = primeTeste (numeroGerado);

        if (booleano == 1) {
          resposta[nPrimosGerados] = numeroGerado;
            nPrimosGerados++;
            if (nPrimosGeradosMax < nPrimosGerados) {
              nPrimosGeradosMax = nPrimosGerados;
            }
        }
      }

      /* averiguação da resposta */
      /* averiguação se os valores vão ser substituidos */
      minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
      if (nPrimosGerados == CHECK) {
        found = 1;
        if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
          minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
        }
        break;
      }
      free (resposta);

  } else if (dim == 1000) {
    /* posso substituir o digito 0, 1 ou 2. 1-2 ou 3 digitos*/

    /* primeiro apenas um digito a trocar */
    for (pos = 0; pos < nAlg-1; pos++) {

      /* reset dos contadores */
      nPrimosGerados = 0;
      resposta = (int*) calloc (10, sizeof (int));
      if (resposta == NULL) {
        printf ("\nFalha na alocação de memória do vector resposta.");
        return 0;
      }

      vDigit = preencheVectorDigit (nTeste, dim, nAlg);
      if (vDigit == NULL) {
        printf ("\nOcorreu uma falha na criação do vector digit.");
        return 0;
      }
      /******/

      for (numero = 0; numero < 10; numero++) {
        if (pos == 0 && numero == 0) {
          continue;
        }
        numeroGerado = subsitui1Digito (vDigit, dim, nAlg, pos, numero);
        booleano = primeTeste (numeroGerado);

        if (booleano == 1) {
          resposta[nPrimosGerados] = numeroGerado;
            nPrimosGerados++;
            if (nPrimosGeradosMax < nPrimosGerados) {
              nPrimosGeradosMax = nPrimosGerados;
            }
          }
        }
        /* averiguação da resposta */
        /* averiguação se os valores vão ser substituidos */
        minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
        if (nPrimosGerados == CHECK) {
          found = 1;
          if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
            minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
          }
          break;
        }
        free (resposta);
      }

      /* 2 digito a subsituir*/
      for (pos1 = 0; pos1 < nAlg-1; pos1++) {
        for (pos2 = 0; pos2 < nAlg-1; pos2++) {

          if (pos1 == pos2) {
            continue;
          }
          /* reset dos contadores */
          nPrimosGerados = 0;
          resposta = (int*) calloc (10, sizeof (int));
          if (resposta == NULL) {
            printf ("\nFalha na alocação de memória do vector resposta.");
            return 0;
          }
          vDigit = preencheVectorDigit (nTeste, dim, nAlg);
          if (vDigit == NULL) {
            printf ("\nOcorreu uma falha na criação do vector digit.");
            return 0;
          }
          /************/

          for (numero = 0; numero < 10; numero++) {
            if (numero == 0 && (pos1 == 0 || pos2 == 0) ) {
              continue;
            }
            numeroGerado = subsitui2Digito (vDigit, dim, nAlg, pos1, pos2, numero);
            booleano = primeTeste (numeroGerado);

            if (booleano == 1) {
              resposta[nPrimosGerados] = numeroGerado;
                nPrimosGerados++;
                if (nPrimosGeradosMax < nPrimosGerados) {
                  nPrimosGeradosMax = nPrimosGerados;
                }
              }
            }

            /* averiguação da resposta */
            /* averiguação se os valores vão ser substituidos */
            minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
            if (nPrimosGerados == CHECK) {
              found = 1;
              if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
                minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
              }
              break;
            }
            free (resposta);

          }
        }

        /* agora falta substituir 3 digitos do algarismo de dimensão 1000 */
        /* reset dos contadores */
        nPrimosGerados = 0;
        resposta = (int*) calloc (10, sizeof (int));
        if (resposta == NULL) {
          printf ("\nFalha na alocação de memória do vector resposta.");
          return 0;
        }
        vDigit = preencheVectorDigit (nTeste, dim, nAlg);
        if (vDigit == NULL) {
          printf ("\nOcorreu uma falha na criação do vector digit.");
          return 0;
        }


        for (numero = 0; numero < 10; numero++) {
          if (numero == 0) {
            continue;
          }
          numeroGerado = subsitui3Digito (vDigit, dim, nAlg, 0, 1, 2, numero);
          booleano = primeTeste (numeroGerado);

          if (booleano == 1) {
            resposta[nPrimosGerados] = numeroGerado;
              nPrimosGerados++;
              if (nPrimosGeradosMax < nPrimosGerados) {
                nPrimosGeradosMax = nPrimosGerados;
              }
          }
        }

        /* averiguação da resposta */
        /* averiguação se os valores vão ser substituidos */
        minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
        if (nPrimosGerados == CHECK) {
          found = 1;
          if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
            minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
          }
          break;
        }
        free (resposta);
  } else if (dim == 10000) {
    /* posso substituir o digito 0, 1, 2 ou 3. 1-2-3 ou 4 digitos*/
    /* primeiro apenas um digito a trocar */
    for (pos = 0; pos < nAlg-1; pos++) {

      /* reset dos contadores */
      nPrimosGerados = 0;
      resposta = (int*) calloc (10, sizeof (int));
      if (resposta == NULL) {
        printf ("\nFalha na alocação de memória do vector resposta.");
        return 0;
      }

      vDigit = preencheVectorDigit (nTeste, dim, nAlg);
      if (vDigit == NULL) {
        printf ("\nOcorreu uma falha na criação do vector digit.");
        return 0;
      }
      /******/

      for (numero = 0; numero < 10; numero++) {
        if (pos == 0 && numero == 0) {
          continue;
        }
        numeroGerado = subsitui1Digito (vDigit, dim, nAlg, pos, numero);
        booleano = primeTeste (numeroGerado);

        if (booleano == 1) {
          resposta[nPrimosGerados] = numeroGerado;
            nPrimosGerados++;
            if (nPrimosGeradosMax < nPrimosGerados) {
              nPrimosGeradosMax = nPrimosGerados;
            }
          }
        }
        /* averiguação da resposta */
        /* averiguação se os valores vão ser substituidos */
        minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
        if (nPrimosGerados == CHECK) {
          found = 1;
          if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
            minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
          }
          break;
        }
        free (resposta);
      }

      /* 2 digito a subsituir*/
      for (pos1 = 0; pos1 < nAlg-1; pos1++) {
        for (pos2 = 0; pos2 < nAlg-1; pos2++) {

          if (pos1 == pos2) {
            continue;
          }
          /* reset dos contadores */
          nPrimosGerados = 0;
          resposta = (int*) calloc (10, sizeof (int));
          if (resposta == NULL) {
            printf ("\nFalha na alocação de memória do vector resposta.");
            return 0;
          }
          vDigit = preencheVectorDigit (nTeste, dim, nAlg);
          if (vDigit == NULL) {
            printf ("\nOcorreu uma falha na criação do vector digit.");
            return 0;
          }
          /************/

          for (numero = 0; numero < 10; numero++) {
            if (numero == 0 && (pos1 == 0 || pos2 == 0) ) {
              continue;
            }
            numeroGerado = subsitui2Digito (vDigit, dim, nAlg, pos1, pos2, numero);
            booleano = primeTeste (numeroGerado);

            if (booleano == 1) {
              resposta[nPrimosGerados] = numeroGerado;
                nPrimosGerados++;
                if (nPrimosGeradosMax < nPrimosGerados) {
                  nPrimosGeradosMax = nPrimosGerados;
                }
              }
            }

            /* averiguação da resposta */
            /* averiguação se os valores vão ser substituidos */
            minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
            if (nPrimosGerados == CHECK) {
              found = 1;
              if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
                minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
              }
              break;
            }
            free (resposta);

          }
        }


        /* agora falta substituir 3 digitos do algarismo de dimensão 10000 */
        for (pos1 = 0; pos1 < nAlg-1; pos1++) {
          for (pos2 = 0; pos2 < nAlg-1; pos2++) {
            for (pos3 = 0; pos3 < nAlg-1; pos3++) {
              if (pos1 == pos2 || pos2 == pos3 || pos1 == pos3) {
                continue;
              }

              /* reset dos contadores */
              nPrimosGerados = 0;
              resposta = (int*) calloc (10, sizeof (int));
              if (resposta == NULL) {
                printf ("\nFalha na alocação de memória do vector resposta.");
                return 0;
              }
              vDigit = preencheVectorDigit (nTeste, dim, nAlg);
              if (vDigit == NULL) {
                printf ("\nOcorreu uma falha na criação do vector digit.");
                return 0;
              }

              for (numero = 0; numero < 10; numero++) {
                if (numero == 0 && (pos1 == 0 || pos2 == 0 || pos3 == 0)) {
                  continue;
                }
                numeroGerado = subsitui3Digito (vDigit, dim, nAlg, pos1, pos2, pos3, numero);
                booleano = primeTeste (numeroGerado);

                if (booleano == 1) {
                  resposta[nPrimosGerados] = numeroGerado;
                    nPrimosGerados++;
                    if (nPrimosGeradosMax < nPrimosGerados) {
                      nPrimosGeradosMax = nPrimosGerados;
                    }
                }
              }

              /* averiguação da resposta */
              /* averiguação se os valores vão ser substituidos */
              minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
              if (nPrimosGerados == CHECK) {
                found = 1;
                if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
                  minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
                }
                break;
              }
              free (resposta);
            }
          }
        }


        /* agora falta substituir 4 digitos do algarismo de dimensão 100 00 */
        /* reset dos contadores */
        nPrimosGerados = 0;
        resposta = (int*) calloc (10, sizeof (int));
        if (resposta == NULL) {
          printf ("\nFalha na alocação de memória do vector resposta.");
          return 0;
        }
        vDigit = preencheVectorDigit (nTeste, dim, nAlg);
        if (vDigit == NULL) {
          printf ("\nOcorreu uma falha na criação do vector digit.");
          return 0;
        }

        for (numero = 1; numero < 10; numero++) {
          numeroGerado = subsitui4Digito (vDigit, dim, nAlg, 0, 1, 2, 3, numero);
          booleano = primeTeste (numeroGerado);

          if (booleano == 1) {
            resposta[nPrimosGerados] = numeroGerado;
              nPrimosGerados++;
              if (nPrimosGeradosMax < nPrimosGerados) {
                nPrimosGeradosMax = nPrimosGerados;
              }
          }
        }

        /* averiguação da resposta */
        /* averiguação se os valores vão ser substituidos */
        minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
        if (nPrimosGerados == CHECK) {
          found = 1;
          if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
            minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
          }
          free (resposta);
          break;
        }
        free (resposta);

  } else if (dim == 100000) {
    /* posso substituir o digito 0, 1, 2, 3 ou 4. 1-2-3-4 ou 5 digitos*/

    /* primeiro apenas um digito a trocar */
    for (pos = 0; pos < nAlg-1; pos++) {

      /* reset dos contadores */
      nPrimosGerados = 0;
      resposta = (int*) calloc (10, sizeof (int));
      if (resposta == NULL) {
        printf ("\nFalha na alocação de memória do vector resposta.");
        return 0;
      }

      vDigit = preencheVectorDigit (nTeste, dim, nAlg);
      if (vDigit == NULL) {
        printf ("\nOcorreu uma falha na criação do vector digit.");
        return 0;
      }
      /******/

      for (numero = 0; numero < 10; numero++) {
        if (pos == 0 && numero == 0) {
          continue;
        }
        numeroGerado = subsitui1Digito (vDigit, dim, nAlg, pos, numero);
        booleano = primeTeste (numeroGerado);

        if (booleano == 1) {
          resposta[nPrimosGerados] = numeroGerado;
            nPrimosGerados++;
            if (nPrimosGeradosMax < nPrimosGerados) {
              nPrimosGeradosMax = nPrimosGerados;
            }
          }
        }
        /* averiguação da resposta */
        /* averiguação se os valores vão ser substituidos */
        minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
        if (nPrimosGerados == CHECK) {
          found = 1;
          if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
            minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
          }
          free (resposta);
          break;
        }
        free (resposta);
      }

      if (found == 1) {
        break;
      }

      /* 2 digito a subsituir*/
      for (pos1 = 0; pos1 < nAlg-1; pos1++) {
        for (pos2 = 0; pos2 < nAlg-1; pos2++) {

          if (pos1 == pos2) {
            continue;
          }
          /* reset dos contadores */
          nPrimosGerados = 0;
          resposta = (int*) calloc (10, sizeof (int));
          if (resposta == NULL) {
            printf ("\nFalha na alocação de memória do vector resposta.");
            return 0;
          }
          vDigit = preencheVectorDigit (nTeste, dim, nAlg);
          if (vDigit == NULL) {
            printf ("\nOcorreu uma falha na criação do vector digit.");
            return 0;
          }
          /************/

          for (numero = 0; numero < 10; numero++) {
            if (numero == 0 && (pos1 == 0 || pos2 == 0) ) {
              continue;
            }
            numeroGerado = subsitui2Digito (vDigit, dim, nAlg, pos1, pos2, numero);
            booleano = primeTeste (numeroGerado);

            if (booleano == 1) {
              resposta[nPrimosGerados] = numeroGerado;
                nPrimosGerados++;
                if (nPrimosGeradosMax < nPrimosGerados) {
                  nPrimosGeradosMax = nPrimosGerados;
                }
              }
            }

            /* averiguação da resposta */
            /* averiguação se os valores vão ser substituidos */
            minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
            if (nPrimosGerados == CHECK) {
              found = 1;
              if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
                minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
              }
              printf ("\n");
              for (i = 0; i < nPrimosGerados; i++) {
                printf (" %d", resposta[nPrimosGerados]);
              }
              break;
            }
            free (resposta);

          }
        }

        if (found == 1) {
          break;
        }
        /* agora falta substituir 3 digitos do algarismo de dimensão 100 000 */

        for (pos1 = 0; pos1 < nAlg-1; pos1++) {
          for (pos2 = 0; pos2 < nAlg-1; pos2++) {
            for (pos3 = 0; pos3 < nAlg-1; pos3++) {
              if (pos1 == pos2 || pos2 == pos3 || pos1 == pos3) {
                continue;
              }

              /* reset dos contadores */
              nPrimosGerados = 0;
              resposta = (int*) calloc (10, sizeof (int));
              if (resposta == NULL) {
                printf ("\nFalha na alocação de memória do vector resposta.");
                return 0;
              }
              vDigit = preencheVectorDigit (nTeste, dim, nAlg);
              if (vDigit == NULL) {
                printf ("\nOcorreu uma falha na criação do vector digit.");
                return 0;
              }

              for (numero = 0; numero < 10; numero++) {
                if (numero == 0 && (pos1 == 0 || pos2 == 0 || pos3 == 0)) {
                  continue;
                }
                numeroGerado = subsitui3Digito (vDigit, dim, nAlg, pos1, pos2, pos3, numero);
                booleano = primeTeste (numeroGerado);

                if (booleano == 1) {
                  resposta[nPrimosGerados] = numeroGerado;
                    nPrimosGerados++;
                    if (nPrimosGeradosMax < nPrimosGerados) {
                      nPrimosGeradosMax = nPrimosGerados;
                    }
                }
              }

              /* averiguação da resposta */
              /* averiguação se os valores vão ser substituidos */
              minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
              if (nPrimosGerados == CHECK) {
                found = 1;
                if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
                  minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
                }
                printf ("\n");
                for (i = 0; i < nPrimosGerados; i++) {
                  printf (" %d", resposta[i]);
                }
                break;
              }
              free (resposta);
            }
          }
        }

        if (found == 1) {
          break;
        }

        /* agora falta substituir 4 digitos do algarismo de dimensão 100 000 */
        for (pos1 = 0; pos1 < nAlg-1; pos1++) {
          for (pos2 = 0; pos2 < nAlg-1; pos2++) {
            for (pos3 = 0; pos3 < nAlg-1; pos3++) {
              for (pos4 = 0; pos4 < nAlg-1; pos4++) {
                if (pos1 == pos2 || pos2 == pos3 || pos1 == pos3) {
                  continue;
                }
                if (pos4 == pos1 || pos4 == pos2 || pos4 == pos3) {
                  continue;
                }

                /* reset dos contadores */
                nPrimosGerados = 0;
                resposta = (int*) calloc (10, sizeof (int));
                if (resposta == NULL) {
                  printf ("\nFalha na alocação de memória do vector resposta.");
                  return 0;
                }
                vDigit = preencheVectorDigit (nTeste, dim, nAlg);
                if (vDigit == NULL) {
                  printf ("\nOcorreu uma falha na criação do vector digit.");
                  return 0;
                }

                for (numero = 0; numero < 10; numero++) {
                  if (numero == 0 && (pos1 == 0 || pos2 == 0 || pos3 == 0 || pos4 == 0)) {
                    continue;
                  }
                  numeroGerado = subsitui4Digito (vDigit, dim, nAlg, pos1, pos2, pos3, pos4, numero);
                  booleano = primeTeste (numeroGerado);

                  if (booleano == 1) {
                    resposta[nPrimosGerados] = numeroGerado;
                      nPrimosGerados++;
                      if (nPrimosGeradosMax < nPrimosGerados) {
                        nPrimosGeradosMax = nPrimosGerados;
                      }
                  }
                }

                /* averiguação da resposta */
                /* averiguação se os valores vão ser substituidos */
                minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
                if (nPrimosGerados == CHECK) {
                  found = 1;
                  if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
                    minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
                  }
                  free (resposta);
                  break;
                }
                free (resposta);
              }
            }
          }
        }

      /* Agora falta subsitituir 5 digitos de um numero com dimensão 100 000 */

          /* reset dos contadores */
          nPrimosGerados = 0;
          resposta = (int*) calloc (10, sizeof (int));
          if (resposta == NULL) {
            printf ("\nFalha na alocação de memória do vector resposta.");
            return 0;
          }
          vDigit = preencheVectorDigit (nTeste, dim, nAlg);
          if (vDigit == NULL) {
            printf ("\nOcorreu uma falha na criação do vector digit.");
            return 0;
          }

          for (numero = 1; numero < 10; numero++) {
            if (numero == 0) {
              continue;
            }
            numeroGerado = subsitui5Digito (vDigit, dim, nAlg, 0, 1, 2, 3, 4, numero);
            booleano = primeTeste (numeroGerado);

            if (booleano == 1) {
              resposta[nPrimosGerados] = numeroGerado;
                nPrimosGerados++;
                if (nPrimosGeradosMax < nPrimosGerados) {
                  nPrimosGeradosMax = nPrimosGerados;
                }
            }
          }

          /* averiguação da resposta */
          /* averiguação se os valores vão ser substituidos */
          minimoPrimoGerado = encontraMinimoPrimo (resposta, nPrimosGerados);
          if (nPrimosGerados == CHECK) {
            found = 1;
            if (minimoPrimoGeradoAbsoluto > minimoPrimoGerado) {
              minimoPrimoGeradoAbsoluto = minimoPrimoGerado;
            }
            free (resposta);
            break;
          }
          free (resposta);

  } else {
    printf ("\nValor superior a 1M.");
    return 0;
  }

}

/* fim da tarefa */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTempo em segundos: %lf", tempo);
if (found == 1) {
  printf ("\nO minimo primo gerado foi o %d.\n", minimoPrimoGeradoAbsoluto);
  for (i = 0; i < nPrimosGerados; i++) {
    printf (" %d", resposta[nPrimosGerados]);
  }
} else {
  printf ("\nNão foi encontrado nenhuma familia com 8 primo com Max dimensão de %d.", MAX);
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

int *preencheVectorDigit (int contador, int dim, int nAlg) {
/* cria e preenche vector com os digitos do numero contador, sabendo dim e nAlg*/
/* devolve apontador do vector*/

int *vectorDigit;
int i;

vectorDigit = (int*) calloc (nAlg, sizeof (int));
if (vectorDigit == NULL) {
  printf ("\nErro a criar o vector.");
  return NULL;
}

for (i = 0; i < nAlg; i++) {
  vectorDigit[i] = contador / dim;
  contador = contador - vectorDigit[i]*dim;
  dim = dim / 10;
}

return vectorDigit;

}

/******************************************************************************/

int geraNumero (int *vDigit, int dim, int nAlg) {
/* devolve o numero com os digitos no vector, de de dimensão dim */

int numero = 0;
int i;

for (i = 0; i < nAlg; i++) {
  numero = numero + vDigit[i]*dim;
  dim = dim / 10;
}

return numero;
}

/******************************************************************************/

int subsitui1Digito (int *vDigit, int dim, int nAlg, int pos, int numero) {
/* subsitui um digito no vector digit e retorna o numero gerado */

int numeroGerado;

vDigit[pos] = numero;
numeroGerado = geraNumero (vDigit, dim, nAlg);

return numeroGerado;
}

/******************************************************************************/

int encontraMinimoPrimo (int *resposta, int nPrimosGerados) {
/* verifica qual o menor primo de entre um vector com n primos*/

int i;
int primoMinimo;

primoMinimo = resposta[0];

for (i = 0; i < nPrimosGerados; i++) {
  if (resposta[i] < primoMinimo) {
    primoMinimo = resposta[i];
  }
}

return primoMinimo;
}

/******************************************************************************/

int subsitui2Digito (int *vDigit, int dim, int nAlg, int pos1, int pos2, int numero) {

/* subsitui dois digitos no vector digit e retorna o numero gerado */

int numeroGerado;

vDigit[pos1] = numero;
vDigit[pos2] = numero;
numeroGerado = geraNumero (vDigit, dim, nAlg);

return numeroGerado;

}

/******************************************************************************/

int subsitui3Digito (int *vDigit, int dim, int nAlg, int pos1, int pos2, int pos3, int numero) {
/* subsitui três digitos no vector digit e retorna o numero gerado */

int numeroGerado;

vDigit[pos1] = numero;
vDigit[pos2] = numero;
vDigit[pos3] = numero;
numeroGerado = geraNumero (vDigit, dim, nAlg);

return numeroGerado;

}

/******************************************************************************/

int subsitui4Digito (int *vDigit, int dim, int nAlg, int pos1, int pos2, int pos3, int pos4, int numero) {
/* subsitui quatro digitos no vector digit e retorna o numero gerado */

int numeroGerado;

vDigit[pos1] = numero;
vDigit[pos2] = numero;
vDigit[pos3] = numero;
vDigit[pos4] = numero;
numeroGerado = geraNumero (vDigit, dim, nAlg);

return numeroGerado;
}

/******************************************************************************/

int subsitui5Digito (int *vDigit, int dim, int nAlg, int pos1, int pos2, int pos3, int pos4, int pos5, int numero) {
/* subsitui cinco digitos no vector digit e retorna o numero gerado */

int numeroGerado;

vDigit[pos1] = numero;
vDigit[pos2] = numero;
vDigit[pos3] = numero;
vDigit[pos4] = numero;
vDigit[pos5] = numero;
numeroGerado = geraNumero (vDigit, dim, nAlg);

return numeroGerado;

}

/******************************************************************************/
