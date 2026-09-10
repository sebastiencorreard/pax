target=quantile1 quantile2 quantile3 quantile4 quantile5
#include "author.inc"
#include "lang_titles.inc"
\precision{1000}
\text{thint=Le premier décile \(D_1\) et le neuvième décile \(D_9\) se calculent de la
même façon que le premier quartile \(Q_1\) et le troisième quartile \(Q_3\), en substituant
 au partage en 4 parties égales un partage en 10 parties égales.}
\text{thelp=On rappelle la définition du premier décile noté \(D_1\) et du neuvième décile noté \(D_9\):<br>
Pour une série statistique ordonnée dans l'ordre croissant, d'effectif total \(n\),<br>
\(D_1\) est la valeur de la série dont le rang est le plus petit entier supérieur ou égal à \(\frac{n}{10}\),<br>
\(D_9\) est la valeur de la série dont le rang est le plus petit entier supérieur ou égal à \(\frac{9n}{10}\)}

#if (defined TARGET_quantile1 || defined TARGET_quantile4 )
\integer{xmin=randint(5..50)}
\integer{xmax=\xmin+randint(10..50)}
\text{lstval=wims(makelist x for x=\xmin to \xmax)}
\text{ind=shuffle(\xmax-\xmin)}
\text{ind=item(1..7,\ind)}
\text{ind=wims(sort numeric list \ind)}
\integer{xmin=\lstval[\ind[1]]}
\integer{D1=\lstval[\ind[2]]}
\integer{Q1=\lstval[\ind[3]]}
\integer{med=\lstval[\ind[4]]}
\integer{Q3=\lstval[\ind[5]]}
\integer{D9=\lstval[\ind[6]]}
\integer{xmax=\lstval[\ind[7]]}
\integer{intQ=\Q3-\Q1}
\integer{intD=\D9-\D1}
\integer{etendue=\xmax-\xmin}

# if defined TARGET_quantile1
\text{data=valeur minimale=\xmin,valeur maximale=\xmax,étendue=\etendue,
Q1=\Q1,Q3=\Q3,écart inter-quartile=\intQ,
D1=\D1,D9=\D9,écart inter-décile=\intD,médiane=\med}
\text{ind1=shuffle(3)}
\text{cedata1=\data[\ind1[1]],\data[\ind1[2]]}
\text{ind2=shuffle(3)}
\text{cedata2=\data[\ind2[1]+3],\data[\ind2[2]+3]}
\text{ind3=shuffle(3)}
\text{cedata3=\data[\ind3[1]+6],\data[\ind3[2]+6]}
\text{cedata4=médiane=\med}
\text{cedata=shuffle(\cedata1,\cedata2,\cedata3,\cedata4)}
\text{quest=\data[\ind1[3]]}
\text{quest=wims(replace internal = by , in \quest)}
\text{quest1=\quest[1]}
\integer{rep1=\quest[2]}
\text{quest=\data[\ind2[3]+3]}
\text{quest=wims(replace internal = by , in \quest)}
\text{quest2=\quest[1]}
\integer{rep2=\quest[2]}
\text{quest=\data[\ind3[3]+6]}
\text{quest=wims(replace internal = by , in \quest)}
\text{quest3=\quest[1]}
\integer{rep3=\quest[2]}

\statement{<p>
On considère une série statistique dont on connaît les indicateurs suivants:
</p>
<table class="wimscenter wimsborder">
<tr><td>\cedata[1]</td><td>\cedata[2]</td><td>\cedata[3]</td><td>\cedata[4]</td></tr>
<tr><td>\cedata[5]</td><td>\cedata[6]</td><td>\cedata[7]</td><td>&nbsp;</td></tr>
</table>
<p>
Calculer les indicateurs manquants:
</p>
<ol>
<li><label for="reply1">\quest1= </label>\embed{reply1,4}</li>
<li><label for="reply2">\quest2= </label>\embed{reply2,4}</li>
<li><label for="reply3">\quest3= </label>\embed{reply3,4}</li>
</ol>
}
\hint{\thint}
\help{\thelp}
\answer{\quest1}{\rep1}{type=numeric}
\answer{\quest2}{\rep2}{type=numeric}
\answer{\quest3}{\rep3}{type=numeric}
# else
\text{q11=moins,plus,}
\text{q12=inférieures ou égales,strictement supérieures}
\text{q21=plus,moins}
\text{q22=strictement supérieures,inférieures ou égales}
\integer{k1=randint(1,2)}
\integer{k2=randint(1,2)}
\text{rep4=25,75}
 \statement{<p>
On considère une série statistique dont on connaît les indicateurs suivants:
</p>
<ul>
<li>Médiane = \med </li>
<li>Premier quartile = \Q1</li>
<li>Troisième quartile = \Q3</li>
<li>Premier décile = \D1 </li>
<li>Neuvième décile = \D9</li>
</ul>
<p>
Compléter les phrases suivantes:
</p>
<ol>
<li> <label for="reply1">Au \q11[\k1]</label> \embed{reply1,3} % des valeurs
  sont \q12[\k1] à \med.</li>
<li> <label for="reply2">Environ la moitié des valeurs se situe entre</label> \embed{reply2,3} <label for="reply3">et</label> \embed{reply3,3}.</li>
<li> <label for="reply4">Au \q21[\k2]</label> \embed{reply4,3} % des valeurs
  se situent \q22[\k2] de \Q3.</li>
</ol>
}
\hint{\thint}
\help{\thelp}
\answer{med}{50}{type=numeric}
\answer{moitié inf}{\Q1}{type=numeric}
\answer{moitié sup}{\Q3}{type=numeric}
\answer{Q3}{\rep4[\k2]}{type=numeric}
# endif
#endif
#if (defined TARGET_quantile2 || defined TARGET_quantile3 )
\text{tclasses=}
\text{tclassem=}
\text{tclassef=}

