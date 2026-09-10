%% AXE GRADUÉ x'x avec demi-graduations %%
\text{taille=17}
\text{taille1=12}
\text{epsil=0.18}
\text{epsil2=0}
\text{epsil3=3}
\text{grad1=text blue,-10-0.25,-1.5,medium,-10}
\for{k= -9 to -1}{
  \text{grad1=\grad1
text blue,\k-0.25,-1.5,medium,\k}}

\text{grad2=text blue,0,-1.5,medium,0}
\for{k= 1 to 10}{
  \text{grad2=\grad2
text black,\k,-1.5,medium,\k}}

\text{Axe =
range -12,12,-8,8
linewidth 1
parallel -12,-1,-12,1,1,0,25,red
parallel -12,-0.5,-12,0.5,0.5,0,48,red
linewidth 3
arrow -12.0,0,12.0,0,20,blue
fcircle 0,0,\taille,blue
\grad1
\grad2
hline 0,0,black}

%% dessin des intervalles décrits par x et y %%

\real{xa=\a>0?\a:\a-0.25}
\real{xb=\b>0?\b:\b-0.25}
\real{xc=\c>0?\c:\c-0.25}
\real{xd=\d>0?\d:\d-0.25}

\text{dessin=
\Axe
fcircle 0,0,\taille1,blue
fcircle \a,\epsil2,\taille1,red
fcircle \b,\epsil2,\taille1,red
fcircle \c,-0.5,\taille1,green
fcircle \d,-0.5,\taille1,green
linewidth 4
segment \a,\epsil,\b,\epsil,red
segment \c,-0.5,\d,-0.5,green
text red,\xa,\epsil3,medium,\a
text red,\xb,\epsil3,medium,\b
text green,\xc,5,medium,\c
text green,\xd,5,medium,\d
}
%%# Visuel figurant le rectangle des paires (x,y) %%#

\integer{N=\R-\r+1}

\text{Encadrement=
   xrange \r,\R
   yrange \r,\R
   parallel \r,\r,\R,\r,0,1,\N, grey
   parallel \r,\r,\r,\R,1,0,\N, grey
   fpoly red,\a,\c,\b,\c,\b,\d,\a,\d
   arrow \r,0,\R,0,8,black
   arrow 0,\r,0,\R,8,black
   arrow 0,0,1,0,8, black
   arrow 0,0,0,1,8, black
   plot green, \eq[1]
   plot green, \eq[2]
   fcircle 0,0,10,black
   fcircle \res3,0,10,green
   fcircle \res4,0,10,green
   text black,-0.3,-0.5,times, O
   text black,\R-0.5,1,times, x
   text black,0.5,\R-0.25,times, y
   text black,\res3 -0.3,-0.5,times,\res3
   text black,\res4 -0.3,-0.5,times,\res4
}
