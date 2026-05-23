import os
import re

def resolve_variable(varname, content):
    """
    Tente de résoudre récursivement la valeur d'une variable dans le contenu d'un fichier OEF.
    """
    # Patterns d'assignation WIMS : \text{var = ...}, \integer{var = ...}, etc.
    # On gère les espaces et le fait que la valeur peut être une autre variable \autrevar
    patterns = [
        r"\\(?:text|integer|def|define|complex|matrix)\s*\{\s*" + re.escape(varname) + r"\s*=\s*(.*?)\s*\}",
        r"\\(?:text|integer|def|define|complex|matrix)\s*\{\s*" + re.escape(varname) + r"\s*,\s*(.*?)\s*\}"
    ]
    
    for p in patterns:
        match = re.search(p, content, re.I | re.DOTALL)
        if match:
            val = match.group(1).strip()
            # Si la valeur est elle-même une variable (commence par \)
            if val.startswith("\\") and len(val) > 1 and val[1:].isidentifier():
                return resolve_variable(val[1:], content)
            return val
    return None

def scan_oef_recursive_types():
    oef_files = []
    roots = ["/ressources", "ressources"]
    found_root = next((r for r in roots if os.path.exists(r)), None)
    
    if not found_root:
        print("Erreur: dossier ressources non trouvé.")
        return

    for root, dirs, files in os.walk(found_root):
        for f in files:
            if f.endswith(".oef"):
                oef_files.append(os.path.join(root, f))
    
    # Regex pour trouver \answer{...}{...}{...type=\varname...}
    ans_re = re.compile(r"\\answer\s*\{[^}]*\}\s*\{[^}]*\}\s*\{[^}]*type=\\([a-zA-Z0-9_]+)[^}]*\}", re.DOTALL | re.I)
    
    results = {}

    for path in oef_files:
        try:
            with open(path, "r", encoding="iso-8859-1") as f:
                content = f.read()
        except:
            continue
            
        matches = ans_re.findall(content)
        for varname in matches:
            final_val = resolve_variable(varname, content)
            if final_val:
                # On nettoie un peu les valeurs complexes (balises, code)
                final_val = final_val.replace("\n", " ").strip()
                if final_val not in results:
                    results[final_val] = []
                if len(results[final_val]) < 3: # On garde quelques exemples par type
                    results[final_val].append(os.path.basename(path))

    # Tri par fréquence
    sorted_results = sorted(results.items(), key=lambda x: len(x[1]), reverse=True)
    
    for val, examples in sorted_results[:100]:
        print(f"Type résolu: {val}  (Ex: {', '.join(examples)})")

if __name__ == "__main__":
    scan_oef_recursive_types()