\integer{range=random(20..100)}
\integer{xmin=random(0..20)}
\integer{parite=random(1,0)}

\integer{nbval=2*randint(4..7)+\parite}
\text{listval=wims(makelist x for x=\xmin to \xmin+\range)}
\text{ind=shuffle(\range)}
\text{ind=item(1..\nbval,\ind)}
\text{listval=item(\ind,\listval)}
\text{olistval=wims(sort numeric list \listval)}
\text{xlistval=\olistval}
\integer{xmin=\xlistval[1]}

\real{med=\parite=1?\olistval[(\nbval+1)/2]:(\olistval[\nbval / 2]+ \olistval[\nbval / 2 +1])/2}

#if defined TARGET_quantile2B
\text{lsteff=wims(makelist 1 for x=1 to \nbval)}
\integer{efftotal=\nbval}
\text{serie=<table class="wimsborder"><tr>}
\for{i=1 to \nbval}{
  \text{serie=\serie <td>\xlistval[\i]</td>}
}
\text{serie=\serie </tr></table>}
# else
%% génération des effectifs
\integer{efftotal=randint(100,200,400,500)}
# include "lsteff.inc"

#   if defined TARGET_quantile2
\text{serie=<table class="wimsborder"><tr><th>Valeur</th>}
\for{i=1 to \nbval}{
  \text{serie=\serie <td>\xlistval[\i]</td>}
}
\text{serie=\serie </tr><tr><th>Effectif</th>}
\for{i=1 to \nbval}{
  \text{serie=\serie <td>\lsteff[\i]</td>}
}

