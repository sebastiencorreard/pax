# Le vrai Maxima, arbitre de l'émulation (`def_engine/cas.py:_call_maxima`).
# Debian stable (trixie) : Maxima 5.47.0 sur GCL, la version de WIMS 4.32
# (relevée sur `wims432`). `maxima-share` porte les fonctions chargées à la
# demande (`trigsimp`…) : sans lui, `trigsimp(1/x)` échoue — c'est le cas du
# WIMS local, installé sans, mais pas d'un serveur WIMS complet.
FROM debian:stable-slim
RUN apt-get update && apt-get install -y --no-install-recommends maxima maxima-share python3 \
    && rm -rf /var/lib/apt/lists/*
