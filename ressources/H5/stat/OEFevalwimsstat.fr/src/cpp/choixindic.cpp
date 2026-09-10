target= choixindic1 choixindic2 choixindic3 choixindic4 choixindic5
#include "author.inc"
#include "lang_titles.inc"
\precision{1000}

\text{lstindic=Mode,Médiane,Moyenne}

#if defined TARGET_choixindic1
\text{lstdef=Valeur de la série ayant le plus grand effectif,
Valeur partageant la série en deux parties de même effectif,
Somme des valeurs de la série divisée par l'effectif total}
\text{size=80x100x200}
\statement{<p>
Associer à chaque indicateur de position sa définition.
</p><div class="wimscenter">\embed{reply1,\size}</div>
}
\answer{}{\lstindic;\lstdef}{type=correspond}
#endif
#if defined TARGET_choixindic2
\text{data=La moitié de la classe a eu plus de 11 au dernier contrôle de Maths.,2
En France&#44; plus de la moitié des candidats à l'examen du code de la route pour le permis de conduire font moins de quatre fautes.,2
Sur une année&#44; le nombre de sorties par jour des pompiers d'une caserne dans la région parisienne est de 2.,3
En France&#44; lors du recensement de 1999&#44; on a dénombré au moins deux enfants dans plus de la moitié des familles.,2
Un coureur cycliste qui a parcouru 60 km en 90 min&#44; a atteint ou dépassé par moment la vitesse de 40 km/h.,3
L'élection de Miss France a été remportée par la candidate de Picardie.,1
Le seul joueur du loto ayant trouvé les 6 bons numéros est un habitant de Nice.,1
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{Quel est l'indicateur de position concerné dans le texte ci-dessous:
<p>
\quest
</p>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep;\lstindic}{type=radio}
#endif

#if defined TARGET_choixindic3
\integer{choix=randint(1,2)}
\integer{n=randint(2..8)*100}
\integer{n2=randint(\n/2,\n/4)}
\integer{nc=randint(\n/4..\n/2)}
\real{x=randint(8..10)+randint(0..9)/10}
\real{y=\x+randint(1..15)/10}
\real{z=\x-randint(1..15)/10}
\if{\choix=1}{
  \text{quest=Lors d'un concours d'entrée à l'école des statistiques,
 la moyenne générale des \n candidats a été de \x sur 20.
  Il y a \n2 places au concours. Mélanie a obtenu \y.
 Est-elle sûre d'intégrer }
  \integer{rep=2}
  \text{tfeed=La moyenne n'est pas l'indicateur permettant de décider si Mélanie peut intégrer ou non,
 c'est son rang de classement qui intervient:<br>
Si le nombre de places au concours est la moitié du nombre de candidats, il faut être au dessus de la médiane pour intégrer.<br>
Si le nombre de places au concours est le quart du nombre de candidats, il faut être au dessus du troisième quartile pour intégrer.<br>
  }
}{
  \text{quest=Lors d'un concours d'entrée à l'école des statistiques,
  la moyenne générale des \n candidats a été de \z sur 20 et la barre d'admissibilité a été fixée à \x.
  Mélanie est arrivée \nc ème.
  Est-elle sûre d'être admissible}
  \integer{rep=2}
  \text{tfeed=Le classement n'est pas l'indicateur permettant de décider si Mélanie peut être admidssible ou non,
  c'est sa moyenne qui intervient .
  }
}
\text{name_ouinon=Oui,Non}
\statement{<p>\quest ?</p>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep;\name_ouinon}{type=radio}
\feedback{1=1}{\tfeed}
#endif
#if defined TARGET_choixindic4
\matrix{data=5,8,9,10,10,10
3,3,6,14,16,17
7,7,7,8,18,18}
\text{ind=shuffle(3)}
\integer{rep1=position(1,\ind)}
\integer{rep2=position(3,\ind)}
\integer{rep3=position(2,\ind)}
\statement{
<p>
Voici 3 séries à comparer:</p>
<table class="wimscenter wimsborder">
<tr><th>série A:</th><td>\data[\ind[1];]</td></tr>
<tr><th>série B:</th><td>\data[\ind[2];]</td></tr>
<tr><th>série C:</th><td>\data[\ind[3];]</td></tr>
</table>
<ul>
<li>Quelle série a le mode le plus élevé? \embed{reply1}</li>
<li>Quelle série a la moyenne la plus élevée? \embed{reply2}</li>
<li>Quelle série a la médiane la plus élevée? \embed{reply3}</li>
</ul>
}
\answer{mode}{\rep1;A,B,C}{type=radio}
\answer{moyenne}{\rep2;A,B,C}{type=radio}
\answer{médiane}{\rep3;A,B,C}{type=radio}
#endif
#if defined TARGET_choixindic5
\integer{ind=randint(1..3)}
integer{ind=3}
\text{dataindic=9.10,8.5,10,9,3
11.66,11.5,7,8,1
7.89,9,10,8,2}
\text{data=1,2,3,3,3,3,3,4,4,6,6.5,7,7,7,7,7.5,7.5,8,9,10,10,10,10,10,10,12,12,13,14,15,16.5,18,19,19,20
7,7,7,7,7,8,9.5,9.5,10,10.5,11,11,11.5,11.5,11.5,11.5,12,12,12,12.5,13,13.5,13.5,13.5,14,14.5,15,16,16.5,16.5,16.5
1,2,3,3,3,3,3,3.5,4,5,6.5,6.5,7,7,7,8,9,9,9,10,10,10,10,10,10,11.5,12,12,12,12,1,13.5,15}
\text{listval=row(\ind,\data)}
\integer{nbval=items(\listval)}
\integer{valsomme=0}
\for{i=1 to \nbval}{
  \integer{valsomme=\valsomme+\listval[\i]}
}
\real{moy=\valsomme/\nbval}
\integer{parite=\nbval/2}
\integer{parite=\parite*2=\nbval?0:1}
\real{med=\parite=0?(\listval[\nbval/2]+\listval[\nbval/2+1])/2:\listval[(\nbval+1)/2]}
\text{slistval=shuffle(\listval)}
\text{cedata=row(\ind,\dataindic)}
\integer{rep=\cedata[5]}
\integer{x=\cedata[4]}
\text{lstrep= au dessus du mode, au dessus de la moyenne, au dessus de la médiane}

\text{table=<table class="wimscenter wimsborder">
<caption>notes de la classe</caption>}

\integer{nn=ceil(\nbval/10)}
\for{i=0 to \nn-1}{
  \text{table=\table<tr>}
  \for{j=1 to 10}{
    \text{a=item(\i*10+\j,\slistval)}
    \text{table=\table <td>\a</td>}
  }
  \text{table=\table </tr>}
}
\text{table=\table </table>}

\statement{<p>
Marc n'a obtenu que \x /20 à son contrôle de statistiques, les notes de la classe sont:
</p>
<div class="wimscenter">\table</div>
<p>
 Pour annoncer positivement sa note à ses parents, quel indicateur Marc utilisera-t-il?</p>
Sa note est : \embed{reply1}
}
\answer{}{\rep;\lstrep}{type=radio}
#endif
