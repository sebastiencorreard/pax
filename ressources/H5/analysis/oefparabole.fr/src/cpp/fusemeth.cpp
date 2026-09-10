target=fusee0,fuseerep

\language{fr}
\range{-5..5}
\author{Rémi, Belloeil}
\email{remi.belloeil@orange.fr}
\computeanswer{yes}
\format{html}
\precision{10000}
\integer{d=randint(1..4)}

#if defined TARGET_fusee0
\title{La fusée au sommet avec plusieurs méthodes}
#define TYPE 2
%%Plusieurs méthodes sont proposées et peuvent être consultées sans réponses intermédiaires%%
\text{COND = 1}
#endif

#if defined TARGET_fuseerep
\title{La fusée au sommet avec réponses intermédiaires}
\text{COND = 1}
#define TYPE 3
%%Plusieurs méthodes sont proposées et peuvent être consultées avec des réponses intermédiaires%%
\integer{M5=0}
#endif
%% Liste des méthodes et icones %%
\text{\list=1,2,3,4,5}
\text{\list2=1,2,3,4,5}
#include "methode.inc"
\matrix{kaXc=
5,4,2.5,5
4,0.5,8,4
4.5,1.5,3,1
3,1,6,4}
\real{k=\kaXc[\d;1]}
\rational{a=\kaXc[\d;2]}
\rational{Xc=\kaXc[\d;3]}
\real{pas=\kaXc[\d;4]}
\rational{p=\a*\Xc/\k}
\real{Xs=\Xc+\p}
\real{Yc=\a*\Xc^2}
\real{Xd=\Xs+\p}
\real{dH=\k*\p^2}
\real{max=\Yc+\k*\p^2}
\real{k1=\max/\k}
\real{X3=sqrt(\k1)}
\real{X2=\Xs+\X3}
\function{c=\a*x^2+sqrt(x)*0+sqrt(\Xc+0.05-x)*0}
\function{r=-\k*x^2+sqrt(x+\p-0.02)*0+sqrt(\X3+0.05-x)*0}
\function{g=-\k*(x-\Xs)^2+\max+sqrt(x-\Xc+0.02)*0+sqrt(\X2+0.01-x)*0}
\integer{Xmax=25}
\integer{Xmin= -\p-1}
\integer{Ymin= -\max}
\integer{Ymax=1.125*\max}
\function{g1=-\k*(x-\Xs)^2+\max}
\function{g3=maxima(expand(\g1))}
\integer{b1=2*\k*\Xs}
\integer{c1=\k*(\Xs^2)-\max}
\function{g2=-\k*x^2+\b1*x-\c1}
\text{s = (0.5*animstep-\p)}
\text{tA = text black,-\p-0.2,-0.2,small,-\p}
\for{i = 1 to 20 }{
  \text{tA = \tA
text black,\i-0.2,-0.2,small,\i}
}
\rational{q=\max/\k}
\real{s3=sqrt(\q)}
\real{s2=\Xs+\s3}
\text{Ord=}
\for{i = \pas to \Ymax-2 step \pas}{
  \text{Ord=\Ord ; text black,-1.2,\i+0.4*\pas,small,\i}
}
\text{cadre=xrange \Xmin,\Xmax
yrange \Ymin,\Ymax
linewidth 1
parallel \Xmin,\Ymin,\Xmin,\Ymax,1,0,\Xmax+3,lightblue
parallel \Xmin,\pas,\Xmax,\pas,0,\pas,\Ymax,lightblue
parallel \Xmin,-\pas,\Xmax,-\pas,0,-\pas,\Ymax,lightblue

text black,0.5,\Ymax,medium,altitude en m
text black,\Xmax-4.5,\pas,medium,temps en s
linewidth 2
arrow \Xmin,0,\Xmax,0,10, black
arrow 0,\Ymin,0,\Ymax,10, black
text black \Xmin,-\p,medium,- \p
\tA
\Ord
plotsteps 500
text green,0.3,2*\pas,medium,f
text black,0.5,-3,medium,r
plot green,\c
plot black,\r
}
\text{graph1=\cadre
plot black, \r+\max
plot red,\g
text red,\Xs,\max-\pas,medium,g
}
\text{graph2=animate 2*\X3+2*\p+1,1,0
\graph1
linewidth 2
arrow \s,\max-\k*\s^2,\s+\Xs,\max-\k*\s^2,10,black
arrow \s,-\k*\s^2,\s,\max-\k*\s^2,10,black
arrow -\p,-\k*\p^2,-\p,\max-\k*\p^2,10,red
arrow -\p,\max-\k*\p^2,\Xc,\Yc,10,red
text black,\s-0.2,-2*\pas,medium,x-\Xs
text black,\s+\Xs-0.2,-2*\pas,medium,x
dsegment \s,-2*\pas,\s,\max-\k*\s^2,black
dsegment \s+\Xs,-2*\pas,\s+\Xs,\max-\k*\s^2,black
}
\text{ga=\(g(x) = r(x)+\Xs+M)}
\text{gb=\(g(x) = r(x+\Xs)+M)}
\text{gc=\(g(x) = r(x-\Xs)+M)}
\text{gd=\(g(x) = r(x)-\Xs+M)}


