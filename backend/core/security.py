from datetime import datetime, timedelta
import bcrypt
from jose import jwt

from config import settings

# bcrypt n'a jamais lu au-delà de 72 octets ; jusqu'en 4.x il ignorait le
# surplus en silence, et passlib s'appuyait dessus. La 5.0 lève désormais une
# `ValueError` — ce qui mettait à terre toute l'authentification à la première
# tentative de hachage. On tronque donc explicitement, ce que faisait déjà la
# bibliothèque : le comportement est inchangé, il est simplement écrit.
# La coupe porte sur les *octets*, jamais sur les caractères — un caractère
# multi-octets peut être sectionné, sans conséquence dès lors que le hachage et
# la vérification appliquent la même règle.
_MAX_BCRYPT_BYTES = 72


def _to_bcrypt_bytes(password: str) -> bytes:
    return password.encode("utf-8")[:_MAX_BCRYPT_BYTES]


def hash_password(password: str) -> str:
    # `gensalt()` produit un `$2b$` à 12 tours, identique à ce que posait
    # passlib : les mots de passe déjà en base restent vérifiables.
    return bcrypt.hashpw(_to_bcrypt_bytes(password), bcrypt.gensalt()).decode("ascii")


def verify_password(plain: str, hashed: str) -> bool:
    # Un compte sans mot de passe (l'invité) porte une empreinte vide, et une
    # empreinte tronquée n'est pas impossible : dans les deux cas c'est un refus,
    # pas une erreur qui remonterait jusqu'à la requête.
    try:
        return bcrypt.checkpw(_to_bcrypt_bytes(plain), hashed.encode("ascii"))
    except (ValueError, TypeError):
        return False


def create_access_token(user_id: str, role: str) -> str:
    expire = datetime.utcnow() + timedelta(minutes=settings.access_token_expire_minutes)
    payload = {"sub": user_id, "role": role, "exp": expire}
    return jwt.encode(payload, settings.secret_key, algorithm=settings.algorithm)


def decode_token(token: str) -> dict:
    return jwt.decode(token, settings.secret_key, algorithms=[settings.algorithm])
