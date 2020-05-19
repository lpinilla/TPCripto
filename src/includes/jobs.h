#ifndef _JOBS_H_
#define _JOBS_H_

#include<payload.h>
#include<carrier.h>
#include <lsb.h>

typedef struct t_jobs{
    long size; //tamaño de los arrays
    carrier * carriers;
    payload * payloads; //array de payloads con defasajes en el content de los payload
} t_jobs;

typedef t_jobs * jobs;

//función para dividir en cantidad de workers dependiendo el tamaño del archivo portador y del archivo a inyectar.
jobs divide_jobs(lsb l, carrier c, payload p);

void destroy_jobs(jobs j);

#endif
