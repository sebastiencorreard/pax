target=mean1 mean2 mean3 mean4 mean5
\precision{100}
\text{data=le salaire, des cadres, d'une entreprise, le salaire, les cadres, l'entreprise,1,2,1500,4500, en Euros
la cylindrée, des automobiles, des français, la cylindrée, les automobiles, les français,1,1,4,15,En Chevaux
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
#if defined TARGET_mean5 
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
\real{moy=\moy / \efftotal}
\integer{val=randitem(\xlistval)}
\integer{ival=position(\val,\xlistval)}
\integer{ceteff=\listeff[\ival]}
\rational{cefreq=\ceteff / \efftotal}
\text{slistval=shuffle(\listval)}
\integer{rangeval=\xmax - \xmin}
#if defined TARGET_mean2 
\text{table= On a obtenu les résultats suivants:<table class="wimscenter wimsborder">
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
#endif
#if defined TARGET_mean1 
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
\text{table=\table </tr></table>}
#endif
#if defined TARGET_mean3 
\real{moy=0}
\text{xlistval=\xlistval,\cedata[10]}
\text{table=On a obtenu les résultats suivants:
<table class="wimscenter wimsborder">
	 <tr>}
\text{table=\table<th>\cedata[4] </th><th> Effectif</th></tr>}

\for{a=1 to \nbval}{
\text{table=\table <tr><td> &#91; \xlistval[\a] &#59; \xlistval[\a+1] &#91; </td><td> \listeff[\a]</td></tr>}
\real{moy=\moy+(\xlistval[\a]+\xlistval[\a+1])/2*\listeff[\a]}
}
\text{table=\table </table>}
\real{moy=\moy / \efftotal}
\text{valmode2=\xlistval[\imode+1]}
\real{rangemod=\xlistval[\imode+1]-\xlistval[\imode]}
#endif
#if defined TARGET_mean5 
\integer{indx=random(1..\nbval)}
\integer{xval=\listeff[\indx]}
\integer{effpartial=\efftotal-\xval}
\if{\effpartial<20}
 {
 \integer{xval=20-\effpartial}
 \integer{efftotal=20}
 }
 {
  \if{\effpartial<40}
  {
   \integer{xval=40-\effpartial}
   \integer{efftotal=40}
  }
  {
   \integer{xval=50-\effpartial}
   \integer{efftotal=50}
  }
 }
\text{listeff=wims(replace item number \indx by \xval in \listeff)}
\integer{moy=0}
\for{i=1 to 5}
 {
 \integer{moy=\moy+\xlistval[\i]*\listeff[\i]}
 }
\real{moy=\moy / \efftotal}

\text{listeff=wims(replace item number \indx by x in \listeff)}
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
\text{table=\table</tr></table>}
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
#if (defined TARGET_mean1  || defined TARGET_mean2  || defined TARGET_mean3 )
#if defined TARGET_mean1 
\title{Moyenne 1}
#endif
#if defined TARGET_mean2 
\title{Moyenne 2}
#endif
#if defined TARGET_mean3 
\title{Moyenne 3}
#endif
\statement{
\tintro
<p>
Calculer la moyenne de cette série:</p>
Moyenne = \embed{reply1,5}
}
\answer{moyenne}{\moy}{type=numeric}

#endif
#if defined TARGET_mean4 
\title{Moyenne 4}
\text{vals=\xmin,\xmax}
\integer{x1=random(\xmin..\xmax)}
\text{vals=wims(append item \x1 to \vals)}
\integer{x2=random(\xmin..\xmax)}
\text{vals=wims(append item \x2 to \vals)}
\integer{x3=random(\xmin..\xmax)}
\text{vals=wims(append item \x3 to \vals)}
\integer{moy=\xmin+\xmax+\x1+\x2+\x3}

\real{moy=\moy / 5}
\integer{val1=item(1,wims(sort list \vals))}
\integer{val2=item(5,wims(sort list \vals))}
\text{trace=\vals: \val1, \val2, x1 \x1, x2 \x2 x3 \x3
}
\statement{
Inventer une série de 5 valeurs telle que:
<ol><li> la valeur minimale est \xmin</li>
<li> la valeur maximale est \xmax</li>
<li> la moyenne est \moy</li>
</ol>
\embed{reply1,5},\embed{reply2,5},\embed{reply3,5},\embed{reply4,5},\embed{reply5,5}
}
\answer{V1}{\v1}{type=numeric}
\answer{V2}{\v2}{type=numeric}
\answer{V3}{\v3}{type=numeric}
\answer{V4}{\v4}{type=numeric}
\answer{V5}{\v5}{type=numeric}
condition{}{(\reply1+\reply2+\reply3+\reply4+\reply5)/5=\moy and item(1, wims(sort list (\reply1,\reply2,\reply3,\reply4,\reply5)))=\xmin and item(5, wims(sort list (\reply1,\reply2,\reply3,\reply4,\reply5)))=\xmax}
\condition{}{(\reply1+\reply2+\reply3+\reply4+\reply5)/5=\moy and \reply1 >= \xmin and \reply2 >=\xmin and \reply3 >= \xmin and \reply4 >= \xmin and \reply5 >= \xmin
and \reply1 <= \xmax and \reply2 <=\xmax and \reply3 <= \xmax and \reply4 <= \xmax and \reply5 <= \xmax
and (\reply1 = \xmin or \reply2 =\xmin or \reply3 = \xmin or \reply4 = \xmin or \reply5 = \xmin)
and (\reply1 = \xmax or \reply2 =\xmax or \reply3 = \xmax or \reply4 = \xmax or \reply5 = \xmax)
}
#endif
#if defined TARGET_mean5 
\title{Moyenne 5}
\statement{
\tintro
<p>
Quelle doit être la valeur de \(x) pour que la moyenne de la série soit \moy ?</p>
Valeur de \(x):\embed{reply1,5}
}
\answer{Valeur de x}{\xval}{type=numeric}
#endif
