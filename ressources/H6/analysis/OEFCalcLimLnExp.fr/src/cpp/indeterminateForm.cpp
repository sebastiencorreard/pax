target=indeterminateForm indformwithln indformwithexp
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = random(-1,1)*random(1..5)}
\integer{b = random(-8..8)}
\integer{c= random(-1,1)*random(1..5)}
\integer{d = random(-8..8)}
\text{sk=random(-,+)}
\integer{op=random(1..4)}
#if defined TARGET_indformwithexp
\integer{op=4}test
#endif

\function{u=maxima(expand(\a*x + \b))}
\function{v=maxima(expand(\c*x + \d))}
\text{u=texmath(\u)}
\text{v=texmath(\v)}
** cas = 1 avec fonction exp ; cas = 2 avec fonction ln**

#if defined TARGET_indeterminateForm
\integer{cas=randitem(1,2)}
#endif
#if defined TARGET_indformwithln
\integer{cas=2}
#endif
#if defined TARGET_indformwithexp
\integer{cas=1}
#endif

\text{g=\cas=1?e^{t}:\ln(t)}
\text{gg=\cas=1?e^{u}:\ln(u)}
\text{ggx=\cas=1?e^{u(x)}:\ln(u(x))}
\function{gdeu=\cas=1?e^{\u}:\ln(\u)}
\text{f=item(\op,\v \sk \gdeu,(\v)\times \gdeu, \frac{\v}{\gdeu},\frac{\gdeu}{\v})}
\text{ff=item(\op,v \sk \gg, v \times \gg, \frac{v}{\gg},\frac{\gg}{v})}
\text{tf=texmath(\f)}

\rational{x0=-\b/\a}

