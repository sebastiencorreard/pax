target=pararap1,pararap2,pararap3,pararap4,pararap5
#define TITRE Parallélisme
\author{Fabrice,Guerimand}
\email{fguerima@free.fr}
#if defined TARGET_pararap1
# define NUM 1
#endif
#if defined TARGET_pararap2
# define NUM 2
#endif
#if defined TARGET_pararap3
# define NUM 3
#endif
#if defined TARGET_pararap4
# define NUM 4
#endif
#if defined TARGET_pararap5
# define NUM 5
#endif
\title{TITRE NUM}
\matrix{sommets=A,B,C,D,E,F,G
E,F,G,H,I,J,K
M,N,O,P,Q,R,S}
\text{sommet=randrow(\sommets)}
\text{sommet=shuffle(\sommet)}

\text{sommet=row(1,\sommets)}

\text{A=item(1,\sommet)}
\text{B=item(2,\sommet)}
\text{C=item(3,\sommet)}
\text{D=item(4,\sommet)}
\text{E=item(5,\sommet)}
\text{F=item(6,\sommet)}
\text{G=item(7,\sommet)}
\text{liste=\A\D,\A\B,\A\E,\A\C,\D\E,\B\C,\D\B,\E\C}

#if defined TARGET_pararap1
 \title{TITRE 1}
 \text{dessin=segment 20,20,180,130,black
segment 20,20,50,180,black
segment 180,130,50,180,black
segment 35,100,100,75,black
text black,10,10,medium,\A
text black,190,135,medium,\B
text black,35,185,medium,\C
text black,25,100,medium,\E
text black,115,70,medium,\D }
 \integer{xrange=200}
 \integer{yrange=200}
#endif

#if defined TARGET_pararap2
 \title{TITRE 2}
 \text{dessin=segment 20,80,180,120,black
segment 90,30,110,170,black
segment 20,80,90,30,black
segment 180,120,110,170,black
text black,110,90,medium,\A
text black,5,70,medium,\B
text black,100,25,medium,\C
text black,95,170,medium,\E
text black,185,120,medium,\D}
 \integer{xrange=200}
 \integer{yrange=200}
#endif

#if defined TARGET_pararap3
 \title{TITRE 4}
 \text{dessin=range 0,200,0,200
segment 25,25,50,200,black
segment 25,25,175,200,black
segment 25,25,200,75,black
segment 38,113,86,96,red
segment 86,96,108,49,red
segment 49,191,140,159,red
segment 140,159,183,70,red
text black,23,23,medium,\A
text black,39,195,medium,\B
text black,182,68,medium,\C
text black,27,117,medium,\D
text black,108,45,medium,\E
text black,82,110,medium,\F
text black,137,175,medium,\G}
 \text{liste=\liste,\A\F,\A\G}
 \integer{xrange=200}
 \integer{yrange=200}
#endif

#if defined TARGET_pararap4
 \title{TITRE 5}
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
 \text{liste=\liste,\F\E,\E\D,\E\A}
 \integer{xrange=280}
 \integer{yrange=200}
#endif

#if defined TARGET_pararap5
 \title{TITRE 3}
 \text{dessin=segment 20,20,180,130,black
segment 20,20,50,180,black
segment 180,130,50,180,black
segment 31,78,78,60,black
segment 84,35,50,180,black
segment 84,35,20,20,black
text black,10,10,medium,\A
text black,190,135,medium,\B
text black,35,185,medium,\C
text black,21,78,medium,\E
text black,93,55,medium,\D
text black,90,30,medium,\F}
 \integer{xrange=200}
 \integer{yrange=200}
 \text{liste=\liste,\A\F,\F\D,\D\C,\C\F}
#endif

\text{rapports1=\A\D/\A\B,\A\E/\A\C}
\text{rapports2=\A\B/\A\D,\A\C/\A\E}
\text{image=draw(\xrange,\yrange
\dessin)}
\text{size=30x25x1}

\statement{
<ul class="wims_nopuce">
  <li>
  Quels sont les rapports à comparer pour décider du parallélisme des droites
  \((\D\E)) et \((\B\C)) sur la figure ci-contre ?
</li><li><b>Votre réponse :</b>
  Il faut comparer les rapports :
</li>
</ul>
<table class="wimscenter wimsnoborder">
<tr>
 <td>\embed{reply 1,\size}</td>
 <td rowspan="3"> et </td>
 <td> \embed{reply 3,\size}</td>
</tr><tr>
 <td style="width:\size2"><hr style="size:2"></td>
 <td style="width:size2"><hr style="size:2"></td>
</tr><tr>
 <td>\embed{reply 2,\size}</td>
 <td>\embed{reply 4,\size}</td>
</tr></table>

<div class="wims_instruction"> Utiliser les étiquettes ci-dessous pour compléter les égalités.</div>

<div class="wims_center"><img src="\image" alt=""></div>}

\reply{Numérateur1}{\num1;\liste}{type=clickfill}
\reply{Dénominateur1}{\den1;\liste}{type=clickfill}
\reply{Numérateur2}{\num2;\liste}{type=clickfill}
\reply{Dénominateur1}{\den2;\liste}{type=clickfill}

\text{tmplin=\num1/\den1,\num2/\den2}
\integer{nbrap=2}
\text{tmplin=wims(listuniq \tmplin)}
\text{set1=wims(listintersect \rapports1 and \tmplin)}
\text{set2=wims(listintersect \rapports2 and \tmplin)}
\integer{lin1=items(\tmplin)}
\integer{lin2=items(\set1)}
\integer{lin3=items(\set2)}

\condition{Bons rapports}{\lin1=\nbrap and (\lin2=\nbrap or \lin3=\nbrap)}
