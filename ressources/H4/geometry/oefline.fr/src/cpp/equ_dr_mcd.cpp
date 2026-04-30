target=equ_dr_mcd

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}

\integer{ k = random(1..3) }
\integer{a=random(-10..10)}
\integer{b=random(-10..10)}

\integer{x1=random(-10..0)}
\integer{y1=simplify(\a*\x1+\b)}
\integer{x2=random(1..10)}
\integer{y2=simplify(\a*\x2+\b)}
\if{\k=1}{\integer{n=1}
\integer{ h = randint(1..2) }
	\if{\h=1}{
	\rational{x1=randint(-100..100)/10}
	\rational{x2=\x1}
	\rational{\y2=\y1+randint(1..3)}
	\text{rep1=1}
	\rational{rep2=\x1}
	\text{Y=x}
	\matrix{X=,}}
	\if{\h=2}{
	\rational{y1=randint(-100..100)/10}
	\rational{y2=\y1}
	\rational{\x2=\x1+randint(1..3)}
	\text{rep1=2}
	\rational{rep2=\y1}
	\text{Y=y}
	\matrix{X=,}}
\text{etape2=reply2}
\integer{poids=6}
	}
\if{\k<>1}{\integer{n=2}
\text{rep1=3}
\rational{rep2=\a}
\rational{rep3=\b}
\text{etape2=reply2,reply3}
\text{Y=y}
\matrix{X=x +,}
\integer{poids=3}
}

#include "lang.inc"

\text{type=item(\rep1,\name_options_list)}
\text{rlist=reply2,reply3}
\steps{reply1
\etape2}


\statement{<div class="wims_difficultylevel spacer">\name_difflevel</div>

<p>\name_statement[1;] \(A\, (\x1,\y1)\)
\name_and \(B\, (\x2,\y2)\).</p>
\if{\step =1}{
<div>\name_statement[2;] \((AB)\) \name_statement[3;] \embed{reply1,1}, \embed{reply1,2} \name_or \embed{reply1,3} ?</div>
<div class="wims_instruction">\name_instruction</div>}
\if{\step =2}{<p>\name_statement[4;] \((AB)\) \name_is \type. \name_statement[5;].</p>
    <div class="spacer">\Y=\for{t=1 to \n}{\embed{\rlist[\t]} \X[1;\t]}</div>}
}

\answer{}{\rep1;\name_options_list }{type= click}{weight=4}
\answer{}{\rep2 }{type= numeric }{weight=\poids}
\answer{}{\rep3 }{type= numeric }{weight=\poids}
