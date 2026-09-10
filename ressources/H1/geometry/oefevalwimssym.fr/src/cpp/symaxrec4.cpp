target=symaxrec4
#define NUM 4
#include "lang_titles.inc"
#include "author.inc"
\keywords{symmetry}
\text{coul=darkblue,green}
\text{coul=shuffle(\coul)}

\text{col=lightblue}
\real{x1=0.4*randint(-24..-12)}
\real{y1=0.4*randint(-12..12)}
\real{ux=0.4*randint(12..22)}
\real{uy=0.4*randint(-12..-4)}
\real{vx=0.4*randint(12..32)}
\real{vy=0.4*randint(2..12)}

%%coordonnées des 2 autres sommets du premier triangle
\real{x2=\x1+\ux}
\real{y2=\y1+\uy}
\real{x3=\x1+\vx}
\real{y3=\y1+\vy}

\real{ma=max(-\x1,max(-\x2,-\x3))}
\real{mi=min(-\x1,min(-\x2,-\x3))}
\real{z=\mi+\ma}
\matrix{dep=0,0,0,-1,oui
0,1.2,0,-1,non
\z,\z,\z,1,non
1.2,1.2,1.2,-1,non
0,0,0,-1,oui
0,0,0,-1,oui}
\integer{n=randint(1..6)}

\text{dep=row(\n,\dep)}
\real{a=\dep[1]}
\real{b=0}
\real{c=\dep[2]}
\real{d=0}
\real{e=\dep[3]}
\real{f=0}
\real{h=\dep[4]}
\real{k=1}
\real{i1=(\x1+\a)*\h}
\real{j1=(\y1+\b)*\k}
\real{i2=(\x2+\c)*\h}
\real{j2=(\y2+\d)*\k}
\real{i3=(\x3+\e)*\h}
\real{j3=(\y3+\f)*\k}
\text{dessincomp=hline 0,0,\col
vline 0,0,black
text black,0.5,9,large,D1
}
#include "dessinsymaxrec.inc"

\statement{
#include "stat_symaxrec.inc"
}
\choice{}{\dep[5]}{oui,non}{type=menu}
