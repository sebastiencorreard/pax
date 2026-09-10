target=sachant1 sachant2
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\precison{100}
\format{html}
\keywords{conditional_probability}
#if defined TARGET_sachant1
\title{H. Probabilité conditionnelle et arbre}
\author{Régine, Mangeard}
\description{Trouver une probabilité conditionnelle à partir d'un arbre pondéré de probabilités}
 d'après un exo de Bernadette PERRIN-RIOU
/*Nombre de branches possibles maximum*/
\integer{MAX=4}
\integer{MAX=\confparm1=1 ? 1}
\integer{MAX=\confparm1=2 ? 2}
\integer{MAX=\confparm1=3 ? 4}

\integer{T=randint(1..7)}
\if{\T=1}{
  \matrix{G=1,2,3
2,4,5,6
3,7,8,9}
\text{nom=*,A1,A2,B1,B2,B3,B1,B2,B3}
}
\if{\T=2}{
  \matrix{G=1,2,3
2,4,5
3,6,7,8}
  \text{nom=*,A1,A2,B1,B2,B1,B2,B3}
}
\if{\T=3}{
  \matrix{G=1,2,3
2,4,5,6
3,7,8,9,10}
  \text{nom=*,A1,A2,B1,B2,B3,B1,B2,B3,B4}
}
\if{\T=4}{
  \matrix{G=1,2,3,4
2,5,6
3,7,8
4,9,10}
  \text{nom=*,A1,A2,A3,B1,B2,B1,B2,B1,B2}
}
\if{\T=5}{
  \matrix{G=1,2,3,4
2,5,6,7
3,8,9,10
4,11,12,13}
  \text{nom=*,A1,A2,A3,B1,B2,B3,B1,B2,B3,B1,B2,B3}
}
\if{\T=6}{
  \matrix{G=1,2,3,4
2,5,6,7
3,8,9
4,10,11,12}
  \text{nom=*,A1,A2,A3,B1,B2,B3,B1,B2,B1,B2,B3}
}
\if{\T=7}{
  \matrix{G=1,2,3,4
2,5,6
3,7,8,9
4,10,11,12}
  \text{nom=*,A1,A2,A3,B1,B2,B1,B2,B3,B1,B2,B3}
}
\text{listechemin=}
\text{cnt=rows(\G)}
\for{i=2 to \cnt}{
  \text{ligne=\G[\i;2..-1]}
  \for{j in \ligne}{
  \matrix{listechemin= \listechemin
\i,\j}
}
}
\integer{N= randitem(10,20,50)}
/* Proba */
\text{p=0}
\for{i=1 to \cnt}{
  \integer{s=items(\G[\i;])-1}
  \text{prob=wims(makelist 1/\s for x = 1 to \s-1)}
  \text{p=\p,slib(stat/multinomial 1,\N, [\prob])}
}
\text{p=pari(1.*[\p]/\N)}
/*Graphe*/
\text{S=slib(graph/drawtree [\G],[[\nom],[\p]],middle point)}
\text{u=wims(declosing \S[1])}
\text{position= \S[3]}
\text{milieu=\S[4]}
\matrix{position= wims(declosing \position)}
\matrix{milieu= wims(declosing \milieu)}
\integer{cas=randint(1,2)}

\if{\cas=1}{
\integer{k=randint(1..rows(\listechemin))}
\integer{kA=\listechemin[\k;1]}
\integer{kB=\listechemin[\k;2]}
\text{evenement=\nom[\kB]}
\text{sachant=\nom[\kA]}
\real{proba=\p[\kB]}
\text{tsol=Cette probabilité conditionnelle se lit directement sur l'arbre, c'est celle indiquée sur la branche reliant
\nom[\kA] à \nom[\kB].}
 }{
\integer{k=randint(1..rows(\listechemin))}
\integer{kA=\listechemin[\k;1]}
\integer{kB=\listechemin[\k;2]}
\text{evenement=\nom[\kA]}
\text{sachant=\nom[\kB]}
\real{pinter=\p[\kB]*\p[\kA]}
\text{listeB=position(\nom[\kB],\nom)}
\real{ps=0}
\text{tsol=Cette probabilité ne se lit pas directement sur l'arbre. <br />
  Il faut d'abord calculer \(P(\nom[\kA] \cap \nom[\kB])=\p[\kB]\times \p[\kA]=\pinter\).<br />
  Puis calculer }
\text{tss=}
\for{t in \listeB}{
  \for{l=2 to \cnt}{
    \if{\t isitemof \G[\l;]}{
      \integer{iA=\G[\l;position(\t,\G[\l;])-1]}
      \real{ps=\ps+\p[\l]*\p[\t]}
      \text{tss=wims(append item \p[\l]\times \p[\t] to \tss)}
    }
  }
}
\text{tss=wims(replace internal , by + in \tss)}
\real{proba=round(100*\pinter/\ps)/100}
\text{tsol=\tsol \(P(\nom[\kB])=\tss=\ps\).<p>
  On obtient alors la probabilité cherchée : \(P_{\sachant}(\evenement) = \frac{\pinter}{\ps}\simeq \proba\).
</p>}
}

\statement{
<p>
  Voici un arbre pondéré de probabilités.
</p>
<p class="wimscenter">\draw{700,200}{\u}</p>
<div class="wims_question">
  Calculer la probabilité conditionnelle de l'événement \evenement sachant \sachant :
<div class="wimscenter"><label for="reply1">\(P_{\sachant}(\evenement) = \)</label>\embed{reply1,5}</div>
</div>
<div class="wims_instruction">Arrondir la probabilité à \(10^{-2}\) près.</div>
}
\answer{Probabilité de \(F\)}{\proba}{type=numeric}
\solution{\tsol}
#endif
\integer{k=random(1,2)}

#if defined TARGET_sachant2
\title{I. Probabilité conditionnelle et tableau croisé}
\description{Déterminer des probabilités conditionnelles dans le cas d'un tirage au hasard d'une personne dans un groupe}
\integer{n=randint(1..20)}
\integer{coef=100}
\text{classeA1=Filles,Externes,Fumeurs,Français,de,d',de,de}
\text{classeA2=Garçons,Demi-pensionnaires,Non fumeurs,Etrangers,de,de,de,d'}
\text{classeB1=Adolescents,Scientifiques,Sportifs,Travailleurs,d',de,de,de}
\text{classeB2=Enfants,Littéraires,Non sportifs,Chômeurs,de,de,de,de}
\integer{total=100}
\integer{totalA1=randint(\total/2..\total-1)}
\integer{totalA2=\total - \totalA1}
\text{l=\totalA1,\totalA2}
\text{ind=shuffle(2)}
\integer{totalA1=\l[\ind[1]]}
\integer{totalA2=\l[\ind[2]]}
\integer{nba1b1=randint(\totalA1 /2..\totalA1-1)}
\integer{nba1b2=\totalA1-\nba1b1}
\integer{nba2b1=randint(\totalA2 /2..\totalA2-1)}
\integer{nba2b2=\totalA2-\nba2b1}
\integer{totalB1=\nba1b1+\nba2b1}
\integer{totalB2=\nba1b2+\nba2b2}

\text{info=\total,\totalA1,\totalA2,\totalB1,\totalB2,\nba1b1, \nba1b2,\nba2b1,\nba2b2}
\integer{itotal=1}
\integer{itotalA1=2}
\integer{itotalA2=3}
\integer{itotalB1=4}
\integer{itotalB2=5}
\integer{inba1b1=6}
\integer{inba1b2=7}
\integer{inba2b1=8}
\integer{inba2b2=9}
\integer{ipcta1b1=10}
\integer{ipcta1b2=11}
\integer{ipcta2b1=12}
\integer{ipcta2b2=13}
\integer{imrgA1b1=14}
\integer{imrgA1b2=15}
\integer{imrgA2b1=16}
\integer{imrgA2b2=17}
\integer{imrga1B1=18}
\integer{imrga1B2=19}
\integer{imrga2B1=20}
\integer{imrga2B2=21}
\integer{ipcttotalA1=22}
\integer{ipcttotalA2=23}
\integer{ipcttotalB1=24}
\integer{ipcttotalB2=25}

\rational{pcttotal=100}
\rational{pcttotalA1=\totalA1 }
\rational{pcttotalA2=\totalA2 }
\rational{pcttotalB1=\totalB1 }
\rational{pcttotalB2=\totalB2 }
\rational{pctnba1b1=\nba1b1 }
\rational{pctnba1b2=\nba1b2 }
\rational{pctnba2b1=\nba2b1 }
\rational{pctnba2b2=\nba2b2 }
\real{margeA1b1= \coef*\nba1b1 / \totalA1}
\real{margeA1b2= \coef*\nba1b2 / \totalA1}
\real{margeA2b1= \coef*\nba2b1 / \totalA2}
\real{margeA2b2= \coef*\nba2b2 / \totalA2}
\real{margea1B1= \coef*\nba1b1 / \totalB1}
\real{margea1B2= \coef*\nba1b2 / \totalB2}
\real{margea2B1= \coef*\nba2b1 / \totalB1}
\real{margea2B2= \coef*\nba2b2 / \totalB2}
\rational{total=\total * \n}
\rational{totalA1=\totalA1 * \n}
\rational{totalA2=\totalA2 * \n}
\rational{totalB1=\totalB1 * \n}
\rational{totalB2=\totalB2 * \n}
\rational{nba1b1=\nba1b1 * \n}
\rational{nba1b2=\nba1b2 * \n}
\rational{nba2b1=\nba2b1 * \n}
\rational{nba2b2=\nba2b2 * \n}

\integer{choix=randint(1..4)}

\text{info=\total,\totalA1,\totalA2,\totalB1,\totalB2,
\nba1b1, \nba1b2,\nba2b1,\nba2b2,
\pctnba1b1,\pctnba1b2,\pctnba2b1,\pctnba2b2,
\margeA1b1,\margeA1b2,\margeA2b1,\margeA2b2,
\margea1B1,\margea1B2,\margea2B1,\margea2B2,
\pcttotalA1,\pcttotalA2,\pcttotalB1,\pcttotalB2}
\text{infoar=}
\for{i=1 to 25}{
 \integer{x=\info[\i]*100}
 \integer{x=\x/100}
 \text{infoar=wims(append item \x to \infoar)}
}
\text{infoori=\info}
\text{info=\infoar}

//// on recalcule les nombres de personnes en fonction des arrondis effectués
\integer{nba1b1=\info[\imrgA1b1]*\totalA1/\coef}
\integer{nba1b2=\info[\imrgA1b2]*\totalA1/\coef}
\integer{nba2b1=\info[\imrgA2b1]*\totalA2/\coef}
\integer{nba2b2=\info[\imrgA2b2]*\totalA2/\coef}
\integer{totalB1=\nba1b1+\nba2b1}
\integer{totalB2=\nba1b2+\nba2b2}

real{margea1B1= \coef*\nba1b1 / \totalB1}
real{margea1B2= \coef*\nba1b2 / \totalB2}
real{margea2B1= \coef*\nba2b1 / \totalB1}
real{margea2B2= \coef*\nba2b2 / \totalB2}

\text{infoar2=\infoar}
\text{infoar2=wims(replace item number 4 by \totalB1 in \infoar2)}
\text{infoar2=wims(replace item number 5 by \totalB2 in \infoar2)}
\text{infoar2=wims(replace item number 6 by \nba1b1 in \infoar2)}
\text{infoar2=wims(replace item number 7 by \nba1b2 in \infoar2)}
\text{infoar2=wims(replace item number 8 by \nba2b1 in \infoar2)}
\text{infoar2=wims(replace item number 9 by \nba2b2 in \infoar2)}
\text{info=\infoar2}

 \text{tintro=
  On étudie un groupe de personnes composé \classeA1[\choix+4] \classeA1[\choix] et \classeA2[\choix+4] \classeA2[\choix].<p>
  Parmi les \info[\itotalA1] \classeA1[\choix], on compte \info[\imrgA1b1] % de \classeB1[\choix]
 et parmi les \info[\ipcttotalA2]% \classeA2[\choix+4] \classeA2[\choix], on compte \info[\inba2b1] \classeB1[\choix].</p>
}
\integer{cas=randint(1,2)}
\text{q1=\cas=1?Sachant que cette personne appartient à la catégorie des \classeA1[\choix], quelle est la probabilité qu'elle appartienne à la catégorie des \classeB2[\choix]:Sachant que cette personne appartient à la catégorie des \classeB1[\choix], quelle est la probabilité qu'elle appartienne à la catégorie des \classeA2[\choix]}
\text{q2=\cas=2?Sachant que cette personne appartient à la catégorie des \classeA1[\choix], quelle est la probabilité qu'elle appartienne à la catégorie des \classeB2[\choix]:Sachant que cette personne appartient à la catégorie des \classeB1[\choix], quelle est la probabilité qu'elle appartienne à la catégorie des \classeA2[\choix]}
\real{rep1=\cas=1?\info[\imrgA1b2]/100:\info[\imrga2B1]/100}
\real{rep2=\cas=2?\info[\imrgA1b2]/100:\info[\imrga2B1]/100}
\text{trace=\infoori<br />\infoar<br />\info<br />nba1b1=\nba1b1}
\statement{
\tintro
<p>Compléter les tableaux ci dessous.</p>
<div class="flex_box"><table class="wimsborder"><caption>Tableau en nombre de personnes</caption>
<tr><th>&nbsp;</th><th>\classeA1[\choix]</th><th>\classeA2[\choix]</th><th>Total</th></tr>
<tr><td>\classeB1[\choix]</td><td>\embed{reply1,4}</td><td>\embed{reply2,4}</td><td>\embed{reply3,4}</td></tr>
<tr><td>\classeB2[\choix]</td><td>\embed{reply4,4}</td><td>\embed{reply5,4}</td><td>\embed{reply6,4}</td></tr>
<tr><td>Total</td><td>\embed{reply7,4}</td><td>\embed{reply8,4}</td><td>\embed{reply9,4}</td></tr>
</table>
<table class="wimsborder"><caption>Tableau marginal en pourcentage</caption>
<tr><th>&nbsp;</th><th>\classeA1[\choix]</th><th>\classeA2[\choix]</th><th>Total</th></tr>
<tr><td>\classeB1[\choix]</td><td>\embed{reply10,4}</td><td>\embed{reply11,4}</td><td>100%</td></tr>
<tr><td>\classeB2[\choix]</td><td>\embed{reply12,4}</td><td>\embed{reply13,4}</td><td>100%</td></tr>
</table>
<table class="wimsborder"><caption>Tableau marginal en pourcentage</caption>
<tr><th>&nbsp;</th><th>\classeA1[\choix]</th><th>\classeA2[\choix]</th></tr>
<tr><td>\classeB1[\choix]</td><td>\embed{reply14,4}</td><td>\embed{reply15,4}</td></tr>
<tr><td>\classeB2[\choix]</td><td>\embed{reply16,4}</td><td>\embed{reply17,4}</td></tr>
<tr><td>Total</td><td>100%</td><td>100%</td></tr>
</table>
</div>
<p>
  On tire une personne au hasard&nbsp;:
</p>
<ol>
<li><label for="reply18">\q1&nbsp;?</label> \embed{reply18,5}</li>
<li><label for="reply19">\q2&nbsp;?</label> \embed{reply19,5}</li>
</ol>
<div class="wims_instruction">La réponse est demandée avec au moins 2
  chiffres significatifs.</div>
}
\answer{Réponse 1}{\info[\inba1b1]}{type=numeric}
\answer{Réponse 2}{\info[\inba2b1]}{type=numeric}
\answer{Réponse 3}{\info[\itotalB1]}{type=numeric}
\answer{Réponse 4}{\info[\inba1b2]}{type=numeric}
\answer{Réponse 5}{\info[\inba2b2]}{type=numeric}
\answer{Réponse 6}{\info[\itotalB2]}{type=numeric}
\answer{Réponse 7}{\info[\itotalA1]}{type=numeric}
\answer{Réponse 8}{\info[\itotalA2]}{type=numeric}
\answer{Réponse 9}{\info[\itotal]}{type=numeric}
\answer{Réponse 10}{\info[\imrga1B1]}{type=numeric}
\answer{Réponse 11}{\info[\imrga2B1]}{type=numeric}
\answer{Réponse 12}{\info[\imrga1B2]}{type=numeric}
\answer{Réponse 13}{\info[\imrga2B2]}{type=numeric}
\answer{Réponse 14}{\info[\imrgA1b1]}{type=numeric}
\answer{Réponse 15}{\info[\imrgA2b1]}{type=numeric}
\answer{Réponse 16}{\info[\imrgA1b2]}{type=numeric}
\answer{Réponse 17}{\info[\imrgA2b2]}{type=numeric}
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
#endif
