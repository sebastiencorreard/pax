target=oefcoder1 oefcoder2 oefcoder3 oefcoder4 oefcoder5
#if defined TARGET_oefcoder1
# define NUM 1
#endif
#if defined TARGET_oefcoder2
# define NUM 2
#endif
#if defined TARGET_oefcoder3
# define NUM 3
#endif
#if defined TARGET_oefcoder4
# define NUM 4
#endif
#if defined TARGET_oefcoder5
# define NUM 5
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\keywords{symmetry}
\text{l1h=draw(24,24
segment 0,12,24,12,black
segment 8,18,12,6,red
segment 12,18,16,6,red)}

\text{l1v=draw(24,24
segment 12,0,12,24,black
segment 18,8,6,12,red
segment 18,12,6,16,red)}

\text{l1d1=draw(24,24
segment 0,0,24,24,black
segment 16,8,4,12,red
segment 19,12,7,16,red)}

\text{l1d2=draw(24,24
segment 0,24,24,0,black
segment 19,12,7,8,red
segment 16,16,4,12,red)}

\text{l3h=draw(24,24
segment 0,12,24,12,black
circle 12,12,8,red)}

\text{l3v=draw(24,24
segment 12,0,12,24,black
circle 12,12,8,red)}

\text{l3d1=draw(24,24
segment 0,24,24,0,black
circle 12,12,8,red)}

\text{l3d2=draw(24,24
segment 0,0,24,24,black
circle 12,12,8,red)}

\text{l3e1=draw(24,24
segment 0,19,24,5,black
circle 12,12,8,red)}

\text{l3e2=draw(24,24
segment 0,5,24,19,black
circle 12,12,8,red)}

\text{a1=draw(24,24
square 2,2,10,red
segment 12,0,12,24,black
segment 0,12,24,12,black)}

\text{a2=draw(24,24
poly red,12,12,6,6,12,0,18,6
segment 0,24,24,0,black
segment 0,0,24,24,black)}

\text{a3=draw(24,24
square 1,14,10,red
segment 1,0,1,24,black
segment 1,23,24,23,black)}

\text{a4=draw(24,24
square 13,14,10,red
segment 23,0,23,24,black
segment 0,23,24,23,black)}

#if defined TARGET_oefcoder1
\text{type=dragfill}
\text{geom=draw(300,300
segment 150,0,150,300,red
segment 75,150,225,150,black
segment 75,150,150,75,black
segment 150,75,225,150,black
segment 70,145,80,155,black
segment 70,155,80,145,black
segment 220,145,230,155,black
segment 230,145,220,155,black
text black,60,140,medium,A
text black,235,140,medium,B
text black,140,65,medium,C
text black,155,10,medium,D1
)}
\text{cod1=100x138}
\text{cod2=180x138}
\text{cod3=138x138}
\text{cod4=101x100}
\text{cod5=175x100}

\text{rep1=\l1h}
\text{rep2=\l1h}
\text{rep3=\a1}
\text{rep4=\l3d1}
\text{rep5=\l3d2}
\text{f1=}
\text{cnt=1}
#endif
#if defined TARGET_oefcoder2
\text{type=clickfill}
\text{geom=draw(300,300
segment 150,0,150,300,red
square 30,150,10,red
segment 30,160,120,160,black
segment 30,160,30,108,black
segment 120,160,30,108,black

segment 25,155,35,165,black
segment 25,165,35,155,black
segment 115,165,125,155,black
segment 115,155,125,165,black
segment 25,103,35,113,black
segment 25,113,35,103,black

segment 270,160,180,160,black
segment 270,160,270,108,black
segment 270,108,180,160,black

segment 265,155,275,165,black
segment 265,165,275,155,black
segment 265,113,275,103,black
segment 275,113,265,103,black
segment 175,155,185,165,black
segment 175,165,185,155,black
text black,15,160,medium,A
text black,130,160,medium,B
text black,15,90,medium,C
text black,280,160,medium,E
text black,165,160,medium,F
text black,280,90,medium,G

text black,155,10,medium,D1
)}
\text{cod1=60x148}
\text{cod2=213x148}
\text{cod3=247x137}
\text{cod4=60x120}
\text{cod5=213x122}

