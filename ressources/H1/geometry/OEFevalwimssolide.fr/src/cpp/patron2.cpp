target=oefpatron2

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{coul=black,white}
\integer{dim=80}
\text{let=a,b,c}
\text{let=shuffle(\let)}

\matrix{pats=1,2,3,6,10,14,120,310,160,20,215,230,80,125,120,150,80x20,160x360,290x70
1,2,6,7,11,12,35,70,295,155,90,20,170,205,200,240,240x280,320x180,320x280
2,5,6,10,11,14,295,235,250,180,120,320,120,240,90,205,210x80,210x150,30x150
1,2,6,10,11,15,120,230,295,310,250,365,120,150,90,125,30x70,160x20,80x20
1,2,6,10,14,15,40,70,90,20,170,20,90,125,120,150,110x230,110x310,160x360
3,7,8,10,11,14,250,20,380,150,330,200,200,150,170,180,110x310,160x360,290x230
2,5,6,7,11,12,165,20,295,150,90,205,90,100,120,70,370x230,320x180,240x280
2,5,6,7,8,11,165,20,295,235,40,155,120,75,90,100,320x100,320x200,370x150
}

\integer{ch=randint(1..8)}
\text{pat=row(\ch,\pats)}
\text{coord=}
\for{i=1 to 6}{
  \integer{v=floor((\pat[\i]-1)/4)}
  \integer{x=50+(\pat[\i]-4*\v-1)*\dim}
  \integer{y=40+\v*\dim}
  \text{coord=wims(append item \x to \coord)}
  \text{coord=wims(append item \y to \coord)}
}

\text{plac1=\pat[17]}
\text{plac2=\pat[18]}
\text{plac3=\pat[19]}

\text{patron=draw(420,400
square \coord[1],\coord[2],\dim,\coul[1]
square \coord[3],\coord[4],\dim,\coul[1]
square \coord[5],\coord[6],\dim,\coul[1]
square \coord[7],\coord[8],\dim,\coul[1]
square \coord[9],\coord[10],\dim,\coul[1]
square \coord[11],\coord[12],\dim,\coul[1]
text black,\pat[7],\pat[8],large,\let[1]
text black,\pat[9],\pat[10],large,\let[2]
text black,\pat[11],\pat[12],large,\let[3]
text black,\pat[13],\pat[14],large,d
text black,\pat[15],\pat[16],large,d)}

\statement{
  \name_enonce:
  <div class="wimscenter">\special{imagefill \patron,420x400,20x20
    r1,\plac1
    r2,\plac2
    r3,\plac3
    }
</div>
 }

\answer{}{\let[1];a,b,c}{type=clickfill}
\answer{}{\let[2];a,b,c}{type=clickfill}
\answer{}{\let[3];a,b,c}{type=clickfill}
