target=vocab21 vocab22 vocab23 vocab24 vocab25

\text{data=le salaire, des cadres, d'une entreprise, le salaire, les cadres, l'entreprise,1,2,1500,4500, en Euros
la cylindrée, des automobiles, des français, la cylindrée, les automobiles, les français,1,1,4,15,En Litres
le nombre d'enfants, des familles, françaises, le nombre d'enfants, les familles, les français,1,1,0,12
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
\integer{nbval=randint(5..10)}
\text{valposs=shuffle(\valmax-\valmin)}
\integer{imode=randint(1..\nbval)}
\text{listeff=}
\integer{efftotal=0}
\text{xlistval=}
\for{i=1 to \nbval}
{
 \integer{val=\valposs[\i]+\valmin}
 \text{xlistval=wims(append item \val to \xlistval)}}
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
   \for{j=1 to \eff}
    {
     \text{listval=wims(append item \val to \listval)}
    }
   \integer{\xmin=\val<\xmin?\val}
   \integer{\xmax=\val>\xmax?\val}
  }
\integer{val=randitem(\xlistval)}
\integer{ival=position(\val,\xlistval)}
\integer{ceteff=\listeff[\ival]}
\rational{cefreq=\ceteff / \efftotal}
\text{slistval=shuffle(\listval)}
\integer{rangeval=\xmax - \xmin}
#if (defined TARGET_vocab22  || defined TARGET_vocab24 )
\text{table= On a obtenu les résultats suivants:
<table class="wimscenter wimsborder">
<caption>\cedata[11]</caption>
	 }

\integer{nn=ceil(\efftotal/10)}
\for{i=0 to \nn-1}{\text{table=\table <tr>}
  \for{j=1 to 10}{
    \text{a=item(\i*10+\j,\slistval)}
    \text{table=\table <td> \a </td>}
   }
 \text{table=\table </tr>}
 }
\text{table=\table </table>}
#endif
#if (defined TARGET_vocab21  || defined TARGET_vocab23 )
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
#if defined TARGET_vocab25
\text{xlistval=\xlistval,\cedata[10]}
\text{table=On a obtenu les résultats suivants:
<table class="wimscenter wimsborder">
	 <tr>}
\text{table=\table<th>\cedata[4] </th><th> Effectif</th></tr>}

\for{a=1 to \nbval}{
\text{table=\table <tr><td> &#91; \xlistval[\a] &#59; \xlistval[\a+1] &#91; </td><td> \listeff[\a]</td></tr>}
}
\text{table=\table </table>}
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
#if (defined TARGET_vocab21  || defined TARGET_vocab22 )
#if defined TARGET_vocab21
\title{Vocabulaire des séries quantitatives 1}
#endif
#if defined TARGET_vocab22
\title{Vocabulaire des séries quantitatives 2}
#endif
\statement{
\tintro

<ol>
<li>Quelle est l'étendue de la série ? \embed{reply1,5}</li>
<li>Quelles sont les valeurs extrêmes ? \(x_{min})=\embed{reply2,5} \(x_{max})=\embed{reply3,5}</li>
</ol>
}
\answer{étendue}{\rangeval}{type=numeric}
\answer{valeur minimale}{\xmin}{type=numeric}
\answer{valeur maximale}{\xmax}{type=numeric}

#endif
#if (defined TARGET_vocab23  || defined TARGET_vocab24 )
#if defined TARGET_vocab23
\title{Vocabulaire des séries quantitatives 3}
#endif
#if defined TARGET_vocab24
\title{Vocabulaire des séries quantitatives 4}
#endif
\statement{
\tintro

<ol>
<li>Quel est le mode de la série ? \embed{reply1,5}</li>
<li>Quelles sont les valeurs extrêmes ? \(x_{min})=\embed{reply2,5} \(x_{max})=\embed{reply3,5}</li>
</ol>
}
\answer{mode}{\valmode}{type=numeric}
\answer{valeur minimale}{\xmin}{type=numeric}
\answer{valeur maximale}{\xmax}{type=numeric}
#endif
#if defined TARGET_vocab25
\title{Vocabulaire des séries quantitatives 5}
\statement{
\tintro

<ol>
<li>Quelle est la classe modale de la série ? &#91;\embed{reply1,5};\embed{reply2,5}&#91;</li>
<li>Quelle est son amplitude ? \embed{reply3,5}</li>
</ol>
}
\answer{classe modale, borne gauche}{\valmode}{type=numeric}
\answer{classe modale, borne droite}{\valmode2}{type=numeric}
\answer{amplitude}{\rangemod}{type=numeric}
#endif
