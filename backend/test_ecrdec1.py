import sys
import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from core.oef.def_engine import DefEngine
from core.oef.def_parser import parse

def main():
    path = "/ressources/H4/algebra/oefnombres.fr/def/ecrdec1.def"
    with open(path, encoding="iso-8859-1") as f:
        text = f.read()
    df = parse(text)
    engine = DefEngine(seed=42, def_path=path)
    engine._exec(df.var_instructions, None)
    
    print("val10:", repr(engine.ctx.get("val10")))
    print("val16:", repr(engine.ctx.get("val16")))
    print("val13:", repr(engine.ctx.get("val13")))
    print("val17:", repr(engine.ctx.get("val17")))
    
    render = engine.render(df)
    print("\n--- HTML ---")
    print(render.statement_html)

if __name__ == "__main__":
    main()
