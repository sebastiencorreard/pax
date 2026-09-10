\text{name_header=Valeurs,Pourcentage,Valeur initiale,Diminution,Valeur finale}

%% Choix des valeurs %%
\real{\vi=20+randint(1..79)}
\integer{p = randint(1..20)}
\integer{pd = 100 - \p}
\real{vp =\vi*0.01*\p}
\real{\vf=\vi-\vp}
\real{k=1-0.01*\p}
\text{ax=}

#if defined TARGET_coeff2
\function{fk=1-p/100}
\text{L1=Une action qui valait \vi &euro; diminue de \p %. Quelle est sa nouvelle valeur ?}
\text{sy1= &euro;}
\text{L2=Lorsqu'une quantité diminue de \p %, par quel nombre faut-il multiplier la valeur initiale pour obtenir la valeur finale ?}
\text{sy2= (nombre)}
\text{L3=Lorsqu'une quantité diminue de \(p) %, par quel nombre faut-il multiplier la valeur initiale pour obtenir la valeur finale ?}
\text{sy3= (formule)}
#endif
#if defined TARGET_percentdim
\function{fd=x-y}
\function{fp=(x-y)/x*100}
\text{L1=Une action qui valait \vi &euro; vaut maintenant \vf &euro;. Quel est le pourcentage de diminution ?}
\text{sy1= %}
\text{L2=Lorsqu'une quantité qui valait \(x) vaut maintenant \(y), de combien a-t-elle diminué ?}
\text{sy2= (formule)}
\text{L3=Lorsqu'une quantité qui valait \(x) vaut maintenant \(y), de quel pourcentage a-t-elle diminué ?}
\text{sy3= % (formule)}
#endif
#if defined TARGET_percentref3
\function{fi=y/(1-p/100)}
\text{L1=Une action a diminué de \p %. Sa nouvelle valeur est \vf &euro;. Quelle était sa valeur initiale ?}
\text{sy1= &euro;}
\text{L2=Une action a diminué de \p %. Par quel nombre faut-il multiplier sa valeur initiale \(x) pour obtenir sa valeur finale \(y) ?}
\text{sy2= (nombre)}
\text{L3=Une action a diminué de \(p) %, quelle formule permet de calculer sa valeur initiale \(x) à partir de sa valeur finale \(y) et de \(p) ?}
\text{ax= \(x =)}
\text{sy3= (formule)}
\text{fl2 = draw(80,16
segment 1,0,3,13,red
segment 1,0,8,3,red
arc 40,0,78,30,20,360,red)}
#endif

%% Diagrammes en barres
\text{bar1 = xrange 0,400
yrange -10,230
text black, 0,230, giant,Pourcentage de diminution
linewidth 1
rectangle 200,200,280,140, black
arc 50,150,16,100,90,180,black
arc 34,150,16,100,270,360,black
arc 34,50,16,100,0,90,black
arc 50,50,16,100,180,270,black
arc 200,170,16,60,90,270,black
arc 280,105,16,70,0,90,black
arc 296,105,16,70,180,270,black
arc 296,35,16,70,90,180,black
arc 280,35,16,70,-90,0,black


linewidth 3
rectangle 50,0,130,200, black
rectangle 200,0,280,140, blue
fill 210,5,pink
text black, 0, 110, medium, 100 %
text black, 60, 160, medium, valeur
text black, 60, 140, medium, initiale
text black, 60, 120, medium, en euros
text black, 180,180, medium, %
text blue, 210, 120, medium, valeur
text blue, 210, 100, medium, finale
text blue, 210, 80, medium,en euros
text black, 205, 190, small, diminution
text black, 345,80, medium, %
}
\text{url1 = draw(400,240
\bar1)}
\text{bar2 = \bar1
text black, 60, 100, medium, \vi
text black, 150,180, medium, \p
text blue, 210, 60, medium,\vf
text black, 205, 160, small, \vp
text black, 315,80, medium, \pd
}
\text{url2 = draw(400,240
\bar2)}
\text{turl2=Rectangle 100% valeur initiale \vi Rectangle \pa % valeur finale \vf surmonté d'un rectangle \p % diminution de \vp}
u
