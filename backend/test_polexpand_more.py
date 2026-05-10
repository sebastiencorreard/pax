from core.answer.checkers import is_polexpand

print("x + 1 ->", is_polexpand("x + 1"))
print("2*x + 3 ->", is_polexpand("2*x + 3"))
print("x^2 ->", is_polexpand("x^2"))
print("x^2 + 1 ->", is_polexpand("x^2 + 1"))
print("-x^2 - 2*x + 1 ->", is_polexpand("-x^2 - 2*x + 1"))
print("(x+1)^2 ->", is_polexpand("(x+1)^2"))
print("x*y + y^2 ->", is_polexpand("x*y + y^2"))
print("2 ->", is_polexpand("2"))
