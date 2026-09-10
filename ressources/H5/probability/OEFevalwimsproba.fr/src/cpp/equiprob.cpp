target=equiprob1 equiprob2 equiprob3 equiprob4 equiprob5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\text{consig=Donner les valeurs sous forme de fractions.}
#if defined TARGET_equiprob1
# define NUM 1
#endif
#if defined TARGET_equiprob2
# define NUM 2
#endif
#if defined TARGET_equiprob3
# define NUM 3
#endif
#if defined TARGET_equiprob4
# define NUM 4
#endif
#if defined TARGET_equiprob5
# define NUM 5
#endif
#include "lang_titles.inc"
#if defined TARGET_equiprob1
\integer{n=randint(4..6)}
\integer{a=randint(1..5)}
\integer{b=\a+randint(1..4)}
\integer{adix=randint(\a,\b)*10^(\n-1)}
\integer{tot=2^\n}
\rational{p1=1/2}
\rational{p2=1/\tot}
\rational{p3=2/\tot}
\rational{p5=\adix=\a*10^(\n-1)?1:1/2}

\statement{<p>
On compose au hasard un nombre de \n chiffres avec uniquement des \a et des \b.
</p>
<div class="wims_question">
Quelle est la probabilité des événements suivants ?
<ul>
<li>A « le nombre commence par un \a » : <label for="reply1">\(P(A)=\)</label>\embed{reply1,3}</li>
<li>B « le nombre se termine par un \b » : <label for="reply2">\(P(B)=\)</label>\embed{reply2,3}</li>
<li>C « le nombre ne contient que des \a » :<label for="reply3">\(P(C)=\)</label>\embed{reply3,3}</li>
<li>D « les chiffres \a et \b alternent » : <label for="reply4">\(P(D)=\)</label>\embed{reply4,3}</li>
<li>E « le nombre est supérieur à \adix » : <label for="reply5">\(P(E)=\)</label>\embed{reply5,3}</li>
</ul>
</div>
<div class="wims_instruction">\consig</div>
}
\answer{\(P(A)\)}{\p1}{type=numexp}{option=noreduction}
\answer{\(P(B)\)}{\p1}{type=numexp}{option=noreduction}
\answer{\(P(C)\)}{\p2}{type=numexp}{option=noreduction}
\answer{\(P(D)\)}{\p3}{type=numexp}{option=noreduction}
\answer{\(P(E)\)}{\p5}{type=numexp}{option=noreduction}
#endif

#if defined TARGET_equiprob2
# define NUM 2
\integer{a=randint(1..6)}
\text{pairs=random(pairs,impairs)}
\integer{a2=randint(1..6)}
\integer{b=\a+\a2}
\integer{a3=randint(1..6)}
\integer{c=\a3+\a2}
\text{ps=0,1,2,3,4,5,6,5,4,3,2,1}
\rational{p1=5/18}
\rational{p2=11/36}
\rational{p3=35/36}
\rational{p4=1/4}
\rational{p5=0}
\for{i=\b+1 to 12}
 {\rational{p5=\p5+\ps[\i]}}
\rational{p5=\p5/36}
\rational{p6=\ps[\c]/36}
\statement{<p>
  On lance deux dés cubiques équilibrés,
  dont les faces sont numérotées de 1 à 6. On note le numéro de la face supérieure de chaque dé.
 </p>
 <div class="wims_question">
  Quelle est la probabilité des événements suivants ?
  <ul>
    <li>A « Obtenir exactement un \a » : <label for="reply1">\(P(A)=\)</label>\embed{reply1,3}</li>
    <li>B « Obtenir au moins un \a » : <label for="reply2">\(P(B)=\)</label>\embed{reply2,3}</li>
    <li>C « Obtenir au plus un \a » : <label for="reply3">\(P(C)=\)</label>\embed{reply3,3}</li>
    <li>D « Obtenir des nombres \pairs » : <label for="reply4">\(P(D)=\)</label>\embed{reply4,3}</li>
    <li>E « Obtenir une somme supérieure strictement à \b » : <label for="reply5">\(P(E)=\)</label>\embed{reply5,3}</li>
    <li>F « Obtenir une somme égale à \c » : <label for="reply6">\( P(F)=\)</label>\embed{reply6,3}</li>
    </ul>
  </div>
  <div class="wims_instruction">\consig</div>
}
\answer{\(P(A)\)}{\p1}{type=numexp}{option=noreduction}
\answer{\(P(B)\)}{\p2}{type=numexp}{option=noreduction}
\answer{\(P(C)\)}{\p3}{type=numexp}{option=noreduction}
\answer{\(P(D)\)}{\p4}{type=numexp}{option=noreduction}
\answer{\(P(E)\)}{\p5}{type=numexp}{option=noreduction}
\answer{\(P(F)\)}{\p6}{type=numexp}{option=noreduction}
#endif

