target=valtrigo1 valtrigo2 valtrigo3
\author{Régine, Mangeard}
#if #TARGET(valtrigo1)
\title{Valeurs remarquables 1}
\text{data=pi/6,\frac{\sqrt{3}}{2},\frac{1}{2},1,1
pi/4,\frac{\sqrt{2}}{2},\frac{\sqrt{2}}{2},1,1
pi/3,\frac{1}{2},\frac{\sqrt{3}}{2},1,1
pi/2,0,1,1,1,
2*pi/3,-\frac{1}{2},\frac{\sqrt{3}}{2},2,1
3*pi/4,-\frac{\sqrt{2}}{2},\frac{\sqrt{2}}{2},2,1
5*pi/6,-\frac{\sqrt{3}}{2},\frac{1}{2},2,1
pi,-1,0,2,1
-5*pi/6,-\frac{\sqrt{3}}{2},-\frac{1}{2},2,2
-3*pi/4,-\frac{\sqrt{2}}{2},-\frac{\sqrt{2}}{2},2,2
-2*pi/3,-\frac{1}{2},-\frac{\sqrt{3}}{2},2,2
-pi/2,0,-1,1,2
-pi/3,\frac{1}{2},-\frac{\sqrt{3}}{2},1,2
-pi/4,\frac{\sqrt{2}}{2},-\frac{\sqrt{2}}{2},1,2
-pi/6,\frac{\sqrt{3}}{2},-\frac{1}{2},1,2
}
\text{symb=\ge,\le}
\text{cedata=randomrow(\data)}
\integer{k=randint(1,2)}
\text{quest=\k=1?\(cos{\alpha}=\cedata[2]) et \(\sin{\alpha} \symb[\cedata[5]] 0):\(sin{\alpha}=\cedata[3]) et \(\cos{\alpha} \symb[\cedata[4]] 0)}
\real{val=\cedata[1]}
\statement{
 Donner une mesure de l'angle \(\alpha) appartenant à &#93; \(-\pi;\pi) &#93;,
 sachant que \quest.
 <div class="wimscenter">
<label for="reply1">\(\alpha=)</label>\embed{reply1,5}</div>
<div class="wims_instruction">Taper <span class="tt">pi</span> pour \(\pi).
</div>
}
\answer{\alpha}{\val}{type=numeric}
#endif
#if #TARGET(valtrigo2)
\title{Valeurs remarquables 2}
\text{lstrep=\(0),\(\frac{\pi}{6}),\(\frac{\pi}{4}),\(\frac{\pi}{3}),\(\frac{\pi}{2}),\(\frac{2\pi}{3}),\(\frac{3\pi}{4}),\(\frac{5\pi}{6}),\(\pi),\(\frac{-\pi}{6}),\(\frac{-\pi}{4}),\(\frac{-\pi}{3}),\(\frac{-\pi}{2}),\(\frac{-2\pi}{3}),\(\frac{-3\pi}{4}),\(\frac{-5\pi}{6})}
\text{data=\(\cos{x}) croit de \(\frac{1}{2}) à 1,\(\sin{x}) décroit de \(\frac{\sqrt{3}}{2}) à 0,décroit,\(\frac{\pi}{3}),\(0)
\(\cos{x}) décroit de 1 à \(\frac{1}{2}),\(\sin{x}) croit de 0 à \(\frac{\sqrt{3}}{2}),croit,\(0),\(\frac{\pi}{3})
\(\cos{x}) croit de \(\frac{\sqrt{2}}{2}) à \(\frac{\sqrt{3}}{2}),\(\sin{x}) décroit de \(\frac{\sqrt{2}}{2}) à \(\frac{1}{2}),décroit,\(\frac{\pi}{4}),\(\frac{\pi}{6})
\(\cos{x}) décroit de \(\frac{\sqrt{3}}{2}) à \(\frac{\sqrt{2}}{2}),\(\sin{x}) croit de \(\frac{1}{2}) à \(\frac{\sqrt{2}}{2}),croit,\(\frac{\pi}{6}),\(\frac{\pi}{4})
\(\cos{x}) croit de \(\frac{-\sqrt{3}}{2}) à \(\frac{-\sqrt{2}}{2}),\(\sin{x}) décroit de \(-\frac{1}{2}) à \(-\frac{\sqrt{2}}{2}),croit,\(-\frac{5\pi}{6}),\(-\frac{3\pi}{4})
\(\cos{x}) croit de \(\frac{\sqrt{2}}{2}) à \(\frac{\sqrt{3}}{2}),\(\sin{x}) croit de \(-\frac{\sqrt{2}}{2}) à \(-\frac{1}{2}),croit,\(-\frac{\pi}{4}),\(-\frac{\pi}{6})
\(\cos{x}) décroit de \(-\frac{1}{2}) à \(-\frac{\sqrt{3}}{2}),\(\sin{x}) décroit de \(\frac{\sqrt{3}}{2}) à \(\frac{1}{2}),croit,\(\frac{2\pi}{3}),\(\frac{5\pi}{6})

}
\text{cedata=randomrow(\data)}
\text{quest1=\cedata[1]}
\text{quest2=\cedata[2]}
\text{verbe=\cedata[3]}
\text{xi=\cedata[4]}
\text{xf=\cedata[5]}

