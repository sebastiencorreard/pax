target=mediane1 mediane2 mediane3 mediane4 mediane5
\precision{100}
\integer{range=random(20..100)}
\integer{xmin=random(0..50)}
\integer{parite=random(1,2)}
\integer{nbval=2*randint(3..5)+\parite}
\text{listval=}
\for{i=1 to \nbval}
 {
 \integer{val=random(\xmin..\xmin+\range)}
 \text{listval=wims(append item \val to \listval)}
 }
\text{olistval=wims(sort numeric list \listval)}
#if defined TARGET_mediane2
\text{xlistval=\listval}
#else
\text{xlistval=\olistval}
#endif

#if (defined TARGET_mediane1  || defined TARGET_mediane2 )
\text{serie=<table class="wimscenter wimsborder"><tr>}
\for{i=1 to \nbval}
  {
  \text{serie=\serie <td>\xlistval[\i]</td>}
  }
\text{serie=\serie </tr></table>}
\real{med=\parite=1?\olistval[(\nbval+1)/2]:(\olistval[\nbval / 2]+ \olistval[\nbval / 2 +1])/2}

#else
 \text{xlistval=wims(listuniq \xlistval)}
 \integer{nbval=items(\xlistval)}
\integer{k1=randint(1,2)}
 ## k1= 1 médiane dans demie série inférieure
 ##     2 médiane dans demie série supérieure
\integer{imed=\k1=1?randint(2..\nbval/2-1):randint(\nbval/2+1..\nbval-1)}
\integer{med=\xlistval[\imed]}
 ## génération des effectifs
\text{lsteff=}
\integer{effinf=0}
\integer{effsup=0}
\for{i=1 to \nbval}
  {
   \integer{eff=random(0..20)}
   \if{\i<\imed}
     {
      \integer{effinf=\effinf+\eff}
     }
     {
      \integer{effsup=\i>\imed?\effsup+\eff}
     }
   \text{lsteff=\i=\rangmed?wims(append item med to \lsteff):wims(append item \eff to \lsteff)}
  }
\if{\effsup=\effinf}
 {
 \integer{eff=\eff+1}
 \integer{effsup=\effsup+1}
 \text{lsteff=wims(replace item number \nbval by \eff in \lsteff)}
 }
  ## choix de l'effectif de la médiane pour que ça marche
#if defined TARGET_mediane3
\integer{borne=abs(\effsup -\effinf)+1}
\integer{effmed=random(\borne..\borne+5)}
#else
\integer{effmed=\parite=1?abs(\effsup - \effinf)+1:abs(\effsup - \effinf)}
\if{\parite=2}
 {
 \real{med=\effsup>\effinf?(\med+\xlistval[\imed+1])/2:(\med+\xlistval[\imed-1])/2}
 }
#endif

\text{lsteff=wims(replace item number \imed by \effmed in \lsteff)}
\text{serie=<table class="wimscenter wimsborder"><tr><th>Valeurs</th>}
\for{i=1 to \nbval}
  {
  \text{serie=\serie <td>\xlistval[\i]</td>}
  }
\text{serie=\serie</tr><tr><th>Effectifs</th>}
\for{i=1 to \nbval}
  {
  \text{serie=\serie <td>\lsteff[\i]</td>}
  }
\text{serie=\serie </tr></table>}
#endif
#if defined TARGET_mediane1
\title{Médiane 1}
#endif
#if defined TARGET_mediane2
\title{Médiane 2}
#endif
#if defined TARGET_mediane3
\title{Médiane 3}
#endif
#if defined TARGET_mediane4
\title{Médiane 4}
#endif
#if defined TARGET_mediane5
\title{Médiane 5}
\text{data=Si la médiane d'une série est \med et qu'on rajoute une valeur égale à \med à cette série &#44; on ne change pas la médiane,1
La médiane est toujours la valeur centrale d'une série ordonnée,2
La médiane est toujours supérieure à la moyenne,2
La médiane est toujours inférieure à la moyenne,2
Si on retire la plus grande valeur d'une série&#44; on est sûr d'abaisser la médiane,2
Si on retire la plus petite valeur d'une série &#44; on est sûr d'augmenter la médiane,2
La sous-série des valeurs inférieures à la médiane et celle des valeurs supérieures à la médiane ont le même effectif total,1
On ne peut pas calculer la médiane d'une série à partir des médianes de sous-groupes,1
}
\text{cedata=randrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
Cocher la bonne réponse:
<div class="wimscenter">\quest<br>
\embed{reply1}</div>
}
\answer{}{\rep;Vrai,Faux}{type=radio}
#else
\statement{
<p>On considère la série statistique suivante:</p>
\serie
<p>Déterminer la médiane de cette série:</p>
Médiane=\embed{reply1,3}
}
\answer{Médiane}{\med}{type=numeric}
#endif
