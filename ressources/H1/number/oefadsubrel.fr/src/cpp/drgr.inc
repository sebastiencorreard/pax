\real{ex=(\xsize-2*\marge)/(\max-\min)}
\real{minx=\min-\marge/\ex}
\real{maxx=\max+\marge/\ex}
\integer{ec=\max-\min+1}
\integer{eca=\max-\min}
\real{delet=4/\ex}
\text{tmp2=}
\for{k=0 to \eca}{\integer{aux2=\min+\k}
                  \real{aux=\min+\k-\delet}
                  \text{tmp=text black,\aux,-0.75,giant,\aux2}
                  \text{tmp2=wims(append line \tmp to \tmp2)}}
\text{essai=range \minx,\maxx,-3,3
linewidth 2
arrow \minx,0,\maxx,0,\marge/2,black
linewidth 3
parallel \min,-0.5,\min,0.5,1,0,\ec,black
\tmp2}
