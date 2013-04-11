-module(tea_crypto_erl).
-compile(export_all).
-define(DELTA,16#9e3779b9).
-define(MAX,16#FFFFFFFF).
t_encrypt(V,K) when (erlang:size(V) == 8) and (erlang:size(K) == 16)->
    <<V0:32,V1:32>> = V,
    <<K0:32,K1:32,K2:32,K3:32>> = K,
    compute(0,V0,V1,K0,K1,K2,K3,0).
compute(32,V0,V1,_K0,_K1,_K2,_K3,_Sum)->
    <<V0:32,V1:32>>;
compute(I,V0,V1,K0,K1,K2,K3,Sum)->    
    Sum1 = Sum + ?DELTA,
    V1K0 = V1 bsl 4 + K0,
    V1Sum = V1 + Sum1,
    V1K1 = (V1 bsr 5) + K1,
    NewV0 = (V0 + ((V1K0 bxor V1Sum) bxor V1K1) ) band ?MAX,
    V0K2 = NewV0 bsl 4 + K2,
    V0Sum = NewV0 + Sum1,
    V0K3 = (NewV0 bsr 5) + K3 ,
    NewV1 = (V1 +((V0K2 bxor V0Sum) bxor V0K3)) band ?MAX,
    compute(I + 1,NewV0,NewV1,K0,K1,K2,K3,Sum1).
