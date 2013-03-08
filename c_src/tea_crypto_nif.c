
#include<erl_nif.h>
#include<stdint.h>
#include<string.h>
extern void t_encrypt(uint32_t* v,uint32_t* k);
extern void t_decrypt(uint32_t* v,uint32_t* k);

static ERL_NIF_TERM tea_encrypt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]){
  ErlNifBinary value,key,bin;
  if(!enif_inspect_binary(env, argv[0], &value) || 8 != value.size){
     return enif_make_badarg(env);
  }

  if(!enif_inspect_binary(env, argv[1], &key) || 16 != key.size){
    enif_release_binary(&value);
    return enif_make_badarg(env);
  }

  if(!enif_alloc_binary(8,&bin)){
    enif_release_binary(&value);
    enif_release_binary(&key);
    return enif_make_badarg(env);
  }

  uint32_t* msg_buff = (uint32_t*)enif_alloc(sizeof(uint32_t)*2);
  uint32_t* key_buff = (uint32_t*)enif_alloc(sizeof(uint32_t)*4);

  memcpy(msg_buff,(value.data),8);
  memcpy(key_buff,(key.data),16);

  t_encrypt(msg_buff,key_buff);

  enif_release_binary(&value);
  enif_release_binary(&key);

  memcpy((bin.data),msg_buff,8);
  enif_free(msg_buff);
  enif_free(key_buff);
  return enif_make_binary(env, &bin);
}

static ERL_NIF_TERM tea_decrypt_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]){
  ErlNifBinary value,key,bin;
  if(!enif_inspect_binary(env, argv[0], &value) || 8 != value.size){
     return enif_make_badarg(env);
  }

  if(!enif_inspect_binary(env, argv[1], &key) || 16 != key.size){
    enif_release_binary(&value);
    return enif_make_badarg(env);
  }

  if(!enif_alloc_binary(8,&bin)){
    enif_release_binary(&value);
    enif_release_binary(&key);
    return enif_make_badarg(env);
  }

  uint32_t* msg_buff = (uint32_t*)enif_alloc(sizeof(uint32_t)*2);
  uint32_t* key_buff = (uint32_t*)enif_alloc(sizeof(uint32_t)*4);

  memcpy(msg_buff,(value.data),8);
  memcpy(key_buff,(key.data),16);

  t_decrypt(msg_buff,key_buff);

  enif_release_binary(&value);
  enif_release_binary(&key);

  memcpy((bin.data),msg_buff,8);
  enif_free(msg_buff);
  enif_free(key_buff);
  return enif_make_binary(env, &bin);
}


static ErlNifFunc nif_funcs[] = {
  {"tea_encrypt",2, tea_encrypt_nif},
  {"tea_decrypt",2, tea_decrypt_nif},
};
 
ERL_NIF_INIT(tea_crypto, nif_funcs, NULL, NULL, NULL, NULL)
