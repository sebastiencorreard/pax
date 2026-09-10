target=diode
#include "author.inc"
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
#include "lang_titles.inc"
#include "lang.inc"

\integer{sig=randitem(1,-1)}
\integer{sid=randitem(1,-1)}
\matrix{liste=g,0,L,l,0,dl,0
g,d,L,l,0,l,0
g,0,dL,l,0,l,0
g,0,dl,0,0,dl,0
g,0,l,0,0,dl,0}
\text{n=rows(\liste)}
\text{schoix=randint(1..\n)}
\text{choix=row(\schoix,\liste)}

\text{circuit=2,0.5,0,0.5,0,5,5,5,5,0.5,3,0.5}
\text{dessin=polyline black ,\circuit
segment 0,3,5,3, black }

\text{pos1=2,0.5,3,0.5}
\text{pos2=5,1,5,2}
\text{pos31=4,3,3,3}
\text{pos32=2,3,1,3}
\text{pos4=0,1,0,2}
\text{pos62= 1,5,2,5}
\text{pos63= 3,5,4,5}
\matrix{position= 2,0.5,3,0.5
2,0.5,3,0.5
5,1,5,2
5,1,5,2
4,3,3,3
2,3,1,3
0,1,0,2
0,2,0,1
0
0
 2,5,1,5,
 4,5,3,5}
 \text{test=0}
\for{i=1 to 7}
{
\if{ d isin item(\i, \choix) }{\integer{test=\test+1}
\text{s=\sid}
\if{\test=2 }{\text{sid2=randitem(1,-1)}
\text{s=\sid2}}
\text{pos=row(2*\i-1,\position)}
\text{pos=\s=-1? item(3,\pos),item(4,\pos),item(1,\pos),item(2,\pos)}
\real{a=item(1,\pos)}
\real{b=item(2,\pos)}
\real{c=item(3,\pos)}
\real{d=item(4,\pos)}
\real{u=(\a+(\c))/2}
\real{v=(\b+(\d))/2}
\real{d1= \c-(\a)}
\real{d2=\d-(\b)}
\text{dessin=\dessin
segment \a+(\d2)/2,\b-(\d1)/2,\a-(\d2)/2,\b+(\d1)/2, black
fpoly black,\a,\b,\c+(\d2)/2,\d-(\d1)/2, \c-(\d2)/2,\d+(\d1)/2}
}
\if{ g isin item(\i, \choix) }{
\text{pos=row(2*\i-1,\position)}
\text{couleur= black}
\text{pos=\sig=-1? item(3,\pos),item(4,\pos),item(1,\pos),item(2,\pos)}}
\if{l isin item(\i, \choix) }{
\text{pos=row(2*\i,\position)}
\text{couleur=\i<5 ? blue: red}}
\real{a=item(1,\pos)}
\real{b=item(2,\pos)}
\real{c=item(3,\pos)}
\real{d=item(4,\pos)}
\real{u=(\a+\c)/2}
\real{v=(\b+\d)/2}
\real{diam= ((\c-\a)^2+(\d-\b)^2)^(1/2)}
\if{l isin item(\i, \choix) }{
\text{dessin=\dessin
ellipse \u,\v,\diam,\diam,\couleur
segment  \a,\b,\c,\d,\couleur
linewidth 5
segment (3*(\a)+(\c))/4,(3*(\b)+(\d))/4,(3*(\c)+(\a))/4,(3*(\d)+(\b))/4, \couleur
linewidth 1
}}
\if{g isin item(\i, \choix) }{
\text{plus=\a<\c ? +:-}
\text{moins=\a<\c ? -:+}
\real{r=max(\a,\c)+ 1}
\real{s=min(\a,\c)- 1}
\text{dessin=\dessin
ellipse \u,\v,\diam,\diam,\couleur
text black, \u-0.1,\v+0.3, medium, G
text black, \r,\v,medium,\plus
text black, \s,\v,medium,\moins
}
}
\if{L isin item(\i, \choix) }{
\text{pos=row(2*\i,\position)}
\real{a=item(1,\pos)}
\real{b=item(2,\pos)}
\real{c=item(3,\pos)}
\real{d=item(4,\pos)}
\real{u=(\a+\c)/2}
\real{v=(\b+\d)/2}
\real{diam= ((\c-\a)^2+(\d-\b)^2)^(1/2)}
\text{dessin=\dessin
ellipse \u,\v,\diam,\diam,black
segment  \a,\b,\c,\d,\couleur
linewidth 5
segment (3*(\a)+(\c))/4,(3*(\b)+(\d))/4,(3*(\c)+(\a))/4,(3*(\d)+(\b))/4, \couleur
linewidth 1
}
}
}
\matrix{rep= g00l0dl0, 2,\sig-(\sid)
gd0l0l0,\sig-(\sid),\sig-(\sid)
g0dl0l0,2,2
g0dl00dl0, \sig-(\sid),\sig-(\sid2)
g0l00dl0, 2, \sig-(\sid)}

\text{rep1= item(2,row(\schoix,\rep))}
\real{u1=abs(\rep1)/2+1}
\text{rep1=item(\u1,\choixrep)}
\text{rep2= item(3,row(\schoix,\rep))}
\real{u2=abs(\rep2)/2+1}
\text{rep2=item(\u2,\choixrep)}
\statement{\name_enonce[1], \name_enonce[2]
\if{\test=2}{\name_enonce[3]}{\name_enonce[4]} :
<div class="wimscenter">\draw{200,200}{xrange -2,7
yrange -2,7
\dessin}
</div>
\name_question[1] \embed{choice 1} \name_question[2] \embed{choice 2}.
}

\choice{\name_answer[1]}{\rep2}{\choixrep}
\choice{\name_answer[2]}{\rep1}{\choixrep}
