import asyncio
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from core.oef.engine import load_and_render

def main():
    path = "/ressources/H4/algebra/oefnombres.fr/def/diffecrdec.def"
    render = load_and_render(path, seed=42)
    
    print("--- HTML ---")
    print(render.statement_html[:500])
    
    print("\n--- SEGMENTS ---")
    for seg in render.statement_segments:
        if seg["type"] != "html":
            print(seg)
        else:
            print("html:", repr(seg["content"]))

if __name__ == "__main__":
    main()
