target= definition

#include "author.inc"
#include "css.inc"
#include "lang_titles.inc"
#include "lang.inc"

\title{TITRE}

\integer{nb=randint(1..100)}
\text{signe=+,-}
\text{sign1=random(+,-)}
\if{\sign1=+}{\text{sign=positif}
\text{tsign=\plus}}{\text{sign=négatif}
\text{tsign=\minus}}
\text{sig=positif,négatif}
\statement{ Compléter les phrases suivantes :
<ul>
<li>Le signe de \(\tsign \nb\) est ... \embed{r1,60x30}.</li>
<li><label for="reply2">La distance à zéro de \( \tsign \nb \) est ...</label> \embed{reply2,3}.</li>
</ul>}

\answer{}{\sign;\sig}{type=clickfill}
\answer{}{\nb}{type=numeric}

\solution{
<ul>
<li>Le signe de \( \tsign \nb  \) est ... \sign.</li>
<li>La distance à zéro de \( \tsign \nb  \) est ... \(\nb\).</li>
</ul>}

\hint{Un nombre relatif est composé d'un signe ( positif ou négatif ) et d'une partie numérique appelée distance à zéro.}
\feedback{\reply2<0}{<div class="macss"><b>Une distance à zéro est toujours positive.</b></div>}
