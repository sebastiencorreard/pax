target=valtrigo1 valtrigo2 valtrigo3 valtrigo4 valtrigo5
#define TITRE Valeurs remarquables
#if defined TARGET_valtrigo1
# define NUM 1
#endif
#if defined TARGET_valtrigo2
# define NUM 2
#endif
#if defined TARGET_valtrigo3
# define NUM 3
#endif
#if defined TARGET_valtrigo4
# define NUM 4
#endif
#if defined TARGET_valtrigo5
# define NUM 5
#endif
#include "lang_titles.inc"
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{1000}
\computeanswer{yes}

\text{dessin=
 xrange -1.4,1.4
 yrange -1.4,1.4
 circle 0,0,200,black
 darrow -1,0,1,0,10,black
 darrow 0,-1,0,1,10,black
 dsegment -cos(pi/6),-sin(pi/6),cos(pi/6),sin(pi/6),green
 dsegment -cos(pi/3),-sin(pi/3),cos(pi/3),sin(pi/3),green
 dsegment -cos(-pi/6),-sin(-pi/6),cos(-pi/6),sin(-pi/6),green
 dsegment -cos(-pi/3),-sin(-pi/3),cos(-pi/3),sin(-pi/3),green
 dsegment cos(pi/4),sin(pi/4),-cos(pi/4),-sin(pi/4),red
 dsegment cos(-pi/4),sin(-pi/4),-cos(-pi/4),-sin(-pi/4),red
 text black,1.2,0,medium,A
 text black,1.2*cos(pi/6),1.2*sin(pi/6),medium,B
 text black,1.2*cos(pi/4),1.2*sin(pi/4),medium,C
 text black,1.2*cos(pi/3),1.2*sin(pi/3),medium,D
 text black,0,1.2,medium,E
 text black,1.2*cos(2*pi/3),1.2*sin(2*pi/3),medium,F
 text black,1.2*cos(3*pi/4),1.2*sin(3*pi/4),medium,G
 text black,1.2*cos(5*pi/6),1.2*sin(5*pi/6),medium,H
 text black,-1.2,0,medium,I
 text black,1.2*cos(7*pi/6),1.2*sin(7*pi/6),medium,J
 text black,1.2*cos(5*pi/4),1.2*sin(5*pi/4),medium,K
 text black,1.2*cos(4*pi/3),1.2*sin(4*pi/3),medium,L
 text black,0,-1.2,medium,M
 text black,1.2*cos(-pi/3),1.2*sin(-pi/3),medium,N
 text black,1.2*cos(-pi/4),1.2*sin(-pi/4),medium,O
 text black,1.2*cos(-pi/6),1.2*sin(-pi/6),medium,P

 }

