#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SIZEDATA 40
typedef struct {
  int originVertice;
  int destinationVertice;
  int dimEdge;
  int booleanoProcessed; /* 0 if not processed or 1 if processed */
} edge;

/* this function stores the data readed from the text file to
the int matrix, and then returns the 1 if it went all ok, or
0 if there was a problem in the function, it returns also by referente
the number of the edge that not exist */
int getDataFromFile (char *nameFile, int **data, int *nNotExist);

/* this function creates dymanicaly the edge array withe the size dimEdgeArray
 and then it fill the  structure with the required data type, and then it
 returns the pointer if it went all ok or NULL if there was a problem in the
 function, it returns also by reference the real size of the edge array and
 the totalEdge sum */
edge* creatEdgeArrayAndFilling (int **data, int sizeData, int dimEdgeArray, int *newSize, int *totalEdge);

/* this function makes the sorting of the array in a ascending order and then
it returns 1 if it went all ok or 0 if there was a problem in the function */
int sortingAscendingOrder (edge *v, int dimEdgeArray);

/* this function makes the calculation of the new edge to insert in the graph,
and then returns if all went ok the size of the new edge, or -1 if there was a
problem in the function */
int connectEdge (int *graph, edge *v, int dimEdgeArray, int sizeData);

int main () {
clock_t inicio, fim;
double tempo;
inicio = clock();
/* work to verify */
char nameFile[12] = "network.txt";
int **data, sizeData = SIZEDATA, i, booleano, nNotExist, dimEdgeArray, newSize;
int totalEdge, answer, *graph, newTotalEdge = 0;
edge *v;

/* creation of the matrix for the raw data storing */
data = (int**) calloc (sizeData, sizeof (int*));
if (data == NULL) {
  printf("\nThere was an erro in the memory allocation of data.");
  return 0;
}
for (i = 0; i < sizeData; i++) {
  data[i] = (int*) calloc (sizeData, sizeof (int));
  if (data[i] == NULL) {
    printf("\nThere was an erro in the memory allocation of data.");
    return 0;
  }
}
/* read file and filling the int matrix */
booleano = getDataFromFile (nameFile, data, &nNotExist);
if (booleano == 0) {
  printf("\nThere was a problem in the function getDataFromFile.");
  return 0;
}
dimEdgeArray = pow(sizeData,2) - nNotExist;
/* filling the edge array */
v = creatEdgeArrayAndFilling (data, sizeData, dimEdgeArray, &newSize, &totalEdge);
if (v == NULL) {
  printf("\nThere was an error in the function creatEdgeArrayAndFilling.");
  return 0;
}
dimEdgeArray = newSize;
/* sorting array in descending order of dimEdge */
booleano = sortingAscendingOrder (v, dimEdgeArray);
if (booleano == 0) {
  printf("\nThere was a problem in the function sortingDescendingOrder.");
  return 0;
}
graph = (int*) calloc (sizeData, sizeof (int));
if (graph == NULL) {
  printf("\nThere was an error in the memory allocation of graph.");
  return 0;
}
/* first two vertex connected */
graph[v[0].originVertice] = 1;
graph[v[0].destinationVertice] = 1;
v[0].booleanoProcessed = 1;
newTotalEdge+=v[0].dimEdge;
/* cycle begin */
for (i = 2; i < sizeData; i++) {
  booleano = connectEdge (graph, v, dimEdgeArray, sizeData);
  if (booleano == -1) {
    printf("\nThere was an error in the function connectEdge.");
    return 0;
  }
  newTotalEdge+=booleano;
}
answer=totalEdge-newTotalEdge;
/* free of memory */
for (i = 2; i < sizeData; i++) {
  free (data[i]);
}
free (data);
free (v);
free (graph);
/* end of the work */
fim = clock();
tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
printf("\nTime in seconds: %lf", tempo);
printf("\nThere will be a save of %d.", answer);
printf("\n");
return 0;
}
/******************************************************************************/
int getDataFromFile (char *nameFile, int **data, int *nNotExist) {
/* this function stores the data readed from the text file to
the int matrix, and then returns the 1 if it went all ok, or
0 if there was a problem in the function, it returns also by referente
the number of the edge that not exist */
if (nameFile == NULL || data == NULL || nNotExist == NULL) {
  return 0;
}
int line = 0, colun = 0, nCount = 0;
char lineC[400], *c;
FILE *f;

f = fopen (nameFile, "r");
if (f == NULL) {
  return 0;
}
while ((fgets(lineC, sizeof (lineC), f)) != NULL) {
  colun = 0;
  c = strtok(lineC, ",");
  if ((strcmp (c, "-") != 0) && (strcmp(c, "-\n") != 0))  {
    data[line][colun] = atoi(c);
  } else {
    data[line][colun] = -1;
    nCount++;
  }
  colun++;
  while ((c = strtok(NULL,","))!= NULL) {
    if ((strcmp (c, "-") != 0) && (strcmp(c, "-\n") != 0)) {
      data[line][colun] = atoi(c);
    } else {
      data[line][colun] = -1;
      nCount++;
    }
    colun++;
  }
  line++;
}
fclose(f);
*nNotExist = nCount;
return 1;
}
/******************************************************************************/
edge* creatEdgeArrayAndFilling (int **data, int sizeData, int dimEdgeArray, int *newSize, int *totalEdge) {
/* this function creates dymanicaly the edge array withe the size dimEdgeArray
and then it fill the  structure with the required data type, and then it
returns the pointer if it went all ok or NULL if there was a problem in the
function, it returns also by reference the real size of the edge array and
the totalEdge sum  */
if (data == NULL || sizeData < 1 || dimEdgeArray < 1 || newSize == NULL) {
  return NULL;
}
edge *v;
int line, colun, indexV = 0, i, totalEdgeSum = 0;
/* creation of the edge array */
v = (edge*) calloc (dimEdgeArray, sizeof (edge));
if (v == NULL) {
  printf("\nThere was a problem in the creation of the v array.");
}
for (line = 0; line < sizeData; line++) {
  for (colun = line+1; colun < sizeData; colun++) {
    if (data[line][colun] == -1) {
      continue;
    }
    v[indexV].originVertice = line;
    v[indexV].destinationVertice = colun;
    v[indexV].dimEdge = data[line][colun];
    totalEdgeSum+=v[indexV].dimEdge;
    indexV++;
  }
}
v = realloc (v, indexV*sizeof(edge));
if (v == NULL) {
  return NULL;
}
*newSize = indexV;
*totalEdge = totalEdgeSum;
return v;
}
/******************************************************************************/
int sortingAscendingOrder (edge *v, int dimEdgeArray) {
/* this function makes the sorting of the array in a ascending order and then
it returns 1 if it went all ok or 0 if there was a problem in the function */
if (v == NULL || dimEdgeArray < 1) {
  return 0;
}
int i, j;
edge aux;
for (i = 0; i < dimEdgeArray-1; i++) {
  for (j = i+1; j < dimEdgeArray; j++) {
    if (v[i].dimEdge > v[j].dimEdge) {
      /* aux = i */
      aux.originVertice = v[i].originVertice;
      aux.destinationVertice = v[i].destinationVertice;
      aux.dimEdge = v[i].dimEdge;
      /* i = j */
      v[i].originVertice = v[j].originVertice;
      v[i].destinationVertice = v[j].destinationVertice;
      v[i].dimEdge = v[j].dimEdge;
      /* j = aux */
      v[j].originVertice = aux.originVertice;
      v[j].destinationVertice = aux.destinationVertice;
      v[j].dimEdge = aux.dimEdge;
    }
  }
}
return 1;
}
/******************************************************************************/
int connectEdge (int *graph, edge *v, int dimEdgeArray, int sizeData) {
/* this function makes the calculation of the new edge to insert in the graph,
and then returns if all went ok the size of the new edge, or -1 if there was a
problem in the function */
if (graph == NULL || v == NULL || dimEdgeArray < 0 || sizeData < 0) {
  return -1;
}
int i, originVertex, destinationVertex;
for (i = 0; i < dimEdgeArray; i++) {
  if (v[i].booleanoProcessed == 0) {
    /* edge not yet inserted */
      originVertex = v[i].originVertice;
      destinationVertex = v[i].destinationVertice;
      if ((graph[originVertex] == 1 && graph[destinationVertex] == 0) ||
      (graph[originVertex] == 0 && graph[destinationVertex] == 1)) {
        /* new edge to be inserted in the graph */
        graph[originVertex] = 1;
        graph[destinationVertex] = 1;
        v[i].booleanoProcessed = 1;
        return v[i].dimEdge;
      }
  }
}
/* if it reaches here then it has a problem the function */
return -1;
}
/******************************************************************************/
