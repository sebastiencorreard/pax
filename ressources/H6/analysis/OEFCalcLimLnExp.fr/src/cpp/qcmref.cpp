target=qcmref
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{x=random(x,t,X,\alpha)}
\integer{n=random(1,1,2,3,4)}
\text{xn=\n>1?\x^\n:\x}
\text{sn=\n=1 or \n=3?-:+}
\text{inf=&#8734;}
\integer{a = random(-1,1)*random(1..8)}
\text{\sa=\a>0?+:-}
\text{\soa=\a>0?-:+}
\integer{b=random(0,0,1,2,3,4)}
\integer{b=random(-1,1)*\b}
\function{u=maxima(expand(\a*\x + \b))}
\text{u=texmath(\u)}
\rational{x0=-\b/\a}
\integer{k=random(-1,1)*random(1..8)}
\text{tk=\k!=1 and \k!=-1?\k}
\text{tk=\k=-1?-}
\text{\sk=\k>0?+:-}
\text{\sok=\k>0?-:+}
\text{ineg=\a>0?>:<}
\matrix{forms=\(\lim_{\x\to+\infty} \; e^{\x}\)
\(\displaystyle\lim_{\x\to-\infty} \; e^{\x}\)
\(\displaystyle\lim_{\x\to+\infty} \; \ln(\x)\)
\(\displaystyle\lim_{\begin{array}{l}\x\to 0\\\x>0\end{array}} \; \ln(\x)\)
\(\displaystyle\lim_{\x\to+\infty} \; \tk e^{\x}\)
\(\displaystyle\lim_{\x\to-\infty} \; \tk e^{\x}\)
\(\displaystyle\lim_{\x\to+\infty} \; \tk\ln(\x)\)
\(\displaystyle\lim_{\begin{array}{l}\x\to 0\\\x>0\end{array}} \; \tk\ln(\x)\)
\(\displaystyle\lim_{\x\to+\infty \; }e^{\u}\)
\(\displaystyle\lim_{\x\to-\infty} \; e^{\u}\)
\(\displaystyle\lim_{\x\to\sa\infty} \; \ln(\u)\)
\(\displaystyle\lim_{\begin{array}{l}\x\to\x0\\\x\ineg\x0\end{array}} \; \ln(\u)\)
\(\displaystyle\lim_{\x\to+\infty} \; \frac{e^{\x}}{\xn}\)
\(\displaystyle\lim_{\x\to-\infty} \; \xn\times e^{\x}\)
\(\displaystyle\lim_{\x\to+\infty} \; \frac{\ln(\x)}{\xn}\)
\(\displaystyle\lim_{\begin{array}{l}\x\to 0\\\x>0\end{array}}\xn\times\ln(\x)\)
\(\displaystyle\lim_{\x\to+\infty}\frac{\xn}{e^{\x}}\)
\(\displaystyle\lim_{\x\to-\infty}\xn\times e^{-\x}\)
\(\displaystyle\lim_{\x\to+\infty}\frac{\xn}{\ln(\x)}\)
\(\displaystyle\lim_{\begin{array}{l}\x\to 0\\\x>0\end{array}} \; \frac{\xn}{\ln(\x)}\)
\(\displaystyle\lim_{\x\to 1} \; \frac{\ln(\x)}{\x-1}\)
\(\displaystyle\lim_{\x\to 0} \; \frac{e^{\x}-1}{\x}\)
}

\text{reps=+inf,0,+inf,-inf,\sk inf,0,\sk inf,\sok inf}
\text{rep9=\a>0?+inf:0}
\text{rep10=\a>0?0:+inf}
\text{rep11=+inf}
\text{rep12=-inf}
\text{reps=\reps,\rep9,\rep10,\rep11,\rep12,+inf,0,0,0,0,\sn inf,+inf,0,1,1}

\text{nums=shuffle(22)}
\text{nums=item(1..6,\nums)}
\text{quest=row([\nums],\forms)}
\text{answ=item([\nums],\reps)}
\text{q1=row(1,\quest)}
\text{q2=row(2,\quest)}
\text{q3=row(3,\quest)}
\text{q4=row(4,\quest)}
\text{q5=row(5,\quest)}
\text{q6=row(6,\quest)}
\text{a1=item(1,\answ)}
\text{a2=item(2,\answ)}
\text{a3=item(3,\answ)}
\text{a4=item(4,\answ)}
\text{a5=item(5,\answ)}
\text{a6=item(6,\answ)}

\statement{
<i>\name_enonce</i>
<div class="wims_question">
<ul><li>
<label for="reply1">\q1</label>=\embed{reply1, 5}
</li><li>
<label for="reply2">\q2</label> =\embed{reply2, 5}
</li><li>
<label for="reply3">\q3</label> =\embed{reply3, 5}
</li><li>
<label for="reply4">\q4</label> =\embed{reply4, 5}
</li><li>
<label for="reply5">\q5</label> =\embed{reply5, 5}
</li><li>
<label for="reply6">\q6</label>=\embed{reply6, 5}
</li></ul>
 </div>
<div class="wims_instruction">\name_inst. </div>
}

\answer{}{\a1}{type=raw}{option=nospace}
\answer{}{\a2}{type=raw}{option=nospace}
\answer{}{\a3}{type=raw}{option=nospace}
\answer{}{\a4}{type=raw}{option=nospace}
\answer{}{\a5}{type=raw}{option=nospace}
\answer{}{\a6}{type=raw}{option=nospace}
