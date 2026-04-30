target=perpendiculaire1,perpendiculaire2,perpendiculaire3,perpendiculaire4,perpendiculaire5,perpendiculaire6,perpendiculaire7

\title{Section plane perpendiculaire}
\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_perpendiculaire1 
 \integer{num=1}
#endif
#if defined TARGET_perpendiculaire2 
 \integer{num=2}
#endif
#if defined TARGET_perpendiculaire3 
 \integer{num=3}
#endif
#if defined TARGET_perpendiculaire4 
 \integer{num=4}
#endif
#if defined TARGET_perpendiculaire5 
 \integer{num=5}
#endif
#if defined TARGET_perpendiculaire6 
 \integer{num=6}
#endif
#if defined TARGET_perpendiculaire7 
 \integer{num=7}
#endif

\matrix{donnees=pave,cube,100,100,50,,,une face,2,
pave,cube,100,100,50,,,une arête,1,
pave,parallélépipède rectangle,75,125,25,,,une face,2,
pave,parallélépipède rectangle,75,125,25,,,une arête,2,
cone,cône de révolution,75,125,25,,,sa base,4,
cone,cône de révolution,75,125,25,,,son axe de révolution,3,
cylindre,cylindre de révolution,75,125,25,,,sa base,2,
cylindre,cylindre de révolution,75,125,25,,,son axe de révolution,3,}

\text{don=row(\num,\donnees)}
\text{bad=carré,rectangle,cercle,triangle,parallélogramme,cube,parallélépipède rectangle,cône de révolution,pyramide,cylindre}
\text{name=item(1,\don)}
\text{solidename=item(2,\don)}
\text{mesures=wims(item 3 to 7 of \don)}
\text{enonce=item(8,\don)}
\integer{rep=item(9,\don)}
\text{rep=item(\rep,\bad)}
\text{complement=item(10,\don)}
\integer{e=0.5}
\text{dessin=slib(local/solide \name,\e,\mesures)}
\text{tmp=wims(line 1 of \dessin)}
\text{dessin=wims(line 2 to -1 of \dessin)}
\integer{X=item(1,\tmp)}
\integer{Y=item(2,\tmp)}

\statement{
  On coupe le \solidename ci-dessous perpendiculairement à \enonce.
  Quelle sera la nature de la section plane obtenue ?
<div class="wimscenter">
\draw{\X,\Y}{\dessin}
</div>

<strong>Votre réponse :</strong>
  C'est \embed{c1}.
}

\choice{Réponse}{\rep}{\bad}