\text{serie=\serie </tr></table>}
#    else
\text{tclasses=classes des }
\text{tclassem=classe du }
\text{tclassef=classe de la }
\integer{val=\xlistval[-1]+10}
\text{xlistval=wims(append item \val to \xlistval)}
\text{serie=<table class="wimsborder"><tr><th>Classe</th>}
\for{i=1 to \nbval}{
  \text{serie=\serie <td>&#91; \xlistval[\i]; \xlistval[\i+1] &#91;</td>}
  }
\text{serie=\serie </tr><tr><th>Effectif</th>}
\for{i=1 to \nbval}{
  \text{serie=\serie <td>\lsteff[\i]</td>}
}

\text{serie=\serie </tr></table>}
#   endif
# endif

%% Détermination des réponses
\integer{med=-1}
\integer{Q1=-1}
\integer{Q3=-1}
\integer{D1=-1}
\integer{D9=-1}
\text{lstecc=}
\integer{ecc=0}
\for{i=1 to \nbval}{
  \integer{ecc=\ecc+\lsteff[\i]}
  \if{\ecc>=\efftotal/10 and \D1=-1}{
    \integer{D1=\xlistval[\i]}
    \integer{D1d=\xlistval[\i+1]}
  }
  \if{\ecc>=\efftotal/4 and \Q1=-1}{
    \integer{Q1=\xlistval[\i]}
    \integer{Q1d=\xlistval[\i+1]}
  }
  \if{\ecc>=3*\efftotal/4 and \Q3=-1}{
    \integer{Q3=\xlistval[\i]}
    \integer{Q3d=\xlistval[\i+1]}
  }
  \if{\ecc>=9*\efftotal/10 and \D9=-1}{
    \integer{D9=\xlistval[\i]}
    \integer{D9d=\xlistval[\i+1]}
  }
  \if{\ecc>=\efftotal/2 and \med=-1}{
    \integer{med=\ecc=\efftotal/2?(\xlistval[\i]+\xlistval[\i+1])/2:\xlistval[\i]}
    \integer{medg=\xlistval[\i]}
    \integer{medd=\xlistval[\i+1]}
  }
}
\statement{
On considère la série statistique suivante:
\serie
# if defined TARGET_quantile3
<p>Déterminer les classes des indicateurs suivants de cette série:</p>
<ol>
<li> <label for="reply1">Classe de la médiane= &#91;</label>\embed{reply1,3}; \embed{reply2,3} &#91; </li>
<li> <label for="reply3">Classe du premier quartile: Q1=&#91; </label>\embed{reply3,3};\embed{reply4,3} &#91;</li>
<li> <label for="reply5">Classe du troisième quartile: Q3=&#91; </label>\embed{reply5,3};\embed{reply6,3} &#91;</li>
</ol>
}
\answer{Médiane gauche}{\medg}{type=numeric}
\answer{Médiane droite}{\medd}{type=numeric}
\answer{Q1 gauche}{\Q1}{type=numeric}
\answer{Q1 droite}{\Q1d}{type=numeric}
\answer{Q3 gauche}{\Q3}{type=numeric}
\answer{Q3 droite}{\Q3d}{type=numeric}
# else
<p>Déterminer les indicateurs suivants de cette série:</p>
<ol>
<li> <label for="reply1">Médiane= </label>\embed{reply1,3}</li>
<li> <label for="reply2">Premier quartile: Q1=</label>\embed{reply2,3}</li>
<li> <label for="reply3">Troisième quartile: Q3=</label>\embed{reply3,3}</li>
<li> <label for="reply4">Premier décile: D1=</label>\embed{reply4,3}</li>
<li> <label for="reply5">Neuvième décile: D9=</label>\embed{reply5,3}</li>
</ol>
}
\hint{\thint}
\answer{Médiane}{\med}{type=numeric}
\answer{Q1}{\Q1}{type=numeric}
\answer{Q3}{\Q3}{type=numeric}
\answer{D1}{\D1}{type=numeric}
\answer{D9}{\D9}{type=numeric}
# endif
#endif
#if defined TARGET_quantile5
\integer{k=randint(3..8)*100}
\text{val=}
\for{i=1 to 16}{
  \integer{v=\k*\i}
  \text{val=wims(append item \v to \val)}
}
\text{al=\val[1],\val[2],\val[3],\val[5],\val[10]}
\text{bl=\val[2],\val[3],\val[5],\val[6],\val[16]}
\matrix{data=La moitié des valeurs ne dépasse pas \val[3],1
Environ 50 % des valeurs sont supérieures à \val[5],2
Le quart supérieur des valeurs a une amplitude de \val[10],2
Le quart des valeurs est égal à au moins 5 fois la valeur minimale,1
L'écart interquartile est de \val[3],3
Environ la moitié des valeurs se situe entre \val[2] et \val[5],3
Environ une valeur sur quatre est inférieure à \val[2],1
Environ 75% des valeurs sont au moins égales à \val[3],2
Au moins 50% des valeurs sont supérieures ou égales à \val[3],3
La valeur maximale est au moins trois fois plus élevée que 50% des valeurs de la série,3}
\integer{cas=randint(1,2)}
\text{q1=\data[\cas;1]}
\text{r1=\data[\cas;2]}
\text{r1=\r1=3?1,2}
\text{q2=\data[2+\cas;1]}
\text{r2=\data[2+\cas;2]}
\text{r2=\r2=3?1,2}
\text{q3=\data[4+\cas;1]}
\text{r3=\data[4+\cas;2]}
\text{r3=\r3=3?1,2}
\text{q4=\data[6+\cas;1]}
\text{r4=\data[6+\cas;2]}
\text{r4=\r4=3?1,2}
\text{q5=\data[8+\cas;1]}
\text{r5=\data[8+\cas;2]}
\text{r5=\r5=3?1,2}

\statement{<p>
On a résumé deux séries statistiques \(A\) et \(B\) en cinq nombres: min, \(Q_1\),Med,\(Q_3\),max:
</p>
<div class="wimscenter"> série \(A\): \al </div>
<div class="wimscenter"> série \(B\): \bl </div>
<p>
Indiquer pour quelle(s) série(s) chacune des affirmations suivantes est vraisemblable:
</p>
<ol>
<li> \q1:\embed{reply1}</li>
<li> \q2:\embed{reply2}</li>
<li> \q3:\embed{reply3}</li>
<li> \q4:\embed{reply4}</li>
<li> \q5:\embed{reply5}</li>
</ol>
}
\answer{Affirmation 1}{\r1;Série \(A\),Série \(B\)}{type=checkbox}
\answer{Affirmation 2}{\r2;Série \(A\),Série \(B\)}{type=checkbox}
\answer{Affirmation 3}{\r3;Série \(A\),Série \(B\)}{type=checkbox}
\answer{Affirmation 4}{\r4;Série \(A\),Série \(B\)}{type=checkbox}
\answer{Affirmation 5}{\r5;Série \(A\),Série \(B\)}{type=checkbox}
#endif
