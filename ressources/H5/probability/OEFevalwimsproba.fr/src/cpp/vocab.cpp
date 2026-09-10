target=vocab1 vocab2 vocab3 vocab4 vocab5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
#if defined TARGET_vocab1
# define NUM 1
#endif
#if defined TARGET_vocab2
# define NUM 2
#endif
#if defined TARGET_vocab3
# define NUM 3
#endif
#if defined TARGET_vocab4
# define NUM 4
#endif
#if defined TARGET_vocab5
# define NUM 5
#endif
#include "lang_titles.inc"

\text{consig1=Taper "vide" s'il n'y a pas d'élément ; s'il y a plusieurs éléments, les séparer par une virgule.}
\text{consig2=Séparer les éléments de chaque ensemble par une virgule.}
#if (defined TARGET_vocab1  || defined TARGET_vocab3 )
\integer{a=randint(15..25)}
\text{s1=wims(makelist x for x=1 to \a)}
\integer{a2=floor(\a/2)}
\text{s2=}
\for{x=1 to \a2}{
  \integer{y=2*\x}
  \text{s2=wims(append item \y to \s2)}
}
\integer{a4=floor(\a/4)}
\text{s3=}
\for{x=1 to \a4}{
  \integer{y=4*\x}
  \text{s3=wims(append item \y to \s3)}
}
\integer{a5=floor(\a/5)}
\text{s4=}
\for{x=1 to \a5}{
  \integer{y=5*\x}
  \text{s4=wims(append item \y to \s4)}
}
\text{s5=wims(listcomplement \s3 in \s2)}
\text{s6=vide}
\text{s7=wims(listintersect \s2 and \s4)}
\text{s8=\s3}
\text{s9=15}
\text{s10=\a>=20?8:6,8}
\text{t1=\s3}
\text{t2=\s2}
\text{t3=\s7}
\text{t4=wims(listunion \s2 and \s4)}
\text{t5=vide}
\text{t6=\s2,15}
\text{t7=15}
\text{t8=\s4}
\integer{n=2*\a}
# if defined TARGET_vocab1
\text{listens=A,B,C,D,E,F,G,H}
\statement{
On choisit au hasard un nombre entier entre 1 et \a.
<div class="wims_question">
<ol>
<li>Quel est l'univers ? \(\Omega =\) \embed{reply1,\n}</li>
</ol>
<div class="wims_instruction">Ecrire les éléments de l'univers en les séparant par une virgule.</div>
<ol start="2">
<li>Décrire de façon ensembliste les événements suivants :
<ul>
<li><label for="reply2">A « le nombre tiré est un multiple de 2 »</label> : \embed{reply2,\a}</li>
<li><label for="reply3">B « le nombre tiré est un multiple de 4 »</label> : \embed{reply3,\a}</li>
<li><label for="reply4">C « le nombre tiré est un multiple de 5 »</label> : \embed{reply4,\a}</li>
<li><label for="reply5">D « le nombre tiré est un multiple de 2 mais pas de 4 »</label> : \embed{reply5,\a}</li>
<li><label for="reply6">E « le nombre tiré est un multiple de 4 mais pas de 2 »</label> : \embed{reply6,\a}</li>
<li><label for="reply7">F « le nombre tiré est un multiple de 2 et de 5 »</label> : \embed{reply7,\a}</li>
<li><label for="reply8">G « le nombre tiré est un multiple de 2 et de 4 »</label> : \embed{reply8,\a}</li>
<li><label for="reply9">H « le nombre tiré est 15 »</label> : \embed{reply9,\a}</li>
</ul></li></ol>
<div class="wims_instruction">\consig1</div>
<ol start="3">
<li>Quels sont les événements élémentaires parmi les événements A à H ?
<div class="wimscenter">\embed{reply10}</div></li></ol>
<div class="wims_instruction">Sélectionner toutes les événements élémentaires.</div>
</div>
}
\answer{univers}{\s1}{type=fset}
\answer{multiple de 2}{\s2}{type=fset}
\answer{multiple de 4}{\s3}{type=fset}
\answer{multiple de 5}{\s4}{type=fset}
\answer{multiple de 2 et pas de 4}{\s5}{type=fset}
\answer{multiple de 4 et pas de 2}{\s6}{type=fset}
\answer{multiple de 2 et de 5}{\s7}{type=fset}
\answer{multiple de 2 et de 4}{\s8}{type=fset}
\answer{le nombre est 15}{\s9}{type=fset}
\answer{événement élémentaire}{\s10;\listens}{type=checkbox}
# else
\statement{<p>
On choisit au hasard un nombre entier entre 1 et \a.</p>
On considère les événements suivants :
<ul class="wims_nopuce">
<li>A « le nombre tiré est un multiple de 2 » </li>
<li>B « le nombre tiré est un multiple de 4 » </li>
<li>C « le nombre tiré est un multiple de 5 » </li>
<li>D « le nombre tiré est un multiple de 2 mais pas de 2 » </li>
<li>E « le nombre tiré est un multiple de 4 mais pas de 2 » </li>
<li>F « le nombre tiré est un multiple de 2 et de 5 » </li>
<li>G « le nombre tiré est un multiple de 2 et de 4 » </li>
<li>H « le nombre tiré est 15 » </li>
</ul>
<div class="wims_question">
  Décrire de façon ensembliste les événements suivants :
<ol>
<li> <label for="reply1">\(A \cap B)</label> = \embed{reply1}</li>
<li> <label for="reply2">\(A \cup B)</label> = \embed{reply2}</li>
<li> <label for="reply3">\(A \cap C)</label> = \embed{reply3}</li>
<li> <label for="reply4">\(A \cup C)</label> = \embed{reply4}</li>
<li> <label for="reply5">\(A \cap H)</label> = \embed{reply5}</li>
<li> <label for="reply6">\(A \cup H)</label> = \embed{reply6}</li>
<li> <label for="reply7">\(C \cap H)</label> = \embed{reply7}</li>
<li> <label for="reply8">\(C \cup H)</label> = \embed{reply8}</li>
</ol>
</div>
<div class="wims_instruction">\consig1</div>
}
\answer{\(A \cap B)}{\t1}{type=fset}
\answer{\(A \cup B)}{\t2}{type=fset}
\answer{\(A \cap C)}{\t3}{type=fset}
\answer{\(A \cup C)}{\t4}{type=fset}
\answer{\(A \cap H)}{\t5}{type=fset}
\answer{\(A \cup H)}{\t6}{type=fset}
\answer{\(C \cap H)}{\t7}{type=fset}
\answer{\(C \cup H)}{\t8}{type=fset}
# endif
#endif
#if defined TARGET_vocab2
\integer{k=randint(4,6)}
\text{typede=\k=4?tétraédriques:cubiques}
\if{\k=4}
 {
\text{s1=11,22,33,44}
\text{s2=12,23,34}
\text{s3=13,24}
\text{s4=23}
\text{s5=11,12,14,23,34}
 }
 {
\text{s1=11,22,33,44,55,66}
\text{s2=12,23,34,45,56}
\text{s3=13,15,35,24,26,46}
\text{s4=23,25,35}
\text{s5=11,12,14,16,23,25,34,56}
 }

