target=equ_dr1

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}

\integer{x1=random(-10..10)}
\integer{y1=random(-10..10)}
\integer{yd=random(-10..10)}
\integer{xd=random(-1,1)*randint(1..5)}
\function{equ=maxima(expand((x-\x1)*\yd-(y-\y1)*\xd = 0))}
\rational{a=\yd/\xd}
\rational{b=\y1-\x1*\yd/\xd}
\function{equr=maxima(y=(\a)*x+\b)}

\steps{reply1,reply2,reply3
reply4,reply5
}

#include "lang.inc"

\statement{\name_statement[1;] \(\math_droite\) \name_statement[2;]
    \(A\) \name_statement[3;] \((\x1 , \y1) \) \name_statement[4;] 
    \(\overrightarrow{u}\) \name_statement[5;] \((\xd,\yd)\).

\if{\step=1}{<p>
 \name_statement[6;] \(\math_droite\) :
</p>
<div class="wimscenter">
\embed{reply 1,6} x + \embed{reply 2,6} y + \embed{reply 3,6}=0
</div>}

\if{\step=2}{
<p>
  \name_statement[7;] \(\math_droite\) \name_is \(\equ), \name_statement[8;]:
</p>
<div class="wimscenter">
\(y = )\embed{reply 4,6} x + \embed{reply 5,6}
</div>}
}
\answer{\name_answer1 \(a\)}{\rep1}{type=rational}
\answer{\name_answer1 \(b\)}{\rep2}{type=rational}
\answer{\name_answer1 \(c\)}{\rep3}{type=rational}

\answer{\name_answer2 \(d\)}{\a}{type=default}
\answer{\name_answer3 \(d\)}{\b}{type=default}

\condition{\(\overrightarrow{u}\) \name_condition1}{(\rep1)*(\xd) + (\rep2)*(\yd) = 0}

\condition{\name_condition2[1] \(A\) \name_condition2[2]}{(\rep1)*(\x1) + (\rep2)*(\y1)+\rep3=0}


\solution{\name_solution[1] \(\math_droite\) \name_is \(\equ), \name_solution[2] \(\equr)}
