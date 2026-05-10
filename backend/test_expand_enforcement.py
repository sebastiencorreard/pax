from core.answer.checkers import check_answer

print("Testing expanded form enforcement:")

# Should be accepted (correct expanded form)
res1 = check_answer("algexp", "x^2 + 3*x + 2", "x^2 + 3*x + 2")
print("x^2 + 3*x + 2 ->", res1.correct)

# Should be accepted (unreduced expanded form)
res5 = check_answer("algexp", "x^2 + 2*x + 1*x + 2", "x^2 + 3*x + 2")
print("x^2 + 2*x + 1*x + 2 ->", res5.correct, res5.status)

# Should be rejected (factorized form when expanded is expected)
res2 = check_answer("algexp", "(x+1)*(x+2)", "x^2 + 3*x + 2")
print("(x+1)*(x+2) ->", res2.correct, res2.status, repr(res2.detail))

