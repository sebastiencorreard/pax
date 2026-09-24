FROM python:3.14-slim

WORKDIR /app
# Graphviz — `!exec graphviz` (`def_engine/graphviz.py`) : le seul programme
# externe du backend, que WIMS non plus n'embarque pas (son script
# `bin/graphviz` appelle le `dot` du serveur). `fonts-liberation` donne à `dot`
# les métriques de Times, sa police par défaut, pour dimensionner les nœuds.
RUN apt-get update \
 && apt-get install -y --no-install-recommends graphviz fonts-liberation \
 && rm -rf /var/lib/apt/lists/*
COPY requirements.txt .
# L'image `python:3.10-slim` fige un pip/setuptools de 2023, que `pip-audit`
# signale (PYSEC-2023-228, PYSEC-2026-2875…). Ils ne servent qu'à la
# construction, mais rien ne justifie de les garder vulnérables.
RUN pip install --no-cache-dir --upgrade pip setuptools wheel \
 && pip install --no-cache-dir -r requirements.txt
COPY . .

RUN chmod +x entrypoint.sh
ENTRYPOINT ["bash", "entrypoint.sh"]
