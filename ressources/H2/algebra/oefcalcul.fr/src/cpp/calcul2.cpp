target=calcul2
#define NUM
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\text{a=randint(1..10)}
\text{b=randint(2..10)}
\text{c=randint(3..10)}

\matrix{data=\(\a + \b \times \c),\((\a + \b) \times \c)
\(\a \times \b+\c),\(\a \times (\b+\c))
 \(\a + \frac{\b}{\c}),\(\frac{\a+\b}{\c})
 \(\frac{\a}{\b+\c}),\(\frac{\a}{\b}+\c)}

\matrix{rep= \a + \b * \c, (\a + \b)* \c
\a*\b+\c,\a*(\b+\c)
\a + \b/\c, (\a+\b)/\c
\a/(\b+\c),\a/\b+\c}
\text{u=randint(1..4)}

\text{datau=\data[\u;]}

\text{v=shuffle(1,2)}
\rational{rep1=\rep[\u;\v[1]]}
\rational{rep2=\rep[\u;\v[2]]}
\text{rep=\rep1,\rep2}
\text{qu1=\datau[\v[1]]}
\text{qu2=\datau[\v[2]]}
\text{STEP=\u<=2? reply1,reply3:reply1,reply2,reply3,reply4}

\steps{\STEP}
\statement{
\if{\u<=2}{
  \name_statement
  <div class="wimscenter"><label for="reply1">\qu1= </label>\embed{reply1,8}</div>
  \name_and
  <div class="wimscenter"><label for="reply3">\qu2=</label> \embed{reply3,8}</div>
}{
  \name_statement
  <table class="wimscenter"><tr><td></td><td></td><td>\embed{reply1,8}</td></tr>
  <tr><td>\qu1 </td><td>=</td><td><hr></td></tr>
  <tr><td></td><td></td><td>\embed{reply2,8}</td>
  </tr></table>
  \name_and
  <table class="wimscenter"><tr><td></td><td></td><td>\embed{reply3,8}</td></tr>
  <tr><td>\qu2</td><td>=</td><td><hr></td></tr>
  <tr><td></td><td></td><td>\embed{reply4,8}</td>
  </tr></table>
}
}

\answer{\name_answer[1]}{\n1}{type=numeric}
\answer{\name_answer[2]}{\d1}{type=numeric}
\answer{\name_answer[1]}{\n2}{type=numeric}
\answer{\name_answer[2]}{\d2}{type=numeric}

\text{d1=\u<=2? 1}
\text{d2=\u<=2? 1}

\text{test=\n1=round(\n1) and \d1=round(\d1) and
\n2=round(\n2) and \d2=round(\d2) ? 1:0}

\condition{\name_answer[1] ?}{\n1=round(\n1) and \n1/\d1=\rep1}
\condition{\name_answer[2] ?}{\n2=round(\n2) and \n2/\d2=\rep2}

\feedback{\test=0}{\name_instruction }

\rational{u1=\n1/\d1}
\rational{u2=\n2/\d2}
\text{s1=\u1 isitemof \rep ?position(\u1,\rep) :100 }
\text{s2=\u2 isitemof \rep ?position(\u2,\rep):100}

\feedback{1=1}{\name_feedback[1] \qu1=\rep1 \name_and \qu2=\rep2}
\feedback{\test=1 and \n1/\d1 !=\rep1 and \s1<>100}
{\name_feedback[2] \for{i in \s1}{\datau[\v[\i]], }
\name_andno \qu1.}

\feedback{\test=1 and \n2/\d2 !=\rep2 and \s2<>100}
{\name_feedback[3] \for{i in \s2}{\datau[\v[\i]], }
\name_andno \qu2.
}
