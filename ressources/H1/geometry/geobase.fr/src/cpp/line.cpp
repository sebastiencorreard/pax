target=line1 line2 line3

#if defined TARGET_line1
affichage de 3 points
# define NUM 1
#endif
#if defined TARGET_line2
affichage de N points
# define NUM 2
#endif
#if defined TARGET_line3
affichage de N points
# define NUM 
#endif
#include "lang_titles.inc"
#include "lang.inc"

\author{Paul, Byache} (et Bernadette Perrin-Riou pour l'idée originale et le code de la première version de l'exercice)
\email{paul@byache.fr}

\text{liste=shuffle(A,B,C,P,Q,R)}
\text{abscisse1=shuffle(30)}
\integer{cnt=items(\liste)}
#if defined TARGET_line1
\integer{N=3} affichage de 3 points
#endif
#if defined TARGET_line2 || defined TARGET_line3
\integer{N=randint(4..6)} affichage de N points
#endif
#if defined TARGET_line3
\real{hh=0.3} hauteur des lettres
#endif
#if defined TARGET_line1 || defined TARGET_line2
\real{hh=0.1} hauteur des lettres
#endif
\integer{cnt=min(\cnt,\N)}
\text{abscisse=\abscisse1[1..\cnt]}
\text{abscisse=wims(sort numeric item \abscisse)}

\integer{xmin=-2}
\integer{xmax=32}
\text{dessin=xrange \xmin,\xmax
yrange -1,1
hline 0,0,black}
\for{j=1 to \cnt}{
  \text{dessin=\dessin
text black,\abscisse[\j],\hh,large,\liste[\j]
segment \abscisse[\j],-0.05,\abscisse[\j],0.05,black}
}

\text{l=wims(makelist x for x= 1 to \cnt)}
\text{trois=randitem(\l)}
\text{undeux=wims(listcomplement \trois in \l)}
\text{undeux=\undeux[1,2]}
\text{undeux=wims(sort numeric item \undeux)}
\text{points= \liste[\undeux,\trois]}
\text{symb=\lbrack,\rbrack,\lpar,\rpar}

#ci-dessous : 1 signifie crochet gauche, 2 crochet droit, 3 parenthèse gauche, 4 parenthèse droite
\text{alea=randrow(1,2
1,2
1,2
1,2
1,4
1,4
3,4)}
# deux lignes 3,2 supprimées ci-dessus pour éviter la notation (AB] pour une demi-droite

#if defined TARGET_line1 || defined TARGET_line2
\if{\alea[1]=1 and \alea[2]=2}{
  \text{rep=\trois >= \undeux[1] and \trois <= \undeux[2] ? 1:2}
}
\if{\alea[1]=1 and \alea[2]=4}{
  \text{rep= \trois >= \undeux[1] ? 1:2}
}
\if{\alea[1]=3 and \alea[2]=2}{
  \text{rep= \trois <= \undeux[2] ? 1:2}
}
\if{\alea[1]=3 and \alea[2]=4}{
  \text{rep=1}
}
\text{dessinfeed= \dessin
linewidth 3
text red,\abscisse[\troix],0.2,large,\liste[\trois]
segment \abscisse[\trois],-0.1,\abscisse[\trois],0.1,red
}
\if{\alea[1]=1 and \alea[2]=2}{
  \text{dessinfeed= \dessinfeed
segments blue,\abscisse[\undeux[1]],0,\abscisse[\undeux[2]],0
segment \abscisse[\undeux[1]],-0.1,\abscisse[\undeux[1]],0.1,blue
segment \abscisse[\undeux[2]],-0.1,\abscisse[\undeux[2]],0.1,blue}
}
\if{\alea[1]=1 and \alea[2]=4}{
  \text{dessinfeed= \dessinfeed
demilines blue,\abscisse[\undeux[1]],0,\abscisse[\undeux[2]],0
segment \abscisse[\undeux[1]],-0.1,\abscisse[\undeux[1]],0.1,blue}
}
\if{\alea[1]=3 and \alea[2]=2}{
  \text{dessinfeed= \dessinfeed
demilines blue, \abscisse[\undeux[2]],0,\abscisse[\undeux[1]],0
segment \abscisse[\undeux[2]],-0.1,\abscisse[\undeux[2]],0.1,blue}
}
\if{\alea[1]=3 and \alea[2]=4}{
  \text{dessinfeed= \dessinfeed
lines blue, \abscisse[\undeux[2]],0,\abscisse[\undeux[1]],0}
}
#endif
#if defined TARGET_line3
\text{dessin=draw(600,200
\dessin)}
\text{rep=slib(draw/convpixel \abscisse[\trois],0,600,200,-2,32,-1,1,0,pixels)}
#endif
#if defined TARGET_line1 || defined TARGET_line2
\text{dessin=canvasdraw(600,200
\dessin)}
\text{dessinfeed=canvasdraw(600,200
\dessinfeed)}
\text{choix=shuffle(\name_choix)}
#endif
\statement{
#if defined TARGET_line1 || defined TARGET_line2
\name_statement[1] \(\points[3]\) \name_statement[2]
\(\symb[\alea[1]] \points[1] \points[2] \symb[\alea[2]]\)?
\dessin
#endif
#if defined TARGET_line3
\name_statement[1] 
 \points[3] .
\embed{r1}
#endif
}
#if defined TARGET_line1 || defined TARGET_line2
\choice{\name_answer}{\name_choix[\rep]}{\choix}
\feedback{1=1}{
<div class="wimscenter">\dessinfeed</div>
}
#endif
#if defined TARGET_line3
\answer{\name_answer}{\dessin;point,\rep}{type=coord}{option=goodanswershown}
\text{resu=wims(declosing \reply1)}
\feedback{\resu[2]<93}{\name_feedback}
#endif
