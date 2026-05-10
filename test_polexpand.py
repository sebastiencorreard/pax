from core.answer.checkers import is_polexpand

print("x^2 + 3*x + 2 ->", is_polexpand("x^2 + 3*x + 2"))
print("(x+1)*(x+2) ->", is_polexpand("(x+1)*(x+2)"))