#if defined TARGET_valtrigo1
\text{data=0,1,0
\pi,-1,0
\frac{\pi}{4},sqrt(2)/2,sqrt(2)/2,\frac{\sqrt{2}}{2},\frac{\sqrt{2}}{2}
\frac{3\pi}{4},-sqrt(2)/2,sqrt(2)/2,-\frac{\sqrt{2}}{2},\frac{\sqrt{2}}{2}
\frac{\pi}{4}+\pi,-sqrt(2)/2,-sqrt(2)/2,-\frac{\sqrt{2}}{2},-\frac{\sqrt{2}}{2}
\frac{3\pi}{4}+\pi,sqrt(2)/2,-sqrt(2)/2,\frac{\sqrt{2}}{2},-\frac{\sqrt{2}}{2}
\frac{\pi}{2},0,1,0,1
\frac{\pi}{2}+\pi,0,-1,0,-1
\frac{\pi}{6},sqrt(3)/2,1/2,\frac{\sqrt{3}}{2},\frac{1}{2}
\frac{5\pi}{6},-sqrt(3)/2,1/2,-\frac{\sqrt{3}}{2},\frac{1}{2}
\frac{\pi}{6}+\pi,-sqrt(3)/2,-1/2,-\frac{\sqrt{3}}{2},-\frac{1}{2}
\frac{5\pi}{6}+\pi,sqrt(3)/2,-1/2,\frac{\sqrt{3}}{2},-\frac{1}{2}
\frac{\pi}{3},1/2,sqrt(3)/2,\frac{1}{2},\frac{\sqrt{3}}{2}
\frac{2\pi}{3},-1/2,sqrt(3)/2,-\frac{1}{2},\frac{\sqrt{3}}{2}
\frac{\pi}{3}+\pi,-1/2,-sqrt(3)/2,-\frac{1}{2},-\frac{\sqrt{3}}{2}
\frac{2\pi}{3}+\pi,1/2,-sqrt(3)/2,\frac{1}{2},-\frac{\sqrt{3}}{2}
}
\text{cedata=randomrow(\data)}
\text{quest=\cedata[1]}
\real{cs=\cedata[2]}
\real{sn=\cedata[3]}
\text{tcs=\cedata[4]}
\text{tsn=\cedata[5]}
\statement{
  Donner la valeur exacte du cosinus et du sinus de
<div class="wimscenter">\(\quest)</div>
<ul>
<li>\(\cos{(\quest)}=)\embed{reply1,5}</li>
<li>\(\sin{(\quest)}=)\embed{reply2,5}</li>
</ul>
<div class="wims_instruction">
  Taper <span class="tt">sqrt(...)</span>
  pour \(\sqrt{}), exemple taper <span class="tt">sqrt(2)</span> pour \(\sqrt{2})
</div>}
\answer{ cosinus}{\cs}{type=numeric}
\answer{ sinus}{\sn}{type=numeric}
\feedback{\reply1 <> \cs or \reply2 <> \sn}{
  Ce qui correspond à
<ul><li>\(\cos{(\quest)}=\tcs)</li>
<li>\(\sin{(\quest)}=\tsn)</li>
</ul>
}

#endif
#if defined TARGET_valtrigo2
\text{donnees=slib(draw/repere 300,300,0,-10,10,-10,10,1,1,black,grey)}
\text{tmp=row(1,\donnees)}
%%%%coordonneees de l'origine du repère
\integer{Ox=item(1,\tmp)}
\integer{Oy=item(2,\tmp)}

\text{tmp=row(2,\donnees)}
%%%%échelle des axes
\integer{ex=item(1,\tmp)}
\integer{ey=item(2,\tmp)}
\text{data=\frac{\pi}{6},10*cos(pi/6),10*sin(pi/6)
\frac{\pi}{4},10*cos(pi/4),10*sin(pi/4)
\frac{\pi}{3},10*cos(pi/3),10*sin(pi/3)
\frac{\pi}{2},0,10
\frac{2\pi}{3},10*cos(2*pi/3),10*sin(2*pi/3)
\frac{3\pi}{4},10*cos(3*pi/4),10*sin(3*pi/4)
\frac{5\pi}{6},10*cos(5*pi/6),10*sin(5*pi/6)
\frac{7\pi}{6},10*cos(7*pi/6),10*sin(7*pi/6)
\frac{5\pi}{4},10*cos(5*pi/4),10*sin(5*pi/4)
\frac{4\pi}{3},10*cos(4*pi/3),10*sin(4*pi/3)
\frac{3\pi}{2},10*cos(3*pi/2),10*sin(3*pi/2)
\frac{5\pi}{3},10*cos(5*pi/3),10*sin(5*pi/3)
\frac{7\pi}{4},10*cos(7*pi/4),10*sin(7*pi/4)
\frac{11\pi}{6},10*cos(11*pi/6),10*sin(11*pi/6)
}
\text{cedata=randomrow(\data)}
\text{quest=\(\cedata[1])}
\real{fx=\Ox+\cedata[2]*\ex}
\real{fy=\Oy+\cedata[3]*\ey}
\real{fxm=\fx-\ex/3}
\real{fxp=\fx+\ex/3}
\real{fym=\fy-\ey/3}
\real{fyp=\fy+\ey/3}

