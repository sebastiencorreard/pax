target=equiprob1 equiprob2 equiprob3 equiprob4 equiprob5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}

\text{valexacte=Donner les valeurs exactes en utilisant des fractions si c'est nécessaire.}
#if defined TARGET_equiprob1
\title{Cas de l'équiprobabilité 1}
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
On compose au \special{help alea,hasard} un nombre de \n chiffres avec uniquement des \a et des \b.
</p>
Quelle est la probabilité des événements suivants ?
<ul>
<li>A <span class="wims_emph">« le nombre commence par un \a »</span> : P(A) = \embed{reply1,3}</li>
<li>B <span class="wims_emph">« le nombre se termine par un \b »</span> : P(B) = \embed{reply2,3}</li>
<li>C <span class="wims_emph">« le nombre ne contient que des \a »</span> : P(C) = \embed{reply3,3}</li>
<li>D <span class="wims_emph">« les chiffres \a et \b alternent »</span> : P(D) = \embed{reply4,3}</li>
<li>E <span class="wims_emph">« le nombre est supérieur à \adix »</span> : P(E) = \embed{reply5,3}</li>
</ul>
<div class="wims_instruction">\valexacte</div>
}
\answer{P(A)}{\p1}{type=numexp}{option=noreduction}
\answer{P(B)}{\p1}{type=numexp}{option=noreduction}
\answer{P(C)}{\p2}{type=numexp}{option=noreduction}
\answer{P(D)}{\p3}{type=numexp}{option=noreduction}
\answer{P(E)}{\p5}{type=numexp}{option=noreduction}
\help{
« Au hasard » signifie que tous les nombres à \n chiffres constitués uniquement des chiffres \a et \b ont la même probabilité d'être choisis.
}
#endif
#if defined TARGET_equiprob2
\title{Cas de l'équiprobabilité 2}
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
 dont les faces sont numérotées de 1 à 6.
 </p>
 <div class="wims_question">
Quelle est la probabilité des événements suivants ?
<ul>
<li>A <span class="wims_emph">« Obtenir exactement un \a »</span> : P(A) = \embed{reply1,3}</li>
<li>B <span class="wims_emph">« Obtenir au moins un \a »</span> : P(B) = \embed{reply2,3}</li>
<li>C <span class="wims_emph">« Obtenir au plus un \a » </span>: P(C) = \embed{reply3,3}</li>
<li>D <span class="wims_emph">« Obtenir des nombres \pairs »</span> : P(D) = \embed{reply4,3}</li>
<li>E <span class="wims_emph">« Obtenir une somme supérieure strictement à \b »</span> : P(E) = \embed{reply5,3}</li>
<li>F <span class="wims_emph">« Obtenir une somme égale à \c »</span> : P(F) = \embed{reply6,3}</li>
</ul></div>
<div class="wims_instruction">\valexacte</div>
}
\answer{P(A)}{\p1}{type=numexp}{option=noreduction}
\answer{P(B)}{\p2}{type=numexp}{option=noreduction}
\answer{P(C)}{\p3}{type=numexp}{option=noreduction}
\answer{P(D)}{\p4}{type=numexp}{option=noreduction}
\answer{P(E)}{\p5}{type=numexp}{option=noreduction}
\answer{P(F)}{\p6}{type=numexp}{option=noreduction}
#endif

#if defined TARGET_equiprob3
\title{Cas de l'équiprobabilité 3}
\integer{n=randint(3..4)}
\text{noms=Aurore, Béatrice, Chloé, Danielle, Elisabeth}
\text{prenoms=Aurore}
\for{i=2 to \n-1}
 { \text{prenoms=\prenoms,&nbsp;\noms[\i]}}
\text{prenoms=\prenoms et \noms[\n]}
\integer{tot=\n !}
\rational{p1=1/\tot}
\rational{p2=\n=3?1/2:1/3}
\rational{p3=\n=3?1/3:3/8}
\rational{p4=\n=3?1/6:1/12}
\statement{<p>
\prenoms vont au spectacle et laissent leur chapeau
au vestiaire. <br>
A la fin du spectacle, chacune reprend un des \n chapeaux au hasard.
</p>
<div class="wims_question">
 Quelle est la probabilité des événements suivants ?
<ul>
<li>A <span class="wims_emph">« Chacune retrouve son chapeau »</span> : P(A) = \embed{reply1,3}</li>
<li>B <span class="wims_emph">« Une seule personne retrouve son chapeau »</span> : P(B) = \embed{reply2,3}</li>
<li>C <span class="wims_emph">« Aucune ne retrouve son chapeau »</span> : P(C) = \embed{reply3,3}</li>
<li>D <span class="wims_emph">« Seule Chloé retrouve son chapeau »</span> : P(D) = \embed{reply4,3}</li>
</ul></div>
<div class="wims_instruction">\valexacte</div>
}
\answer{P(A)}{\p1}{type=numexp}{option=noreduction}
\answer{P(B)}{\p2}{type=numexp}{option=noreduction}
\answer{P(C)}{\p3}{type=numexp}{option=noreduction}
\answer{P(D)}{\p4}{type=numexp}{option=noreduction}
#endif

#if defined TARGET_equiprob4
\title{Cas de l'équiprobabilité 4}
\integer{n=randint(3..5)}
\text{ex=\n=3?W randint(1..9) randint(1..9) randint(1..9):W randint(1..9) randint(1..9) randint(1..9) randint(1..9)}
\text{ex=\n=5?\ex randint(1..9)}
\rational{p1=1/2*1/10^\n}
\rational{p2=1/10}
\rational{p3=1/10^(\n-1)}
\statement{<p>
Le « digicode » de la porte d'entrée d'un immeuble propose un
clavier à 12 touches ; elles sont marquées de 10 chiffres de 0 à 9,
 et des lettres V et W.</p>
Un code est formé d'une lettre suivie d'un nombre à \n chiffres
 (comme par exemple \ex).
<div class="wims_question"><ol>
<li>Quelle est la probabilité pour qu'en composant un code au \special{help alea,hasard},
 on obtienne le code secret ? \embed{reply1,5}</li>
<li>Quelle est la probabilité pour que le code secret se termine
 par 0 ? \embed{reply2,5}</li>
<li>Un individu indiscret a pu déterminer que le code commence par
 la lettre V et s'achève par un 8.<br>
Quelle est la probabilité, grâce à ces renseignements,
qu'il trouve le bon code du premier coup en composant au hasard
 les numéros qu'il ne connaît pas ? \embed{reply3,5}</li>
</ol></div>
<div class="wims_instruction">\valexacte</div>
}
\answer{Obtenir le code secret}{\p1}{type=numexp}{option=noreduction}
\answer{Le code se termine par 0}{\p2}{type=numexp}{option=noreduction}
\answer{Le code secret connaissant V...8}{\p3}{type=numexp}{option=noreduction}
\help{« Au hasard » signifie que tous les codes possibles ont la même chance d'être composés. }
#endif

#if defined TARGET_equiprob5
\title{Cas de l'équiprobabilité 5}
\integer{a=randint(8..15)}
\integer{b=randint(5..\a-1)}
\integer{n=randint(2..\b-1)}
\rational{pa=\b/\a}
\rational{pb=(\a-\n+1)/\a}
\rational{c=(\b-\n+1)/\a}
\statement{<p>
On a disposé dans une urne \a boules indiscernables numérotées de 1 à \a.
</p><p>
On choisit au \special{help alea, hasard} une boule dans cette urne.</p>
 On considère les événements :
<ul>
<li>A : <span class="wims_emph">«le numéro de la boule tirée est inférieur ou égal à \b »</span></li>
<li>B : <span class="wims_emph">«le numéro de la boule tirée est supérieur ou égal à \(n\) »,</span>
 où \(n\) est un entier compris entre 1 et \b.</li>
</ul>
<div class="wims_question">
Déterminer la valeur de l'entier \(n\), sachant que \(P( A \cap B) = \c\).
<div class="wimscenter"> \(n =\) \embed{reply1,3}</div></div>
}
\answer{Valeur de \(n\)}{\n}{type=numexp}
\help{« Au hasard » signifie que chaque boule a la même chance d'être tirée. }
#endif


