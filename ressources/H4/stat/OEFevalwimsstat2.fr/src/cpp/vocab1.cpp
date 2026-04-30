target=vocab11 vocab12 vocab13 vocab14 vocab15

\text{data=le salaire, des cadres, d'une entreprise, le salaire, les cadres de l'entreprise, l'entreprise,1,2,1500,4500, en Euros
la cylindrée, des automobiles, des français, la cylindrée, les automobiles des français, les français,1,1,4,15,En Litres
le nombre d'enfants, des familles, en France, le nombre d'enfants, les familles en France, les français,1,1,0,12
la taille, des femmes de 30 ans, en France, la taille, les femmes de 30 ans en France, les françaises,1,2,150,185, En cm
le temps passé sur Internet, par les adolescents, d'une ville de province, le temps passé sur Internet, les adolescents d'une ville de province, une ville de province,1,2,0,360, En minutes}

#if (defined TARGET_vocab11 || defined TARGET_vocab12 )
\text{data=\data
la couleur des yeux, des élèves, du lycée, la couleur des yeux, les élèves du lycée, un lycée,2,1
le sport pratiqué, par les jeunes, d'un lycée de Nice, le sport pratiqué, les jeunes d'un lycée de Nice, un lycée de Nice,2,1
l'émission favorite, des pensionnaires, d'une maison de retraite,l'émission favorite,les pensionnaires d'une maison de retraite, la maison de retraite,2,1}
#endif

\text{table=}
\text{cedata=randomrow(\data)}

#if(defined TARGET_vocab14  || defined TARGET_vocab15 )
\integer{n=randint(20..50)}
\text{listval=}
\integer{valmin=\cedata[9]}
\integer{xmax=\valmin}
\integer{valmax=\cedata[10]}
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
\text{table= On a obtenu les résultats suivants:
<table class="wimscenter wimsborder">
<caption>\cedata[11]</caption>
	 }

\integer{nn=ceil(\efftotal/10)}
\for{i=0 to \nn-1}
 {\text{table=\table <tr>}
 \for{j=1 to 10}
 {\text{a=item(\i*10+\j,\slistval)}
\text{table=\table <td> \a </td>}
 }
\text{table=\table </tr>}
}
\text{table=\table </table>}

#endif

\text{tintro=On étudie \cedata[1] \cedata[2] \cedata[3].

\table
}
\text{pop=\cedata[5]}
\text{car=\cedata[4]}
\text{indiv=\cedata[6]}
\integer{typecar=\cedata[7]}
\integer{typecar2=\cedata[8]}

\text{lstrep=\pop,\car,\indiv}
\text{size=170x40x1}
#if defined TARGET_vocab11 
\title{Vocabulaire des séries 1}
\statement{
\tintro

<ol>
<li>Quelle est la population étudiée ? \embed{reply1,\size}</li>
<li>Quel est le caractère étudié ? \embed{reply2,\size}</li>
</ol>
}
\answer{population}{\pop;\lstrep}{type=clickfill}{option=shuffle}
\answer{caractère}{\car;\lstrep}{type=clickfill}{option=shuffle}

#endif
#if defined TARGET_vocab12 
\title{Vocabulaire des séries 2}
\statement{
\tintro

Le caractère étudié est-il quantitatif ou qualitatif?
\embed{reply1}
}
\answer{caractère}{\typecar;Quantitatif,Qualitatif}{type=radio}
#endif
#if defined TARGET_vocab13 
\title{Vocabulaire des séries 3}
\statement{
\tintro
<p>
Le caractère quantitatif étudié est-il discret ou continu?</p>
\embed{reply1}
}
\answer{caractère}{\typecar2;Discret,Continu}{type=radio}
#endif
#if defined TARGET_vocab14 
\title{Vocabulaire des séries 4}
\statement{
\tintro

<ol>
<li>Quelle est la taille de l'échantillon étudié? \embed{reply1}</li>
<li>Combien y a-t-il de valeurs distinctes dans la série? \embed{reply2}</li>
</ol>
}
\answer{échantillon}{\efftotal}{type=numeric}
\answer{valeurs}{\nbval}{type=numeric}
#endif
#if defined TARGET_vocab15 
\title{Vocabulaire des séries 5}
\statement{
\tintro

<ol>
<li>Quel est l'effectif total de la série? \embed{reply1}</li>
<li>Quel est l'effectif de la valeur \val? \embed{reply2}</li>
<li>Quelle est la fréquence de la valeur \val? \embed{reply3}</li>
</ol>
}
\answer{effectif total}{\efftotal}{type=numeric}
\answer{effectif de \val}{\ceteff}{type=numeric}
\answer{frequence de \val}{\cefreq}{type=numeric}
#endif