#if defined TARGET_equiprob3
# define NUM 3
\integer{n=randint(3..4)}
\text{noms=Aurore,Béatrice,Chloé,Danielle,Elisabeth}
\text{prenoms=Aurore}
\for{i=2 to \n-1}
 { \text{prenoms=\prenoms,\noms[\i]}}
\text{prenoms=\prenoms et \noms[\n]}
\integer{tot=\n !}
\rational{p1=1/\tot}
\rational{p2=\n=3?1/2:1/3}
\rational{p3=\n=3?1/3:3/8}
\rational{p4=\n=3?1/6:1/12}
\statement{<p>
\prenoms vont au spectacle et laissent leur chapeau
au vestiaire. <br>
A la fin du spectacle, chacune reprend un des \n chapeaux au hasard.</p>
<div class="wims_question">
 Quelle est la probabilité des événements suivants ?
<ul>
<li>A « Chacune retrouve son chapeau » : <label for="reply1">\(P(A)=\)</label>\embed{reply1,3}</li>
<li>B « Une seule personne retrouve son chapeau » : <label for="reply2">\(P(B)=\)</label>\embed{reply2,3}</li>
<li>C « Aucune ne retrouve son chapeau » : <label for="reply3">\(P(C)=\)</label>\embed{reply3,3}</li>
<li>D « Seule Chloé retrouve son chapeau » : <label for="reply4">\(P(D)=\)</label>\embed{reply4,3}</li>
</ul>
</div>
<div class="wims_instruction">\consig</div>
}
\answer{Chacune retrouve son chapeau}{\p1}{type=numexp}{option=noreduction}
\answer{Une seule personne retrouve son chapeau}{\p2}{type=numexp}{option=noreduction}
\answer{Aucune ne retrouve son chapeau}{\p3}{type=numexp}{option=noreduction}
\answer{Seule Chloé retrouve son chapeau}{\p4}{type=numexp}{option=noreduction}
#endif

#if defined TARGET_equiprob4
# define NUM 4
\integer{n=randint(3..5)}
\text{ex=\n=3?W 1 2 3:W 1 2 7 5}
\text{ex=\n=5?\ex 8}
\rational{p1=1/2*1/10^\n}
\rational{p2=1/10}
\rational{p3=1/10^(\n-1)}
\statement{<p>
Le « digicode » de la porte d'entrée d'un immeuble propose un
clavier à 12 touches ; elles sont marquées de 10 chiffres de 0 à 9,
 et des lettres V et W.</p><p>
Un code est formé d'une lettre suivie d'un nombre à \n chiffres
 (comme par exemple \ex).</p>
 <div class="wims_question">
<ol>
<li><label for="reply1">Quelle est la probabilité pour qu'en composant un code au hasard,
 on obtienne le code secret</label> ? \embed{reply1,5}</li>
<li><label for="reply2">Quelle est la probabilité pour que le code secret se termine
 par 0 ?</label> \embed{reply2,5}</li>
<li>Un individu indiscret a pu déterminer que le code commence par
 la lettre V et s'achève par un 8.<br>
<label for="reply3">Quelle est la probabilité, grâce à ces renseignements,
qu'il trouve le bon code du premier coup en composant au hasard
 les numéros qu'il ne connaît pas </label>? \embed{reply3,5}</li>
</ol></div>
<div class="wims_instruction">\consig</div>
}
\answer{Obtenir le code secret}{\p1}{type=numexp}{option=noreduction}
\answer{Le code se termine par 0}{\p2}{type=numexp}{option=noreduction}
\answer{Obtenir le code secret connaisant V...8}{\p3}{type=numexp}{option=noreduction}
#endif

#if defined TARGET_equiprob5
# define NUM 5
\integer{a=randint(8..15)}
\integer{b=randint(5..\a-1)}
\integer{n=randint(2..\b-1)}
\rational{pa=\b/\a}
\rational{pb=(\a-\n+1)/\a}
\rational{c=(\b-\n+1)/\a}
\statement{<p>
On a disposé dans une urne \(\a\) boules indiscernables numérotées de \(1\) à \(\a\).<br>
On choisit au hasard une boule dans cette urne.</p>
 On considère les événements :
<ul class="wims_nopuce">
<li>A « le numéro de la boule tirée est inférieur ou égal à \(\b\) ». </li>
<li>B « le numéro de la boule tirée est supérieur ou égal à \(n\) »,
 où \(n\) est un entier compris entre \(1\) et \(\b\).</li>
</ul>
<div class="wims_question">Déterminer la valeur de l'entier \(n\), sachant que \(P( A \cap B)=\c\).
<div class="wimscenter"> <label for="reply1">\(n =\)</label>\embed{reply1,3}.</div>
</div>
}
\answer{Valeur de \(n\)}{\n}{type=numexp}
#endif
