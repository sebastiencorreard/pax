target=simplifieratio

#include "avant_header.inc"
#include "css.inc"

\title{Simplifier un ratio}

\integer{coef=randint(2..10)}
\integer{nbre1=\coef*randint(1..5)}
\integer{nbre2=\coef*randint(1..5)}
\text{liste=\nbre1,\nbre2}
\text{liste2=wims(listuniq \liste)}
\if{items(\liste2)<2}{\integer{nbre2=\coef*6}}
\integer{pgcd=gcd(\nbre1,\nbre2)}
\integer{simnbre1=\nbre1/\pgcd}
\integer{simnbre2=\nbre2/\pgcd}

\statement{<div class="wims_instruction">Simplifier un ratio, c'est diviser chaque nombre du ratio par un diviseur commun aux nombres du ratio.
</div>

Simplifier <b>au maximum</b> le ratio <span class="nowrap"><b>\(\nbre1 : \nbre2\)</b>.</span>
<div><label for="reply1">On obtient</label><span class="nowrap">\embed{r1,3}<label for="reply2">:</label>\embed{r2,3}</span>.</div>}

\answer{}{\simnbre1}{type=numexp}
\answer{}{\simnbre2}{type=numexp}
\integer{test=gcd(\reply1,\reply2)}
\condition{Votre réponse est-elle correcte ?&nbsp;}{\reply1/\reply2=\simnbre1/\simnbre2 and \test=1}

\integer{repnonsim1=\reply1/\test}
\integer{repnonsim2=\reply2/\test}

\feedback{\reply1/\reply2=\simnbre1/\simnbre2 and \test<>1}{<div class="macss">Vous pouviez encore simplifier chaque nombre de votre réponse par <b>\test</b>.
<p>En effet, \reply1 et \reply2 sont divisibles par \test.</p>
<p>\(\reply1 = \test \times \repnonsim1\) et <span class="nowrap">\(\reply2 = \test \times \repnonsim2\).</span></p></div>}

\feedback{\reply1/\reply2<>\simnbre1/\simnbre2}{<div class="macss">Tu as fait une erreur dans ta simplification.</div>}

\hint{Simplifier un ratio (quand c'est possible), c'est diviser chaque nombre du ratio par un diviseur commun aux nombres du ratio.
<p>Par exemple, pour simplifier le ratio \(16:18\), on cherche un diviseur commun à \(16\) et \(18\).</p>
<p>\(16) et \(18) sont divisibles par \(2) et on a \( 16 = 2 \times 8 \) et <span class="nowrap">\( 18 = 2 \times 9\).</span></p>
<p>Donc le ratio \(16:18\) se simplifie en \(8:9\).</p>}
\solution{
\if{\nbre1!=\nbre2}
{<p>Simplifier un ratio, c'est diviser chaque nombre du ratio par un diviseur commun aux nombres du ratio.</p>
Le nombre \nbre1 et le nombre \nbre2 sont divisibles par \pgcd car \( \nbre1=\pgcd \times \simnbre1 \) et <span class="nowrap">\( \nbre2=\pgcd \times \simnbre2 \).</span></p>
<p>Par conséquent, le ratio \(\nbre1 : \nbre2\) peut également s'écrire <span class="nowrap">\(\simnbre1 : \simnbre2\).</span></p>
}{<p>Les deux nombres étant égaux, le ratio \(\nbre1 : \nbre2\) peut également s'écrire <span class="nowrap">\(\simnbre1 : \simnbre2\).</span></p>
}
}
