target=linmean1 linmean2 linmean3 linmean4 linmean5
\precision{100}
#if defined TARGET_linmean1 
\title{Linéarité de la moyenne 1}
\integer{n=randint(25..36)}
\integer{Moy=random(randint(50..80),randint(130..180))}
\text{verb=remonter,baisser}
\integer{choix=\Moy>100?2:1}
\real{moy1=\Moy/10}
\real{x=random(0.5,1,1.5,2)}
\real{moy2=\choix=1?\moy1+\x:\moy1-\x}
\statement{
A un contrôle de mathématiques , la moyenne obtenue est de \moy1.<p>
Le professeur décide de \verb[\choix] toutes les notes des \n élèves de \x points.
Quelle sera la nouvelle moyenne du contrôle?
</p>
Nouvelle moyenne=\embed{reply1,5}
}
\answer{Nouvelle moyenne}{\moy2}{type=numeric}

#endif
#if defined TARGET_linmean2 
\title{Linéarité de la moyenne 2}
\integer{n=randint(25..36)}
\integer{Moy=random(randint(50..80),randint(130..180))}
\text{verb=remonter,baisser}
\integer{choix=\Moy>100?2:1}
\real{moy1=\Moy/10}
\real{x=random(5,10,15,20)}
\real{moy2=\choix=1?\moy1*(1+\x/100):\moy1*(1-\x/100)}
\statement{
A un contrôle de mathématiques, la moyenne obtenue est de \moy1.<p>
Le professeur décide de \verb[\choix] toutes les notes des \n élèves de \x %.
Quelle sera la nouvelle moyenne du contrôle?
</p>
Nouvelle moyenne=\embed{reply1,5}
}
\answer{Nouvelle moyenne}{\moy2}{type=numeric}
#endif
#if defined TARGET_linmean3 
\title{Linéarité de la moyenne 3}
\text{temp=}
\real{moyF=0}
\for{i=1 to 12}
  {
   \integer{t=randint(500..800)}
   \real{t=\t /10}
   \text{temp=wims(append item \t to \temp)}
   \real{moyF=\moyF+\t}
  }
\real{moyF=\moyF / 12}
\real{moyC=5/9*(\moyF-32)}
\statement{
Voici des statistiques américaines sur la température moyenne mensuelle à San Francisco:
<table class="wimscenter wimsborder"><tr><th>Mois</th><th>Jan.</th><th>Fev.</th><th>Mar.</th><th>Avr.</th><th>Mai</th><th>Juin</th></tr>
<tr><td>°F</td><td>\temp[1]</td><td>\temp[2]</td><td>\temp[3]</td><td>\temp[4]</td><td>\temp[5]</td><td>\temp[6]</td></tr></table>
<table class="wimscenter wimsborder"><tr><th>Mois</th><th>Juil.</th><th>Août</th><th>Sep.</th><th>Oct.</th><th>Nov.</th><th>Dec.</th></tr>
<tr><td>°F</td><td>\temp[7]</td><td>\temp[8]</td><td>\temp[9]</td><td>\temp[10]</td><td>\temp[11]</td><td>\temp[12]</td></tr></table>

<ol>
<li> Calculer la température annulle moyenne en degré fahrenheit.<p>
 Moyenne en °F:\embed{reply1,5}</p></li>
<li> Sachant que la température <i>t </i> en degré Celsius s'obtient à partir de la tepérature T en degré fahrenheit par la formule :
 <div class="wimscenter"><i>t</i>=\(\frac{5}{9}(T-32))</div>
Calculer la température annuelle moyenne en degré Celsius.<p>
 Moyenne en °C:\embed{reply2,5}</p>
 </li>
</ol>
}
\answer{moyenne en °F}{\moyF}{type=numeric}
\answer{moyenne en °C}{\moyC}{type=numeric}

#endif
#if defined TARGET_linmean4 
\title{Linéarité de la moyenne 4}
\text{data=en prenant les inverses des valeurs de la série A,en prenant l'inverse de la moyenne de la série A,2
en prenant les carrés des valeurs de la série A,en prenant le carré de la moyenne de la série A,2
en doublant les valeurs de la série A,en doublant la moyenne de la série A,1
en augmentant chaque valeur de la série A de 10, en augmentant la moyenne de la série A de 10,1
en prenant les opposés des valeurs de la série A, en prenant l'opposé de la moyenne de la série A,1
}
\text{cedata=randomrow(\data)}
\text{q1=\cedata[1]}
\text{q2=\cedata[2]}
\integer{rep=\cedata[3]}
\statement{
Cocher la bonne réponse : <p>
On considère une série statistique A dont on connait la moyenne, et on construit une série statistique B \q1.
</p>
On peut alors calculer la moyenne de la série B, \q2.
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep;Vrai,Faux}{type=radio}
#endif
#if defined TARGET_linmean5 
\title{Linéarité de la moyenne 5}
\integer{x=randint(10..30)}
\real{x=\x/10}
\real{xd=\x / 10}
\real{moy=randint(70..160)/10}
\integer{n=randint(7..16)}
\real{nm=10*(\moy*10+\n)/11}
\integer{nm=\nm}
\real{nm=\nm / 10}
\real{bm=\moy+\n/10}
\real{nm2=\bm}
\real{bm2=\nm}
\real{nm3=\moy*100/11}
\integer{nm3=\nm3}
\real{nm3=\nm3/10}
\real{bm3=\moy*11}
\integer{bm3=\bm3}
\real{bm3=\bm3/10}
\text{data=Si on augmente toutes les notes de \x points, la moyenne augmente de \x points, la moyenne augmente de \x %, la moyenne augmente de \xd
Si on duplique chaque note, la moyenne reste inchangée, la moyenne double, on ne peut pas connaitre la moyenne
Si on duplique une note, on ne peut pas connaitre la moyenne, la moyenne reste inchangée,  la moyenne double
Si on ajoute une note valant \n, la moyenne vaut \nm, on ne peut pas connaitre la moyenne, la moyenne vaut \bm
Si on augmente une note de \n, la moyenne vaut \nm2, on ne peut pas connaitre la moyenne, la moyenne vaut \bm2
Si on rajoute une note nulle, la moyenne vaut \nm3, la moyenne reste inchangée, la moyenne vaut \bm3
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\text{lstrep=item(2..4,\cedata)}

\statement{
Cocher la bonne réponse:<p>
On considère une série de 10 notes dont la moyenne est \moy.</p>
\quest
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{1;\lstrep}{type=radio}{option=shuffle}
#endif
