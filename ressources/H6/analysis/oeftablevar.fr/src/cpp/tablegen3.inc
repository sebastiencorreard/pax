\integer{tabcnt=3}

\text{sh=wims(sort numeric items item(1..8,shuffle(\vcnt)))}
\text{vx=item(\sh,\values)}
\integer{cut=random(\vcnt/4..\vcnt*3/4)}
\text{V1=shuffle(item(3..\cut-3,\values))}
\text{V2=shuffle(item(\cut+3..\vcnt-2,\values))}

\integer{orient=random(1,2)}
\if{\orient=1}{
 \text{arrows=ne,se,ne,se}
 \text{left=random(0..10)>8?-\infty:\V1[1]}
 \text{right=random(0..10)>8?+\infty:\V2[2]}
 \text{ys=\left,\V2[1],\V1[2],\right}
 \text{pos=bottom,top,bottom,top,bottom}
}{
 \text{arrows=se,ne,se,ne}
 \text{left=random(0..10)>8?+\infty:\V2[1]}
 \text{right=random(0..10)>8?-\infty:\V1[2]}
 \text{ys=\left,\V1[1],\V2[2],\right}
 \text{pos=top,bottom,top,bottom,top}
}

\text{YY=wims(replace internal \infty by \infval in \ys)}
\text{ymiddles=}
\for{s=1 to 3}{
 \text{yl=}
 \for{Y in \values}{
  \if{\Y>min(\YY[\s],\YY[\s+1]) and \Y<max(\YY[\s],\YY[\s+1])}{
   \text{yl=wims(append item \Y to \yl)}
  }
 }
 \text{yl=item(1..2,shuffle(\yl))}
 \text{yl=\arrows[\s] issametext ne?
    wims(sort numeric items \yl):
    wims(sort reverse numeric items \yl)}
 \text{ymiddles=\ymiddles\yl;}
}

\text{xmiddles=\vx[1,2];\vx[4,5];\vx[7,8]}
\text{xs=-\infty, \vx[3,6], +\infty}
\text{xshow=wims(makelist \(x) for x in \xs)}
\text{yshow=wims(makelist \(x) for x in \ys)}
\text{arrowlen=1}

