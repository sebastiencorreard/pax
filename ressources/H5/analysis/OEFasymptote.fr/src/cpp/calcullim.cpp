target=calcullim

\language{fr}
\range{-5..5}
d'après un ex de F. Pitoun
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\computeanswer{no}
\format{html}
\precision{10000}

\text{inf=inf}
\text{minf=-inf}

\integer{a=random(-1,1)*randint(1..5)}
\integer{b=randint(-10..10)}

\integer{c=random(-1,1)*randint(1..5)}
\integer{d=randint(-10..10)}
\integer{e=random(-10..10)}

\rational{v1=-\b/\a}
\rational{v2=-\d/\c}

\integer{feinte=random(1,2)}

\if{\v1=\v2 and \feinte=1}{
  \integer{d=\d+1}
  \rational{v2=-\d/\c}
}
\function{den=maxima(expand((\a*x+\b)*(\c*x+\d)))}
\integer{coefden=\a*\c}
\integer{u=randint(-2..2)}
\integer{v=randint(-5..5)}
\integer{w=randint(-5..5)}


\function{num=maxima(\u*x^2+\v*x+\w)}
\integer{coefnum=\u}
\if{\u=0 and \v=0 and \w=0}{
  \function{num=x^3}
  \integer{coefnum=1}
}
\if{\feinte=1}{
  \function{num=maxima(expand((\a*x+\b)*(x+\e)))}
  \integer{coefnum=\a}
}
\text{points=
\(+ \infty),
\(- \infty),
\v1 \name_points[1],
\v1 \name_points[2],
\v2 \name_points[1],
\v2 \name_points[2]
}

\text{points_tex=
+ \infty,
- \infty,
{\v1}^-,
{\v1}^+,
{\v2}^-,
{\v2}^+
}

\text{points_max=
INF,
MINF,
\v1,
\v1,
\v2,
\v2
}
\integer{al=random(1..6)}
%%integer{al=2}
%%integer{feinte=2}
\if{\feinte=1}{\integer{al=random(3..4)}}
\text{point=item(\al,\points)}
\text{point_tex=item(\al,\points_tex)}
\text{point_max=item(\al,\points_max)}
\if{\al<=2}{\text{lim=maxima(limit((\num)/(\den),x,\point_max))}}
\if{\al=3 or \al=5}{
  \text{lim=maxima(limit((\num)/(\den),x,\point_max,MINUS))}
  \rational{v=\al=3?\v1-0.01:\v2-0.01}
}
\if{\al=4 or \al=6}{
  \text{lim=maxima(limit((\num)/(\den),x,\point_max,PLUS))}
  \rational{v=\al=4?\v1+0.01:\v2+0.01}
}
\rational{numv=evalue(\num,x=\v)}
\rational{denv=evalue(\den,x=\v)}
\text{tsignenum=\numv>0?\name_posneg[1]:\name_posneg[2]}
\text{tsigneden=\denv>0?\name_posneg[1]:\name_posneg[2]}

\if{\al<=2}{\text{asymp=1}}
\if{(\feinte=2 and \al>=3) or (\feinte=1 and \al>=5)}{
  \text{asymp=2}
}
\if{\feinte=1 and (\al=3 or \al=4)}{
\text{asymp=3}
}
\if{inf isin \lim}{
  \text{lim_tex= +\infty}
  \text{lim2=+inf}
}
\if{minf isin \lim}{
  \text{lim_tex= -\infty}
  \text{lim2=-inf}
}
\if{inf notin \lim}{
  \text{lim_tex= \lim}
  \text{lim2=\lim}
}
\text{signeden=\coefden>0?+:-}
\if{\num=x^3}{
\text{textsol=\name_textsol \name_textsola}
\text{textsol=wims(replace internal YYYY by \name_supinf[1] in \textsol)}
\text{textsol=wims(replace internal ZZZZ by \name_infzero[1] in \textsol)}
\text{textsol=wims(replace internal UUUU by \( \signeden \infty\) in \textsol) \(\lim_tex\).}
\text{textsol1=wims(replace internal XXXX by \(+\infty\) in \textsol)}
\text{textsol2=wims(replace internal XXXX by \(-\infty\) in \textsol)}
}{
 \if{\u=0}{
    \text{textsol=\name_textsol}
    \text{textsol=wims(replace internal YYYY by \name_supinf[2] in \textsol)}
    \text{textsol=wims(replace internal ZZZZ by \name_infzero[2] in \textsol)}
    \text{textsol1=wims(replace internal XXXX by \(+\infty\) in \textsol)}
    \text{textsol2=wims(replace internal XXXX by \(-\infty\) in \textsol)}
  }{
  \text{textsol1=wims(replace internal XXXX by \(+\infty\) in \name_textsolb)
    \(\frac{\coefnum}{\coefden}).}
  \text{textsol2=wims(replace internal XXXX by \(-\infty\) in \name_textsolb)
    \(\frac{\coefnum}{\coefden}).}
  }
}
\if{\feinte=2}{
  \text{textsol3=\name_textsolc \(\lim_tex\).}
  \text{textsol3=wims(replace internal XXXX by \(x=\v1\) in \textsol3)}
  \text{textsol3=wims(replace internal YYYY by \tsignenum in \textsol3)}
  \text{textsol3=wims(replace internal ZZZZ by \tsigneden in \textsol3)}
  \text{textsol3=wims(replace internal UUUU by \(x=\point_tex\) in \textsol3)}
}{
\text{textsol3=wims(replace internal XXXX by \(x=\v1) in \name_textsolc) \(\lim_tex).}
}
\text{textsol5=\name_textsold \(\lim_tex\).}
\text{textsol5=wims(replace internal XXXX by \(x=\v2\) in \textsol5)}
\text{textsol5=wims(replace internal YYYY by \tsignenum in \textsol5)}
\text{textsol5=wims(replace internal ZZZZ by \tsigneden in \textsol5)}
\text{textsol5=wims(replace internal UUUU by \(x=\point_tex\) in \textsol5)}

\steps{reply 1
reply 2
}
#include "confparm.inc"
\statement{
<div \fsize>
  \name_question[1]
<div class="wimscenter">\( f(x) = (\num)/(\den) \)</div>
  \name_question[2] \point.
<div class="wims_question">
\if{\step=1}{
<label for="reply1">
\(\displaystyle{\lim_{x \to \point_tex}f(x) = })</label>
\embed{reply 1,10}
}
\if{\step=2}{
  \name_question2[1] \(\displaystyle{\lim_{x \to \point_tex}f(x) = \lim_tex}).<br>
  \name_question2[2], \name_question2[3] \embed{reply 2}
}
\if{\step=1}{
  <div class="wims_instruction">
  \name_inst[1] <span class="tt">+inf </span> \name_inst[2] \(+\infty),
  <span class="tt">-inf </span> \name_inst[2] \(-\infty).
  </div>}
</div>
</div>
}

\answer{\name_answer}{\lim2,\inf}{type=function}
\answer{}{\asymp;\as1,\as2,\as3}{type=menu}
\feedback{1=1}{<div \fsize>
\if{\al=1}{\textsol1}
\if{\al=2}{\textsol2}
\if{\al=3 or \al=4}{\textsol3}
\if{\al=5 or \al=6}{\textsol5}
</div>
}
