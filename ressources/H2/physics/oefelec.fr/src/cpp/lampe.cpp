target=lampe

#include "author.inc"
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
#include "lang_titles.inc"
#include "lang.inc"

\real{n=randitem(4.5,6,9,12)}
nombre de lampes
\integer{m=randint(2..4)}
\text{choix=random(1,2,3,4,6)}
\text{m=\choix=3 ? 4}
\text{m=\choix>=5? 4}
\text{m=\choix=4 ? 3}
\text{lamp=\(L_1)}
\for{i=2 to \m}{\text{lamp=\lamp, \(L_\i)}}
\integer{u=randint(1..\m)}
\real{N=randitem(9,\n*\m,2*\n,\m*\n/2,6,18)}

choix 1 en parallèle :
choix 2 en série :

choix 3 : en parallèles deux par deux
choix 4 : en parallèles deux +un
choix   trois + un
\text{couleur=yellow}
\text{circuit=2,0.5,0,0.5,0,5,5,5,5,0.5,3,0.5}

\text{pos1=\choix>1 ? 1,5,2,5}
\text{pos1=\choix=1  ? 2,5,3,5}
\real{a=item(1,\pos1)}
\real{b=item(2,\pos1)}
\real{c=item(3,\pos1)}
\real{d=item(4,\pos1)}
\real{u1=(\a+\c)/2}
\real{v=(\b+\d)/2}
\real{diam= ((\c-\a)^2+(\d-\b)^2)^(1/2)}
\text{R1=ellipse \u1,\v,\diam,\diam,\couleur
segment \a,\b,\c,\d,\couleur
linewidth 5
segment (3*(\a)+(\c))/4,(3*(\b)+(\d))/4,(3*(\c)+(\a))/4,(3*(\d)+(\b))/4, \couleur
linewidth 1}

\text{pos2=\choix>1 ? 3,5,4,5}
\text{pos2=\choix=1  ? 3,4,4,4}
\text{pos2=\choix=4  ? 3,3,4,3}
\real{a=item(1,\pos2)}
\real{b=item(2,\pos2)}
\real{c=item(3,\pos2)}
\real{d=item(4,\pos2)}
\real{u1=(\a+\c)/2}
\real{v=(\b+\d)/2}
\real{diam= ((\c-\a)^2+(\d-\b)^2)^(1/2)}
\text{R2=ellipse \u1,\v,\diam,\diam,\couleur
segment \a,\b,\c,\d,\couleur
linewidth 5
segment (3*(\a)+(\c))/4,(3*(\b)+(\d))/4,(3*(\c)+(\a))/4,(3*(\d)+(\b))/4, \couleur
linewidth 1}
\text{pos3=\choix=1? 1,3,2,3}
\text{pos3=\choix=3 or \choix=4? 1,3,2,3}
\text{pos3=\choix=2 ? 0,2.5,0,3.5}
\text{pos3= \choix=6? 0,3.5,0,4.5}
\text{pos3= \choix=5? 0,1,0,2}
\real{a=item(1,\pos3)}
\real{b=item(2,\pos3)}
\real{c=item(3,\pos3)}
\real{d=item(4,\pos3)}
\real{u1=(\a+\c)/2}
\real{v=(\b+\d)/2}
\real{diam= ((\c-\a)^2+(\d-\b)^2)^(1/2)}
\text{R3=ellipse \u1,\v,\diam,\diam,\couleur
segment \a,\b,\c,\d,\couleur
linewidth 5
segment (3*(\a)+(\c))/4,(3*(\b)+(\d))/4,(3*(\c)+(\a))/4,(3*(\d)+(\b))/4, \couleur
linewidth 1}

\text{pos4=\choix=2? 5,2.5,5,3.5}
\text{pos4=\choix=1? 3,2,4,2}
\text{pos4=\choix=3 or \choix>=5? 3,3,4,3}
\real{a=item(1,\pos4)}
\real{b=item(2,\pos4)}
\real{c=item(3,\pos4)}
\real{d=item(4,\pos4)}
\real{u1=(\a+\c)/2}
\real{v=(\b+\d)/2}
\real{diam= ((\c-\a)^2+(\d-\b)^2)^(1/2)}
\text{R4=ellipse \u1,\v,\diam,\diam,\couleur
segment \a,\b,\c,\d,\couleur
linewidth 5
segment (3*(\a)+(\c))/4,(3*(\b)+(\d))/4,(3*(\c)+(\a))/4,(3*(\d)+(\b))/4, \couleur
linewidth 1}

\matrix{R=\pos1
\pos2
\pos3
\pos4}
\text{dessin=polyline black ,\circuit}
\for{i=1 to \m}
{\text{f=item(1..2,row(\i,\R))}
\text{f=item(1,\f)-1,item(2,\f)}
\text{dessin=\dessin
text black,\f, medium,L\i}}

\text{pos=2,0.5,3,0.5}
\real{a=item(1,\pos)}
\real{b=item(2,\pos)}
\real{c=item(3,\pos)}
\real{d=item(4,\pos)}
\real{u1=(\a+\c)/2}
\real{v=(\b+\d)/2}
\real{diam= ((\c-\a)^2+(\d-\b)^2)^(1/2)}
\text{gen=ellipse \u1,\v,\diam,\diam,black
text black, \u1-0.1,\v+0.2, medium, G
text black, \u1-1,\v,medium,+
text black, \u1+1,\v,medium,-}

\text{dessin=\dessin
\gen
\R1
\R2}
\text{dessin=\choix=1?\dessin
polyline black ,0,4,5,4
text }

\if{\m>=3}{
\text{dessin=\dessin
\R3}
\text{dessin=\choix=1 or \choix>=3?\dessin
polyline black ,0,3,5,3}
}
\if{\m>=4}{
\text{dessin=\dessin
\R4}
\text{dessin=\choix=1?\dessin
polyline black ,0,2,5,2}
}

\if{\choix=2}{\text{rep=item(sign(\m*\n-\N) +2,\listechoix)}}
\if{\choix=1}{\text{rep=item(sign(\n-\N) +2,\listechoix)}}
\if{\choix=3}{\text{rep=item(sign(2*\n-\N) +2,\listechoix)}}
\if{\choix=4}{\text{rep=\u=1 ? item(sign(\n-\N) +2,\listechoix): item(sign(2*\n-\N) +2,\listechoix)}}
\if{\choix=5}{\text{rep=\u>=3? item(sign(2*\n-\N) +2,\listechoix): item(sign(3*\n-\N) +2,\listechoix)}}
\if{\choix=6}{\text{rep=\u=4? item(sign(\n-\N) +2,\listechoix): item(sign(3*\n-\N) +2,\listechoix)}}
\statement{\name_enonce[1] \lamp \name_enonce[2] \n Volts.\name_enonce[3] \N V.
<div class="wimscenter">\draw{200,200}{xrange -2,7
yrange -2,7
\dessin}
</div>
 \name_enonce[4] \(L_\u\) \name_enonce[5] \embed{choice 1}}

\choice{\name_answer \(L_\u)}{\rep}{\listechoix}
