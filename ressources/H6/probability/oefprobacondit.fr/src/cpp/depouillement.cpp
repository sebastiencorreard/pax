target=depouillement1 depouillement2

\language{fr}
\author{Sophie, Lemaire}
\email{sophie.lemaire@universite-paris-saclay.fr}
\computeanswer{yes}
\format{html}
\precision{10000}
\keywords{conditional_probability}
\integer{n=randint(2..5)}
\integer{nb=randint(10..50)}
\real{p0=1/(\n+1)}
\text{p=wims(values \p0 for x=1 to \n)}
\real{s=1-\n*\p0}
\text{p=\p,\s}
\matrix{k=slib(stat/multinomial \n,\nb,[\p])}

\if{\k[1;1]>=1}{\text{result=<ul><li>\k[1;1] voix pour la première liste,</li>}
}
{\text{result=<ul><li>aucune voix pour la première liste,</li>}}
\text{liste=wims(values 1 for x=1 to \k[1;1])}
\for{j=2 to \n}{
  \if{\k[1;\j]>=1}
    {\text{result=\result <li> \k[1;\j] voix pour la liste \j,</li>}
     \text{liste=\liste, wims(values \j for x=1 to \k[1;\j])}}
  {\text{result=\result <li>aucune voix pour la liste \j,</li>}}
}
\if{\k[1;\n+1]>1}{\text{result=\result <li> \k[1;\n+1] votes blancs.</li></ul>}}
{\text{result=\result <li> \k[1;\n+1] vote blanc.</li></ul>}}
\text{liste=\liste, wims(values 0 for x=1 to \k[1;\n+1])}
\integer{d=randint(3..5)}
\text{depouil=slib(data/random \d,item, \liste )}
\text{present=wims(replace 0 by blanc in \depouil)}
\for{j=1 to \n}{\text{present=wims(replace \j by liste \j in \present)}}

\text{s=pari(k=Mat([\k]);nb=\nb ;dep=Mat([\depouil]);s=1;for(i=1,\d,if(dep[1,i],j=dep[1,i],j=\n+1);s=s*k[1,j]/nb
;nb=nb-1;k[1,j]=k[1,j]-1);print(s))}
\real{res=\s}
\matrix{compt=pari(k=Mat([\k]);dep=Mat([\depouil]);v=vector(\n+1,i,0);
for(i=1,\d,if(dep[1,i],j=dep[1,i],j=\n+1);v[j]=v[j]+1);print(v))}
\integer{poss=1}
\integer{rest=\d}
\for{j=1 to \n}{
  \integer{poss=\poss*binomial(\rest,\compt[1;\j])}
  \integer{rest=\rest-\compt[1;\j]}
}
\rational{prob2=\poss*\s}
\real{prob2r=\prob2}
\text{quest1 = Quelle est la probabilité pour que les \d premiers bulletins dépouillés soient dans l'ordre }
\text{quest2=<ul>}
\if{\compt[1;1]=1}{
\text{quest2=\quest2 <li> un bulletin pour la liste 1</li>}}
if{\compt[1;1]=0}{
text{quest2=<ul> <li> aucun bulletin pour la liste 1</li>}}
\if{\compt[1;1]>1}{
\text{quest2=\quest2 <li> \compt[1;1] bulletins pour la liste 1</li>}}
\for{j=2 to \n}{
  \if{\compt[1;\j]>=2}
    {\text{quest2=\quest2 <li> \compt[1;\j] bulletins pour la liste \j</li>}}
\if{\compt[1;\j]=1}
    {\text{quest2=\quest2 <li> un bulletin pour la liste \j</li>}}}
\if{\compt[1;\n+1]>1}{\text{quest2=\quest2 <li> \compt[1;\n+1] bulletins blancs</li>}}
\if{\compt[1;\n+1]=1}{\text{quest2=\quest2 <li> un bulletin blanc</li>}}
\text{quest2=\quest2 </ul>}
\text{consigne=Donner votre réponse sous forme d'une fraction rationnelle.}
#if defined TARGET_depouillement1 
\title{Dépouillement d'un vote I}
\steps{reply1}
#else
\title{Dépouillement d'un vote II}
\description{exercice comportant deux questions}
\steps{reply1
reply2}
#endif
\statement{Lors d'un vote dans une entreprise, les électeurs devaient choisir entre \n listes.
 Sur les \nb bulletins, il y a : \result
#if defined TARGET_depouillement1 
 <div class="wims_question">\quest1
<div class="wimscenter"><span style="color:#000080;">\present</span> ?</div>
</div>
#else
\if{\step>=1}{
<div class="wims_question">
 1- \quest1
<div class="wimscenter"><span style="color:#000080;">\present</span> ?</div>
}
\if{\step>=2}{<p class="oef_indgood">Bonne réponse ! La probabilité d'obtenir ce
 dépouillement est \s\(\simeq\)\res.</p>
 2- Déterminer la probabilité pour que parmi les \d premiers bulletins dépouillés, il y ait en tout \quest2
}
</div>
#endif
<div class="wims_instruction">\consigne</div>
}
#if defined TARGET_depouillement1 
\answer{Résultat (sous forme d'une fraction)}{\s}{type=formal}
\feedback{1=1}{<div class="oef_indgood">La probabilité d'obtenir ce dépouillement
 est \s\(\simeq\)\res.</div>}
#else
\answer{Question 1 (sous forme d'une fraction)}{\s}{type=formal}
\answer{Question 2 (sous forme d'une fraction)}{\prob2}{type=formal}
\feedback{\step>=2}{<div class="oef_indgood">La probabilité pour que parmi les \d premiers bulletins
 dépouillés, il y ait \quest2 est égale à \prob2\(\simeq\)\prob2r</div>}
\hint{\if{\step=1}{Il n'y a pas d'indication pour la question 1 de l'exercice}
\if{\step=2}{Commencer par regarder si la probabilité que les \d premiers bulletins soient
<span style="color:#000080;"> \present</span> dépend de l'ordre dans lequel ces bulletins
 sont apparus.}}
#endif