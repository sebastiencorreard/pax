target=egarap1,egarap2,egarap3,egarap4,egarap5
#define TITRE Égalités de rapports
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
#if defined TARGET_egarap1
# define NUM 1
#endif
#if defined TARGET_egarap2
# define NUM 2
#endif
#if defined TARGET_egarap3
# define NUM 3
#endif
#if defined TARGET_egarap4
# define NUM 4
#endif
#if defined TARGET_egarap5
# define NUM 5
#endif
\title{TITRE NUM}
\matrix{sommets=A,B,C,D,E,F
E,F,G,H,I,J
M,N,O,P,Q,R}
\text{sommet=randrow(\sommets)}
\text{sommet=shuffle(\sommet)}

\text{A=item(1,\sommet)}
\text{B=item(2,\sommet)}
\text{C=item(3,\sommet)}
\text{D=item(4,\sommet)}
\text{E=item(5,\sommet)}
\text{F=item(6,\sommet)}
\text{liste=\A \D,\A \B,\A \E,\A \C,\D \E,\B \C,\D \B,\E \C}

#if defined TARGET_egarap1
\text{dessin=segment 20,20,180,130,black
segment 20,20,50,180,black
segment 180,130,50,180,red
segment 35,100,100,75,red
text black,10,10,medium,\A
text black,190,135,medium,\B
text black,35,185,medium,\C
text black,25,100,medium,\E
text black,115,70,medium,\D }
 \text{comp=Les deux droites rouges sont parallèles et les points \E et \D appartiennent respectivement aux segments [\A\C] et [\A\B].}
 \integer{xrange=200}
 \integer{yrange=200}
#endif
#if defined TARGET_egarap2
 \text{dessin=segment 20,80,180,120,black
segment 90,30,110,170,black
segment 20,80,90,30,red
segment 180,120,110,170,red
text black,110,90,medium,\A
text black,5,70,medium,\B
text black,100,25,medium,\C
text black,95,170,medium,\E
text black,185,120,medium,\D}
 \text{comp=\A est le point d'intersection de (\E\C) et (\B\D). Les deux droites rouges sont parallèles.}
 \integer{xrange=200}
 \integer{yrange=200}
#endif

#if defined TARGET_egarap3
 \text{dessin=segment 90,80,250,120,black
segment 160,30,180,170,black
segment 20,130,160,30,black
segment 20,130,180,170,black
segment 250,120,180,170,black
text black,180,90,medium,\A
text black,75,70,medium,\B
text black,170,25,medium,\C
text black,170,175,medium,\E
text black,255,120,medium,\D
text black,5,130,medium,\F}
 \text{liste=\liste,randitem(\F \E,\F \B)}
 \text{comp=\(\B \D \E \F) est un parallélogramme, \B appartient au segment [\F\C] et \A est le point d'intersection des droites (\C\E) et (\B\D).}
 \integer{xrange=280}
 \integer{yrange=200}
#endif

#if defined TARGET_egarap4
 \text{dessin=segment 90,80,250,120,black
segment 160,30,180,170,black
segment 20,130,160,30,black
segment 20,130,180,170,black
segment 250,120,180,170,black
text black,180,90,medium,\E
text black,75,70,medium,\D
text black,170,25,medium,\A
text black,170,175,medium,\C
text black,255,120,medium,\F
text black,5,130,medium,\B}
 \text{liste=\liste,randitem(\F \E,\F \C)}
 \text{comp=\(\D \F \C \B) est un parallélogramme, \D appartient au segment [\A\B] et \E est le point d'intersection des droites (\D\F) et (\A\C).}
 \integer{xrange=280}
 \integer{yrange=200}
#endif
#if defined TARGET_egarap5
 \text{dessin=segment 20,20,180,130,black
segment 20,20,50,180,black
segment 180,130,50,180,red
segment 31,78,78,60,red
segment 84,35,50,180,black
segment 84,35,20,20,black
text black,10,10,medium,\A
text black,190,135,medium,\B
text black,35,185,medium,\C
text black,21,78,medium,\E
text black,93,55,medium,\D
text black,90,30,medium,\F}
 \text{comp=Les deux droites rouges sont parallèles, le point \E appartient au segment [\A\C] et le point \D est l'intersection de (\A\B) et (\F\C).}
 \integer{xrange=200}
 \integer{yrange=200}
 \text{liste=\liste,\A \F,\F \D,\D \C,\C \F}
#endif

\text{rapports1=\A \D/\A \B,\A \E/\A \C,\D \E/\B \C}
\text{rapports2=\A \B/\A \D,\A \C/\A \E,\B \C/\D \E}
\text{image=draw(\xrange,\yrange
\dessin)}
\text{size=35x25x1}

\statement{
<ul class="wims_nopuce">
<li>
\comp
</li><li>
  Quelles égalités de rapports peut-on écrire en utilisant le théorème de Thalès ?
 </li>
</ul>
<div class="wimscenter">
<img src="\image" alt=""></div>
<p>Votre réponse : </p>
<table class="wimscenter wimsnoborder">
<tr>
<td>\embed{reply 1,\size}</td>
<td rowspan="3">  = </td>
<td> \embed{reply 3,\size}</td>
<td rowspan="3"> = </td>
<td> \embed{reply 5,\size}</td>
</tr><tr>
<td style="width:\size2"><hr style="size:2"></td>
<td style="width:\size2"><hr style="size:2"></td>
<td style="width:\size2"><hr style="size:2"></td>
</tr><tr>
<td> \embed{reply 2,\size}</td>
<td> \embed{reply 4,\size}</td>
<td> \embed{reply 6,\size}</td>
</tr></table>
<div class="wims_instruction"> Utiliser les étiquettes ci-dessous
 pour compléter les égalités.</div>
}

\reply{numérateur1}{\num1;\liste}{type=clickfill}
\reply{dénominateur1}{\den1;\liste}{type=clickfill}
\reply{numérateur2}{\num2;\liste}{type=clickfill}
\reply{dénominateur1}{\den2;\liste}{type=clickfill}
\reply{numérateur3}{\num3;\liste}{type=clickfill}
\reply{dénominateur3}{\den3;\liste}{type=clickfill}

\text{tmplin=\num1/\den1,\num2/\den2,\num3/\den3}
\integer{nbrap=3}
\text{tmplin=wims(listuniq \tmplin)}
\text{set1=wims(listintersect \rapports1 and \tmplin)}
\text{set2=wims(listintersect \rapports2 and \tmplin)}
\integer{lin1=items(\tmplin)}
\integer{lin2=items(\set1)}
\integer{lin3=items(\set2)}

\condition{Bons rapports}{\lin1=\nbrap and (\lin2=\nbrap or \lin3=\nbrap)}
