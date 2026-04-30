target=evolmeth1 evolmeth2 evolmeth3 evolmeth5
\author{Bernadette, Perrin-Riou}
\email{bpr@math.u-psud.fr}
\text{choix=randint(1..4)}
#include "lang_fr.inc"
#if defined TARGET_evolmeth1
\title{B - TITRE}
#endif
#if defined TARGET_evolmeth2
\title{C - TITRE}
#endif
#if defined TARGET_evolmeth3
\title{D - TITRE}
#endif
#if defined TARGET_evolmeth5
\title{E - TITRE}
#endif


\integer{s=3}
\integer{s=\confparm1=1 ? 5}
\integer{M=\confparm1=2 ? randint(3..4)}
\integer{N=\confparm1=3 ? randint(1..2)}

\matrix{Data=wims(translate [] to {} in \Data)}
\text{data=wims(embraced randitem \Data)}

\integer{lg0=items(\data[1;])}
\integer{min=max(1,\lg0-\s)}
\integer{max=min(\min+4,\lg0)}
\integer{lg=randint(\min .. \max)}
\integer{lg=\lg>=5 ? \lg:\lg0}
\text{bat=wims(makelist x for x=1 to \lg0)}
\text{bat=shuffle(\bat)}
\text{bat=\bat[1..\lg]}
\text{bat=wims(sort numeric items \bat)}
\text{data1=\data}
\matrix{data=\data[1;\bat]
\data[2;\bat]}
#if defined TARGET_evolmeth1
\text{orga0=randint(2..\lg)}
\text{orga=\data[1;\orga0]}
\text{rep=\orga0!=\lg ? \data[1;\orga0+1..\lg]: \data[1;\orga0-1]}
\text{liste=\data[1;]}
#endif
#if defined TARGET_evolmeth2
\text{rep=randint(2..\lg-3)}
\text{n=randint(2..4)}
\integer{m=min(\lg-\rep+1,\n)}
\text{c=wims(makelist x for x=\rep to \lg)}
\text{c=shuffle(\c)}
\text{c=\c[1..\m]}
\text{orga=\data[1;\c]}
\text{rep=pari(vecmin([\c]))}
\text{rep=1..\rep}
\text{rep=\data[2;\rep]}
\text{rep=wims(nonempty items \rep)}
\text{liste=\data[2;]}
#endif
#if defined TARGET_evolmeth3 || TARGET_evolmeth5
\text{rep=randint(2..\lg-3)}
\text{n=randint(2..4)}
\integer{m=min(\lg-\rep+1,\n)}
\text{c=wims(makelist x for x=\rep+1 to \lg)}
\text{c=shuffle(\c)}
\text{c=\c[1..\m]}
\text{rep=pari(vecmin([\c]))}
\text{orga=\data[1;\c]}
\text{liste=\data[1;]}
#endif
#include "tree.inc"
#if defined TARGET_evolmeth1 || defined TARGET_evolmeth2
\text{dessincanvas=canvasdraw(800,400
\dessin)}
\statement{
\instruction <span class="wims_emph">\orga</span>.
<div class="wimscenter">\dessincanvas</div>
<div class="wimscenter">\embed{r1,150 x 30 x 5}</div>}
\answer{}{\rep;\liste}{type=dragfill}{option=noorder}
#endif
#if defined TARGET_evolmeth3 || TARGET_evolmeth5
# if defined TARGET_evolmeth3
\text{replist=}
\for{j=1 to \rep}{
  \text{replist=wims(append item \points[2*\j-1],\points[2*\j] to \replist)}
}
# else
\text{replist=\points[2*\rep-1],\points[2*\rep]}
# endif
\statement{
\instruction <span class="wims_emph">\orga</span>.
<div class="wimscenter">\embed{r1,800 x 400}</div>
}
\answer{}{[\dessin];crosshairs, \replist}{type=draw}{option=eqweight split legend}
#endif