\integer{M1=0}
\integer{M2=0}
\integer{M3=0}
\integer{M4=0}

\text{W=}
\text{ETAPE = r1}

\nextstep{ \ETAPE}
\conditions{ \COND}

\statement{
<div class="wims_question">
<ul class="wims_nopuce">
<li>Un club organise le lancement d'une fusée. Maud explique que la fusée va d'abord
monter grâce à la puissance de son moteur pendant \Xc secondes.</li>
<li>Dans cette phase son altitude en mètres sera égale à \a multiplié par le carré du temps
\(x) écoulé depuis l'instant 0 en secondes,\(\a*x^2).</li>
<li>Elle montre la courbe en vert de la fonction notée \(f).</li>
<li>Au bout de \Xc secondes, le moteur va s'arrêter et la fusée va continuer à monter
pendant \p s puis elle va redescendre jusqu'au sol.</li>
<li>Dans cette deuxième phase, la courbe sera obtenue par une translation à partir de celle
de la fonction \(r) avec \(r(x) = -\k*x^2) qu'elle a tracée en noir.</li>
</ul>
</div>
<div class="wimscenter">
\if{\M1=0}
  {\draw{500,400}{\cadre}}
  {\draw{500,400}{\graph1}}
</div>
<p>
Le graphique doit être complété par la deuxième phase par translation de la courbe de \(r)
(voir la méthode géométrie).</p>
<div class="wims_question">
<ol>
<li>Jusqu'à quelle hauteur monte la fusée dans la première phase ?
\if{\W= répondre }{\embed{reply 2,8} m.}</li>
<li>De combien de mètres la fusée monte-t-elle dans la deuxième phase ?
\if{\W= répondre }{\embed{reply 3,8} m.}</li>
<li>On appelle g la fonction représentée dans cette deuxième phase. Quel est le maximum \(M) de la fonction g ?</li>
\if{\W= répondre }{\embed{reply 4,8} m.}
<li>Quelle est la formule de \(g) ?
\if{\W= répondre }{<ul class="wims_nopuce">
  <li>\embed{reply 5,1}</li><li>\embed{reply 5,2}</li><li>\embed{reply 5,3}</li>
  <li>\embed{reply 5,4}</li>
  </ul>
  Donne l'expression de \(g) en fonction de \(x) sans les lettres \(r) et \(M).<br>
  Rappel \(r(x) = -\k*x^2).<br>
  Vérifie que \(g(\Xc) = \Yc) et que \(g(\Xs) = M).<br>
  \(g(x) = ) \embed{reply 6,25}.
}
</li><li>
Au bout de combien de secondes après son départ la fusée retombe-t-elle au sol ?
\if{\W= répondre }{\embed{reply 7,8} s.}
</li>
</ol>
</div>
\if{\step=1}{
#include "listmeth.inc"
}{
#if defined TARGET_fuseerep
  \if{\M1=1}{<p>Dans la première phase, la fusée monte bien de \Yc m.</p>}
  \if{\M1=-1}{<p>Mauvaise réponse pour la hauteur maximale dans la première phase \(f(\Xc)).</p>}
  \if{\M5=1}{<p>Dans la deuxième phase la fusée continue bien à monter de \dH m.</p>}
  \if{\M5=-1}{<p>Mauvaise réponse pour la différence des altitudes maximales des phase 1 et 2.</p>}
  \if{\M2=1}{<p>La fusée monte bien jusqu'à \(M=\max) m.</p>}
  \if{\M2=-1}{<p>Mauvaise réponse pour l'altitude maximale de la fusée.</p>}
  \if{\M3=1}{<p>La formule est bien \gc.</p>}
  \if{\M3=-1}{<p>Mauvaise réponse pour la formule de \(g)</p>}
  \if{\M4=1}{<p>La fusée rejoint bien le sol au bout de \X2 s.</p>}
  \if{\M4=-1}{<p>Mauvaise réponse pour le retour au sol de la fusée.</p>}
#endif
<p>Choix : <b>\W</b>.<p>
}
\if{\W=géométrie}{
<ul class="wims_nopuce">
<li>Avec un logiciel de <b>géométrie</b> on peut refaire les courbes puis translater la courbe de
\(r) pour obtenir celle de \(g).</li>
<li>Par exemple, avec Geogebra, pour définir \(r) et \(f), écrire :</li>
<li>f=Fonction[x^2,0,\Xc]</li>
<li>r=Fonction[-\a x^2,-\p,8]</li>
<li>Définir un point A à la fin de la courbe de \(f) et un point B au début de celle de \(r).
<li>Puis effectuer une translation de la courbe de \(r) de B en A.</li>
</ul>
#if defined TARGET_fuseerep
<p>L'ordonnée de A est la hauteur maximale dans la phase 1, c'est \embed{reply8,8} m.</p>
#endif
}
\if{\W=tableaux}{
<p>Compléter le <b>tableau de valeurs</b> de la fonction \(r).</p>
<table class="wimscenter wimsborder">
<tr>
<td>\(x)</td><td>-\p</td><td>0</td><td>\p</td></tr>
<tr>
<td> \(r(x))</td><td>   </td><td>0</td><td> </td><td> </td></tr></table>
<p>Puis compléter le tableau de valeurs de la fonction \(g) qui prolonge la courbe de
\(f).</p>
<table class="wimscenter wimsborder"><tr>
<th>\(x)</th><td>\Xc</td><td>\Xs</td><td>\Xd</td></tr>
<tr>
<th> \(g(x))</th><td>\Yc</td><td> </td><td> </td><td> </td></tr>
</table>
<div>Le premier tableau permet de voir de combien de mètre la fusée va continuer à monter
dans la phase 2.
#if defined TARGET_fuseerep
\embed{reply9,8}
#endif

</div><div>En déduire le maximum \(M) de \(g).
#if defined TARGET_fuseerep
\embed{reply10,8}
#endif
</div>
}
\if{\W=fonctions}{
Observons le liens entre les <b>fonctions</b>.
<ul class="wims_nopuce">
<li>On doit avoir \(g(\Xc)=f(\Xc)).</li>
<li>Pour calculer la valeur de \(g(x)), on doit chercher l'image de \(x-\Xc-\p) par \(r) et lui
ajouter la bonne valeur.</li>
</ul>
La formule de \(g) est l'une des formules suivante :
#if defined TARGET_fusee0
<ul class="wims_nopuce">
<li>\(g(x)=r(x-\Xc)+M)</li>
<li>\(g(x)=r(x+\Xc)+M)</li>
<li>\(g(x)=r(x-\Xs)+M)</li>
<li>\(g(x)=r(x+\Xs)+M)</li>
</ul>
#endif

#if defined TARGET_fuseerep
<ul class="wims_nopuce">
<li>\embed{reply 5,1}</li><li>\embed{reply 5,2}</li><li>\embed{reply 5,3}</li>
<li>\embed{reply 5,4}</li>
</ul>
#endif
}
\if{\W=équation}{
<ul class="wims_nopuce">
<li>Pour déterminer à quel instant la fusée arrive au sol, on peut résoudre
  <b>l'équation</b> \(g(x)=0).</li>
<li>Si le graphique le permet, on peut résoudre graphiquement cette équation.<li>
<li>Sinon, il faut connaître la formule de \(g) (voir le lien entre les fonctions).</li>
<li>Puis on peut ramener l'équation \(g(x)=0) à \(X^2=k).</li>
</ul>
#if defined TARGET_fuseerep
<div>Au bout de combien de secondes la fusée revient-elle au sol ? \(x =) \embed{reply11,8} s.</div>
#endif
}

  \if{(\step>1) and (\W!=répondre)}{
    Choisir une autre méthode ou "répondre" :
    <ul>
    <li>\embed{reply1,1} \tch[1]</li>
    \if{\M1<1}{<li>\embed{reply1,2} : \tch[2]</li>}
    \if{\M2<1}{<li>\embed{reply1,3} : \tch[3]</li>}
    \if{\M3<1}{<li>\embed{reply1,4} : \tch[4]</li>}
    \if{\M4<1}{<li>\embed{reply1,5} : \tch[5]</li>}
    </ul>
  }
}
#include "reponses.inc"

\solution{
\draw{500,400}{\graph2}
<ul>
<li>Dans la première phase, la fusée monte jusqu'à \Yc m.</li>
<li>Dans la deuxième phase, elle continue à monter de \dH m jusqu'à une altitude de \(M =) \max m.</li>
<li>Dans cette deuxième phase, l'altitude \(y) en fonction du temps \(x) est :</li>
<li>\(y =) \gc \(= \g1).</li>
<li>La fusée atteint le sol lorsque \(g(x)=0) ce qui équivaut à :
    <ul class="wims_nopuce">
    <li>\(-\k(x-\Xs)^2=-\max)</li>
    <li>\((x-\Xs)^2=\k1)</li>
    <li>\((x-\Xs)=-\X3) ou \((x-\Xs)=\X3)</li>
    </ul>
</li><li>Or \(x > \Xs) donc \(x=\X2).</li>
</ul>
}
