#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include <arpa/inet.h>

void t_encrypt (uint32_t* v, uint32_t* k) {
  uint32_t v0=ntohl(v[0]), v1=ntohl(v[1]), sum=0, i;           /* set up */
  uint32_t delta=0x9e3779b9;                     /* a key schedule constant */
  uint32_t k0=ntohl(k[0]), k1=ntohl(k[1]), k2=ntohl(k[2]), k3=ntohl(k[3]);   /* cache key */
  for (i=0; i < 32; i++) {                       /* basic cycle start */
    sum += delta;
    v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
    v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
  }                                              /* end cycle */
  v[0]=htonl(v0); v[1]=htonl(v1);
}
 
void t_decrypt (uint32_t* v, uint32_t* k) {
  uint32_t v0=ntohl(v[0]), v1=ntohl(v[1]), sum=0xC6EF3720, i;  /* set up */
  uint32_t delta=0x9e3779b9;                     /* a key schedule constant */
  uint32_t k0=ntohl(k[0]), k1=ntohl(k[1]), k2=ntohl(k[2]), k3=ntohl(k[3]);   /* cache key */
  for (i=0; i<32; i++) {                         /* basic cycle start */
    v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
    sum -= delta;                                   
  }                                              /* end cycle */
  v[0]=htonl(v0); v[1]=htonl(v1);
}

