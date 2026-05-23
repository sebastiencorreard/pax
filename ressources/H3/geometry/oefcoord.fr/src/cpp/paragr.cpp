target=paragr

\title{Parallélogramme (4ième sommet graphique)}
\language{fr}
\range{-5..5}
#inlcude "author.inc"
\keywords{parallelogram}
\computeanswer{no}
\format{html}
\precision{10000}
\integer{xrange=400}
\integer{yrange=400}

\matrix{nom=A,B,C,D
E,F,G,H
M,N,R,P}
\text{don=randrow(\nom)}
\text{don=shuffle(\don)}
\text{A=item(1,\don)}
\text{B=item(2,\don)}
\text{C=item(3,\don)}
\text{D=item(4,\don)}
\integer{xa=random(-4..4)}
\integer{ya=random(-4..4)}
\integer{xb=random(-4..4)}
\integer{yb=random(-4..4)}
\integer{xc=random(-4..4)}
\integer{yc=random(-4..4)}
\integer{tmp=(\xb-(\xa))*(\yc-(\ya))-(\yb-(\ya))*(\xc-(\xa))}
\if{\tmp=0}{
 \integer{xa=1}
 \integer{ya=-1}
 \integer{xb=3}
 \integer{yb=5}
 \integer{xc=-2}
 \integer{yc=-2}
}
\matrix{don=\overrightarrow{\A \B},\xb-(\xa),\yb-(\ya),\A \B \D \C
\overrightarrow{\B \A},\xa-(\xb),\ya-(\yb),\A \B \C \D}
\text{don=randrow(\don)}
\text{vect=item(1,\don)}
\integer{Vx=item(2,\don)}
\integer{Vy=item(3,\don)}
\integer{xd=\xc+(\Vx)}
\integer{yd=\yc+(\Vy)}
\text{para=item(4,\don)}
\integer{Mx=maxima(max(\xa,\xb,\xc,\xd,0);)+1}
\integer{mx=maxima(min(\xa,\xb,\xc,\xd,0);)-1}
\integer{My=maxima(max(\ya,\yb,\yc,\yd,0);)+1}
\integer{my=maxima(min(\ya,\yb,\yc,\yd,0);)-1}
\text{graph=slib(draw/repere \xrange,\yrange,20,\mx,\Mx,\my,\My,1,1,black,grey)}
\text{ligne=row(1,\graph)}
\integer{x0=item(1,\ligne)}
\integer{y0=item(2,\ligne)}
\text{ligne=row(2,\graph)}
\real{ex=item(1,\ligne)}
\real{ey=item(2,\ligne)}
\text{repere=wims(line 3 to -1 of \graph)}
\text{repere=\repere
text black,\x0-10,\y0+4,small,O
text black,\x0+\ex-4,\y0+4,small,I
text black,\x0-12,\y0+\ey-4,small,J}
\integer{Ax=\ex*(\xa)+(\x0)}
\integer{Ay=\ey*(\ya)+(\y0)}
\integer{Bx=\ex*(\xb)+(\x0)}
\integer{By=\ey*(\yb)+(\y0)}
\integer{Cx=\ex*(\xc)+(\x0)}
\integer{Cy=\ey*(\yc)+(\y0)}
\integer{Dx=\ex*(\xd)+(\x0)}
\integer{Dy=\ey*(\yd)+(\y0)}
\text{color=red}
\text{dessin1=\repere
fcircle \Ax,\Ay,4,\color
text \color,\Ax+4,\Ay+4,medium,\A
fcircle \Bx,\By,4,\color
text \color,\Bx+4,\By+4,medium,\B}

\text{enonce=Sur la figure, on représente 3 points \(\A), \(\B) et \(\C) du
  plan muni du repère orthogonal \((O, I, J)).}
\text{dessin1=\dessin1
fcircle \Cx,\Cy,4,\color
text \color,\Cx+4,\Cy+4,medium,\C
}
\text{pt=\D}
\integer{X=\Dx}
\integer{Y=\Dy}

\text{dessin1=draw(\xrange,\yrange,
\dessin1)}
\integer{R=maxima(max(abs(\ex)/5,abs(\ey)/5);)}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\embed{r1}</div>
 <div class="medium_size text_col">
\enonce
  En cliquant sur la figure, placer le point \(\pt) tel que \(\para)
  soit un parallélogramme.
</div>
</div>
}
\answer{\pt}{\dessin1;circle,\X,\Y,\R}{type=coord}
