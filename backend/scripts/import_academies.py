"""
Script d'import des académies depuis un fichier CSV.
Usage:
    python scripts/import_academies.py resources/a_integrer_dans_db/academies_france.csv
"""

import sys
import os
import csv
import asyncio

# Ajoute le dossier parent au sys.path pour pouvoir importer les modules du backend
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select
from db import AsyncSessionLocal
from models.user import Academie

async def import_academies(csv_path: str):
    if not os.path.exists(csv_path):
        print(f"Erreur : Le fichier {csv_path} n'existe pas.")
        return

    async with AsyncSessionLocal() as db:
        async with db.begin():
            with open(csv_path, mode="r", encoding="utf-8") as f:
                reader = csv.reader(f)
                next(reader, None)  # Sauter l'en-tête
                count = 0
                for row in reader:
                    if not row or len(row) < 2:
                        continue
                    
                    name = row[0].strip()
                    code = row[1].strip()

                    # Vérifier si l'académie existe déjà
                    existing = await db.execute(select(Academie).where(Academie.code == code))
                    if existing.scalar_one_or_none():
                        print(f"Ignoré : L'académie {name} ({code}) existe déjà.")
                        continue

                    academie = Academie(name=name, code=code)
                    db.add(academie)
                    count += 1
            
            print(f"Succès : {count} académies importées.")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python scripts/import_academies.py <path_to_csv>")
        sys.exit(1)

    csv_file = sys.argv[1]
    asyncio.run(import_academies(csv_file))
