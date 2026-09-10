target=trinomeRJ trinomeRA trinomeRE trinomeCJ trinomeCA trinomeCE

\language{fr}
\author{Paul,Byache}
\email{paul@byache.fr}
\format{html}
\precision{1000}
\keywords{equations,trinomial}
\text{instr=X}
%%% MB : 
mis dans question2 le pt d'intérogation et supprimé dans le statement
ajout div wimsquestion et feedback
%%%
#define TITRE Équation du second degré 
#if defined TARGET_trinomeRJ
  ////résolution sur R, les solutions tombent "juste"
  \title{TITRE (R,J)}
  \observation{Dans cet exercice, la résolution se fait dans l'ensemble des réels.<br>Il y a deux solutions distinctes dans 50% des cas.
<br>Les solutions tombent "juste" (les élèves n'auront pas à saisir de racine carrée dans le champ de réponse).}
#endif

#if defined TARGET_trinomeRA
  ////résolution sur R, les solutions doivent être arrondies
  \title{TITRE (R,A)}
  \observation{Dans cet exercice, la résolution se fait dans l'ensemble des réels.<br>Il y a deux solutions distinctes dans 50% des cas.
<br>Les solutions devront être données sous forme arrondies.}
#endif

#if defined TARGET_trinomeRE
  ////résolution sur R, les solutions doivent être sous forme exactes avec des racines carrées
  \title{TITRE (R,E)}
  \observation{Dans cet exercice, la résolution se fait dans l'ensemble des réels.<br>Il y a deux solutions distinctes dans 50% des cas.
<br>Les solutions ne tombent pas "juste" et doivent être données de façon exacte (les élèves devront en général saisir un quotient et une racine carrée dans le champ de réponse).}
#endif

#if defined TARGET_trinomeCJ
  ////résolution sur C, les solutions tombent "juste"
  \title{TITRE (C,J)}
  \observation{Dans cet exercice, la résolution se fait dans l'ensemble des complexes.<br>Il y a deux solutions complexes conjuguées dans 60% des cas.
<br>Les solutions tombent "juste" (les élèves n'auront pas à saisir de racine carrée dans le champ de réponse).}
#endif

#if defined TARGET_trinomeCA
  ////résolution sur C, les solutions doivent être arrondies
  \title{TITRE (C,A)}
  \observation{Dans cet exercice, la résolution se fait dans l'ensemble des complexes.<br>Il y a deux solutions complexes conjuguées dans 60% des cas.
<br>Les solutions devront être données sous forme arrondies.}
#endif

#if defined TARGET_trinomeCE
  ////résolution sur C, les solutions doivent être données sous forme exactes avec des racines carrées
  \title{TITRE (C,E)}
  \observation{Dans cet exercice, la résolution se fait dans l'ensemble des complexes.<br>Il y a deux solutions complexes conjuguées dans 60% des cas.
<br>Les solutions ne tombent pas "juste" et doivent être données de façon exacte (les élèves devront en général saisir un quotient et une racine carrée dans le champ de réponse).}
#endif

#if defined TARGET_trinomeRJ || defined TARGET_trinomeRA || defined TARGET_trinomeRE
  ////les solutions sont des réels
  \text{lstrep=deux solutions, une solution double,pas de solution réelle}
  ////2 fois sur 4, il y aura deux soutions
  \integer{rep=randint(1,1,2,3)}
  \text{xun=x_1}
  \text{ensemble=RR}
#endif

#if defined TARGET_trinomeCJ || defined TARGET_trinomeCA || defined TARGET_trinomeCE
  ////les solutions sont des complexes
  \text{lstrep=deux solutions réelles, une solution réelle double,deux solutions complexes conjuguées}
  ////3 fois sur 5, il y aura des solutions complexes conjuguées
  \integer{rep=randint(1,2,3,3,3)}
  \text{xun=z_1}
  \text{ensemble=CC}

#endif


#if defined TARGET_trinomeCJ || defined TARGET_trinomeRJ
  ////construction de l'équation admettant des solutions qui "tombent juste"
  \if{\rep=1}
  {
  \integer{x1=randint(1..10)*randint(1,-1)}
  \integer{x2=\x1+randint(2..5)}
  \rational{x2=\x2==0?\x1/2}
  \integer{a=randint(1..3)*randint(1,-1)}
  \text{equat=texmath(maxima(expand(\a*(z-\x1)*(z-\x2))))}
  \real{b=-(\a)*((\x1)+(\x2))}
  \real{c=(\a)*(\x1)*(\x2)}
  \text{mstep=r1
  r2}
  \text{question2=Quelles sont ces solutions réelles \(x_1) et \( x_2) &#63;}
  }
  \if{\rep=2}
  {
  \integer{denom=randint(2..5)}
  \rational{x1=randint(1..10)*randint(1,-1)/\denom}
  \integer{a=randint(1..3)*\denom^2*randint(1,-1)}
  \text{equat=texmath(maxima(expand(\a*(z-\x1)^2)))}
  \real{b=-(\a)*2*(\x1)}
  \real{c=(\a)*(\x1)^2}
  \text{mstep=r1
  r3}
  \text{question2=Quelle est cette solution réelle double \(\xun) &#63;}
  }
  \if{\rep=3}
  {
  \integer{x1=randint(-10..10)}
  \integer{y1=randint(1..10)}
  \integer{a=randint(1..3)*randint(1,-1)}
  \complex{z1=\x1-\y1*i}
  \complex{z2=\x1+\y1*i}
  \text{equat=texmath(maxima(expand(\a*(z-\z1)*(z-\z2))))}
  \real{b=-(\a)*(\x1)*2}
  \real{c=(\a)*((\x1)^2+(\y1)^2)}
  \text{mstep=r1
  r4}
  \text{question2=Quelles sont ces solutions complexes  \(z_1) et \(z_2) &#63;}
  }
  \integer{taille=5}
  \text{type=aset}
#endif

#if defined TARGET_trinomeRA || TARGET_trinomeRE || defined TARGET_trinomeCA || defined TARGET_trinomeCE
  ////construction de l'équation admettant des solutions qui ne "tombent pas juste"
  \if{\rep=1}
  {
  ////on met souvent b à 0 ou à 1 ou -1 pour habituer les élèves à bien identifier la valeur de b  BUG LE DELTA N EST PAS TOUJOURS POSITIF !!!!!!!!!!!!!!!!
  \integer{b=randint(0..2)*randint(1,-1)}
  \integer{a=randint(1..3)*randint(1,-1)}
  \integer{lim=(\b)^2/(4*(\a))}
  \if{\a>0}{
    \integer{c=randint(-5..\lim-1)}
  }{
    \integer{c=randint(\lim+1..5)}

    }
  \text{equat=texmath(maxima(expand(\a*z^2+\b*z+\c)))}
  \integer{d=(\b)^2-4*(\a)*(\c)}
  \integer{e=2*(\a)}
  \text{et=\e<0 ? (\e) : \e}
  \integer{mb=-\b}
  \text{mbt=\b<0 ? \mb : -\b}
  \text{n1t=\b==0 ? -sqrt(\d) : (\mbt-sqrt(\d))}
  \text{n2t=\b==0 ? sqrt(\d) : (\mbt+sqrt(\d))}
  \text{x1=wims(nospace \n1t / \et)}
  \text{x2=wims(nospace \n2t / \et)}
  \text{mstep=r1
  r2}
  \text{question2=Quelles sont ces solutions réelles \(x_1) et \( x_2) &#63;}
  }
  \if{\rep=2}
  {
  \integer{denom=random(3,7)}
  \rational{x1=randint(8..20)*randint(1,-1)/\denom}
  \integer{a=randint(1..3)*\denom^2*randint(1,-1)}
  \text{equat=texmath(maxima(expand(\a*(z-\x1)^2)))}
  %%% ajout MB
  \real{b=-(\a)*2*(\x1)}
  \real{c=(\a)*(\x1)^2}
  %%%% fin ajout MB
  \text{mstep=r1
  r3}
  \text{question2=Quelle est cette solution réelle double \(\xun) &#63;}
  }
  \if{\rep=3}
  {
  ////on met souvent b à 0 ou à 1 ou -1 pour habituer les élèves à bien identifier la valeur de b
  \integer{b=randint(0..2)*randint(1,-1)}
  \integer{c=randint(0..5)*randint(1,-1)}
  \integer{a=randint(1..3)*randint(1,-1)}

  \integer{lim=(\b)^2/(4*(\a))}
  \if{\a<0}{
    \integer{c=randint(-5..\lim-1)}
  }{
    \integer{c=randint(\lim+1..5)}
    }
  \text{equat=texmath(maxima(expand(\a*z^2+\b*z+\c)))}
  \integer{d=-((\b)^2-4*(\a)*(\c))}
  \integer{e=2*\a}
  \text{et=\e<0 ? (\e) : \e}
  \integer{mb=-\b}
  \text{mbt=\b<0 ? \mb : -\b}
  \text{n1t=\b==0 ? -i*sqrt(\d) : (\mbt-i*sqrt(\d))}
  \text{n2t=\b==0 ? i*sqrt(\d) : (\mbt+i*sqrt(\d))}
  \text{z1=wims(nospace \n1t / \et)}
  \text{z2=wims(nospace \n2t / \et)}
  \real{x1=(-(\b))/(\e)}
  \real{x2=(-(\b))/(\e)}
  \real{y1=(-sqrt(\d))/(\e)}
  \real{y2=(sqrt(\d))/(\e)}
  \text{mstep=r1
  r4}
  }
#endif

#if defined defined TARGET_trinomeCA || defined TARGET_trinomeCE
  \text{question2=Quelles sont ces solutions complexes  \(z_1\) et \(z_2\) &#63;}
#endif

#if defined TARGET_trinomeRA
  ////on remplace les solutions par leur valeur arrondie au centième
  \integer{x1=\x1*100}
  \real{x1=\x1/100}
  \integer{x2=\x2*100}
  \real{x2=\x2/100}
  \integer{y1=\y1*100}
  \real{y1=\y1/100}
  \integer{y2=\y2*100}
  \real{y2=\y2/100}
  \text{instr=Donner des valeurs arrondies à \(10^{-2}\) près.}
  \integer{taille=5}
  \text{type=aset}
#endif

#if defined TARGET_trinomeCA
  ////on remplace les solutions avec les valeurs arrondies au centième des parties réelles et imaginaires
  \integer{x1=\x1*100}
  \real{x1=\x1/100}
  \integer{x2=\x2*100}
  \real{x2=\x2/100}
  \integer{y1=\y1*100}
  \real{y1=\y1/100}
  \integer{y2=\y2*100}
  \real{y2=\y2/100}
  \complex{z1=\x1+i*\y1}
  \complex{z2=\x2+i*\y2}
  \text{instr=Arrondir à \(10^{-2}) près la partie réelle et la partie imaginaire des solutions .}
  \if{\rep==2}{
    \text{instr=Arrondir à \(10^{-2}) près la solution.}
  }
  \integer{taille=10}
  \text{type=aset}
#endif


#if defined TARGET_trinomeRE || defined TARGET_trinomeCE
  \text{instr=Donner des valeurs exactes des solutions.<br/>Rappel : la racine carrée se note "sqrt(...)". Par exemple, saisir " sqrt(5) " pour \(\sqrt{5}).}
  \integer{taille=15}
  \text{type=fset}
#endif

#if defined TARGET_trinomeRJ || defined TARGET_trinomeRA || defined TARGET_trinomeRE
  ////On appelle x la variable quand on est sur R...
  \text{equat=wims(replace internal z by x in \equat)}
  ////Si pas de solution réelle, une seule étape
  \if{\rep=3}{\text{mstep=r1}}


#endif


\real{d=(\b)^2-4*(\a)*(\c)}
\text{at=\a<0 ? (\a) : \a}
\text{bt=\b<0 ? (\b) : \b}
\text{ct=\c<0 ? (\c) : \c}
\text{feedb=Pour savoir combien il y a de solutions, on peut calculer le discriminant de l'équation : \(\Delta=b^2-4ac)<br>
Ici, on a \(a=\a), \(b=\b) et \(c=\c). Donc le calcul du discriminant se fait ainsi :<br>
\(\Delta=\bt^2-4\times \at \times \ct=\d)}


\steps{\mstep}
\statement{<p>
On considère l'équation \((E) : \equat=0).
<br>On veut résoudre cette équation sur \(\ensemble).
</p>
\if{\step=1}
 {
L'équation \((E)) possède :
<div class="wims_question"><ul class="wims_nopuce">
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
</ul></div>
 }
 {
\if{\rep=1}
 {L'équation \((E)) possède \lstrep[\rep].
\question2 
<div class="wims_question"><div class="wimscenter">Donner l'ensemble de ces deux solutions : \embed{reply2,\taille}</div></div>
 }
\if{\rep=2}
 {L'équation \((E)) possède \lstrep[\rep].
\question2 
<div class="wims_question"><div class="wimscenter"> \(\xun)=\embed{reply3,\taille}</div></div>
 }
\if{\rep=3}
 {L'équation \((E)) possède \lstrep[\rep].
\question2 
<div class="wims_question"><div class="wimscenter">Donner l'ensemble de ces deux solutions : \embed{reply4,\taille}</div></div>

 }
\if{\instr notsametext X}{<br/><br/><div class=wims_instruction>\instr</div>}
}
}
\answer{type de solutions}{\rep;\lstrep}{type=radio}
\answer{\(x_1) et \(x_2)}{\x1,\x2}{type=\type}{option=distinct_inputs}
\answer{\(\xun)}{\x1}{type=numexp}
\answer{\(z_1) et \(z_2)}{\z1,\z2}{type=\type}{option=distinct_inputs}
\feedback{\step=1}{<div class="feedback">\feedb</div>}
