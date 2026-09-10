\text{name_header=Valeurs,Pourcentage,Valeur initiale,Augmentation,Valeur finale}

%% Choix des valeurs %%
\real{\vi=20+randint(1..79)}
\integer{p = randint(1..20)}
\integer{pa = 100 + \p}
\real{vp =\vi*0.01*\p}
\real{\vf=\vi+\vp}
\real{k=1+0.01*\p}
\function{fk=1+p/100}
\text{ax=}

%% Les questions et les formules
#if defined TARGET_augm
\text{L1=Une action qui valait \vi &euro; vaut maintenant \vf &euro;. Quel est le pourcentage d'augmentation ?}
\text{sy1=%}
\text{L2=Une action qui valait \(x) &euro; a augmenté et vaut maintenant \(y) &euro;. De combien a-t-elle été augmentée ?}
\text{sy2=&euro; (formule)}
\text{L3=Une action qui valait \(x) &euro; a augmenté et vaut maintenant \(y) &euro;. Quel est le pourcentage d'augmentation ?}
\text{sy3=% (formule)}
\function{fd=y-x}
\function{fp=(y-x)/x*100}
#endif
#if defined TARGET_coeff1
\text{L1=Une action qui valait \vi &euro; augmente de \p % quelle est sa nouvelle valeur ?}
\text{sy1=&euro;}
\text{L2=Lorsqu'une quantité augmente de \p %, par quel nombre faut-il multiplier la valeur initiale pour obtenir la valeur finale ?}
\text{sy2=(nombre)}
\text{L3=Lorsqu'une quantité augmente de \(p) %, par quel nombre faut-il multiplier la valeur initiale pour obtenir la valeur finale ?}
\text{sy3= (formule)}
#endif
#if defined TARGET_percentref2
\text{L1=Une action a augmenté de \p %. Sa nouvelle valeur est \vf &euro;. Quelle était sa valeur initiale ?}
\text{sy1=&euro;}
\text{L2=Une action a augmenté de \(p) %. Par quel nombre faut-il multiplier sa valeur initiale pour obtenir sa valeur finale ?}
\text{sy2= (formule)}
\text{L3=Une action a augmenté de \(p) %. Quelle formule permet de retrouver sa valeur initiale \(x) à partir de sa valeur finale \(y) et de \(p) ?}
\text{ax= x =}
\text{sy3=&euro; (formule)}
\function{fi=y/(1+p/100)}
#endif

%% Diagrammes en barres
\text{bar1 = xrange 0,400
yrange -10,340
text black, 0,330, giant,Pourcentage d'augmentation
linewidth 1
rectangle 200,200,280,260, black
arc 50,150,16,100,90,180,black
arc 34,150,16,100,270,360,black
arc 34,50,16,100,0,90,black
arc 50,50,16,100,180,270,black
arc 200,230,16,60,90,270,black
arc 280,195,16,130,0,90,black
arc 296,195,16,130,180,270,black
arc 296,65,16,130,90,180,black
arc 280,65,16,130,-90,0,black

linewidth 3
rectangle 50,0,130,200, black
rectangle 200,0,280,260, blue
fill 210,5,pink
fill 210,255,pink
text black, 0, 110, medium, 100 %
text black, 60, 160, medium, valeur
text black, 60, 140, medium, initiale
text black, 60, 120, medium, en euros
text black, 180,240, medium, %
text blue, 210, 180, medium, valeur
text blue, 210, 160, medium, finale
text blue, 210, 140, medium,en euros
text black, 205, 250, small, augmentation
text black, 345,140, medium, %
}
\text{url1 = draw(400,350
\bar1)}
\text{turl1=Rectangle de hauteur 100% avec une valeur initiale à trouver et
un rectangle de même hauteur surmonté d'un petit rectangle avec valeur finale, augmentation,
 pourcentage d'augmentation et pourcentage total à trouver}

\text{bar2 = \bar1
text black, 60, 100, medium, \vi
text black, 150,240, medium, \p
text blue, 210, 120, medium,\vf
text black, 205, 230, small, \vp
text black, 315,140, medium, \pa
}
\text{url2 = draw(400,350
\bar2)}
\text{turl2=Rectangle 100% valeur initiale \vi Rectangle \pa % valeur finale \vf dont rectangle \p % augmentation de \vp}

\text{size1=3}

\matrix{tab1=1.,\name_header[1],\name_header[2]
\name_header[3],reply2,100 %
\name_header[4],reply4,reply3 %
\name_header[5],reply5,reply6 %}

\text{mat1=slib(text/matrixhtml [\tab1],wimscenter wimsborder,TH=[;1] CAPTION="Tableau de proportionnalité 1")}
