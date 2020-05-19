#include <jobs.h>
#include <carrier.h>
#include <payload.h>
#include <lsb.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

jobs divide_jobs(lsb l, carrier c, payload p){
    int pixels_needed = p->size * (BYTE_SIZE / l->n);
    long jobs_needed = (long) ceil((float) pixels_needed /c->pixel_width);
    jobs ret = (jobs) malloc(sizeof(t_jobs));
    ret->size = jobs_needed;
    ret->carriers = (carrier *) malloc(sizeof(t_carrier) * pixels_needed);
    ret->payloads = (payload *) malloc(sizeof(t_carrier) * pixels_needed);
    carrier temp_carrier = NULL;
    payload  temp_payload = NULL;
    for(long i = 0; i < jobs_needed; i++){
        //generando los carriers
        temp_carrier = (carrier) malloc(sizeof(t_carrier));
        temp_carrier->content = c->content + i * c->pixel_width;
        temp_carrier->counter = 0;
        ret->carriers[i] = temp_carrier;
        //generando los payload
        temp_payload = (payload) malloc(sizeof(t_payload));
        temp_payload->content = p->content + i * c->pixel_width;
        temp_payload->counter = 0;
        ret->payloads[i] = temp_payload;
    }
    return ret;
}

void destroy_jobs(jobs j){
    for(int i = 0; i < j->size; i++){
        free(j->carriers[i]);
        free(j->payloads[i]);
    }
    free(j->carriers);
    free(j->payloads);
    free(j);
}
