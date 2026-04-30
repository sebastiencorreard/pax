\text{prob=La situation décrite est-elle le fruit du hasard ?}
\text{imagebd="\imagedir/GF.png" alt="Natalité en Chine et au Canada"}
\integer{jk=randint(0..1)}

\text{quest1=(\jk==0)?Déterminer la fréquence de garçons nés dans le village de Xicun, en
Chine.}
\text{quest1=(\jk==1)?Déterminer la fréquence de garçons nés dans la réserve indienne
d'Aamjiwnaag.}

\text{quest2=Déterminer la probabilité théorique de naissance des garçons.}

\real{fob=(\jk==0)?0.8}
\real{fob=(\jk==1)?0.348}

\integer{teee=(\jk==0)?20}
\integer{teee=(\jk==1)?132}

\integer{nnn=\teee}
\integer{zz=randint(0..5)}
\integer{nbrech=100+\zz*25}
\real{p=0.512}
\real{aaxe=0.51}

\text{listrep=r5,r6,r7,r8,r9,r10,r11,r12}

\text{enonce=Les données statistiques suivantes ont été relevées :
<ul><li>en 2000, dans le village de Xicun, en Chine, il est né 20 enfants,
 parmi lesquels 16 garçons</li>
<li>dans la réserve indienne d'Aamjiwnaag, située au Canada à proximité d'industries
 chimiques, il est né entre 1999 et 2003, 132 enfants dont 46 garçons.</li>
 </ul>
La proportion de garçons à la naissance est habituellement estimée à 50 %.
 En réalité elle est, de façon étonnamment stable, de 51,2 %.}


\text{instruction=La simulation est réalisée à l'aide de Python. Le prélèvement est réalisé
 sur des échantillons aléatoires de taille \(\nnn\) dans une population où la fréquence
 des garçons est \(\p\). Initialiser correctement les valeurs
 des variables \(\text{p}\), \(\text{te}\), \(\text{ne}\) et jouer le code. Les fréquences des
 garçons observées sur \(\nbrech\) échantillons simulés sont représentées
 ci-dessous :}