\text{image=draw(300,300
xrange -10,10
yrange -10,10
circle 0,0,300,blue
dsegment 10*cos(pi/6),10*sin(pi/6),10*cos(5*pi/6),10*sin(5*pi/6),red
dsegment 10*cos(-pi/6),10*sin(-pi/6),10*cos(-5*pi/6),10*sin(-5*pi/6),red
dsegment 10*cos(pi/3),10*sin(pi/3),10*cos(-pi/3),10*sin(-pi/3),red
dsegment 10*cos(2*pi/3),10*sin(2*pi/3),10*cos(-2*pi/3),10*sin(-2*pi/3),red
segment -10,0,10,0,black
segment 0,-10,0,10,black
dsegment 10*cos(pi/4),10*sin(pi/4),-10*cos(pi/4),-10*sin(pi/4),green
dsegment 10*cos(3*pi/4),10*sin(3*pi/4),-10*cos(3*pi/4),-10*sin(3*pi/4),green
)
}
\statement{
  Cliquer sur le point du cercle trigonométrique ci-dessous, correspondant à un angle de \quest radian.
<div class="wimscenter">\embed{reply1}</div>
}
\answer{\quest}{\image;rectangle,\fxm,\fym,\fxp,\fyp}{type=coord}
#endif
#if defined TARGET_valtrigo4
\text{interdata= &#91; \(0;\frac{\pi}{2}) &#93;,AE,EA
&#91; \(\frac{\pi}{2};\pi) &#93;,EI,IE
&#91; \(\frac{\pi}{4};\frac{3\pi}{4}) &#93;,CG,GC
&#91; \(\pi;\frac{3\pi}{2}) &#93;,IM,MI
&#91; \(\frac{3\pi}{2};2\pi) &#93;,MA,AM
&#91; \(\frac{-3\pi}{4};\frac{-\pi}{4}) &#93;,KO,OK
&#91; \(\frac{\pi}{6};\frac{\pi}{3}) &#93;,BD,DB
&#91; \(\frac{2\pi}{3};\frac{4\pi}{3}) &#93;,FL,LF
&#91; \(\frac{-5\pi}{6};\frac{-\pi}{6}) &#93;,JP,PJ
&#91; \(\frac{5\pi}{4};\frac{5\pi}{3}) &#93;,KN,NK
&#91; \(\frac{\pi}{3};\frac{3\pi}{4}) &#93;,DG,GD
&#91; \(\frac{\pi}{4};\frac{5\pi}{6}) &#93;,CH,HG
}
\text{cedata=randomrow(\interdata)}
\text{inter=\cedata[1]}
\text{rep1=\cedata[2]}
\text{rep2=\cedata[3]}

\statement{<div class="wims_columns">
 <div class="medium_size img_col">\draw{260,260}{\dessin}</div>
 <div class="medium_size text_col">
  Sur quel arc du cercle trigonométrique ci-contre se trouvent les points images
  des réels \(x) tels que
 <div class="wimscenter"> \(x \in) \inter.</div>
 <div class="wimscenter">\embed{reply1}</div>
  <div class="wims_instruction">
  Nommer l'arc de cercle par ses extrémités.</div>
  </div>
  </div>
}
\answer{Arc de cercle}{\arc}{type=text}
\condition{\reply1 issametext \rep1 or \reply1 issametext \rep2}
#endif
#if defined TARGET_valtrigo5
\text{lstrep=\(0\),\(\frac{\pi}{6}),\(\frac{\pi}{4}),\(\frac{\pi}{3}),\(\frac{\pi}{2}),
\(\frac{2\pi}{3}),\(\frac{3\pi}{4}),\(\frac{5\pi}{6}),\(\,\pi),\(-\frac{5\pi}{6}),
\(-\frac{3\pi}{4}),\(-\frac{2\pi}{3}),\(-\frac{\pi}{2}),-\(\frac{\pi}{3}),\(-\frac{\pi}{4}),
\(-\frac{\pi}{6}),\(\frac{4\pi}{3})}

