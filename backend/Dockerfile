FROM python:3.10-slim

WORKDIR /app
COPY requirements.txt .
# L'image `python:3.10-slim` fige un pip/setuptools de 2023, que `pip-audit`
# signale (PYSEC-2023-228, PYSEC-2026-2875…). Ils ne servent qu'à la
# construction, mais rien ne justifie de les garder vulnérables.
RUN pip install --no-cache-dir --upgrade pip setuptools wheel \
 && pip install --no-cache-dir -r requirements.txt
COPY . .

RUN chmod +x entrypoint.sh
ENTRYPOINT ["bash", "entrypoint.sh"]
