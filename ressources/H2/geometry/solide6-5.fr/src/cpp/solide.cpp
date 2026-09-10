target=solide1 solide2 solide3 solide4

\langage{fr}
\format{html}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_solide1 || defined TARGET_solide3
\integer{nb=15}
#endif
#if defined TARGET_solide2
\integer{nb=5}
#endif
#if defined TARGET_solide4
\integer{nb=10}
#endif

#if defined TARGET_solide1 || defined TARGET_solide2 || defined TARGET_solide3
\matrix{figures=\name_solide[2],\imagedir/prismetrianga2.jpg
\name_solide[1],\imagedir/cylindre2.jpg
\name_solide[2],\imagedir/pave2.jpg
\name_solide[3],\imagedir/pyramide2.jpg
\name_solide[2],\imagedir/prismehexa2.jpg
\name_solide[2],\imagedir/cube2.jpg
\name_solide[2],\imagedir/prismeb2.jpg
\name_solide[2],\imagedir/prismec2.jpg
\name_solide[3],\imagedir/prismed2.jpg
\name_solide[2],\imagedir/prismemaison2.jpg
\name_solide[1],\imagedir/solide12.jpg
\name_solide[3],\imagedir/solide22.jpg
\name_solide[3],\imagedir/solide32.jpg
\name_solide[3],\imagedir/solide42.jpg
\name_solide[3],\imagedir/solide52.jpg
}
#endif
#if defined TARGET_solide4
\matrix{figures=5,\imagedir/prismetrianga2.jpg
10,\imagedir/solide72.jpg
6,\imagedir/pave2.jpg
14,\imagedir/solide62.jpg
8,\imagedir/prismehexa2.jpg
6,\imagedir/cube2.jpg
14,\imagedir/prismeb2.jpg
8,\imagedir/prismec2.jpg
10,\imagedir/solide82.jpg
7,\imagedir/prismemaison2.jpg
}
#endif
\text{pos=wims(values v for v=1 to \nb)}
\text{pos=shuffle(\pos)}
#if defined TARGET_solide1 || defined TARGET_solide2 || defined TARGET_solide3
\text{fig1=row(\pos[1],\figures)}
\text{fig2=row(\pos[2],\figures)}
\text{fig3=row(\pos[3],\figures)}
\text{fig4=row(\pos[4],\figures)}
\text{fig5=row(\pos[5],\figures)}
#endif
#if defined TARGET_solide4
\text{fig2=row(\pos[2],\figures)}
\integer{fac=\fig2[1]}
\integer{som=(\fac - 2)*2}
\integer{are=(\fac - 2)*3}
#endif
#if defined TARGET_solide1 || defined TARGET_solide3
\statement{
\name_enonce
<table class="wimscenter wimsborder"><tr>
<td><img src="\fig1[2]" alt=""></td>
<td><img src="\fig2[2]" alt=""></td>
<td><img src="\fig3[2]" alt=""></td>
<td><img src="\fig4[2]" alt=""></td>
<td><img src="\fig5[2]" alt=""></td>
</tr><tr>
<td>\embed{r1}</td><td>\embed{r2}</td>
<td>\embed{r3}</td><td>\embed{r4}</td>
<td>\embed{r5}</td>
</tr>
</table>}

# if defined TARGET_solide1
\answer{}{\fig1[1];\name_solide[1]}{type=dragfill}
\answer{}{\fig2[1];\name_solide[3]}{type=dragfill}
\answer{}{\fig3[1];\name_solide[1]}{type=dragfill}
\answer{}{\fig4[1];\name_solide[3]}{type=dragfill}
\answer{}{\fig5[1];\name_solide[1]}{type=dragfill}
# endif
# if defined TARGET_solide3
\answer{}{\fig1[1];\name_solide[1]}{type=clickfill}
\answer{}{\fig2[1];\name_solide[3]}{type=clickfill}
\answer{}{\fig3[1];\name_solide[1]}{type=clickfill}
\answer{}{\fig4[1];\name_solide[3]}{type=clickfill}
\answer{}{\fig5[1];\name_solide[1]}{type=clickfill}
# endif
#endif
#if defined TARGET_solide2
\text{right=\fig1[1],\fig2[1],\fig3[1],\fig4[1],\fig5[1]}
\text{left=<img src="\fig1[2]" alt="">,<img src="\fig2[2]" alt="">,
<img src="\fig3[2]" alt="">,<img src="\fig4[2]" alt="">,<img src="\fig5[2]" alt="">}
\statement{
\name_enonce
<div class="wimscenter"> \embed{r1,90x100}</div>}
\answer{}{\left;\right}{type=correspond}
#endif
#if defined TARGET_solide4
\statement{
<div class="float_right"><img src="\fig2[2]" alt=""></div>
 \name_enonce[1;]
<ul><li>
<label for="reply1">\name_enonce[2;]:</label> \embed{r1,3}
</li><li>
<label for="reply2">\name_enonce[3;]:</label> \embed{r2,3}
</li><li>
<label for="reply3">\name_enonce[4;]:</label> \embed{r3,3}
</li></ul>
}
\answer{\name_enonce[2;]}{\fac}{type=auto}
\answer{\name_enonce[3;]}{\som}{type=auto}
\answer{\name_enonce[4;]}{\are}{type=auto}
#endif
