from sympy.parsing.sympy_parser import parse_expr, standard_transformations, implicit_multiplication_application
expr = parse_expr("-x^2 - 2*x + 1".replace("^", "**"), transformations=standard_transformations+(implicit_multiplication_application,), evaluate=False)

def is_monomial(e):
    if e.is_Number or e.is_Symbol:
        return True
    if e.is_Pow:
        return e.base.is_Symbol and e.exp.is_Number
    if e.is_Mul:
        return all(is_monomial(arg) for arg in e.args)
    return False

def get_signature(m):
    if m.is_Number:
        return "1"
    if m.is_Symbol:
        return str(m)
    if m.is_Pow:
        return f"{m.base}^{m.exp}"
    if m.is_Mul:
        non_nums = [get_signature(arg) for arg in m.args if not arg.is_Number]
        return "*".join(sorted(non_nums)) if non_nums else "1"
    return str(m)

print("is_monomial for args:")
for arg in expr.args:
    print(arg, is_monomial(arg), get_signature(arg))
