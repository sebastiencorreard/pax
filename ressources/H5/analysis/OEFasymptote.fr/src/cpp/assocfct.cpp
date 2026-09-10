target=assocfct assocfct2 assocfct3

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\language{fr}
\precision{10000}
\range{-5..5}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}
\integer{xmin=-10}
\integer{xmax=10}
\integer{ymin=-10}
\integer{ymax=10}
\rational{a=random(0,random(1,2,3,-1,-2,-3,1/2,1/3,-1/2,-1/3))}
\text{aa=\a}
\text{aa=wims(replace internal / by , in \aa)}
\integer{a=\aa[1]}
\integer{g=items(\aa)=1?1:\aa[2]}
\text{ta=\g=1?\a:\(\frac{\a}{\g})}
\text{ta=\ta=1?:\ta}
\text{ta=\ta=-1?-:\ta}
\integer{b=randint(1..5)}
#if defined TARGET_assocfct || defined TARGET_assocfct3
\integer{c=randint(1..5)*10}
#endif
#if defined TARGET_assocfct2
\integer{c=randint(1..5)*5}
#endif
\integer{d=randint(1..5)}
\integer{e=randint(1..3)}
\integer{f=randint(1..5)}
#if defined TARGET_assocfct
\text{flist= + \c/((\d*x+\e)^2+\f), - \c/((\d*x+\e)^2+\f),+\c/(\d*x+\e),+ \c/((\d*x+\e)*(x-\f))}
\text{denlist= (\d*x+\e)^2+\f, (\d*x+\e)^2+\f,\d*x+\e,+ (\d*x+\e)*(x-\f)}
#endif
#if defined TARGET_assocfct2
\text{den= \d*x+\e}
\text{flist= + \c/(\den), - \c/(\den),+\f/(\den),- \f/(\den)}
#endif
#if defined TARGET_assocfct3
\text{den= (\d*x+\e)*(x-\f)}
\text{flist= + \c/(\den), - \c/(\den),+(\c*x)/(\den),- (\c*x)/(\den)}
#endif
\text{fslist=}
\text{ftlist=}
\text{ftplist=}
\integer{ind=randint(1..2)}
\for{i=1 to 4}{
  \function{fi=\a/\g*x+\b \flist[\i]}
  \function{fi=simplify(\fi)}
  \text{numfi=pari(numerator(\fi))}
  \text{denfi=pari(denominator(\fi))}
#if defined TARGET_assocfct
  \text{den=\denlist[\i]}
#endif
  \text{ft=\(\frac{texmath(\numfi)}{texmath(\denfi)}\)}
  \function{ftp=\(\frac{\c}{texmath(\den)})}
  \text{fslist=wims(append item \fi to \fslist)}
  \text{ftlist=wims(append item \ft to \ftlist)}
  \text{ftplist=wims(append item \ftp to \ftplist)}
}
\text{couleurs=shuffle(purple,blue,orange,green)}
\text{size=200}
\text{size2=300}
\text{graph3=dsegment -\e/\d,\ymin,-\e/\d,\ymax,red}
#if defined TARGET_assocfct || defined TARGET_assocfct3
\text{graph4=dsegment -\e/\d,\ymin,-\e/\d,\ymax,red
   dsegment \f,\ymin,\f,\ymax,red}
#endif
#if defined TARGET_assocfct2
\text{graph4=dsegment -\e/\d,\ymin,-\e/\d,\ymax,red}
#endif
\text{graphList=}
\text{graph2List=,,\graph3,\graph4}
%%# cadre générique %%#
\text{cadre=
   xrange \xmin, \xmax
   yrange \ymin,\ymax
   parallel \xmin,\ymin,\xmin,\ymax,1,0,\xmax - \xmin +1,grey
   parallel \xmin,\ymin,\xmax,\ymin,0,1,\ymax -\ymin +1,grey
   hline 0,0,black
   arrow  0,0,1,0,6,black
   arrow 0,0,0,1,6,black
   vline 0,0,black
   linewidth 2
   dsegment \xmin,\a/\g*\xmin+\b,\xmax,\a/\g*\xmax+\b,red}
\for{k=1 to 4}{
#if defined TARGET_assocfct
  \if{\k=3}{
    \text{graph=<img src="draw(\size,\size
      \cadre
     plot \couleurs[\k], \fslist[\k]
     \graph3
      )" width="\size" height="\size" alt="">}
 }{
  \if{\k=4}{
  \text{graph=<img src="draw(\size,\size
    \cadre
    plot \couleurs[\k], \fslist[\k]
   \graph4
    )" width="\size" height="\size" alt="">}
   }{
  \text{graph=<img src="draw(\size,\size
    \cadre
   plot \couleurs[\k], \fslist[\k]
    )" width="\size" height="\size" alt="">}
    }
   }
#endif
#if defined TARGET_assocfct2
  \text{graph=<img src="draw(\size,\size
    \cadre
    \graph4
   range \xmin,-\e/\d-0.1
   plot \couleurs[\k], \fslist[\k]
   range -\e/\d+0.1,\xmax
   plot \couleurs[\k], \fslist[\k]
  )" width="\size" height="\size" alt="">
    }
#endif
#if defined TARGET_assocfct3
\text{graph=<img src="draw(\size,\size
    \cadre
    \graph4
   plot \couleurs[\k], \fslist[\k]
    )" width="\size" height="\size" alt="">}
#endif
  \text{graph=<table border="1">
      <tr><td>\graph</td></tr></table>}
  \text{graphList=wims(append item \graph to \graphList)}
}
\text{taille=\size x\size x\size2}
\text{ftdte=\a=0?\b:\ta x + \b}
#if defined TARGET_assocfct
\text{textsol=\name_textsol:<ul><li>
\ftlist[1]=\ftdte + \ftplist[1]</li><li>
\ftlist[2]=\ftdte - \ftplist[2]</li><li>
\ftlist[3]=\ftdte + \ftplist[3]</li><li>
\ftlist[4]=\ftdte + \ftplist[4]</li></ul>}
#endif
#if defined TARGET_assocfct3
\text{f=\f x}
#endif
#if defined TARGET_assocfct2 || defined TARGET_assocfct3
\text{textsol=\name_textsol:<ul><li>
\ftlist[1]=\ftdte + \(\frac{\c}{texmath(\den)}\)</li><li>
\ftlist[2]=\ftdte - \(\frac{\c}{texmath(\den)}\)</li><li>
\ftlist[3]=\ftdte + \(\frac{\f}{texmath(\den)}\)</li><li>
\ftlist[4]=\ftdte - \(\frac{\f}{texmath(\den)}\)</li></ul>}
#endif
\statement{
  \name_question
<div class="wimscenter">
  \embed{reply 1,\taille}
</div>
}
%%%% soumission de réponse %%%%
\answer{\name_answer}{\graphList;\ftlist}{type=correspond}
\feedback{1=1}{\textsol}