\statement{<p>
On lance deux dés \typede dont les faces sont numérotées de 1 à \k.
 On note le résultat du lancer réalisé sous la forme d'un nombre formé
 par les deux numéros obtenus, rangés dans l'ordre croissant.
</p>
<div class="wims_question">
 Décrire de façon ensembliste les événements suivants :
<ul class="wims_nopuce">
<li><label for="reply1">A « Les deux nombres sont identiques »</label> : \embed{reply1}</li>
<li><label for="reply2">B « Les deux nombres sont consécutifs »</label> : \embed{reply2}</li>
<li><label for="reply3">C « Les deux nombres sont distincts et de même parité »</label> : \embed{reply3}</li>
<li><label for="reply4">D « Les deux nombres sont premiers et distincts »</label> : \embed{reply4}</li>
<li><label for="reply5">E « La somme obtenue est un nombre premier »</label> : \embed{reply5}</li>
</ul>
</div>
<div class="wims_instruction">\consig2</div>
}
\answer{2 nombres identiques}{\s1}{type=fset}
\answer{2 nombres consécutifs}{\s2}{type=fset}
\answer{2 nombres distincts et de même parité}{\s3}{type=fset}
\answer{2 nombres premiers}{\s4}{type=fset}
\answer{la somme est un nobre premier}{\s5}{type=fset}
#endif
#if defined TARGET_vocab4
\text{lstrep=prendre,une,pomme,poire,orange,pomme jaune,pomme rouge,et,ou}
\text{s1=prendre,une,poire,ou,une,orange}
\text{s1b=prendre,une,orange,ou,une,poire}
\text{s2=prendre,une,orange,ou,une,pomme rouge}
\text{s2b=prendre,une,pomme rouge,ou,une,orange}
\text{s3=prendre,une,pomme,ou,une,poire}
\text{s3b=prendre,une,poire,ou,une,pomme}
\text{s5a=prendre,une,pomme}
\text{s5b=prendre,une,pomme jaune,ou,une,pomme rouge}
\text{s5c=prendre,une,pomme rouge,ou,une,pomme jaune}
\text{s5d=prendre,une,pomme,ou,une,pomme jaune}
\text{s5e=prendre,une,pomme rouge,ou,une,pomme}
\text{s5f=prendre,une,pomme,ou,une,pomme rouge}
\text{s5g=prendre,une,pomme jaune,ou,une,pomme}
\text{s5h=prendre,une,pomme,ou,une,pomme jaune}
\text{s5i=prendre,une,pomme,ou,une,pomme}
\text{name_anal=Votre réponse est-elle correcte}
\text{size=80x45x6}
\statement{
Une corbeille contient des pommes rouges, des pommes jaunes, des poires jaunes et des oranges.
 On prend un fruit au hasard dans cette corbeille.
 <div class="wims_question">
 Décrire par une phrase l'événement contraire des événements suivants, en utilisant au plus six étiquettes parmi celles proposées :
<ol>
<li><label for="reply1">Prendre une pomme</label> : \embed{reply1,\size}</li>
<li><label for="reply2">Prendre un fruit jaune</label> : \embed{reply2,\size}</li>
<li><label for="reply3">Prendre une orange</label> : \embed{reply3,\size}</li>
<li><label for="reply4">Ne prendre ni pomme ni poire</label> : \embed{reply4,\size}</li>
<li><label for="reply5">Prendre une orange ou une poire</label> : \embed{reply5,\size}</li>
</ol>
</div>
}
\answer{1. Prendre une pomme}{\rep1;\lstrep}{type=clickfill}
\answer{2. Prendre un fruit jaune}{\rep2}{type=clickfill}
\answer{3. Prendre une orange}{\rep3}{type=clickfill}
\answer{4. Ne prendre ni pomme ni poire}{\rep4}{type=clickfill}
\answer{5. Prendre une orange ou une poire}{\rep5}{type=clickfill}
\condition{1. \name_anal ?}{\reply1 issametext \s1 or \reply1 issametext \s1b}
\condition{2. \name_anal ?}{\reply2 issametext \s2 or \reply2 issametext \s2b}
\condition{3. \name_anal ?}{\reply3 issametext \s3 or \reply3 issametext \s3b}
\condition{4. \name_anal ?}{\reply4 issametext \s3 or \reply4 issametext \s3b}
\condition{5. \name_anal ?}{\reply5 issametext \s5a or \reply5 issametext \s5b  or \reply5 issametext \s5c or \reply5 issametext \s5d or \reply5 issametext \s5e or \reply5 issametext \s5f
or \reply5 issametext \s5g or \reply5 issametext \s5h or \reply5 issametext \s5i}

