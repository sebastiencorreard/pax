target=classersuitesA classersuitesB
#include "author.inc"
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}

#include "lang_titles.inc"
#include "lang.inc"

\integer{nbfnct=3}
\integer{nonlin=1}
\text{size=220x60x5}

\integer{a=random(2..10)}
\integer{b=random(-1,1)*random(2..10)}
\integer{c=random(2..11)}
\integer{d=random(-1,1)*random(2..100)}
\real{d=\d/10}
\integer{e=random(2..90)}
\real{e=\e/10}
#if defined TARGET_classersuitesA
\integer{c=\c=\a? \c+1}
\real{e=\e=\b? \e+1}
#endif
#if defined TARGET_classersuiteB
\real{e=\e=\c? \e+1}
#endif
\integer{f=randitem(-1,1)*randitem(3,5,9,15)}
\integer{g=randitem(-1,1)*randitem(2,7,4,8,14)}
#if defined TARGET_classersuitesA
\matrix{donnees=x+\sqrt{\a},x-\c,x+\a,x-\a,\e+x,-\e+x,x-\frac{\f}{\c},\frac{\sqrt{\a}}{\e} +x,x+\frac{\a}{\c},\c(\b+\frac{x}{\c})
\sqrt{\a}x,\b x,\e x,\frac{\f}{\e}x,\frac{\sqrt{\a}}{\c}x
\cos(\a x),-x-\c,\frac{\c}{x},\b x^2+\a x+\c,\sqrt{\a}x^2+\e x+\c, \frac{\f}{\g}x^2+\frac{\a}{\b} x+\c,\b x^2,(x+\c)(x+\a),(x+\e)^2,(x-\c)^2}
#endif
#if defined TARGET_classersuitesB
\matrix{donnees=\b n+\sqrt{\a},-\sqrt{\c}n+\a,\b(n+\a),-n-\a,\f+\e n,-\e+\c n,n-\frac{\f}{\c},\frac{\sqrt{\a}}{\e} +\c n,\b n+\frac{\a}{\c},\c(\b+\frac{n}{\c})
(\sqrt{\a})^n,\b^n,(-\e)^n,(\frac{\f}{\e})^{n+\a},\frac{\sqrt{\a}}{\c^n},\f^{\c n},\g^{\a n+\c}
\cos(\a n),\frac{\c}{n},\b n^2+\a n+\c,\sqrt{\a}n^2+\e n+\c, \frac{\f}{\g}n^2+\frac{\a}{\b} n+\c,\b n^2,(n+\c)(n+\a),(n+\e)^n,(n-\c)^2}
#endif
\matrix{sortie=}
\for{i=1 to 3}{
\text{tmp=row(\i,\donnees)}
#if defined TARGET_classersuitesA
\text{tmp=wims(replace internal x by u_n in \tmp)}
#endif
\text{tmp=shuffle(\tmp)}
\text{line=}
\for{j=1 to \nbfnct}{
\text{tmp1=item(\j,\tmp)}
#if defined TARGET_classersuitesA
\text{tmp1=\(u_{n+1}= \tmp1)}
#endif
#if defined TARGET_classersuitesB
\text{tmp1=\(u_n= \tmp1)}
#endif
\text{line=wims(append item \tmp1 to \line)}
}
\text{sortie=wims(append line \line to \sortie)}
}
\text{goodari=row(1,\sortie)}
\text{goodgeo=row(2,\sortie)}
\text{goodaut=row(3,\sortie)}
\text{list=\goodari,\goodgeo,\goodaut}
\if{\nonlin=0}{
\text{goodgeo=\goodgeo,\goodari}
\text{enonceaffine=}
}{
\text{enonceaffine=\name_affine}
}

\statement{
\name_question: <ul>
<li>\name_type[1]: <br>\embed{r1,\size}</li>
<li>\name_type[2]: <br>\embed{r2,\size}</li>
<li>\name_type[3]: <br>\embed{r3,\size}</li>
</ul>
}
\reply{\name_type[1]}{\repari;\list}{type=clickfill}
\reply{\name_type[2]}{\repgeo;\list}{type=clickfill}
\reply{\name_type[3]}{\repaut;\list}{type=clickfill}
\text{tmpari=\repari,\goodari}
\text{tmpari=wims(listuniq \tmpari)}
\text{repari=wims(listuniq \repari)}
\integer{ari1=items(\tmpari)}
\integer{ari2=items(\repari)}
\condition{\name_type[1] }{\ari1=\nbfnct and \ari2=\nbfnct}
\text{tmpgeo=\repgeo,\goodgeo}
\text{tmpgeo=wims(listuniq \tmpgeo)}
\integer{geo1=items(\tmpgeo)}
\text{repgeo=wims(listuniq \repgeo)}
\integer{geo2=items(\repgeo)}
\integer{geo=items(\goodgeo)}
\condition{\name_type[2] }{\geo1=\nbfnct and \geo2=\nbfnct}
\text{tmpaut=\repaut,\goodaut}
\text{tmpaut=wims(listuniq \tmpaut)}
\integer{aut1=items(\tmpaut)}
\text{repaut=wims(listuniq \repaut)}
\integer{aut2=items(\repaut)}
\condition{\name_type[3]}{\aut1=\nbfnct and \aut2=\nbfnct}
\solution{<ul>
<li>\name_type[1]: <br>\goodari</li>
<li>\name_type[2]: <br>\goodgeo</li>
<li>\name_type[3]: <br>\goodaut</li>
</ul>}
