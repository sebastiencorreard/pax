# Le vrai Maxima, arbitre de l'émulation (`def_engine/cas.py:_call_maxima`).
# Debian stable (trixie) : Maxima 5.47.0 sur GCL, la version de WIMS 4.32
# (relevée sur `wims432`).
FROM debian:stable-slim
RUN apt-get update && apt-get install -y --no-install-recommends maxima python3 \
    && rm -rf /var/lib/apt/lists/*