#endif

#if defined TARGET_vocab5
\text{lstrep=Oui,Non}
\text{name_event=Les événements}
\text{name_and=et}
\text{name_are=sont-ils}
\text{name_opposite=contraires }
\text{name_incompatible=incompatibles }
\matrix{name_enonce=On lance deux dés cubiques équilibrés, dont les faces sont numérotées de 1 à 6. 
 On s'intéresse aux numéros visibles sur la face supérieure de chaque dé lorsque ceux-ci ne bougent plus. 
 On considère les événements suivants }
\text{num1=random(1,3,5)}
\text{num2=randint(3..10)}
\text{num3=randint(2..12)}
\integer{rep5=\num3>\num2?2:1}
\matrix{name_quest=Obtenir exactement un numéro \num1
Obtenir au moins un numéro \num1
Obtenir au plus un numéro \num1
Obtenir deux nombres pairs
Obtenir une somme supérieure strictement à \num2
Obtenir une somme inférieure ou égale à \num2
Obtenir une somme égale à \num3}
\text{latexchoix=\textcircled{ } \lstrep[1] \textcircled{ } \lstrep[2] }
\text{latexquest=\begin{itemize}
  \item \name_opposite ? \latexchoix
  \item \name_incompatible ? \latexchoix
  \end{itemize}
}
  
