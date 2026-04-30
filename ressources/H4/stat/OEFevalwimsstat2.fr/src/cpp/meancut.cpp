target=meancut1 meancut2 meancut3 meancut4 meancut5


\precision{100}
\text{data=le salaire, des cadres, d'une entreprise, le salaire, les cadres, l'entreprise,1,2,1500,4500, en Euros,-1,150000
la cylindrée, des automobiles, des français, la cylindrée, les automobiles, les français,1,1,4,15,En Litres,0,100
le nombre d'enfants, des familles, françaises, le nombre d'enfants, les familles, les français,1,1,0,10,,-1,30
la taille, des femmes de 30 ans, en France, la taille, les femmes de 30 ans, les françaises,1,2,150,185, En cm,50,280
le temps passé sur Internet, par les adolescents, d'une ville de province, le temps passé sur Internet, les adolescents, une ville de province,1,2,0,360, En minutes,-1,996}


\text{table=}
\text{cedata=randomrow(\data)}

\integer{n=randint(20..50)}
\text{listval=}
\integer{valmin=\cedata[9]}
\integer{xmax=\valmin}
\integer{valmax=\cedata[10]-1}
\integer{cutmin=\cedata[12]<0?\cedata[9]:\cedata[12]}
\integer{cutmax=\cedata[13]}
\integer{xmin=\valmax}
## détermination des effectifs des valeurs extrêmes
#if defined TARGET_meancut4
\integer{nbval=randint(5,6)}
\integer{choixeff=0}
\if{\nbval=5}
 {
 \text{leffdata=27,18,22
31,9,17
14,19,24
}
 \text{leff=randomrow(\leffdata)}
 \integer{ch=randint(1,2)}
 \text{leff=\ch=1?2,shuffle(\leff),1:1,shuffle(\leff),2}
 \integer{effcutmin=\ch=1?2:1}
 \integer{effcutmax=\ch=1?1:2}
 }
 {
 \text{leffdata=24,11,14,27
9,19,16,32
10,28,17,21
}
 \text{leff=randomrow(\leffdata)}
 \text{leff=2,shuffle(\leff),2}
 \integer{effcutmin=2}
 \integer{effcutmax=2}
 }

#else
\integer{nbval=randint(5..10)}
 \integer{effcutmin=1}
 \integer{effcutmax=1}
 \integer{choixeff=1}
#endif
\text{valposs=shuffle(\valmax-\valmin)}
\integer{imode=randint(1..\nbval)}
\text{listeff=}
\integer{efftotal=0}
\text{xlistval=}
\real{moy=0}
\real{moycut=0}
\for{i=1 to \nbval}
{
 \integer{val=\valposs[\i]+\valmin}
 \text{xlistval=wims(append item \val to \xlistval)}
}
\text{xlistval=wims(sort numeric list \xlistval)}
   \if{\cedata[12]>=0}
    { \text{xlistval=wims(replace item number 1 by \cutmin in \xlistval)}}
   \text{xlistval=wims(replace item number \nbval by \cutmax in \xlistval)}

   \integer{efftotal=\efftotal+\effcutmin}
   \text{listeff=wims(append item \effcutmin to \listeff)}
   \integer{val=\xlistval[1]}
   \real{moy=\moy+\val*\effcutmin}
   \if{\cedata[12]<0}
   {\real{moycut=\moycut+\val*\effcutmin}}
   \for{j=1 to \effcutmin}
   {
   \text{listval=wims(append item \val to \listval)}
   }
\for{i=2 to \nbval-1}
  {
   \integer{eff=\choixeff=0?\leff[\i]:random(5..10)}
   \integer{efftotal=\efftotal+\eff}
   \text{listeff=wims(append item \eff to \listeff)}
   \integer{val=\xlistval[\i]}
   \real{moy=\moy+\eff*\val}
   \real{moycut=\moycut+\eff*\val}
   \for{j=1 to \eff}
    {
     \text{listval=wims(append item \val to \listval)}
    }
  }
   \integer{efftotal=\efftotal+\effcutmax}
   \text{listeff=wims(append item \effcutmax to \listeff)}
   \integer{val=\xlistval[\nbval]}
   \real{moy=\moy+\val*\effcutmax}
   \for{j=1 to \effcutmax}
   {
   \text{listval=wims(append item \val to \listval)}
   }
\real{moy=\moy / \efftotal}
\real{moycut=\cedata[12]>=0?\moycut / (\efftotal-\effcutmin - \effcutmax):\moycut / (\efftotal-\effcutmax)}
\integer{val=randitem(\xlistval)}
\integer{ival=position(\val,\xlistval)}
\integer{ceteff=\listeff[\ival]}
\rational{cefreq=\ceteff / \efftotal}
\text{slistval=shuffle(\listval)}
\integer{rangeval=\xmax - \xmin}
#if defined TARGET_meancut1
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
#endif
#if (defined TARGET_meancut2 || defined TARGET_meancut4 )
\text{table= On a obtenu les résultats suivants: <table class="wimscenter wimsborder">}
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
#if defined TARGET_meancut3
\real{moy=0}
\text{xlistval=item(1..\nbval-1,\xlistval),\cedata[10],\xlistval[\nbval]}
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
#if (defined TARGET_meancut1  || defined TARGET_meancut2  || defined TARGET_meancut3  || defined TARGET_meancut4 )
#if defined TARGET_meancut1
\title{Moyenne et Moyenne élaguée 1}
\statement{
\tintro
<p>
Calculer la moyenne et la moyenne élaguée des 2 valeurs extrêmes de cette série:</p>
Moyenne = \embed{reply1,5}<br>
Moyenne élaguée = \embed{reply2,5}<br>
}
#endif
#if defined TARGET_meancut2
\title{Moyenne et Moyenne élaguée 2}
\statement{
\tintro
<p>
Calculer la moyenne et la moyenne élaguée des valeurs semblant aberrantes de cette série:</p>
Moyenne = \embed{reply1,5}<br>
Moyenne élaguée = \embed{reply2,5}<br>
}
#endif
#if defined TARGET_meancut3
\title{Moyenne et Moyenne élaguée 3}
\statement{
\tintro
<p>
Calculer la moyenne et la moyenne élaguée des valeurs extrêmes de cette série:</p>
Moyenne = \embed{reply1,5}<br>
Moyenne élaguée = \embed{reply2,5}<br>
}
#endif
#if defined TARGET_meancut4
\title{Moyenne et Moyenne élaguée 4}
\statement{
\tintro
<p>
Calculer la moyenne et la moyenne élaguée de 5% des valeurs extrêmes de cette série:</p>
Moyenne = \embed{reply1,5}<br>
Moyenne élaguée = \embed{reply2,5}<br>
}
#endif

\answer{moyenne}{\moy}{type=numeric}
\answer{moyenne}{\moycut}{type=numeric}
#endif

#if defined TARGET_meancut5
\title{Moyenne et Moyenne élaguée 5}
\text{lstrep=On ne change pas la moyenne, On obtient une moyenne supérieure, On obtient une moyenne inférieure}
\integer{rep=randint(1..3)}
\integer{xmin=random(0..4)}
\integer{xmax=random(16..20)}
\real{moy=(\xmin+\xmax)/2}
\integer{med=randint(\moy-2..\moy+2)}
\real{offset=randint(5..30)/10}
\if{\rep=2}
 {
  \real{moy=\moy+\offset}
 }
\if{\rep=3}
 {
  \real{moy=\moy-\offset}
 }
\statement{
On s'intéresse à la série des notes d'un contrôle commun de Mathématiques dans un lycée.
Pour cette série, on a les indicateurs suivants:
<ul>
<li> les valeurs extrêmes sont un \xmin et un \xmax.</li>
<li> la moyenne est de \moy.</li>
<li> la médiane est à \med.</li>
</ul>
Cocher la bonne réponse:
<div class="wimscenter"> Si on supprime les notes extrêmes,<br>
\embed{reply1}</div>
}
\answer{}{\rep;\lstrep}{type=radio}
#endif
