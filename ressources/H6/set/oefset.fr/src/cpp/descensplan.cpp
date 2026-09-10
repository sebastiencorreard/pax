target=descensplan
#define GGG C1 -
\title{GGG Description d'un sous-ensemble du plan}
\description{exercice guidé pour le calcul du cardinal de quatre types d'ensembles différents}
\observation{Pour 2 types d'ensembles, l'énoncé comportera 3 étapes au lieu de 2 si on a sélectionné la plus faible valeur pour le paramètre "Complexité des ensembles".}
\keywords{set_theory,combinatorics}
\language{fr}
\author{Sophie, Lemaire}
\email{sophie.lemaire@universite-paris-saclay.fr}
\computeanswer{yes}
\precision{10000}
\format{html}
#include "css.inc"
#include "common.inc"
#include "lang_descensplan_fr.inc"
\if{\lang=it}{
#include "lang_descensplan_it.inc"
}
\if{\lang=es}{
#include "lang_descensplan_es.inc"
}
\integer{d=randint(0..40)-20}
\integer{nb2=randint(10..50)}
\integer{f=\nb2+(\d)-1}
\integer{dp=\d+1}
\integer{fm=\f-1}
\text{E2=\d, \dp, ..., \fm, \f}
\integer{c=randint(1..4)}
\integer{nivex=2}
\if{\confparm1=1}{\integer{nivex=1}}

\integer{c=randint(1..4)}

\if{\c=1}{
\integer{p=randint((\d-(\f)+2)..(\f-(\d)-2))}
\text{ens={ \( (x, y)\in\{\E2\}^2 \;\text{\name_suchthat}\; x - y = \p \) }.}
\integer{nelt=min(\f,\f-(\p))-max(\d, \d-(\p))+1}
\text{ord=simplify(x-(\p))}
\if{\p>0}{\integer{borne1=\d+\p}\integer{borne2=\f}}
         {\integer{borne1=\d}\integer{borne2=\f+\p}}
\integer{v=2}
}
\if{\c=2}{
\integer{p=randint((2*\d+2)..(2*\f-2))}
\text{ens={ \( (x, y)\in\{\E2\}^2\) \name_suchthat \(x + y = \p \) }.}
\integer{nelt=min(\f,\p-(\d))-max(\d, \p-(\f))+1}
\text{ord=\p-x}
\if{\p<(\d+\f)}{\integer{borne1=\d}\integer{borne2=\p-\d}}
         {\integer{borne1=\p-\f}\integer{borne2=\f}}
\integer{v=2}
}
\if{\c=3}{
\text{ens={ \( (x,y)\in\{\E2\}^2\) \name_suchthat \(x < y \) }.}
\integer{nelt=binomial(\nb2,2)}
\text{ord=y-1}
\integer{borne0=\d+1}
\integer{borne1=\d}
\integer{borne2=\f}
\integer{v=3}
\integer{nd=-(\d)}
\text{ny=\nd>0?y+\nd:y \nd}
}
\if{\c=4}{
\text{ens={ \((x,y)\in\{\E2\}^2\) \name_suchthat \(x \leq y \) }.}
\integer{nelt=binomial(\nb2+1,2)}
\text{ord=y}
\integer{borne0=\d}
\text{borne1=\d}
\text{borne2=\f}
\integer{v=3}
\integer{nd=-(\d)+1}
\text{ny=\nd>0?y+\nd:y \nd}
}
\text{reunion1=E = \bigcup_{ y = \borne0}^{reply3}\{ (x,y) \;\text{\name_suchthat}\; x \in \ZZ \;\text{\name_and}\;reply2 \leq x \leq reply4 \}}
\text{reunion2=wims(replace internal reply2 by \borne1 in \reunion1)}
\text{reunion2=wims(replace internal reply3 by \borne2 in \reunion2)}
\text{reunion2=wims(replace internal reply4 by \ord in \reunion2)}
\real{err=-1}
\if{\nivex=1 and \c>2}{
\text{ETAPES=reply1,reply2,reply3,reply4;reply6;reply5}
}
{\text{ETAPES=reply1,reply2,reply3,reply4;reply5}}
\steps{\ETAPES}
\statement{<div class="color1"> \instruction[1;]
<div class="center"> \(E\) = \ens</div>
</div>
<div class="wims_question">
<ol>
<li> \instruction[2;]
\if{\step=1}{\embed{reply1}.}{<span class="oef_indgood">\listeforme[\v].</span>}
</li><li>
\instruction[3;]:
\if{\c<=2}{
<div class="center">\(E\) = \(\{\)(x,\if{\step=1}{\embed{reply4,5}}{<span class="oef_indgood">\ord</span>}) \(\in \ZZ^2\) \name_suchthat
\if{\step=1}{\embed{reply2,4}}{<span class="oef_indgood">\borne1</span>}\(\leq\) x \(\leq\)
\if{\step=1}{\embed{reply3,4}}{<span class="oef_indgood">\borne2</span>}\(\}\)</div>
}
{
 \if{\step=1}{
<div class="center">\special{mathmlinput [\displaystyle{\reunion1}],3,noanswer
reply2
reply3
reply4}
</div>
 } {<div class="center color2">\(\displaystyle{\reunion2}\)</div>}

}
</li>
\if{\step>=2}{
<li>\if{\nivex=1 and \c>2}{\instruction[4;] \(\borne0 \leq y \leq \borne2\),
\instruction[5;]
<div class="wimscenter">\(E_y=\{\) (x,y) \name_suchthat
x\(\in \ZZ\) \name_and \borne1 \(\leq\) x \(\leq\) \ord \(\}\)</div>
\name_has \if{\step=2}{\embed{reply6,10}}{\ny} \name_elements.}
       {\instruction[6;]\embed{reply5}.}</li>
   }
\if{\step>2}{<li>\instruction[6;] \embed{reply5}.</li>}</ol>
</div>}
\answer{}{\v;\listeforme}{type=menu}{weight=1}
\answer{}{\borne1}{type=formal}{weight=1}
\answer{}{\borne2}{type=formal}{weight=1}
\answer{}{\ord}{type=formal}{weight=1}
\answer{Card( E )}{\var}{type=numeric}{weight=2}
\answer{}{\ny}{type=formal}{weight=1}
\real{err=pari(abs(\var-\nelt))}
\condition{Avez-vous donné la bonne réponse}{\err==0}{option=hide}
\feedback{\step>=2 and \err==0}{<div class="oef_indgood">
\name_feedback[1;] \nelt \name_elements.
</div>}
\feedback{((\step=2 and \c<=2) or (\step=2 and \c>2 and \nivex>1) or (\step=3 and \c>2 and \nivex=1)) and \err>0}{
<div class="oef_indbad">
\name_feedback[2;] \nelt \name_elements \name_andnot \var \if{\var=1 or \var=0}{\name_element.}{
\name_elements.}
</div>}
\help{\name_help <br>
\if{\step=2}{\name_solution[3;].}}
\solution{
\if{\step=1}{2. \if{\c<=2}{
\(E = \{(x,\ord) \in \ZZ^2, \borne1 \leq x \leq \borne2 \}\)}
{ \(E= \displaystyle{\bigcup_{y=\borne0}^{\borne2}\{(x,y), x\in \ZZ
\;\text{\name_and}\; \borne1 \leq x \leq \ord \}}\)}}

\if{\step=2 and \nivex=1 and \c>2}{3. \name_forall \(\borne0 \leq y \leq \borne2\), \instruction[5;]
\(\{ (x,y), x\in \ZZ \;\text{ \name_and}\; \borne1 \leq x \leq \ord \}\) \name_has \ny
\name_elements.}
\if{\step=2 and \c<=2}{3.
\name_solution[1;] \borne1 \name_and \borne2. }
\if{(\step=2 and \c>2 and \nivex>1) or (\step>=3)}{<br>\if{\step>=3}{4.}{3.}
\name_solution[2;] :
\(E = \displaystyle{ \bigcup_{y=\borne0}^{\borne2}} E_y\) \name_avec \(E_y\)
\name_feedback[3;] \(\ny\) \name_elements.<br>
\name_solution2
&#91;\d, \f &#93;<sup>2</sup> \name_solution3.}
}
