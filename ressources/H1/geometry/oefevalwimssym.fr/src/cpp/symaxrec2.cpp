target=symaxrec2
#define NUM 2
#include "lang_titles.inc"
#include "author.inc"
\keywords{symmetry}
\text{coul=darkblue,green}
\text{coul=shuffle(\coul)}

\text{col=lightblue}
\real{x1=0.4*randint(-12..12)}
\real{y1=0.4*randint(-24..-12)}
\real{ux=0.4*randint(-12..-4)}
\real{uy=0.4*randint(2..12)}
\real{vx=0.4*randint(2..12)}
\real{vy=0.4*randint(2..12)}

##coordonnées des 2 autres sommets du premier triangle
\real{x2=\x1+\ux}
\real{y2=\y1+\uy}
\real{x3=\x1+\vx}
\real{y3=\y1+\vy}

\real{ma=max(-\y1,max(-\y2,-\y3))}
\real{mi=min(-\y1,min(-\y2,-\y3))}
\real{z=\mi+\ma}
\matrix{dep=0,0,0,-1,oui
0,1.2,0,-1,non
\z,\z,\z,1,non
1.2,1.2,1.2,-1,non
0,0,0,-1,oui
0,0,0,-1,oui}
\integer{n=randint(1..6)}

\text{dep=row(\n,\dep)}
\real{b=\dep[1]}
\real{a=0}
\real{d=\dep[2]}
\real{c=0}
\real{f=\dep[3]}
\real{e=0}
\real{k=\dep[4]}
\real{h=1}
\real{i1=(\x1+\a)*\h}
\real{j1=(\y1+\b)*\k}
\real{i2=(\x2+\c)*\h}
\real{j2=(\y2+\d)*\k}
\real{i3=(\x3+\e)*\h}
\real{j3=(\y3+\f)*\k}
\text{dessincomp=vline 0,0,\col
hline 0,0,black
text black,9,1,large,D1}
#include "dessinsymaxrec.inc"

\statement{
#include "stat_symaxrec.inc"
}
\choice{}{\dep[5]}{oui,non}{type=menu}