\text{interdata= \lstrep[1],\lstrep[5],0,pi/2,0,90
\lstrep[5],\lstrep[9],pi/2,pi,90,180
\lstrep[3],\lstrep[7],pi/4,3*pi/4,45,135
\lstrep[9],\lstrep[13],pi,3*pi/2,180,270
\lstrep[13],\lstrep[1],3*pi/2,2*pi,270,360
\lstrep[11],\lstrep[15],-3*pi/4,-pi/4,-135,-45
\lstrep[2],\lstrep[4],pi/6,pi/3,30,60
\lstrep[6],\lstrep[17],2*pi/3,4*pi/3,120,240
\lstrep[10],\lstrep[16],-5*pi/6,-pi/6,-150,-30
\lstrep[11],\lstrep[12],-3*pi/4,-2*pi/3,-135,-120
\lstrep[4],\lstrep[7],pi/3,3*pi/4,60,135
\lstrep[3],\lstrep[8],pi/4,5*pi/6,45,150
}
\text{cedata=randomrow(\interdata)}
\text{xi=\cedata[1]}
\text{xf=\cedata[2]}
\text{ang1=\cedata[5]}
\text{ang2=\cedata[6]}
\text{dessin=\dessin
linewidth 3
arc 0,0,2.2,2.2,\ang1,\ang2,red
}
\text{size=70x60x1}

\statement{<div class="wims_columns">
 <div class="medium_size img_col">\draw{260,260}{\dessin}</div>
 <div class="medium_size text_col">
  Donner un encadrement des réels \(x)
 dont les points images sur le cercle trigonométrique sont
  représentés par l'arc de cercle en rouge sur la figure ci-contre.
<div class="wimscenter">\embed{reply1,\size} \(\le x \le) \embed{reply2,\size}</div>
 </div>
</div>
}
\answer{borne inférieure}{\xi;\lstrep}{type=clickfill}
\answer{borne supérieure}{\xf;\lstrep}{type=clickfill}
#endif
#if defined TARGET_valtrigo3
\text{interdata=\(\frac{\pi}{8}),\(\frac{\pi}{3}),cos,<,2
\(\frac{\pi}{8}),\(\frac{\pi}{3}),cos,>,1
\(\frac{\pi}{8}),\(\frac{\pi}{3}),sin,<,1
\(\frac{\pi}{8}),\(\frac{\pi}{3}),sin,>,2
\(\frac{5\pi}{8}),\(\frac{2\pi}{3}),cos,<,2
\(\frac{5\pi}{8}),\(\frac{2\pi}{3}),cos,>,1
\(\frac{5\pi}{8}),\(\frac{2\pi}{3}),sin,<,2
\(\frac{5\pi}{8}),\(\frac{2\pi}{3}),sin,>,1
\(-\frac{3\pi}{8}),\(-\frac{\pi}{6}),cos,<,1
\(-\frac{3\pi}{8}),\(-\frac{\pi}{6}),cos,>,2
\(-\frac{3\pi}{8}),\(-\frac{\pi}{6}),sin,<,1
\(-\frac{3\pi}{8}),\(-\frac{\pi}{6}),sin,>,2
}
\text{cedata=randomrow(\interdata)}
\text{xi=\cedata[1]}
\text{xf=\cedata[2]}
\text{ftrig=\cedata[3]}
\text{symb=\cedata[4]}
\integer{rep=\cedata[5]}
\text{prop1=Comme \xi \(<) \xf}
\text{prop2= \ftrig(\xi) \symb \ftrig(\xf)}
\statement{
La proposition suivante est-elle vraie&nbsp;?

<div class="wimscenter">
\prop1, \prop2 </div>
<div class="wimscenter">\embed{reply1}</div>
}
\answer{}{\rep;Vrai,Faux}{type=radio}
#endif
