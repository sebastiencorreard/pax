target= placerangle1 placerangle2 placerassoc1 placerassoc2
#if defined TARGET_placerangle1
 \title{Placer un angle 1}
#endif
#if defined TARGET_placerangle2
 \title{Placer un angle 2}
#endif
#if defined TARGET_placerassoc1
 \title{Placer un angle associé 1}
#endif
#if defined TARGET_placerassoc2
 \title{Placer un angle associé 2}
#endif
\language{fr}
\author{David Doyen}
\email{david.doyen@u-pem.fr}

\if{\confparm1=}{
\text{typarg=randitem(1,2,3,4)}
}{
\text{typarg=randitem(\confparm1,\confparm1)}
}

#if defined TARGET_placerangle1 || TARGET_placerangle2
#if defined TARGET_placerangle1 
\text{k=0}
#endif
#if defined TARGET_placerangle2
\text{k=randitem(1/2,1,3/2,1/4,3/4,5/4,7/4,1/3,2/3,4/3,5/3,1/6,5/6,7/6,11/6)}
#endif
\text{al=simplify(randitem(-1,1)*\k*pi)}
\real{Ax=cos(\al)}
\real{Ay=sin(\al)}
\if{\typarg=1}{
\text{k=randitem(1/2,1,3/2)}
}
\if{\typarg=2}{
\text{k=randitem(1/4,3/4,5/4,7/4)}
}
\if{\typarg=3}{
\text{k=randitem(1/3,2/3,4/3,5/3)}
}
\if{\typarg=4}{
\text{k=randitem(1/6,5/6,7/6,11/6)}
}
\text{bet=simplify(randitem(-1,1)*\k*pi)}
\real{Mx=cos(\bet+\al)}
\real{My=sin(\bet+\al)}
#endif
#if defined TARGET_placerassoc1 || TARGET_placerassoc2
\real{Ax=1}
\real{Ay=0}
#if defined TARGET_placerassoc1
\text{k=randitem(1/12,1/6,1/3,5/12)}
#endif
#if defined TARGET_placerassoc2
\text{k=randitem(1/12,1/6,1/3,5/12)}
\rational{k=randitem(1/2+\k,-\k)}
#endif
\text{al=simplify(\k*pi)}
\real{Bx=cos(\al)}
\real{By=sin(\al)}
\text{i=randint(1..6)}
\matrix{mbet=-\alpha,\frac{\pi}{2}-\alpha,\frac{\pi}{2}+\alpha,\pi-\alpha,\pi+\alpha,2\pi-\alpha
-\al,pi/2-\al,pi/2+\al,pi-\al,pi+\al,2*pi-\al}
\text{bbet=\mbet[1;\i]}
\text{bet=\mbet[2;\i]}
\real{Mx=cos(\bet)}
\real{My=sin(\bet)}
#endif



\text{s=1.3}
\text{ep=0.07}
\text{npix=400}

\text{cercle=trange 0,2*pi
plot blue,cos(t),sin(t)}

\text{angles=}
\for{i=-6 to  6}{
\real{x=cos(\i*pi/12)}
\real{y=sin(\i*pi/12)}
\text{angles=\angles
line -\x,-\y,\x,\y,gray}}

\text{quadrillage=}
\for{i=-4 to  4}{
\text{quadrillage=\quadrillage
line -1,\i/4, 1,\i/4,gray}}
\for{i=-4 to  4}{
\text{quadrillage=\quadrillage
line \i/4,-1, \i/4,1,gray}}


#if defined TARGET_placerangle1 || TARGET_placerangle2
\text{points=disk \Ax,\Ay,10,black
text black,\Ax+\ep,\Ay+2*\ep,giant,A
}
#endif
#if defined TARGET_placerassoc1 || TARGET_placerassoc2
\text{points=disk \Ax,\Ay,10,black
text black,\Ax+\ep,\Ay+2*\ep,giant,A
disk \Bx,\By,10,black
text black,\Bx+\ep,\By+2*\ep,giant,B
}
#endif

\text{axes=
hline 0,0,black
arrow  0,0,\s,0,10,black
arrow 0,0,0,\s,10,black
vline 0,0,black
disk 0,0,10,black
text black,-2*\ep,-\ep,giant,O
}

\if{(\confparm2=) or (\confparm2=1)}{
\text{fond=\quadrillage}
}{
\text{fond=\angles}
}

\text{dessin= draw(\npix,\npix
xrange -\s,\s
yrange -\s,\s
\fond
\axes
\cercle
\points)}

\real{Mxp=(\npix*\Mx/\s+\npix)/2}
\real{Myp=(-\npix*\My/\s+\npix)/2}

\text{AOM=(\overrightarrow{OA},\overrightarrow{OM})}
\text{AOB=(\overrightarrow{OA},\overrightarrow{OB})}


#if defined TARGET_placerangle1 || TARGET_placerangle2
\statement{Placer sur le cercle unité ci-dessous le point \(M\) de sorte que l'angle \(\AOM\) ait une mesure égale à \(\bet\).
<div class="wimscenter">\embed{reply1}</div>
}
#endif
#if defined TARGET_placerassoc1 || TARGET_placerassoc2
\statement{Placer sur le cercle unité ci-dessous le point \(M\) de sorte que l'angle \(\AOM\) ait une mesure égale à \(\bbet\), où \({\alpha}\) désigne la mesure de l'angle \(\AOB\).
<div class="wimscenter">\embed{reply1}</div>
}
#endif

\answer{}{\dessin;point,\Mxp,\Myp}{type=coord}

\feedback{\result1=-1}{<br /> Voici la bonne réponse :
<div class="wimscenter">\draw{\npix,\npix}{
xrange -\s,\s
yrange -\s,\s
\fond
\axes
\cercle
\points
disk \Mx,\My,10,green
text black,\Mx-\ep,\My-\ep,giant,M}
</div>}
