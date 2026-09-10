target=expression6
%% Reconnaître les coefficients
\language{fr}
\computeanswer{yes}
\precision{1000}
\format{html}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = (-1)^random(0,1)*random(1..3)}
\integer{b = (-1)^random(0,1)*random(1..5)}
\integer{c = (-1)^random(0,1)*random(1..3)}
\integer{d = (-1)^random(0,1)*random(1..5)}
\integer{k = (-1)^random(0,1)*random(1..2)}

\function{u=\a*x + \b}
\function{v=\d + \c*x}
\function{w=\c*x^2 + \a*x}
\text{liste=\(\k(\u)(\v)),\(\k(\w)),\((\u)^2 + (\v)^2), \((\u)^2 + \d), \(\k + (\u)(\v)) }
\integer{a1=\k*\a*\c}
\integer{c1=\k*\b*\d}

\integer{a2=\k*\c}
\integer{c2=0}

\integer{a3=(\a)^2+(\c)^2}
\integer{c3=(\b)^2+(\d)^2}
\integer{a4=(\a)^2}
\integer{c4=(\b)^2 + \d}
\integer{a5=\a*\c}
\integer{c5=\k + \b*\d}
\integer{cas=random(1..5)}
\text{exp=item(\cas,\liste)}
\text{repa=item(\cas,\a1,\a2,\a3,\a4,\a5)}
\text{repc=item(\cas,\c1,\c2,\c3,\c4,\c5)}
\statement{
<div class="monenonce">
<p>\name_statement</p>
<div class="wimscenter"> \( f(x)) = \exp.</div>
<p>\name_question[1;1] \(a*x^2 + b*x + c\) \name_question[1;2] \(f(x)\).</p>
<p>\name_question[2;]:</p>
<ul>
<li>\name_coeff[1] \(a\) \name_coeff[2] \(x^2\) : <label for="reply1">\(a\) =</label> \embed{reply1}</li>
<li>\name_coeff[3] \(c\): <label for="reply2">\(c\) =</label> \embed{reply2}</li>
</ul>
</div>}

\answer{}{\repa}
\answer{}{\repc}
