target=matrice proba stable

\author{Sophie,Lemaire}
\email{Sophie.Lemaire@math.u-psud.fr}
\precision{1000}
\computeanswer{yes}


/* Construction de la matrice de transition T*/
\real{p1=randint(5..95)/100}
\real{p2=randint(5..95)/100}
\real{q1=1-\p1}
\real{q2=1-\p2}
\matrix{T=\q1,\p1
\p2,\q2}

/* Dessin du graphe*/
\text{graphe=
xrange -8,8
yrange -3,3
circle -4,0, 16,black
circle 4,0, 16,black
text black,-4.1,0.2,,1
text black,3.9,0.2,,2
arc -5,0, 2,2, 35,335,blue
arc 5,0, 2,2, 215,515,blue
arc 0,0, 8,3.5, 15,165,blue
arc 0,0, 8,3.5, 205,345,blue
arrow -4.2,0.55,-4,0.35,10,blue
arrow 4.2,-0.55,4,-0.35,10,blue
arrow 3.8,0.45,3.9,0.35,10,blue
arrow -3.8,-0.45,-3.9,-0.35,10,blue
text navy, -0.2,2.5,,\p1
text navy, -0.2,-2,,\p2
text navy, -7.2,0.1,,\q1
text navy, 6.2,0.1,,\q2
}
\text{dessin = draw(400,150
\graphe)}

#if defined TARGET_matrice
\title{Matrice de transition}
\text{rlist=reply1,reply2,reply3,reply4}
\steps{\rlist}
\text{enonce=Donner la matrice de transition du graphe probabiliste suivant :}
\text{accolg=draw(25,50
xrange -1,2
yrange -1.1,1.2
arc 0,0, 1,2, 100,260,black)}
\text{accold=draw(25,50
xrange -1,2
yrange -1.1,1.2
arc 0,0, 1,2, 260,100,black)}

#elif defined TARGET_stable
\title{Etat stable}
\real{mu1=\p2/(\p1+\p2)}
\real{mu2=\p1/(\p1+\p2)}
\integer{mu1a=10000*\mu1}
\real{mu1a=\mu1a/10000}
\text{enonce=L'évolution de l'état d'un système entre deux unités de temps
  \(n\) et \(n+1\) est décrit par le graphe probabiliste ci-dessous.<br>
  Déterminer l'état stable du système.}
\text{rlist=r1,r2}
\steps{\rlist}
#elif defined TARGET_proba
\title{Etat d'un système}
\integer{n0=randint(0..10)} /*choix des instants pour la question*/
\integer{dn=randint(2..5)}
\integer{n1=\n0+\dn}
\integer{e0=random(1,2)} /*choix des etats pour la question*/
\integer{e1=random(1,2)}
/* Calcul de la loi a l'instant n1*/
\real{som=\p1+\p2}
\real{aux=(1-\som)^\dn}
\real{v11=(\p1*\aux+\p2)/\som}
\real{v12=(-\p1*\aux+\p1)/\som}
\real{v21=(-\p2*\aux+\p2)/\som}
\real{v22=(\p2*\aux+\p1)/\som}
\matrix{Tn=\v11,\v12
\v21,\v22}
/* Choix de la question*/
\integer{c=random(1,2)}
\if{\c=1}{
\real{res=\Tn[\e0;\e1]}
\text{enonce=L'évolution de l'état d'un système entre deux unités de temps n et n+1 est décrit par le graphe probabiliste ci-dessous.<br>
  On sait qu'à l'instant \n0, le système est dans l'état \e0. }
\text{question=  probabilité que le système se trouve dans l'état \e1 à l'instant \n1}
}
{
  \integer{L1=randint(1..99)}
  \integer{L2=100-\L1}
  \matrix{Vn=pari(Tn=Mat([\Tn]);v=[\L1/100,\L2/100]*Tn;print(v))}
  \if{\e0=1}{\text{h1=\L1}}
                 {\text{h1=\L2} }
  \real{res= \Vn[1;\e1]}
 \text{enonce=L'évolution de l'état d'un système entre deux unités de temps \(n\) et \(n+1\) est décrit par le graphe probabiliste ci-dessous.<br>
  On suppose  qu'à l'instant \n0, le système a \h1 % de chance de se trouver dans l'état \e0.}
\text{question=  probabilité que le système se trouve dans l'état \e1 à l'instant \n1}
}
\text{enoncesuite=Déterminer la \question}
\integer{resa=10000*\res}
\real{resa=\resa/10000}
#endif

\statement{\enonce
<p class="wimscenter"> <img src="\dessin" alt=""></p>
#if defined TARGET_proba
\enoncesuite : \embed{reply1,8}
<div class="wims_instruction">
 Donner une valeur approchée à \(10^{-4}\) près.
 </div>
#elif defined TARGET_matrice
<p>
  La matrice de transition est :
</p>
<div class="wimscenter">
\special{mathmlinput [\begin{pmatrix}\rlist[1]&\rlist[2]\\\rlist[3]&\rlist[4]\end{pmatrix}],3,noanswer
reply1
reply2
reply3
reply4}
</div>


#elif defined TARGET_stable
  L'état probabiliste stable est : &#40; \embed{\rlist[1],5} \embed{\rlist[2],5} &#41;
<div class="wims_instruction">
Donner des valeurs approchées à \(10^{-4}\) près.</div>
#endif
}

/*Analyse des réponses*/

#if defined TARGET_matrice
\answer{}{\T[1;1]}{type=formal}{weight=\poids1}{option=noanalyzeprint}
\answer{}{\T[1;2]}{type=formal}{weight=\poids1}{option=noanalyzeprint}
\answer{}{\T[2;1]}{type=formal}{weight=\poids1}{option=noanalyzeprint}
\answer{}{\T[2;2]}{type=formal}{weight=\poids1}{option=noanalyzeprint}
#elif defined TARGET_proba
\answer{Probabilité}{\res}{type=numeric}{option=noanalyzeprint}
#elif defined TARGET_stable
\answer{}{\mu1}{type=numeric}{weight=\poids1}{option=noanalyzeprint}
\answer{}{\mu2}{type=numeric}{weight=\poids1}{option=noanalyzeprint}
#endif
#if defined TARGET_matrice
\solution{La matrice de transition est \([\T]\).}
#elif defined TARGET_proba
\solution{\if{\res!=\resa}{La valeur approchée à \(10^{-4}\) près de la}{La} \question est \(\resa\).}
#elif defined TARGET_stable
\solution{L'état probabiliste stable s'écrit \([p,  1-p]\) avec \(p\simeq \mu1a\).}
#endif
