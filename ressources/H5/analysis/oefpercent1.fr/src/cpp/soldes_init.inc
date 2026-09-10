%%Choix du contexte%%
\text{L=chemise,casquette,veste,pull,pantalon,sweatshirt,sac,foulard,ballon}

\text{A = shuffle(9)}
\text{TQ = shuffle(3)}

%% bornes : prix minimum, pas, nombre de pas
\matrix{M=14.7,2.1,10
10.5,2.1,15
35,6.3,5
14.7,8.2,10
16.8,4.2,8
12.6,2.1,8
21,10.5,6
8.4,2.1,6
6.3,2.1,10
}

\integer{n=\A[1]}
\text{U1= \n < 4 ? une : un}
\text{U2= \n < 4 ? cette : ce }
\text{U3= \n < 4 ? étiquetée : étiqueté}
\text{\obj=\L[\n]}
\real{\vi1=\M[\n;1]+\M[\n;2]*randint(0..\M[\n;3])}
\integer{p1 = random(10,20,30,40,60,70)}
\real{\vp1=\vi1*0.01*\p1}
\integer{m=\TQ[1]}
\integer{ns=\m%3}

\text{L1=Flo a bénéficié d'une remise sur \U1 \obj de \p1 %. Flo a ainsi gagné \vp1 &euro;. Quel était le prix initial de \U2 \obj ?}

\text{L2=Sur le marché \U1 \obj est \U3 à \vi1 &euro;. Le vendeur fait une remise de \vp1 &euro;. Quel est le pourcentage de la remise sur le prix affiché ?}

\text{L3=Le prix affiché d'\U1 \obj est \vi1 &euro;. Pendant les soldes le prix est diminué de \p1 %. Quelle est la valeur de cette réduction ?}

\text{sy1= \ns = 2 ? %:&euro;}
\if{\ns=1}{
  \text{E1=\L1}
  \real{v1=\vi1}
}
\if{\ns=2}{
  \text{E1=\L2}
  \real{v1=\p1}
}
\if{\ns=0}{
  \text{E1=\L3}
  \real{v1=\vp1}
}

\integer{n=\A[2]}
\text{U1= \n < 4 ? une : un}
\text{U2= \n < 4 ? cette : ce }
\text{U3= \n < 4 ? étiquetée : étiqueté}
\text{\obj=\L[\n]}
\real{\vi2=\M[\n;1]+\M[\n;2]*randint(0..\M[\n;3])}
\integer{p2 = random(10,20,30,40)}
\integer{pa2 = 100 + \p2}
\real{\vp2=\vi2*0.01*\p2}
\real{\va2=\vi2+\vp2}
\integer{m=\TQ[2]}
\integer{ns=\m%3}

\text{L4=Le prix d'\U1 \obj a augmenté de \p2 % par rapport à l'an dernier. Quel était le prix l'an dernier d'\U1 \obj dont le prix est  \va2 &euro; cette année ?}
\text{L5=Dans une boutique \U1 \obj est \U3 \vi2 &euro; Hors Taxe et est vendu \va2 &euro; Toute Taxe Comprise. Quel est le pourcentage de la taxe par rapport au prix Hors taxe de \U2 \obj ? }
\text{L6=Le prix d'\U1 \obj a augmenté de \p2 % par rapport à l'an dernier. Quel est le prix d'\U1 \obj qui valait \vi2 &euro; l'an dernier ? }

\text{sy2= \ns = 2 ? %:&euro;}
\if{\ns=1}{
  \text{E2=\L4}
  \real{v2=\vi2}
}
\if{\ns=2}{
  \text{E2=\L5}
  \real{v2=\p2}
}
\if{\ns=0}{
  \text{E2=\L6}
  \real{v2=\va2}
}

\integer{n=\A[3]}
\text{U1= \n < 4 ? une : un}
\text{U2= \n < 4 ? cette : ce }
\text{U3= \n < 4 ? étiquetée : étiqueté}
\text{\obj=\L[\n]}
\real{\vi3=\M[\n;1]+\M[\n;2]*randint(0..\M[\n;3])}
\integer{p3 = random(10,20,30,40)}
\integer{pd3 = 100 - \p3}
\real{\vp3=\vi3*0.01*\p3}
\real{\vd3=\vi3-\vp3}
\integer{m=\TQ[3]}
\integer{ns=\m%3}

\text{L7=Grâce à une remise de \p3 % Dominique a payé \U1 \obj \vd3 &euro;. Quel était l'ancien prix de  \U2 \obj ?}
\text{L8=Dans un magasin Jo paye \vd3 &euro; \U1 \obj dont l'ancien prix était \vi3 &euro;. Quel est le pourcentage de la remise ?}
\text{L9=Camille a acheté \U1 \obj \U3 \vi3 &euro; mais Camille a droit à une réduction de \p3 %. Quel sera le prix final de \U2 \obj ?}

\text{sy3= \ns = 2 ? %:&euro;}
\if{\ns=1}{
  \text{E3=\L7}
  \real{v3=\vi3}
}
\if{\ns=2}{
  \text{E3=\L8}
  \real{v3=\p3}
}
\if{\ns=0}{
  \text{E3=\L9}
  \real{v3=\vd3}
}
%%Création d'un ordre aléatoire pour les énoncés pour solde2, dans l'ordre pour solde1
\text{ListeEn=\E1,\E2,\E3}
\text{ListeVn=\v1,\v2,\v3}
\text{ListeSy=\sy1,\sy2,\sy3}
\text{ListeTy=Pourcentage proportion,Pourcentage d'augmentation,Pourcentage de diminution}
\text{ListeQ=la valeur de la référence, le pourcentage, la valeur de la partie ou la valeur finale}
\text{Er1=\ListeEn[\T[1]]}
\text{Er2=\ListeEn[\T[2]]}
\text{Er3=\ListeEn[\T[3]]}
\text{sr1=\ListeSy[\T[1]]}
\text{sr2=\ListeSy[\T[2]]}
\text{sr3=\ListeSy[\T[3]]}
\text{vr1=\ListeVn[\T[1]]}
\text{vr2=\ListeVn[\T[2]]}
\text{vr3=\ListeVn[\T[3]]}

%% Diagrammes en barres
\text{bar1 = xrange 0,1000
yrange -10,340
text black, 0,330, giant,Pourcentage proportion
text black, 290,330, giant,Pourcentage d'augmentation
text black, 650,330, giant,Pourcentage de diminution
linewidth 1
arc 50,150,16,100,90,180,black
arc 34,150,16,100,270,360,black
arc 34,50,16,100,0,90,black
arc 50,50,16,100,180,270,black
arc 200,40,16,80,90,270,black
rectangle 490,200,570,260, black
arc 340,150,16,100,90,180,black
arc 324,150,16,100,270,360,black
arc 324,50,16,100,0,90,black
arc 340,50,16,100,180,270,black
arc 490,230,16,60,90,270,black
arc 570,195,16,130,0,90,black
arc 586,195,16,130,180,270,black
arc 586,65,16,130,90,180,black
arc 570,65,16,130,-90,0,black

rectangle 850,120,930,200, black
arc 700,150,16,100,90,180,black
arc 684,150,16,100,270,360,black
arc 684,50,16,100,0,90,black
arc 700,50,16,100,180,270,black
arc 850,160,16,80,90,270,black
arc 930,90,16,60,0,90,black
arc 946,90,16,60,180,270,black
arc 946,30,16,60,90,180,black
arc 930,30,16,60,-90,0,black

linewidth 3
rectangle 50,0,130,200, black
rectangle 200,0,280,80, blue
fill 240,5,pink
text black, 0, 110, medium, 100 %
text black, 60, 140, medium, référence
text black, 60, 120, medium, en euros
text blue, 210, 80, medium, partie
text blue, 210, 60, medium, en euros
text black, 180, 50, medium, %
segment 285,-10,285,350, red

rectangle 340,0,420,200, black
rectangle 490,0,570,260, blue
fill 500,5,pink
fill 500,255,pink
text black, 290, 110, medium, 100 %
text black, 350, 160, medium, valeur
text black, 350, 140, medium, initiale
text black, 350, 120, medium, en euros
text black, 470,240, medium, %
text blue, 500, 180, medium, valeur
text blue, 500, 160, medium, finale
text blue, 500, 140, medium,en euros
text black, 495, 250, small, augmentation
text black, 635,140, medium, %

segment 645,-10,645,350, red
rectangle 700,0,780,200, black
rectangle 850,0,930,120, blue
fill 900,5,pink
text black, 650, 110, medium, 100 %
text black, 710, 160, medium, valeur
text black, 710, 140, medium, initiale
text black, 710, 120, medium, en euros
text black, 860, 190, small, diminution
text black, 830,180, medium, %
text blue, 860, 90, medium, valeur
text blue, 860, 70, medium, finale
text blue, 860, 50, medium,en euros
text black, 990,70, medium, %
}
\text{url1 = draw(1000,350
\bar1)}
\text{bar2 = \bar1
text black, 60, 100, medium, \vi1
text blue, 210, 40, medium, \vp1
text black, 150, 50, medium, \p1
text black, 350, 100, medium, \vi2
text black, 440,240, medium, \p2
text blue, 500, 120, medium,\va2
text black, 495, 230, small, \vp2
text black, 605,140, medium, \pa2
text black, 710, 100, medium, \vi3
text black, 860, 170, small, \vp3
text black, 800,180, medium, \p3
text blue, 860, 30, medium,\vd3
text black, 960,70, medium, \pd3
}
\text{url2 = draw(1000,350
\bar2)}