\text{inf=&#8734;}
\text{sx=\cas=1?random(-,+)}
\text{sx=\cas=2 and \a>0?+}
\text{sx=\cas=2 and \a<0?-}
\integer{ssx=(\sx issametext +)?1:-1}
\text{xlim=\sx\inf}
\text{texlim=\sx\infty}
\\\ 16/09 : correction affichage certains intervalles, suite au passage wims + mathml
\text{ensdef=\cas=2 and \a>0?\(\rbrack \x0 ; \xlim \lbrack\)}
\text{ensdef=\cas=2 and \a<0? \(\rbrack \xlim ; \x0 \lbrack\)}
\text{ensdef=\cas=1?\(\mathbb{R}\)}

\text{vlim=(\c*\ssx)>0?+inf,+\infty,1:-inf,-\infty,-1}
\text{rep1=item(1,\vlim)}
\text{sol1=item(2,\vlim)}

\text{ulim=(\a*\ssx)>0?+inf,+\infty:-inf,-\infty}
\text{rep2=item(1,\ulim)}
\text{sol2=item(2,\ulim)}

\text{glim=\cas=1 and \rep2 issametext -inf?0,0,0:+inf,+\infty,1}
\text{rep3=item(1,\glim)}
\text{sol3=item(2,\glim)}

\text{rep4=\rep3}
\text{sol4=\sol3}

\text{fi=, 0 x \infty, 0 / 0, \infty / \infty , -\infty + (+\infty)}

\integer{tmp=item(3,\vlim)}
\integer{tmp2=item(3,\glim)}
\integer{tmp2=\tmp*\tmp2}
\text{rep5=1}
\text{rep5=\op=1 and \sk issametext + and \tmp2<0?5}
\text{rep5=\op=1 and \sk issametext - and \tmp2>0?5}
\text{rep5=\op=2 and \tmp2=0?2}
\text{rep5=\op>2 and \tmp2!=0?4}
\text{lafi=item(\rep5,\fi)}

!!!! 10/10/08 bug cas : e^u/v en cas de FI +inf/-inf le résultat est -inf
!!!! (et non pas rep4, car signe négatif pour v modifie signe rep4)

\if{\op=4}{\text{rep6=\tmp=1?+inf:-inf}}

\matrix{filims=\rep4,\rep1
\rep4,\rep1
0,\rep1
\rep6,0}

\if{\rep5=1}{\text{sol6=\op!=4?\rep1:0}}{\text{tmp=row(\op,\filims)}
  \text{sol6=item(\cas,\tmp)}
}
\text{prelim=wims(replace internal NNNN by 6 in \name_prelim)}

\steps{reply1
reply2
reply3
reply4
reply5
reply6}
\statement{<div class="wims_instruction">\prelim</div>
<div class="wims_question">
<p>
\name_enonce \ensdef \name_by
\(f(x) = \f\). \name_enonce2[1] \(f = \ff ) \name_with, \name_enonce2[2] \ensdef,
\(u(x) = \u\) \name_and \(v(x) = \v).
\name_aim \(f\) \name_at \(\texlim\).
</p></div>
\if{\step=1}
{1. \name_question3 \(v) \name_at \(\texlim\) :
  <div class="wimscenter">
  <label for="reply1">\(\displaystyle \lim_{x\to\texlim} \v ) =</label> \embed{reply1,5}</div>
}
\if{\step>1}{
1.
\if{\step=2}
    {\if{\sc_reply1=1}
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad">\name_youranswer[2;1..2].</span>}
}
<span class="oef_indgood">\name_question2[1] \(v\) \name_at \(\texlim\) \name_question2[2]</span>:
<p class="wimscenter">
\(\displaystyle \lim_{x\to\texlim} v(x) = \lim_{x\to\texlim} \v = \sol1)</p>
}
\if{\step=2}
{2. \name_question3 \(u) \name_at \(\texlim\) :
<div class="wimscenter">
<label for="reply1">
\(\displaystyle \lim_{x\to\texlim} \u \) =</label> \embed{reply2,5}</div>
}
\if{\step>2}
{2.
  \if{\step=3}
    {\if{\sc_reply2=1}
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad">\name_youranswer[3;1] (\reply2) \name_youranswer[3;2].</span>}
}
<span class="oef_indgood">\name_question2[1] \(u\) \name_at \(\texlim\) \name_question2[2]</span>:
<p class="wimscenter">\(\displaystyle \lim_{x\to\texlim} u(x) = \lim_{x\to\texlim} \u = \sol2\)</p>
}
\if{\step=3}
{3. \name_question3 \(\g\) \name_at \(\sol2\) :
  <div class="wimscenter">
  <label for="reply3">\(\displaystyle \lim_{t\to\sol2} \g \) =</label> \embed{reply3,5}</div>
}
\if{\step=4}
{3.
  \if{\sc_reply3=1}
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad">\name_youranswer[3;1] (\reply3) \name_youranswer[3;2].</span>}
<p>
4. \name_deduc2[1] \(t = \u\), \name_deduc2[2] \(\displaystyle \lim_{t\to\sol2} \g = \sol3\), \name_deduc2[3]:</p>
<div class="wimscenter">
<label for="reply4">\(\displaystyle \lim_{x\to\texlim} \gdeu \) =</label> \embed{reply4,5}</div>
}
\if{\step>4}
{4. \if{\step=5}
    {\if{\sc_reply4=1}
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad">\name_youranswer[3;1] (\reply4) \name_youranswer[3;2]</span>}
}
<span class="oef_indgood">\name_question2[1] \(\gg\) \name_at \(\texlim\) \name_question2[2]</span>:
<p class="wimscenter">\(\displaystyle \lim_{x\to\texlim} \ggx =\lim_{x\to\texlim} \gdeu = \lim_{t\to\sol2} \g = \sol4\).</p>
}
\if{\step=5}{
5. <label for="reply5">\name_question5[1] \(\texlim\) \name_question5[2] \(f = \ff\) \name_question5[3]?</label>
<div class="wimscenter">\embed{reply5,size=5}</div>
}

\if{\step=6}{
5. \if{\sc_reply5=1}
     {<span class="oef_indgood">\name_youranswer[1;].</span>}
     {<span class="oef_indbad">\name_youranswer[3;1] (\reply5) \name_youranswer[3;2].</span>}
<p>
\if{\rep5=1}{\name_rule[1;]}
  {\name_rule[2;] \(\lafi\). \name_rule[3;]:
<i>\if{\cas=1}{"\name_choix[1]".}{"\name_choix[2]".}</i>
}</p>
\name_onobtient:
  <div class="wimscenter">
  <label for="reply6">\(\displaystyle \lim_{x\to\texlim} f(x)\) = </label>\embed{reply6,5}</div>
}
<div class="wims_instruction">\name_inst</div>
}

\answer{\name_answer v : }{\rep1}{type=raw}{option=nospace,nonstop}
\answer{\name_answer u : }{\rep2}{type=raw}{option=nospace,nonstop}
\answer{\name_answer \(\g\) : }{\rep3}{type=raw}{option=nospace,nonstop}
\answer{\name_answer \(\gg\) : }{\rep4}{type=raw}{option=nospace,nonstop}
\answer{\name_answer2 :}{\rep5;\typeindet}{type=select}{option=nonstop}
\answer{\name_answer f : }{\sol6}{type=raw}{option=nospace}
#if defined TARGET_indeterminateForm || defined TARGET_indformwithexp
\feedback{\cas=1 && \op=4 && \rep5=4}{
<span class="wims_emph"><b>\name_feed[1]</b> : \name_feed[2]:
\(\displaystyle f(x) = \frac{\gdeu}{\v} = \frac{\gdeu}{\u} \times \frac{\u}{\v}\)
</span>}
#endif
