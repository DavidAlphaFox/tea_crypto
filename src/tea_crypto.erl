-module(tea_crypto).
-export([tea_encrypt/2,tea_decrypt/2]).
-export([tea_htonl/1,tea_ntohl/1]).
-on_load(init/0).
init() ->
    Dir = case code:priv_dir(tea_crypto) of
              {error, bad_name} ->
                  case code:which(tea_crypto) of
                      Filename when is_list(Filename) ->
                          filename:join(
                            [filename:dirname(Filename), "../priv"]);
                      _ ->
                          "../priv"
                  end;
              Priv -> Priv
          end,
    erlang:load_nif(filename:join(Dir, "tea_crypto_nif"), 0).

tea_encrypt(_Value,_Key)->    
    exit(nif_library_not_loaded).
tea_decrypt(_Value,_Key)->
    exit(nif_library_not_loaded).
tea_htonl(_Value)->    
    exit(nif_library_not_loaded).
tea_ntohl(_Value)->    
    exit(nif_library_not_loaded).
