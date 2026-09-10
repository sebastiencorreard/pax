target=ball
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\author{Chouhaïd, Souissi; Mounir,Mensi}
\email{chsouissi@yahoo.fr} et mounirmensi@yahoo.fr
\computeanswer{yes}
\format{html}
\precision{1000}

\integer{k=random(1,2)}
\text{color1=k=1? 1:2}
\text{color2=k=2? 3:4}
\integer{c1=randint(4..8)}
\integer{c2=randint(4..8)}
\integer{t=\c1+\c2}
\integer{et=randint(2..4)}
\integer{ec1=randint(1..(\et-1))}
\integer{ec2=\et-\ec1}
\text{qcolor=random(\color1,\color2)}
\integer{c0=\qcolor issametext \color1?\c1:\c2}
\real{sol0=binomial(\c0,\et)/binomial(\t,\et)}
\real{sol1=binomial(\c1,\ec1)*binomial(\c2,\ec2)/binomial(\t,\et)}
\integer{m1=floor((1+\c1)/2)}
\integer{m2=floor((1+\c2)/2)}
\integer{m=\m1+\m2}
\text{quest3=randitem(\name_evenodd)}
\integer{m=\quest3 issametext \name_evenodd[1]?\t-\m:\m}
\integer{tm=\t-\m}
\real{sol2=binomial(\m,\ec1)*binomial(\tm,\ec2)/binomial(\t,\et)}

\if{\ec1>1}{
  \text{b1=\ec1}
  \text{printball=\name_balls[2]}
  \text{printcol1=\sort_nameadj=1?\name_balls[2] \name_colors[\color1]:\name_colors[\color1] \name_balls[2]}
  \text{printhave=\name_balls[2] \name_have[2]}
}{
  \text{b1=\name_one}
  \text{printball=\name_balls[1]}
  \text{printcol1=\sort_nameadj=1?\name_balls[1] \name_color[\color1]:\name_color[\color1] \name_balls[1]}
  \text{printhave=\name_balls[1] \name_have[1]}
}
\if{\ec2>1}{
  \text{b2=\ec2}
  \text{printcol2=\sort_nameadj=1?\name_balls[2] \name_colors[\color2]:\name_colors[\color2] \name_balls[2]}
}{
  \text{b2=\name_one}
  \text{printcol2=\sort_nameadj=1?\name_balls[1] \name_color[\color2]:\name_color[\color2] \name_balls[1]}
}

\steps{reply1
reply2
reply3}

\statement{\name_statement1 \c1
    \if{\sort_nameadj=1}{\name_balls[2] \name_colors[\color1]}{\name_colors[\color1] \name_balls[2]}
    \name_and \c2
    \if{\sort_nameadj=1}{\name_balls[2] \name_colors[\color2].}{\name_colors[\color2] \name_balls[2].}
    \name_statement2[1] \et \name_balls[2] \name_statement2[2]
    <div class="wims_question">
<ol class="spacer"><li>
\if{\step=1}{<label for="reply1">\name_step1[1] \name_colors[\qcolor] \name_step1[2] \name_is\name_space: </label>\embed{reply1,12}.}
\if{\step>1}{\name_step1[1] \name_colors[\qcolor] \name_step1[2] \name_is\name_space: <span class="oef_indgood">\sol0</span>.
<span class="wims_emph">\name_replygood</span>
</li><li> }
\if{\step=2}{<label for="reply2">\name_step2 \b1 \printcol1 \name_and \b2
 \printcol2 \name_is\name_space: </label>\embed{reply2,12}}
\if{\step>=3}{\name_step2 \b1 \printcol1 \name_and \b2
 \printcol2 \name_is\name_space: <span class="oef_indgood">\sol1</span>.
<span class="wims_emph">\name_replygood </span>
</li><li><div>
\name_the[2] \printcol1 \name_enum \c1 \name_and \name_the[4]
\name_colors[\color2] \name_enum \c2.
</div>
<label for="reply3">\name_step3[1] \et \name_step3[2] \b1 \printhave
    \if{\sort_nameadj=1}{\name_a \name_number \quest3}{\name_a \quest3 \name_number}
    \name_is\name_space: </label> \embed{reply3,12}}
</li></ol>
</div>
}

\answer{1. \name_yourreply}{\sol0}{type=numeric}
\answer{2. \name_yourreply}{\sol1}{type=numeric}
\answer{3. \name_yourreply}{\sol2}{type=numeric}

\solution{
1. \name_sol1[1] \name_colors[\qcolor] \name_sol1[2] \name_is
\(\frac{C_{\c0}^{\et}}{C_{\t}^{\et}}=\sol0\).

\if{\step>=2}{
<p>
2. \name_sol2 \b1 \printcol1 \name_and \b2 \printcol2
  \name_is \(\frac{C_{\c1}^{\ec1}C_{\c2}^{\ec2}}{C_{\t}^{\et}}=\sol1\).
</p>}
\if{\step>=3}{<p>
3. \name_sol3[1] \m \name_balls[2] \name_sol3[2] \quest3, \name_sol3[3]
\b1 \printball \name_sol3[2] \quest3 \name_is
\(\frac{C_{\m}^{\ec1}C_{\tm}^{\ec2}}{C_{\t}^{\et}}=\sol2\). }
</p>
}
