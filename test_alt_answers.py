import sys
import os
sys.path.append(os.path.join(os.getcwd(), "backend"))
from core.oef.engine import load_and_render
from core.oef.def_engine import check_analyze

oef_path = "ressources/H4/algebra/oefcalcullit.fr/src/factdir1.oef"
seed = 12345
rendered = load_and_render(oef_path, seed=seed)

val63 = rendered.ev_ctx.get("val63")
val52 = rendered.ev_ctx.get("val52")
val58 = rendered.ev_ctx.get("val58")

print(f"Target polynomial: {val63}")
print(f"Example factors: {val52}, {val58}")

# Alternative valid answer (swapped)
alt1 = {64: val58, 65: val52}
# Alternative valid answer (factored out)
# 8x - 8 -> 8(x-1)
alt2 = {64: "8*(x-1)", 65: val58}

def run_test(name, replies):
    print(f"\nTesting {name} with {replies}...")
    from core.oef.def_engine import DefEngine
    from core.answer.checkers import _normalize_expr
    engine = DefEngine(seed=seed)
    engine.ctx.update(rendered.check_sections["ctx"])
    for var_n, value in replies.items():
        norm_val = _normalize_expr(value)
        print(f"  Normalized val{var_n}: {norm_val}")
        engine.ctx[f"val{var_n}"] = f"({norm_val})"
    
    engine._exec(rendered.check_sections["postdef"], output_buf=None)
    val66 = engine.ctx.get("val66")
    print(f"Calculated student result (val66): {val66}")
    
    engine._exec(rendered.check_sections["test"], output_buf=None)
    results = {k: int(v) for k, v in engine.ctx.items() if k.startswith("condtest") and str(v).strip() in ("0", "1")}
    score = sum(results.values()) / len(results) if results else 0
    print(f"Score: {score}")

run_test("Swapped", alt1)
run_test("Factored out", alt2)
