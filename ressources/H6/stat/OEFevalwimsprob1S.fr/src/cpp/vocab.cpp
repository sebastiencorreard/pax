target=vocab1 vocab2 vocab3 vocab4 vocab5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\fromat{html}

#if (defined TARGET_vocab1 || defined TARGET_vocab3)
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
\text{s10=\a>=20?H:F,H}
\text{t1=\s3}
\text{t2=\s2}
\text{t3=\s7}
\text{t4=wims(listunion \s2 and \s4)}
\text{t5=vide}
\text{t6=\s2,15}
\text{t7=15}
\text{t8=\s4}

#if defined TARGET_vocab1
\title{Vocabulaire univers et événement 1}
\statement{<p>
On choisit au hasard (de manière équiprobable) un nombre entier entre 1 et \a.
</p><ol>
<li>Quel est l'univers ? <label for="reply1">\(\Omega =\) </label> \embed{reply1,\n}</li>
<li>Décrire de façon ensembliste les événements suivants :
<ul>
<li><label for="reply2">A "le nombre tiré est un multiple de 2" :</label> \embed{reply2}</li>
<li><label for="reply3">B "le nombre tiré est un multiple de 4" :</label> \embed{reply3}</li>
<li><label for="reply4">C "le nombre tiré est un multiple de 5" :</label> \embed{reply4}</li>
<li><label for="reply5">D "le nombre tiré est un multiple de 2 mais pas de 4" :</label> \embed{reply5}</li>
<li><label for="reply6">E "le nombre tiré est un multiple de 4 mais pas de 2" :</label> \embed{reply6}</li>
<li><label for="reply7">F "le nombre tiré est un multiple de 2 et de 5" :</label> \embed{reply7}</li>
<li><label for="reply8">G "le nombre tiré est un multiple de 2 et de 4" :</label> \embed{reply8}</li>
<li><label for="reply9">H "le nombre tiré est 15" :</label> \embed{reply9}</li>
</ul></li>
</ol>
<div class="wims_instruction">Taper "vide" s'il n'y a pas d'élément ;
s'il y a plusieurs éléments, les séparer par une virgule.</div>
<ol start="3">
<li><label for="reply9">Quels sont les événements élémentaires (c'est-à-dire qui ne comportent qu'une issue)
parmi les événements A à H ?</label> \embed{reply10}</li>
</ol>
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
\answer{événement élémentaire}{\s10}{type=fset}
#else
\title{Vocabulaire univers et événement 3}

\statement{<p>
On choisit au hasard (de manière équiprobable) un nombre entier entre 1 et \a.</p>
<div class="wims_columns">
  <div class="medium_size text_col">
On considère les événements suivants :
<ul>
<li>A "le nombre tiré est un multiple de 2"</li>
<li>B "le nombre tiré est un multiple de 4"</li>
<li>C "le nombre tiré est un multiple de 5"</li>
<li>D "le nombre tiré est un multiple de 2 mais pas de 2"</li>
<li>E "le nombre tiré est un multiple de 4 mais pas de 2"</li>
<li>F "le nombre tiré est un multiple de 2 et de 5"</li>
<li>G "le nombre tiré est un multiple de 2 et de 4"</li>
<li>H "le nombre tiré est 15"</li>
</ul>
</div>
<div class="medium_size text_col">
<div class="wims_question">
Décrire de façon ensembliste les événements suivants :
<ol>
<li><label for="reply1"> \(A \cap B\):</label> \embed{reply1}</li>
<li><label for="reply2"> \(A \cup B\):</label> \embed{reply2}</li>
<li><label for="reply3"> \(A \cap C\):</label> \embed{reply3}</li>
<li><label for="reply4"> \(A \cup C\):</label> \embed{reply4}</li>
<li><label for="reply5"> \(A \cap H\):</label> \embed{reply5}</li>
<li><label for="reply6"> \(A \cup H\):</label> \embed{reply6}</li>
<li><label for="reply7"> \(C \cap H\):</label> \embed{reply7}</li>
<li><label for="reply8"> \(C \cup H\):</label> \embed{reply8}</li>
</ol>
</div>
</div>
</div>
}
\answer{\(A \cap B\)}{\t1}{type=fset}
\answer{\(A \cup B\)}{\t2}{type=fset}
\answer{\(A \cap C\)}{\t3}{type=fset}
\answer{\(A \cup C\)}{\t4}{type=fset}
\answer{\(A \cap H\)}{\t5}{type=fset}
\answer{\(A \cup H\)}{\t6}{type=fset}
\answer{\(C \cap H\)}{\t7}{type=fset}
\answer{\(C \cup H\)}{\t8}{type=fset}

#endif
#endif

#if defined TARGET_vocab2
\title{Vocabulaire univers et événement 2}
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
 On note le résultat du lancer réalisé sous la forme d'un nombre
formé par les deux numéros obtenus, rangés dans l'ordre croissant.
</p>
<div class="wims_question">
Décrire les événements suivants :
<ul><li><label for="reply1">A "les deux nombres sont identiques" :</label> \embed{reply1}</li>
<li><label for="reply2">B  "les deux nombres sont consécutifs" :</label> \embed{reply2}</li>
<li><label for="reply3">C  "les deux nombres sont distincts et de même parité" :</label> \embed{reply3}</li>
<li><label for="reply4">D  "les deux nombres sont premiers et distincts" :</label> \embed{reply4}</li>
<li><label for="reply5">E  "la somme obtenue est un nombre premier" :</label> \embed{reply5}</li>
</ul>
</div>
}
\answer{2 nombres identiques}{\s1}{type=fset}
\answer{2 nombres consécutifs}{\s2}{type=fset}
\answer{2 nombres distincts et de même parité}{\s3}{type=fset}
\answer{2 nombres premiers}{\s4}{type=fset}
\answer{La somme est un nombre premier}{\s5}{type=fset}
#endif