\text{rbrack=&#93;}
\text{size=70x60x1}

\statement{Soit \(x \in )\rbrack \(-\pi;\pi) \rbrack .<p>
Indiquer de quelle valeur à quelle valeur \(x) \verbe lorsque
</p>
<ul>
 <li>\quest1</li>
 <li>et \quest2</li>
</ul>
<div class="wimscenter">
\(x) \verbe de \embed{reply1,\size} à \embed{reply2,\size}
</div>
}
\answer{départ}{\xi;\lstrep}{type=clickfill}
\answer{arrivée}{\xf;\lstrep}{type=clickfill}
#endif
#if #TARGET(valtrigo3)
\title{Valeurs remarquables 3}
\text{se=\(\searrow)}
\text{ne=\(\nearrow)}
\text{data=\(\frac{\pi}{4}),\(\frac{\sqrt{2}}{2}),\(\frac{\sqrt{2}}{2}),\(\frac{\pi}{2}),\(0),\(1),\(\pi),\(-1),\(0),\(\frac{5\pi}{4}),\(\frac{-\sqrt{2}}{2}),\(\frac{-\sqrt{2}}{2})
\(\frac{-\pi}{6}),\(\frac{\sqrt{3}}{2}),\(\frac{-1}{2}),\(0),\(1),\(0),\(\frac{\pi}{2}),\(0),\(1),\(\frac{5\pi}{6}),\(\frac{-\sqrt{3}}{2}),\(\frac{1}{2})
\(\frac{-\pi}{3}),\(\frac{1}{2}),\(\frac{-\sqrt{3}}{2}),\(0),\(1),\(0),\(\frac{\pi}{2}),\(0),\(1),\(\frac{2\pi}{3}),\(\frac{-1}{2}),\(\frac{\sqrt{3}}{2})
\(\frac{-\pi}{4}),\(\frac{\sqrt{2}}{2}),\(\frac{-\sqrt{2}}{2}),\(0),\(1),\(0),\(\frac{\pi}{2}),\(0),\(1),\(\pi),\(-1),\(0),\(\frac{5\pi}{4}),\(\frac{-\sqrt{2}}{2}),\(\frac{-\sqrt{2}}{2})
\(\frac{-\pi}{2}),\(0),\(-1),\(0),\(1),\(0),\(\frac{\pi}{2}),\(0),\(1),\(\frac{5\pi}{6}),\(\frac{-\sqrt{3}}{2}),\(\frac{1}{2})
\(\frac{\pi}{6}),\(\frac{\sqrt{3}}{2}),\(\frac{1}{2}),\(\frac{\pi}{2}),\(0),\(1),\(\pi),\(-1),\(0),\(\frac{3\pi}{2}),\(0),\(-1),\(\frac{5\pi}{3}),\(\frac{1}{2}),\(\frac{-\sqrt{3}}{2})
}
\text{datasymb=\se,\ne,\se,\se,\ne,\se
\ne,\ne,\se,\ne,\se,\se
\ne,\ne,\se,\ne,\se,\se
\ne,\ne,\se,\ne,\se,\se,\ne,\se
\ne,\ne,\se,\ne,\se,\se
\se,\ne,\se,\se,\ne,\se,\ne,\ne
}
\integer{k=randint(1..6)}
\text{cedata=row(\k,\data)}
\text{cesymb=row(\k,\datasymb)}
\text{xi=\cedata[1]}
\text{xlist=}
\text{cosl=}
\text{sinl=}
\integer{j=items(\cedata)/3}
\for{i=1 to \j}
 {
 \text{xlist=wims(append item \cedata[3*(\i-1)+1] to \xlist)}
 \text{cosv=\cedata[3*(\i-1)+2]}
 \text{sinv=\cedata[3*(\i-1)+3]}
 \text{cosl=wims(append item \cosv to \cosl)}
 \text{sinl=wims(append item \sinv to \sinl)}
 }
\text{xf=\xlist[\j]}
\text{repl=item(2..\j-1,\xlist),\cosl[1]}
\for{i=2 to \j}
 {
 \text{repl=wims(append item \cesymb[2*(\i-2)+1] to \repl)}
 \text{repl=wims(append item \cosl[\i] to \repl)}
 }
\text{repl=wims(append item \sinl[1] to \repl)}
\for{i=2 to \j}
 {
 \text{repl=wims(append item \cesymb[2*(\i-2)+2] to \repl)}
 \text{repl=wims(append item \sinl[\i] to \repl)}
 }

\text{vlist=\(0),\(\frac{\pi}{2}),\(\pi),\(\frac{3\pi}{2})}
\text{vflist=\(1),\(\frac{\sqrt{3}}{2}),\(\frac{1}{2}),\(\frac{\sqrt{2}}{2}),\(0),\(\frac{-\sqrt{2}}{2}),\(\frac{-1}{2}),\(\frac{-\sqrt{3}}{2}),\(-1)}
\text{mstep=wims(makelist r x for x = 1 to 3*\j+2*(\j-1)-2)}
\text{mstep=wims(nospace \mstep)}

\text{lstrep=\vlist,\vflist,\se,\ne}
\text{size=70x60x1}
\steps{\mstep}
\integer{jx=\j-2}
\integer{jc1=\jx+1}
\integer{jc2=\jc1+2*\j-2}
\integer{js1=\jc2+1}
\integer{js2=\js1+2*\j-2}
\statement{
Compléter le tableau des variations suivant.
<table class="wimscenter wimsborder">
<tr><td>\(x)</td><td>\xi</td><td>&nbsp;</td>
\for{ii=1 to \jx}
  {
<td>\embed{reply\ii,\size}</td><td>&nbsp;</td>
  }
<td>\xf</td></tr>
<tr><td>\(\cos{x})</td>
\for{jj=\jc1 to \jc2}
  {
<td>\embed{reply\jj,\size}</td>
  }
</tr><tr><td>\(\sin{x})</td>
\for{kk=\js1 to \js2}
  {
<td>\embed{reply\kk,\size}</td>
  }
</tr></table>
}
\answer{}{\repl[1];\lstrep}{type=clickfill}
\answer{}{\repl[2];\lstrep}{type=clickfill}
\answer{}{\repl[3];\lstrep}{type=clickfill}
\answer{}{\repl[4];\lstrep}{type=clickfill}
\answer{}{\repl[5];\lstrep}{type=clickfill}
\answer{}{\repl[6];\lstrep}{type=clickfill}
\answer{}{\repl[7];\lstrep}{type=clickfill}
\answer{}{\repl[8];\lstrep}{type=clickfill}
\answer{}{\repl[9];\lstrep}{type=clickfill}
\answer{}{\repl[10];\lstrep}{type=clickfill}
\answer{}{\repl[11];\lstrep}{type=clickfill}
\answer{}{\repl[12];\lstrep}{type=clickfill}
\answer{}{\repl[13];\lstrep}{type=clickfill}
\answer{}{\repl[14];\lstrep}{type=clickfill}
\answer{}{\repl[15];\lstrep}{type=clickfill}
\answer{}{\repl[16];\lstrep}{type=clickfill}
\answer{}{\repl[17];\lstrep}{type=clickfill}
\answer{}{\repl[18];\lstrep}{type=clickfill}
\answer{}{\repl[19];\lstrep}{type=clickfill}
\answer{}{\repl[20];\lstrep}{type=clickfill}
\answer{}{\repl[21];\lstrep}{type=clickfill}
#endif
