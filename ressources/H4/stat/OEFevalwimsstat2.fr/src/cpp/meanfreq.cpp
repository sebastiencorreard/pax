target=meanfreq1 meanfreq2 meanfreq3 meanfreq4 meanfreq5
\precision{100}
\text{data=le salaire, des cadres, d'une entreprise, le salaire, les cadres, l'entreprise,1,2,1500,4500, en Euros
la cylindrée, des automobiles, des français, la cylindrée, les automobiles, les français,1,1,4,15,En Litres
le nombre d'enfants, des familles, françaises, le nombre d'enfants, les familles, les français,1,1,0,12,
la taille, des femmes de 30 ans, en France, la taille, les femmes de 30 ans, les françaises,1,2,150,185, En cm
le temps passé sur Internet, par les adolescents, d'une ville de province, le temps passé sur Internet, les adolescents, une ville de province,1,2,0,360, En minutes}


\text{table=}
\text{cedata=randomrow(\data)}

\integer{n=randint(20..50)}
\text{listval=}
\integer{valmin=\cedata[9]}
\integer{xmax=\valmin}
\integer{valmax=\cedata[10]-1}
\integer{xmin=\valmax}
#if defined TARGET_meanfreq5
\integer{nbval=5}
#else
\integer{nbval=randint(5..10)}
#endif
\text{valposs=shuffle(\valmax-\valmin)}
\integer{imode=randint(1..\nbval)}
\text{listeff=}
\integer{efftotal=0}
\text{xlistval=}
\real{moy=0}
\for{i=1 to \nbval}
{
 \integer{val=\valposs[\i]+\valmin}
 \text{xlistval=wims(append item \val to \xlistval)}
}
\text{xlistval=wims(sort numeric list \xlistval)}
\for{i=1 to \nbval}
  {
   \if{\i=\imode}{\integer{eff=random(6..10)}
                   \integer{valmode=\xlistval[\i]}
                  }
      {\integer{eff=random(1..5)}}
   \integer{efftotal=\efftotal+\eff}
   \text{listeff=wims(append item \eff to \listeff)}
   \integer{val=\xlistval[\i]}
   \real{moy=\moy+\eff*\val}
   \for{j=1 to \eff}
    {
     \text{listval=wims(append item \val to \listval)}
    }
   \integer{\xmin=\val<\xmin?\val}
   \integer{\xmax=\val>\xmax?\val}
  }
\text{lstfreq=}
\text{lstfreqcum=}
\real{freqcum=0}
\for{i=1 to \nbval}
 {
 \integer{f=\listeff[\i]*100/\efftotal}
 \real{f=\f/100}
 \text{lstfreq=wims(append item \f to \lstfreq)}
 \real{freqcum=\freqcum+\f}
 \text{lstfreqcum=wims(append item \freqcum to \lstfreqcum)}

 }
\real{moy=\moy / \efftotal}
\integer{val=randitem(\xlistval)}
\integer{ival=position(\val,\xlistval)}
\integer{ceteff=\listeff[\ival]}
\rational{cefreq=\ceteff / \efftotal}
\text{slistval=shuffle(\listval)}
\integer{rangeval=\xmax - \xmin}

#if defined TARGET_meanfreq1
\text{table= On a obtenu les résultats suivants:
<table class="wimscenter wimsborder">}
\text{table=\table<tr><th> \cedata[4] </th>}
\for{j=1 to \nbval}
{
 \text{table=\table<td> \xlistval[\j] </td>}
}
\text{table=\table</tr><tr><th>Fréquence</th>}
\for{j=1 to \nbval}
{
 \text{table=\table<td> \lstfreq[\j] </td>}
}
\text{table=\table</tr></table>}
\text{quest=Calculer la moyenne de cette série.}
#endif

#if defined TARGET_meanfreq2
\text{table= On a obtenu les résultats suivants:
<table class="wimscenter wimsborder">
<caption>\cedata[11]</caption>
	 }

\integer{nn=ceil(\efftotal/10)}
\for{i=0 to \nn-1}
 {\text{table=\table <tr>}
 \for{j=1 to 10}
   {
    \text{a=item(\i*10+\j,\slistval)}
    \text{table=\table <td> \a </td>}
   }
 \text{table=\table </tr>}
 }
\text{table=\table </table>}
\text{table=\table<table class="wimscenter wimsborder"><tr><th> \cedata[4] </th>}
\for{j=1 to \nbval}
{
 \text{table=\table<td> \xlistval[\j] </td>}
}
\text{table=\table</tr><tr><th>Fréquence</th>}
\text{quest=Remplir le tableau des fréquences (valeurs décimales arrondies au centième) et calculer la moyenne de cette série.}
#endif

#if defined TARGET_meanfreq3
\text{table= On a obtenu les résultats suivants:
<table class="wimscenter wimsborder">}
\text{table=\table<tr><th> \cedata[4] </th>}
\for{j=1 to \nbval}
{
 \text{table=\table<td> \xlistval[\j] </td>}
}
\text{table=\table</tr><tr><th>Effectif</th>}
\for{j=1 to \nbval}
{
 \text{table=\table<td> \listeff[\j] </td>}
}
\text{table=\table </tr><tr><th>Fréquence</th>}
#endif

#if defined TARGET_meanfreq4
\real{moy=0}
\text{xlistval=\xlistval,\cedata[10]}
\text{table=On a obtenu les résultats suivants:}
\for{a=1 to \nbval}{
\real{moy=\moy+(\xlistval[\a]+\xlistval[\a+1])/2*\listeff[\a]}
}
\real{moy=\moy / \efftotal}
\text{valmode2=\xlistval[\imode+1]}
\real{rangemod=\xlistval[\imode+1]-\xlistval[\imode]}
#endif

#if defined TARGET_meanfreq5
\text{lstind=shuffle(5)}
\integer{indx=\lstind[1]}
\integer{indy=\lstind[2]}
\integer{xval=\listeff[\indx]}
\integer{yval=\listeff[\indy]}
\integer{effpartial=\efftotal-\xval-\yval}
\if{\effpartial<20}
 {
 \integer{xval=randint(0..20-\effpartial)}
 \integer{yval=20-\effpartial-\xval}
 \integer{efftotal=20}
 }
 {
  \if{\effpartial<40}
  {
 \integer{xval=randint(0..40-\effpartial)}
 \integer{yval=40-\effpartial-\xval}
   \integer{efftotal=40}
  }
  {
 \integer{xval=randint(0..50-\effpartial)}
 \integer{yval=50-\effpartial-\xval}
   \integer{xval=50-\effpartial}
   \integer{efftotal=50}
  }
 }
\text{lstfreq=}
\text{lstfreqcum=}
\real{freqcum=0}
\text{listeff=wims(replace item number \indx by \xval in \listeff)}
\text{listeff=wims(replace item number \indy by \yval in \listeff)}
\integer{moy=0}
\for{i=1 to \nbval}
 {
 \integer{f=\listeff[\i]*100/\efftotal}
 \real{f=\f/100}
 \text{lstfreq=wims(append item \f to \lstfreq)}
 \real{freqcum=\freqcum+\f}
 \text{lstfreqcum=wims(append item \freqcum to \lstfreqcum)}
 \integer{moy=\moy+\xlistval[\i]*\listeff[\i]}
 }
\real{moy=\moy / \efftotal}

\text{lstfreq=wims(replace item number \indx by x in \lstfreq)}
\text{lstfreq=wims(replace item number \indy by y in \lstfreq)}
\integer{xfreq=\xval*100 /\efftotal}
\real{xfreq=\xfreq / 100}
\integer{yfreq=\yval*100 /\efftotal}
\real{yfreq=\yfreq / 100}
\text{table= On a obtenu les résultats suivants:
<table class="wimscenter wimsborder">}
\text{table=\table<tr><th> \cedata[4] </th>}
\for{j=1 to \nbval}
{
 \text{table=\table<td> \xlistval[\j] </td>}
}
\text{table=\table</tr><tr><th>Fréquence</th>}
\for{j=1 to \nbval}
{
 \text{table=\table<td> \lstfreq[\j] </td>}
}
\text{table=\table </tr></table>}
#endif

\text{tintro=On étudie \cedata[1] \cedata[2] \cedata[3].

\table
}
\text{pop=\cedata[6]}
\text{car=\cedata[4]}
\text{indiv=\cedata[5]}
\integer{typecar=\cedata[7]}
\integer{typecar2=\cedata[8]}

\text{lstrep=\pop,\car,\indiv}
\text{size=100x40x1}

#if defined TARGET_meanfreq1
\title{Moyenne  et fréquences 1}
\statement{
\tintro

<p>
Calculer la moyenne de cette série :</p>
Moyenne = \embed{reply1,5}
}
\answer{moyenne}{\moy}{type=numeric}
#endif

#if (defined TARGET_meanfreq4  || defined TARGET_meanfreq2  || defined TARGET_meanfreq3 )
#if defined TARGET_meanfreq2
\title{Moyenne  et fréquences 2}
#endif
#if defined TARGET_meanfreq3
\title{Moyenne  et fréquences 3}
#endif
#if defined TARGET_meanfreq4
\title{Moyenne  et fréquences 4}
#endif
\text{mstep=wims(makelist r x for x=1 to \nbval+1)}
\text{mstep=wims(nospace \mstep)}
\steps{\mstep}
\statement{
\tintro
#if defined TARGET_meanfreq4
  <table class="wimscenter wimsborder">
   <tr>
    <th>\cedata[4] </th><th> Effectif</th><th> Fréquence</th>
   </tr>
\for{jj=2 to \nbval+1}
{
<tr><td> &#91; \xlistval[\jj-1] &#59; \xlistval[\jj] &#91; </td><td> \listeff[\jj-1]</td>
<td> \embed{reply\jj,4} </td></tr>
}
 </table>
#else
\for{jj=2 to \nbval+1}
{
<td> \embed{reply\jj,4} </td>
}
</tr>
</table>
#endif


<p>
Remplir le tableau des fréquences (valeurs décimales arrondies au centième)
et calculer la moyenne de cette série :</p>
Moyenne = \embed{reply1,5}
}
\answer{moyenne}{\moy}{type=numeric}
\answer{f1}{\lstfreq[1]}{type=numeric}
\answer{f2}{\lstfreq[2]}{type=numeric}
\answer{f3}{\lstfreq[3]}{type=numeric}
\answer{f4}{\lstfreq[4]}{type=numeric}
\answer{f5}{\lstfreq[5]}{type=numeric}
\answer{f6}{\lstfreq[6]}{type=numeric}
\answer{f7}{\lstfreq[7]}{type=numeric}
\answer{f8}{\lstfreq[8]}{type=numeric}
\answer{f9}{\lstfreq[9]}{type=numeric}
\answer{f10}{\lstfreq[10]}{type=numeric}
#endif

#if defined TARGET_meanfreq5
\title{Moyenne et fréquences 5}
\statement{
\tintro
<p>
Quelle doivent être les valeurs de \(x) et \(y) pour que la moyenne de la série soit \moy ?</p>
<label for="reply1">Valeur de \(x):</label> \embed{reply1,5}<br>
<label for="reply2">Valeur de \(y):</label> \embed{reply2,5}<br>
}
\answer{Valeur de x}{\xfreq}{type=numeric}
\answer{Valeur de y}{\yfreq}{type=numeric}
#endif
