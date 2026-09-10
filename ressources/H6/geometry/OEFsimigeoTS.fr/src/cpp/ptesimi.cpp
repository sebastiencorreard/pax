target=ptesimi1 ptesimi2 ptesimi3 ptesimi4 ptesimi5
#include "lang_titles.inc"
#include "author.inc"
\precision{1000}
\computeanswer{yes}

#if defined TARGET_ptesimi5
\rational{xA=randint(0..10)*randint(1,-1)/2}
\rational{yA=randint(1..10)*randint(1,-1)/2}
\rational{xC=randint(0..10)*randint(1,-1)/2}
\rational{yC=randint(1..10)*randint(1,-1)/2}
\rational{x0=randint(0..3)*randint(1,-1)}
\rational{y0=randint(0..3)*randint(1,-1)}
\rational{coef=randint(10..50)/20}
\rational{xB=\x0+\coef*(\xA-\x0)}
\rational{yB=\y0+\coef*(\yA-\y0)}
\rational{xD=\x0+\coef*(\xC-\x0)}
\rational{yD=\y0+\coef*(\yC-\y0)}
\integer{max=pari(vecmax([\xA,\yA,\xC,\yC,\xB,\yB,\xD,\yD])+2)}
\integer{min=pari(vecmin([\xA,\yA,\xC,\yC,\xB,\yB,\xD,\yD])-2)}
\text{filename=findhomothetie.ggb}
\text{appletcommand=setCoordSystem(\min,\max,\min,\max)
A=(\xA,\yA)
B=(\xB,\yB)
C=(\xC,\yC)
D=(\xD,\yD)
setFixed('A',true)
setFixed('B',true)
setFixed('C',true)
setFixed('D',true)
setLabelVisible('A',true)
setLabelVisible('B',true)
setLabelVisible('C',true)
setLabelVisible('D',true)
}

\text{appletcommand2=\appletcommand
a=Line[A,B]
b=Line[C,D]
O=(\x0,\y0)}
\text{dem=n,abs(x_O-(\x0))<0.3&abs(y_O-(\y0))<0.3,O est le centre de l'homothétie}
text{dem=f,O=Intersect(Line[A,B],Line[C,D])}
\text{chkpt='O'}
\text{option=file=\filename
width=500
height=500
showToolBar=true
customToolBar="0|2|3|4|5|19|40|41|42"
enableRightClick=true
}
\text{option2=\option
setLabelVisible('O',true)}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">
\embed{r1, 500x500
\option
\appletcommand}
</div>
 <div class="medium_size text_col">
On considère l'homothétie \(h) par laquelle les points \(B) et \(D)
 sont les images respectives des points \(A) et \(C).
 <p>
 Construire le point \(O) centre de l'homothétie \(h).
 </p>
 <div class="wims_instruction">
 Utiliser le zoom si les points n'apparaissent pas.
 <br>
 Ne pas oublier de renommer le point créé par un click droit afin qu'il s'appelle \(O).
 </div>
 </div></div>
}
\answer{centre homothétie}{\dem}{type=geogebra}{option=check=\chkpt precision=2 output=formal max=50 extra=yes weight=0&0.2&1}
#endif

#if defined TARGET_ptesimi1
\integer{k=randint(2..6)}
\text{size=50x40x4}
\text{vk=\(\k)}
\text{egal=\(=)}
\text{lstrep=\vk,\egal,\(\vec{v}),\(\overrightarrow{AB}),\(\overrightarrow{BA}),\(\overrightarrow{CD}),\(\overrightarrow{CA}),\(\overrightarrow{CB}),
\(\overrightarrow{DA}),\(\overrightarrow{DB}),\(AB),\(AC),\(AD),\(BC),\(BD),\(CD)}
\integer{ch=randint(1..8)}
\if{\ch=1}{
 \text{quest=\(B) a pour image \(A)  par une similitude de centre C et de rapport \k }
 \text{rep1=\(AC),\egal,\vk,\(BC)}
 \text{rep2=\vk,\(BC),\egal,\(AC)}
 }
