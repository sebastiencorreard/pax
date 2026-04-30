target=indic1 indic2 indic3 indic4 indic5
#if defined TARGET_indic1 
\title{Choix d'un indicateur 1}
\text{data=La moitié de la classe a eu plus de 11 au dernier contrôle de Maths,1
En France&#44; plus de la moitié des candidats à l'examen du code de la route pour le permis de conduire font moins de quatre fautes,1
Sur une année&#44; le nombre de sorties par jour des pompiers d'une caserne dans la région parisienne est de 2,2
En France&#44; lors du recensement de 1999&#44; on a dénombré au moins deux enfants dans plus de la moitié des familles,1
Un coureur cycliste qui a parcouru 60 km en 90 min a atteint ou dépassé par moments la vitesse de 40 km/h,2
L'élection de Miss France a été remportée par la candidate de Picardie,3
Le seul joueur du loto ayant trouvé les 6 bons numéros est un habitant de Nice,3
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
De quel indicateur est-il question dans le texte suivant:
<p>
\quest
</p>
\embed{reply1}
}
\answer{Indicateur}{\rep;Médiane,Moyenne,Mode}{type=radio}
#endif
#if defined TARGET_indic2 
\title{Choix d'un indicateur 2}
\text{data=La moyenne est sensible aux valeurs extrêmes,1
La médiane est sensible aux valeurs extrêmes,2
Une série statistique comporte toujours autant de valeurs de part et d'autre de la médiane,1
Une série statistique comporte toujours autant de valeurs de part et d'autre de la moyenne,2
Une série statistique comporte toujours une unique valeur modale,2
La valeur modale est toujours supérieure à la moyenne d'une série,2
La valeur modale est toujours supérieure à la médiane d'une série,2
On ne change pas la médiane d'une série en supprimant la valeur minimale et la valeur maximale,1
On ne change pas la moyenne d'une série en supprimant la valeur minimale et la valeur maximale,2
La moyenne est un indicateur de position,1
La moyenne est un indicateur de dispersion,2
La médiane est un indicateur de position,1
La médiane est un indicateur de dispersion,2
Le mode est un indicateur de position,1
Le mode est un indicateur de dispersion,2
L'étendue est un indicateur de position,2
L'étendue est un indicateur de dispersion,1
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
Dire si l'affirmation suivante est vraie ou fausse:
<p>
\quest
</p>
\embed{reply1}
}
\answer{}{\rep;Vrai,Faux}{type=radio}
#endif

#if (defined TARGET_indic3  || defined TARGET_indic4 )
\integer{n=randint(25..36)}
\integer{moy=randint(70..170)}
\real{moy=\moy/10}
\integer{med=randint(14..34)}
\real{med=\med/2}
\integer{i=randint(1..3)}

#if defined TARGET_indic3 
\title{Choix d'un indicateur 3}
\text{lstrep=On est sûr que la moyenne augmente, On est sûr que la moyenne diminue, On est sûr que la moyenne est inchangée, On ne peut pas savoir si la moyenne change}
\if{\i=3}
  {
   \real{x=\moy}
   \integer{rep=3}
  }
\if{\i=2}
 {
 \integer{x=randint(4..\moy-1)}
 \integer{rep=2}
 }
\if{\i=1}
 {
 \integer{x=randint(\moy+1..18)}
 \integer{rep=1}
 }

#endif
#if defined TARGET_indic4 
\title{Choix d'un indicateur 4}
\text{lstrep=On est sûr que la médiane augmente, On est sûr que la médiane diminue, On est sûr que la médiane est inchangée, On ne peut pas savoir si la médiane change}
\if{\i=3}
  {
   \real{x=\med}
   \integer{rep=3}
  }
\if{\i=2}
 {
 \integer{x=randint(4..\moy-1)}
 \integer{rep=4}
 }
\if{\i=1}
 {
 \integer{x=randint(\moy+1..18)}
 \integer{rep=4}
 }
#endif
\statement{
Un professeur corrige \n copies d'un devoir à la maison:
<ul><li> la moyenne est de \moy</li>
<li> la médiane \med</li>
<li> les notes extrèmes sont 4 et 18</li>
</ul>
Un retardataire rend sa copie et obtient \x.<p>
Que peut-on dire alors:</p>
\embed{reply1}
}
\answer{}{\rep;\lstrep}{type=radio}
#endif

#if defined TARGET_indic5 
\title{Choix d'un indicateur 5}
\integer{x1=random(10..40)}
\integer{x2=random(55..80)}
\text{lstrep=La médiane est au dessus de la moyenne,La moyenne est au dessus de la médiane, On ne peut pas savoir comment se situe la médiane par rapport à la
moyenne}
\text{data=S'il y a exactement \x1 % de notes au dessus de la moyenne,2
S'il y a exactement \x1 % de notes en dessous de la moyenne,1
S'il y a exactement \x2 % de notes au dessus de la moyenne,1
S'il y a exactement \x2 % de notes en dessous de la moyenne,2
S'il y a exactement \x1 % de notes au dessus de 10,3
S'il y a exactement \x1 % de notes en dessous de 10,3
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\integer{rep=\cedata[2]}
\statement{
On considère une série de notes de 0 à 20.<p>
Cocher la bonne réponse:</p>
<div class="wimscenter">\quest</div>
<ul>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
</ul>}
\answer{}{\rep;\lstrep}{type=radio}
#endif
