import os
import re

def scan_oef_dynamic_types():
    oef_files = []
    # Try multiple common locations
    roots = ["/ressources", "ressources", "../ressources"]
    found_root = None
    for r in roots:
        if os.path.exists(r):
            found_root = r
            break
    
    if not found_root:
        return ["Error: ressources directory not found"]

    for root, dirs, files in os.walk(found_root):
        for f in files:
            if f.endswith(".oef"):
                oef_files.append(os.path.join(root, f))
    
    # More flexible regex for \answer
    # We look for 'type=\varname' anywhere in the options (3rd block)
    ans_re = re.compile(r"\\answer\s*\{[^}]*\}\s*\{[^}]*\}\s*\{([^}]*type=\\([a-zA-Z0-9_]+)[^}]*)\}", re.DOTALL | re.I)
    
    # Regex for assignments
    assign_re = re.compile(r"\\(?:text|integer|def|define|complex)\s*\{ *(%s) *= *(.*?)\}", re.I | re.DOTALL)

    dynamic_values = []
    
    for path in oef_files:
        try:
            with open(path, "r", encoding="iso-8859-1") as f:
                content = f.read()
        except:
            continue
            
        matches = ans_re.findall(content)
        if not matches:
            continue
            
        for full_opt, varname in matches:
            # Search for its assignment in the same file
            # We use a loop-safe version of assign_re
            pattern = r"\\(?:text|integer|def|define|complex)\s*\{ *" + re.escape(varname) + r" *= *(.*?)\}"
            val_match = re.search(pattern, content, re.I | re.DOTALL)
            if val_match:
                val = val_match.group(1).strip()
                dynamic_values.append(f"{path} -> \\{varname} = {val}")
                if len(dynamic_values) >= 100:
                    break
        if len(dynamic_values) >= 100:
            break
            
    return dynamic_values

if __name__ == "__main__":
    vals = scan_oef_dynamic_types()
    for v in vals:
        print(v)