\if{\ch=2}{
 \text{quest=\(A) est l'image de \(B)  par une similitude de centre C et de rapport \k }
 \text{rep1=\(AC),\egal,\vk,\(BC)}
 \text{rep2=\vk,\(BC),\egal,\(AC)}
 }
\if{\ch=3}{
 \text{quest=\(A) a pour image \(B)  par une similitude de centre C et de rapport \k }
 \text{rep1=\(BC),\egal,\vk,\(AC)}
 \text{rep2=\vk,\(AC),\egal,\(BC)}
 }
\if{\ch=4}{
 \text{quest=\(B) est l'image de \(A)  par une similitude de centre C et de rapport \k }
 \text{rep1=\(BC),\egal,\vk,\(AC)}
 \text{rep2=\vk,\(AC),\egal,\(BC)}
 }
\if{\ch=5}{
 \text{quest=\(A) et \(B) sont les images respectives de \(C) et \(D) par la même similtude de rapport \(\k)}
 \text{rep1=\(AB),\egal,\vk,\(CD)}
 \text{rep2=\vk,\(CD),\egal,\(AB)}
 }
\if{\ch=6}{
 \text{quest=\(A) et \(B) ont pour images respectives \(C) et \(D) par la même similtude de rapport \(\k)}
 \text{rep1=\(CD),\egal,\vk,\(AB)}
 \text{rep2=\vk,\(AB),\egal,\(CD)}
 }
\if{\ch=7}{
 \text{quest=\(A) est l'image de \(B) par la similitude de rapport \vk qui transforme \(C) en \(D)}
 \text{rep1=\(AD),\egal,\vk,\(BC)}
 \text{rep2=\vk,\(BC),\egal,\(AD)}
 }
\if{\ch=8}{
 \text{quest=\(A) a pour image \(B) par la similitude de rapport \vk qui transforme \(C) en \(D)}
 \text{rep1=\(BD),\egal,\vk,\(AC)}
 \text{rep2=\vk,\(AC),\egal,\(BD)}
 }
\statement{<p>
Traduire par une égalité le fait que
</p>
<div class="wimscenter">\quest</div>

<div class="wimscenter">\embed{reply1,\size}</div>
}
\answer{égalité }{\rep;\lstrep}{type=dragfill}
\condition{égalité }{
(\reply1 issametext \rep1) or (\reply1 issametext \rep2) or (\ch>5 and ((\reply1 issametext \rep3) or (\reply1 issametext \rep4)))}
\solution{On peut écrire \rep1}
#endif
#if (defined TARGET_ptesimi2  || defined TARGET_ptesimi3 )
\text{filename=ruche.ggb}
\text{appletcommand=}
\text{option=
file=\filename
width=500
height=400
showToolBar=true
customToolBar="40|41|42|"
showAlgebraInput=false}
\text{applet=slib(geo2D/geogebra \appletcommand , \option)}
#if defined TARGET_ptesimi2
\text{data=3,\frac{1}{3},\frac{2\pi}{3},P,T,R,H,L,J,K,O,M,C,G,E
\frac{1}{3},3,\frac{2\pi}{3},P,R,L,H,J,D,S,U,O,K,M,G
\frac{2}{3},\frac{3}{2},\frac{\pi}{3},P,R,I,H,J,B,S,U,L,K,M,D
\frac{3}{2},\frac{2}{3},\frac{\pi}{3},P,Z,R,H,Q,J,K,T,M,C,L,E
2,\frac{1}{2},\frac{\pi}{3},P,Q,I,H,I,B,S,T,L,K,L,D
\frac{1}{2},2,\frac{\pi}{3},P,Z,Q,H,Q,I,K,T,L,C,L,D
\frac{1}{3},3,\frac{2\pi}{3},Q,O,U,I,G,M,F,D,J,N,L,R
3,\frac{1}{3},\frac{2\pi}{3},Q,M,O,I,E,G,N,J,L,V,R,T
\frac{3}{2},\frac{2}{3},\frac{\pi}{3},Q,H,O,I,A,G,V,M,T,N,E,L
\frac{2}{3},\frac{3}{2},\frac{\pi}{3},Q,O,W,I,G,P,F,D,M,N,L,U
\frac{1}{2},2,\frac{\pi}{3},Q,H,P,I,A,H,N,E,M,V,M,U
2,\frac{1}{2},\frac{\pi}{3},Q,P,W,I,H,P,F,E,M,N,M,U}
\text{datanum=3,1/3,2/3
1/3,3,2/3
2/3,3/2,1/3
3/2,2/3,1/3
2,1/2,1/3
1/2,2,1/3
1/3,3,2/3
3,1/3,2/3
3/2,2/3,1/3
2/3,3/2,1/3
1/2,2,1/3
2,1/2,1/3
}
#endif
#if defined TARGET_ptesimi3
\text{data=\frac{2\sqrt{3}}{3},\frac{\sqrt{3}}{2},\frac{\pi}{6},P,M,I,H,E,B,M,H,L,E,A,B,I,L,P,Q,T,W
\frac{\sqrt{3}}{2},\frac{2\sqrt{3}}{3},\frac{\pi}{6},Q,H,L,I,A,D,Z,P,T,H,Q,M,I,P,Q,Q,W,Z,P,Z,U
\sqrt{3},\frac{\sqrt{3}}{3},\frac{5\pi}{6},P,Q,K,H,I,C,Q,M,T,I,E,L,H,L,E,P,T,M
\frac{\sqrt{3}}{3},\sqrt{3},\frac{5\pi}{6},P,S,Q,H,K,I,Q,L,U,I,D,M,H,M,D,P,U,L
\sqrt{3},\frac{\sqrt{3}}{3},\frac{\pi}{2},H,I,A,P,Q,H,Q,M,L,I,E,D,M,I,P,E,B,H
\frac{\sqrt{3}}{3},\sqrt{3},\frac{\pi}{2},I,B,H,Q,I,P,M,H,Q,E,A,I,I,L,M,B,D,E
}
\text{datanum=2*sqrt(3)/3,sqrt(3)/2,1/6
\sqrt(3)/2,2*sqrt(3)/3,1/6
sqrt(3),sqrt(3)/3,5/6
sqrt(3)/3,sqrt(3),5/6
sqrt(3),sqrt(3)/3,1/2
sqrt(3)/3,sqrt(3),1/2
}
#endif
\text{transf=la similitude directe de centre }
\integer{ir=randint(1..rows(\data))}
\text{cedata=row(\ir,\data)}
\text{cedatanum=row(\ir,\datanum)}
\integer{cas=randint(1,2)}
\integer{choix=randint(1..5)}
integer{choix=3}
\text{rapport=\cas=1?\cedata[1]:\cedata[2]}
\text{reprap=\cas=1?\cedatanum[1]:\cedatanum[2]}
\text{angle=\cas=1?\cedata[3]:-\cedata[3]}
\text{repang=\cas=1?\cedatanum[3]:-\cedatanum[3]}
\integer{nbpt=items(\cedata)/3}
\integer{i=randint(1..\nbpt-1)}
\text{centre=\cedata[3*\i+1]}
\text{repcentre=\cedata[3*\i+1]}
\text{repant=\cas=1?\cedata[3*\i+2]:\cedata[3*\i+3]}
\text{repimage=\cas=2?\cedata[3*\i+2]:\cedata[3*\i+3]}
\if{\choix=1}
 {
\text{quest1=\cas=1?du point \cedata[3*\i+2]:du point \cedata[3*\i+3]}
\text{quest2=\transf \centre , de rapport \(\rapport) et d'angle \(\angle)}
 }

\text{mstep=r\choix}
\steps{\mstep}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\applet</div>
 <div class="medium_size text_col">
<p>Tous les hexagones sont réguliers.</p>

\if{\choix=1}{
<p><label for="reply1">Quelle est l'image \quest1 par \quest2 ?</label></p>
<div class="wimscenter"> \embed{reply1,3}</div>
}
\if{\choix=2}{
  <label for="reply2">Quel est l'angle de la similitude directe de
  centre \centre et de rapport \(\rapport) qui envoie \repant sur \repimage?</label>
  <div class="wimscenter"> \embed{reply2,3}\(\pi)</div>
}
\if{\choix=3}{
  <label for="reply3">Quel est le rapport de la similitude directe de centre \centre
  et d'angle \(\angle) qui envoie \repant sur \repimage?
  </label>
  <div class="wimscenter"> \embed{reply3,7}</div>
  <div class="wims_instruction"> Taper sqrt(a) pour \(\sqrt{a})</div>
}
\if{\choix=4}{
  <label for="reply4">Quel est l'antécédent du point \repimage par la
    similitude directe de centre \centre, d'angle \(\angle) et de rapport \(\rapport)?
    </label>
  <div class="wimscenter"> \embed{reply4,5}</div>
}
\if{\choix=5}{
  <label for="reply5">Quel est le centre de la similitude directe
  d'angle \(\angle) et de rapport \(\rapport) qu envoie le point \repant sur le point \repimage?
  </label><div class="wimscenter"> \embed{reply5,5}</div>
}
<div class="wims_instruction">Utiliser le zoom si les points n'apparaissent pas.</div>
</div></div>
}
\answer{image}{\repimage}{type=nocase}
\answer{angle}{\repang}{type=numexp}
\answer{rapport}{\reprap}{type=numeric}
\answer{antecédent}{\repant}{type=nocase}
\answer{centre}{\repcentre}{type=nocase}
#endif
#if defined TARGET_ptesimi4
\text{filename=ruche.ggb}
\text{appletcommand=}
\text{option=
file=\filename
width=500
height=400
showToolBar=true
customToolBar="40|41|42|"
showAlgebraInput =false}
\text{applet=slib(geo2D/geogebra \appletcommand , \option)}


\text{data=3,1/3,2/3,P,T,R,H,L,J,K,O,M,C,G,E
1/3,3,2/3,P,R,L,H,J,D,S,U,O,K,M,G
2/3,3/2,1/3,P,R,I,H,J,B,S,U,L,K,M,D
3/2,2/3,1/3,P,Z,R,H,Q,J,K,T,M,C,L,E
2,1/2,1/3,P,Q,I,H,I,B,S,T,L,K,L,D
1/2,2,1/3,P,Z,Q,H,Q,I,K,T,L,C,L,D
1/3,3,2/3,Q,O,U,I,G,M,F,D,J,N,L,R
3,1/3,3,2/3,Q,M,O,I,E,G,N,J,L,V,R,T
3/2,2/3,1/3,Q,H,O,I,A,G,V,M,T,N,E,L
2/3,3/2,1/3,Q,O,W,I,G,P,F,D,M,N,L,U
1/2,2,1/3,Q,H,P,I,A,H,N,E,M,V,M,U
2,1/2,1/3,Q,P,W,I,H,P,F,E,M,N,M,U
2*sqrt(3)/3,sqrt(3)/2,1/6,P,M,I,H,E,B,M,H,L,E,A,B,I,L,P,Q,T,W
sqrt(3)/2,2*sqrt(3)/3,1/6,Q,H,L,I,A,D,Z,P,T,H,Q,M,I,P,Q,Q,W,Z,P,Z,U
sqrt(3),sqrt(3)/3,5/6,P,Q,K,H,I,C,Q,M,T,I,E,L,H,L,E,P,T,M
sqrt(3)/3,sqrt(3),5/6,P,S,Q,H,K,I,Q,L,U,I,D,M,H,M,D,P,U,L
sqrt(3),sqrt(3)/3,1/2,H,I,A,P,Q,H,Q,M,L,I,E,D,M,I,P,E,B,H
sqrt(3)/3,sqrt(3),1/2,I,B,H,Q,I,P,M,H,Q,E,A,I,I,L,M,B,D,E
}
\text{cedata=randomrow(\data)}
text{cedata=row(4,\data)}
\integer{cas=randint(1,2)}
\text{rapport=\cas=1?\cedata[1]:\cedata[2]}
\rational{angle=\cas=1?\cedata[3]:-\cedata[3]}
\text{transf=la similitude directe de centre}
\integer{nbpt=items(\cedata)/3}
\text{ind=shuffle(\nbpt-1)}
\text{pt1=\cas=1? \cedata[3*\ind[2]+2]:\cedata[3*\ind[2]+3]}
\text{pt2=\cas=2? \cedata[3*\ind[2]+2]:\cedata[3*\ind[2]+3]}
\text{centre= \cedata[3*\ind[2]+1]}
\text{quest2=la similitude directe de centre \centre qui envoie \pt1 sur \pt2}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\applet</div>
 <div class="medium_size text_col">
<p>Tous les hexagones sont réguliers.</p>
 Déterminer le rapport et l'angle de la similitude directe de centre \centre qui envoie \pt1 sur \pt2:
<div class="wimscenter"><label for="reply1">rapport=</label>\embed{reply1,10}</div>
<div class="wimscenter"><label for="reply2">angle=</label>\embed{reply2,5}\(\pi)</div>
<div class="wims_instruction">Utiliser le zoom si les points n'apparaissent pas.<br>
Taper sqrt(3) pour \(\sqrt{3})
</div>
</div>
</div>

}
\answer{rapport}{\rapport}{type=numeric}
\answer{angle}{\angle}{type=numexp}
#endif
