target=nature1,nature2,nature3,nature4,nature5,nature6

\title{Nature d'un solide}
\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_nature1 
 \integer{num=1}
 \integer{l=150}
 \integer{h=75}
 \integer{p=50}
 \text{name=pave}
#endif

#if defined TARGET_nature2 
 \integer{num=2}
 \integer{l=100}
 \integer{h=100}
 \integer{p=50}
 \text{name=pave}
#endif

#if defined TARGET_nature3 
 \integer{num=3}
 \integer{l=75}
 \integer{h=125}
 \integer{p=25}
 \text{name=cone}
#endif

#if defined TARGET_nature4 
 \integer{num=4}
 \integer{l=120}
 \integer{h=150}
 \integer{p=80}
 \integer{h2=100}
 \integer{p2=randint(50..70)}
 \text{name=randitem(tetraedre,pyramide)}
#endif

#if defined TARGET_nature5 
 \integer{num=5}
 \integer{l=150}
 \integer{h=80}
 \text{name=sphere}
#endif

#if defined TARGET_nature6 
 \integer{num=6}
 \integer{l=75}
 \integer{h=125}
 \integer{p=25}
 \text{name=cylindre}
#endif

\text{bad=un parallélépipède rectangle,un cube,un cône,une pyramide,une sphère,un cylindre,un carré, un cercle, un rectangle, un triangle}
\text{rep=item(\num,\bad)}
\integer{e=0.5}
\text{dessin=slib(local/solide \name,\e,\l,\h,\p,\h2,\p2)}
\text{tmpfab=\dessin}
\text{tmp=wims(line 1 of \dessin)}
\text{dessin=wims(line 2 to -1 of \dessin)}
\integer{X=item(1,\tmp)}
\integer{Y=item(2,\tmp)}

\statement{
  Quel est le nom du solide représenté ci-dessous ?
<div class="wimscenter">
\draw{\X,\Y}{\dessin}
</div>

<strong>Votre réponse :</strong>
  C'est \embed{c1}.
}

\choice{Réponse}{\rep}{\bad}
