
import re

def test_regex():
    # Simulation de la regex corrigée
    regex = r"item\s+(.*?)\s+to\s*(.*)"
    
    # Cas qui semble échouer : slib_out est vide
    # !append item 1 to $slib_out  => subst => "item 1 to"
    args = "item 1 to"
    m = re.match(regex, args, re.DOTALL | re.I)
    if m:
        print(f"Match OK: item='{m.group(1)}', list='{m.group(2)}'")
    else:
        print("Match FAILED")

    # Autre cas possible
    args2 = "item 1 to "
    m2 = re.match(regex, args2, re.DOTALL | re.I)
    if m2:
        print(f"Match 2 OK: item='{m2.group(1)}', list='{m2.group(2)}'")
    else:
        print("Match 2 FAILED")

if __name__ == "__main__":
    test_regex()
