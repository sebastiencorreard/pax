from core.answer.checkers import is_polexpand

print("x^2 + 3*x + 2 ->", is_polexpand("x^2 + 3*x + 2"))
print("(x+1)*(x+2) ->", is_polexpand("(x+1)*(x+2)"))
print("x^2 + x*3 + 2 ->", is_polexpand("x^2 + x*3 + 2"))
print("4*x^2 - 1 ->", is_polexpand("4*x^2 - 1"))
print("(2*x-1)*(2*x+1) ->", is_polexpand("(2*x-1)*(2*x+1)"))
