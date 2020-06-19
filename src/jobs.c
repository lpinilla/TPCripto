#include <carrier.h>
#include <jobs.h>
#include <lsb.h>
#include <payload.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

jobs divide_jobs(lsb l, carrier c, payload p, int injections_per_job) {
  long jobs_needed = (long)ceil((float)p->size / injections_per_job);
  jobs ret = (jobs)malloc(sizeof(t_jobs) * jobs_needed);
  ret->size = jobs_needed;
  carrier temp_carrier = NULL;
  payload temp_payload = NULL;
  for (long i = 0; i < jobs_needed; i++) {
    // generando los carriers
    temp_carrier = (carrier)malloc(sizeof(t_carrier));
    temp_carrier->content =
        c->content + i * injections_per_job * BYTE_SIZE / l->n;
    temp_carrier->counter = 0;
    temp_carrier->c_size =
        (c->c_size % injections_per_job == 0) ? injections_per_job : c->c_size;
    ret[i].carrier = temp_carrier;
    // generando los payload
    temp_payload = (payload)malloc(sizeof(t_payload));
    temp_payload->content = p->content + i * injections_per_job;
    temp_payload->counter = 0;
    temp_payload->size =
        (p->size % injections_per_job == 0) ? injections_per_job : p->size;
    ret[i].payload = temp_payload;
  }
  return ret;
}

void destroy_jobs(jobs j) {
  for (long i = 0; i < j->size; i++) {
    free(j[i].carrier);
    free(j[i].payload);
  }
  free(j);
}