#if defined TARGET_vocab4
\title{Vocabulaire univers et événement 4}
\text{lstrep=prendre,une,pomme,poire,orange,pomme jaune,pomme rouge,et,ou}
\text{s1=prendre,une,poire,ou,une,orange}
\text{s1b=prendre,une,orange,ou,une,poire}
\text{s2=prendre,une,orange,ou,une,pomme rouge}
\text{s2b=prendre,une,pomme rouge,ou,une,orange}
\text{s3=prendre,une,pomme,ou,une,poire}
\text{s3b=prendre,une,poire,ou,une,pomme}
\text{s5=prendre,une,pomme}
\text{size=100x50x6}
\statement{<p>
Une corbeille contient des pommes rouges, des pommes jaunes, des poires jaunes et des oranges.
 On prend un fruit au hasard (de manière équiprobable).
 </p>
<div class="wims_question">
 Décrire par une phrase (sans utiliser de négation)
l'événement contraire des événements suivants :
<ol>
<li><label for="reply1">Prendre une pomme :</label> \embed{reply1,\size}</li>
<li><label for="reply2">Prendre un fruit jaune :</label> \embed{reply2,\size}</li>
<li><label for="reply3">Prendre une orange :</label> \embed{reply3,\size}</li>
<li><label for="reply4">Ne prendre ni pomme ni poire :</label> \embed{reply4,\size}</li>
<li><label for="reply5">Prendre une orange ou une poire :</label> \embed{reply5,\size}</li>
</ol>
</div>
}
\answer{Prendre une pomme}{\rep1;\lstrep}{type=clickfill}
\answer{Prendre un fruit jaune}{\rep2}{type=clickfill}
\answer{Prendre une orange}{\rep3}{type=clickfill}
\answer{Ne prendre ni pomme ni poire}{\rep4}{type=clickfill}
\answer{Prendre une orange ou une poire}{\s5}{type=clickfill}
\condition{Prendre une pomme}{\reply1 issametext \s1 or \reply1 issametext \s1b}
\condition{Prendre un fruit jaune}{\reply2 issametext \s2 or \reply2 issametext \s2b}
\condition{Prendre une orange}{\reply3 issametext \s3 or \reply3 issametext \s3b}
\condition{Ne prendre ni pomme ni poire}{\reply4 issametext \s3 or \reply4 issametext \s3b}
#endif

#if defined TARGET_vocab5
\title{Vocabulaire univers et événement 5}
\text{lstrep=Oui,Non}
\statement{<p>
On lance deux dés cubiques équilibrés, dont les faces sont numérotées
 de 1 à 6.</p>
 On considère les événements suivants :
<ul>
<li> A "obtenir exactement un 1".</li>
<li> B "obtenir au moins un 1".</li>
<li> C "obtenir au plus un 1".</li>
<li> D "obtenir des nombres pairs".</li>
<li> E "obtenir une somme supérieure strictement à 10".</li>
<li> F "obtenir une somme inférieure ou égale à 10".</li>
<li> G "obtenir une somme égale à 7".</li>
</ul>
<div class="wims_question">
<ol>
<li><label for="reply1">Les événements A et B sont-ils contraires ?</label> \embed{reply1} - <label for="reply2">Incompatibles ?</label> \embed{reply2}</li>
<li><label for="reply3">Les événements C et B sont-ils contraires ?</label> \embed{reply3} - <label for="reply4">Incompatibles ?</label> \embed{reply4}</li>
<li><label for="reply5">Les événements A et D sont-ils contraires ?</label> \embed{reply5} - <label for="reply6">Incompatibles ?</label> \embed{reply6}</li>
<li><label for="reply7">Les événements E et F sont-ils contraires ?</label> \embed{reply7} - <label for="reply8">Incompatibles ?</label> \embed{reply8}</li>
<li><label for="reply9">Les événements E et G sont-ils contraires ?</label> \embed{reply9} - <label for="reply10">Incompatibles ?</label> \embed{reply10}</li>
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
\answer{ E et G incompatibles}{1;\lstrep}{type=radio}
#endif
