target=solide5 solide6
\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}

\integer{nb=10}

\matrix{figures=\name_figure[1],\imagedir/prismetrianga2.jpg
\name_figure[2],\imagedir/pave2.jpg
\name_figure[3],\imagedir/prismehexa2.jpg
\name_figure[4],\imagedir/cube2.jpg
\name_figure[5],\imagedir/prismeb2.jpg
\name_figure[3],\imagedir/prismec2.jpg
\name_figure[6],\imagedir/prismemaison2.jpg
\name_figure[5],\imagedir/solide62.jpg
\name_figure[7],\imagedir/solide72.jpg
\name_figure[7],\imagedir/solide82.jpg}
\text{pos=wims(values v for v=1 to \nb)}
\text{pos=shuffle(\pos)}
\text{fig2=row(\pos[2],\figures)}
#if defined TARGET_solide6
\text{fig=\name_figure}
\integer{p=positionof(\fig2[1],\fig)}
#endif
\statement{<div class="float_right"><img src="\fig2[2]" alt=""></div>
\name_enonce
#if defined TARGET_solide5
\embed{c1}.
#endif
#if defined TARGET_solide6
\embed{r1}.
#endif
}
#if defined TARGET_solide5
\choice{}{\fig2[1]}{\name_figure}
#endif
#if defined TARGET_solide6
\answer{}{\p;\name_figure}{type=menu}
#endif
