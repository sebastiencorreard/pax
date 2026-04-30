target=snddegre snddegre2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_snddegre
\integer{a0=random(1..6)}
\integer{sa=randitem(-1,1)}
\integer{a=2*\sa*\a0}
\integer{rep1=-(\sa*\a0)}
\text{trep1=\sa==1? + \a0 : - \a0}
\text{ta=\sa==1? + 2\times\a0\times : - 2\times\a0\times }
\integer{trep2=(\a0)^2}
\text{trep2=-\trep2}
\rational{rep2=-(\rep1)^2}
#endif
#if defined TARGET_snddegre2
\integer{a0=randitem(-1,1)*random(1..12)}
\integer{b0=randitem(1,1,1,2,2,3)}
\rational{a=\a0/\b0}
\rational{rep1=-(\a/2)}
\rational{rep2=-(\a/2)^2}
#endif
\function{u=x^2 +\a x}
#if defined TARGET_snddegre
\integer{k=randitem(-1,1,-1)}
\text{tk=\k==1?:-}
\integer{c=randitem(-1,1)*random(1..12)}
#endif
#if defined TARGET_snddegre2
\integer{k=randitem(-1,-2,-3,-4,1,2,3,4)}
\text{tk=\k}
\text{tk=\k==1?}
\text{tk=\k==-1?-}
\integer{c=randitem(-1,1)*random(1..12)}
#endif
\function{u=x^2 +\a*x}
\text{tu=wims(replace internal * by in \u)}
\function{f=maxima(\k*(\u) +\c)}
#if defined TARGET_snddegre
\rational{rep3=\c-\k*(\rep1)^2}
#endif
#if defined TARGET_snddegre2
\rational{rep3=\c-\k*(\a/2)^2}
#endif
\steps{reply1, reply2
reply3, reply4}
<!-- <div style="background:#F6E497;padding:2;">-->
\statement{
<!--- Première étape -->
Soit \(u\) la fonction définie sur \(\R\) par \( u(x) = \u\).
\if{\step==1}{
  <h2 class="small">Question 1.</h2>
  Réécrire \(u(x)\) sous forme canonique :
  <div class="wimscenter"> \(u(x) = (x - \alpha)^2 + \beta \)
  avec <label for="reply1">\(\,\alpha\) =</label> \embed{reply1,8}
   <label for="reply2">et \(\,\beta\) =</label> \embed{reply2,8}.</div>
}
<!--- Deuxième étape-->
\if{\step==2}{
  <h2 class="small">Analyse de la question 1.</h2>
  \if{\reply1=\rep1 and \reply2=\rep2}{
    <span class="oef_indgood">Vous avez répondu correctement. On a bien&nbsp;:</span>}
    {<span class="oef_indbad">Vous vous êtes trompé. La bonne réponse est&nbsp;:</span> }
#if defined TARGET_snddegre
  \(\tu= [x^2 \ta x + \a0^2] - \a0^2 = (x \trep1)^2 \trep2 = (x - (\rep1))^2 \rep2\).
#endif
#if defined TARGET_snddegre2
  \(\u = (x - \rep1)^2 + \rep2\).
#endif
  <h2 class="small">Question 2.</h2>
  En déduire la forme canonique de \(f(x) = \f\) :
  <div class="wimscenter"> \(f(x) = \tk(x - \alpha)^2 + \gamma \)
  avec <label for="reply3">\(\,\alpha\) =</label> \embed{reply3,8}
   <label for="reply4">et \(\,\gamma\) =</label> \embed{reply4,8}.
   </div>
}
}
\answer{Coefficient \(\,\alpha\)}{\rep1}{type=rational}{option=nonstop}
\answer{Coefficient \(\,\beta\)}{\rep2}{type=rational}{option=nonstop}
\answer{Coefficient \(\,\alpha\)}{\rep1}{type=rational}{option=nonstop}
\answer{Coefficient \(\,\gamma\)}{\rep3}{type=rational}{option=nonstop}

\hint{
Dans l'expression \(x^2 + a x\) on reconnaît le début du développement
de \(\left(x + \frac{a}{2} \right)^2\).
#if defined TARGET_snddegre2
On fait apparaître \(\left(\frac{a}{2} \right)^2\)
et l'on utilise une identité remarquable :
#endif
<div class="wimscenter">
#if defined TARGET_snddegre1
\(x^2 + a x = x^2 + 2\times\frac{a}{2}\times x + \left(\frac{a}{2}\right)^2 - \left(\frac{a}{2}\right)^2= \left(x + \frac{a}{2}\right)^2 - \left(\frac{a}{2}\right)^2\).</div>
#endif
#if defined TARGET_snddegre2
\(x^2 + a x = \left[ x^2 + 2\times\frac{a}{2}\times x + \left(\frac{a}{2}\right)^2 \right] \; - \; \left(\frac{a}{2}\right)^2= \left(x + \frac{a}{2}\right)^2 - \left(\frac{a}{2}\right)^2\).</div>
#endif
</div>
}
