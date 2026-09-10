target=symaxrec3
#define NUM 3
#include "lang_titles.inc"
#include "author.inc"
\keywords{symmetry}
\text{coul=darkblue,green}
\text{coul=shuffle(\coul)}

\text{col=lightblue}
\integer{x=randint(-20..-5)}
\real{x1=0.4*\x}
\real{y1=0.4*randint(-20..\x)}

\integer{x=randint(-5..10)}
\real{x2=0.4*\x}
\real{y2=0.4*randint(-20..-10)}

\integer{x=randint(12..22)}
\real{x3=0.4*\x}
\real{y3=0.4*randint(-15..\x)}

##coordonnées des 2 autres sommets du premier triangle

\real{ma=max(\y1,max(\y2,\y3))}
\real{mi=min(\x1,min(\x2,\x3))}
\real{z=(10-\ma)*0.8}
\matrix{dep=0,0,0,0,0,0,1,1,oui
1.2,1.2,0,0,0,0,1,1,non
\x1-\y1,\y1-\x1,\x2-\y2,\y2-\x2,\x3-\y3,\y3-\x3,-1,1,non
0,0,0,0,0,0,1,1,oui
\x1-\y1,\y1-\x1,\x2-\y2,\y2-\x2,\x3-\y3,\y3-\x3,1,-1,non
\x1-\y1,\y1-\x1+\z,\x2-\y2,\y2-\x2+\z,\x3-\y3,\y3-\x3+\z,1,1,non
0,0,0,0,0,0,1,1,oui
0,0,0,0,0,0,1,1,oui}
\integer{n=randint(1..8)}

\text{dep=row(\n,\dep)}
\real{a=\dep[1]}
\real{b=\dep[2]}
\real{c=\dep[3]}
\real{d=\dep[4]}
\real{e=\dep[5]}
\real{f=\dep[6]}
\real{h=\dep[7]}
\real{k=\dep[8]}

\real{i1=(\y1+\a)*\h}
\real{j1=(\x1+\b)*\k}
\real{i2=(\y2+\c)*\h}
\real{j2=(\x2+\d)*\k}
\real{i3=(\y3+\e)*\h}
\real{j3=(\x3+\f)*\k}
\text{dessincomp=vline 0,0,\col
segment 10,10,-10,-10,black
text black,9,9,large,D1}
#include "dessinsymaxrec.inc"

\statement{
#include "stat_symaxrec.inc"
}
\choice{}{\dep[9]}{oui,non}{type=menu}