\statement{<p>
\name_enonce[1;]\name_enonce[2;]</p>
\name_enonce[3;]
<ul class="wims_nopuce">
<li> A : « \name_quest[1;] »</li>
<li> B : « \name_quest[2;] »</li>
<li> C : « \name_quest[3;] »</li>
<li> D : « \name_quest[4;] »</li>
<li> E : « \name_quest[5;] »</li>
<li> F : « \name_quest[6;] »</li>
<li> G : « \name_quest[7;] »</li>
</ul>
<div class="wims_question">
<ol class="spacer">
<li>\name_event A \name_and B \name_are 
  <ul><li>\name_opposite? \embed{reply1}</li>
   <li>\name_incompatible? \embed{reply2}</li>
  </ul></li>
<li>\name_event C \name_and B \name_are 
  <ul><li>\name_opposite? \embed{reply3}</li>
      <li>\name_incompatible?  \embed{reply4}</li>
  </ul></li>    
<li>\name_event A \name_and D \name_are 
  <ul><li>\name_opposite? \embed{reply5}</li>
      <li>\name_incompatible? \embed{reply6}</li>
  </ul></li>
<li>\name_event E \name_and F \name_are 
  <ul><li>\name_opposite? \embed{reply7}</li>
      <li>\name_incompatible? \embed{reply8}</li>
  </ul></li>
<li>\name_event E \name_and G \name_are 
  <ul><li>\name_opposite? \embed{reply9}</li>
      <li>\name_incompatible? \embed{reply10}</li>
  </ul></li>
</ol>
</div>
}
\answer{ A et B contraires}{2;\lstrep}{type=radio}
\answer{ A et B incompatibles}{2;\lstrep}{type=radio}
\answer{ C et B contraires}{2;\lstrep}{type=radio}
\answer{ C et B incompatibles}{2;\lstrep}{type=radio}
\answer{ A et D contraires}{2;\lstrep}{type=radio}
\answer{ A et D incompatibles}{1;\lstrep}{type=radio}
\answer{ E et F contraires}{1;\lstrep}{type=radio}
\answer{ E et F incompatibles}{1;\lstrep}{type=radio}
\answer{ E et G contraires}{2;\lstrep}{type=radio}
\answer{ E et G incompatibles}{\rep5;\lstrep}{type=radio}
\latex{
\begin{statement}
\name_enonce[1;]\name_enonce[2;]
\name_enonce[3;]
\begin{itemize}
\item A : « \name_quest[1;] »
\item B : « \name_quest[2;] »
\item C : « \name_quest[3;] »
\item D : « \name_quest[4;] »
\item E : « \name_quest[5;] »
\item F : « \name_quest[6;] »
\item G : « \name_quest[7;] »
\end{itemize}
\begin{enumerate}
\item \name_event A \name_and B \name_are \latexquest
\item \name_event C \name_and B \name_are \latexquest
\item \name_event A \name_and D \name_are \latexquest
\item \name_event E \name_and F \name_are \latexquest
\item \name_event E \name_and G \name_are \latexquest
\end{enumerate}
\end{statement}
}
#endif
