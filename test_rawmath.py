import sympy
from sympy.parsing.sympy_parser import parse_expr, standard_transformations, implicit_multiplication_application
s = "(8*x+-1)^2+-5*x"
s = s.replace("+-", "-").replace("-+", "-").replace("--", "+").replace("++", "+")
print(s)
