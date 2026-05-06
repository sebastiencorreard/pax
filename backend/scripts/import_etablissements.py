"""
Script d'import des établissements depuis un fichier CSV.
Usage:
    python scripts/import_etablissements.py <academie_code> <path_to_csv>
Exemple:
    python scripts/import_etablissements.py ac-aix-marseille.fr /ressources/a_integrer_dans_db/etablissements_aix_marseille.csv
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
from models.user import Academie, Etablissement

async def import_etablissements(academie_code: str, csv_path: str):
    if not os.path.exists(csv_path):
        print(f"Erreur : Le fichier {csv_path} n'existe pas.")
        return

    async with AsyncSessionLocal() as db:
        # Trouver l'académie correspondante
        res = await db.execute(select(Academie).where(Academie.code == academie_code))
        academie = res.scalar_one_or_none()
        if not academie:
            print(f"Erreur : Académie avec le code '{academie_code}' introuvable.")
            return

        with open(csv_path, mode="r", encoding="utf-8") as f:
            reader = csv.DictReader(f)
            count = 0
            ignored = 0
            for row in reader:
                uai = row.get("UAI", "").strip()
                name = row.get("Nom", "").strip()
                commune = row.get("Commune", "").strip() or None
                code_postal = row.get("Code_Postal", "").strip() or None
                type_etab = row.get("Type", "").strip() or None

                if not uai or not name:
                    continue

                # Vérifier si l'établissement existe déjà
                existing = await db.execute(select(Etablissement).where(Etablissement.uai == uai))
                if existing.scalar_one_or_none():
                    ignored += 1
                    continue

                etablissement = Etablissement(
                    uai=uai,
                    name=name,
                    commune=commune,
                    code_postal=code_postal,
                    type_etab=type_etab,
                    academie_id=academie.id
                )
                db.add(etablissement)
                count += 1
        
        await db.commit()
        print(f"Succès : {count} établissements importés.")
        if ignored > 0:
            print(f"Note : {ignored} établissements déjà présents ont été ignorés.")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python scripts/import_etablissements.py <academie_code> <path_to_csv>")
        sys.exit(1)

    ac_code = sys.argv[1]
    csv_file = sys.argv[2]
    asyncio.run(import_etablissements(ac_code, csv_file))