\text{rep1=\l1h}
\text{rep2=\l1h}
\text{rep3=\a4}
\text{rep4=\l3e2}
\text{rep5=\l3e1}
\text{f1=<img src="\l3d1" alt="">,<img src="\l3d2" alt="">}
\text{cnt=3}
#endif
#if defined TARGET_oefcoder3
\text{type=clickfill}
\text{geom=draw(300,300
segment 100,0,100,300,red
segment 0,150,300,150,red
segment 20,150,100,70,black
segment 100,70,239,150,black
segment 100,230,239,150,black
segment 20,150,100,230,black

text black,10,135,medium,A
text black,90,60,medium,B
text black,245,135,medium,C
text black,90,230,medium,D
)}
\text{cod1=48x178}
\text{cod2=48x98}
\text{cod3=88x138}
\text{cod4=156x97}
\text{cod5=156x179}

\text{rep1=\l1d1}
\text{rep2=\l1d2}
\text{rep3=\a1}
\text{rep4=\l3e2}
\text{rep5=\l3e1}
\text{f1=<img src="\l3d1" alt="">,<img src="\l3d2" alt="">}
\text{cnt=1}
#endif
#if defined TARGET_oefcoder4
\text{type=clickfill}
\text{geom=draw(300,300
segment 300,80,0,80,red
segment 10,230,290,69,red
segment 150,10,150,290,black
segment 150,10,30,80,black
segment 150,10,270,80,black
segment 30,80,150,290,black
segment 270,80,150,290,black
segment 150,150,30,80,black

text black,160,2,medium,A
text black,155,150,medium,B
text black,20,85,medium,C
text black,275,85,medium,E
text black,160,285,medium,F
text black,5,65,medium,D1
text black,10,210,medium,D2
)}
\text{cod1=90x26}
\text{cod2=90x110}
\text{cod3=138x200}
\text{cod4=138x40}
\text{cod5=138x100}

\text{rep1=\l3e1}
\text{rep2=\l3e2}
\text{rep3=\l3v}
\text{rep4=\l1v}
\text{rep5=\l1v}
\text{f1=<img src="\l3d1" alt="">,<img src="\l3d2" alt="">}
\text{cnt=3}
#endif
#if defined TARGET_oefcoder5
\text{type=clickfill}
\text{geom=draw(300,300
segment 110,300,190,0,red
segment 19,155,261,218,black
segment 160,117,261,218,black
segment 229,98,261,218,black
segment 140,187,229,98,black
segment 19,155,229,98,black
segment 19,155,132,218,black
segment 132,218,261,218,black

text black,265,210,medium,A
text black,10,150,medium,B
text black,150,105,medium,C
text black,130,170,medium,E
text black,225,80,medium,F
text black,135,220,medium,G

text black,190,10,medium,D1
)}
\text{cod1=150x153}
\text{cod2=196x107}
\text{cod3=173x130}
\text{cod4=73x180}
\text{cod5=180x206}

\text{rep1=\l1d2}
\text{rep2=\l1d2}
\text{rep3=\a2}
\text{rep4=\l3e2}
\text{rep5=\l3h}
\text{f1=<img src="\l3d1" alt="">,<img src="\l3d2" alt="">}
\text{cnt=2}
#endif

\statement{
<ul>
\for{k=1 to \cnt}{
  <li>\enonc[\k;]</li>
}
</ul>
\name_stat
  <div class="wimscenter">\special{imagefill \geom,300x300,24x24
    r1,\cod1
    r2,\cod2
    r3,\cod3
    r4,\cod4
    r5,\cod5}
</div>

 }

\answer{}{<img src="\rep1" alt="">;<img src="\l1h" alt="">,<img src="\l1v" alt="">}{type=\type}{option=shuffle}
\answer{}{<img src="\rep2" alt="">;<img src="\l3h" alt="">,<img src="\l3v" alt="">,<img src="\a2" alt="">}{type=\type}{option=shuffle}
\answer{}{<img src="\rep3" alt="">;<img src="\l1d2" alt="">,\f1}{type=\type}{option=shuffle}
\answer{}{<img src="\rep4" alt="">;<img src="\l3e1" alt="">,<img src="\l3e2" alt="">}{type=\type}{option=shuffle}
\answer{}{<img src="\rep5" alt="">;<img src="\a1" alt="">,<img src="\a3" alt="">,<img src="\a4" alt="">}{type=\type}{option=shuffle}
