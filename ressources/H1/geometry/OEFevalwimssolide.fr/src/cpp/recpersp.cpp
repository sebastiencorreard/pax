target=oefrecpersp1 oefrecpersp2
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
#if defined TARGET_oefrecpersp1
\text{fig=src="\imagedir/cubeaxe.gif"}
#endif
#if defined TARGET_oefrecpersp2
\text{fig=src="\imagedir/Cubec.gif"}
#endif
\statement{<div class="wims_columns">
 <div class="medium_size img_col"><img \fig alt=""></div>
 <div class="medium_size text_col">
\enonc.
<ul><li><label for="reply1">\name_question[1]:</label> \embed{r1,3}
</li><li><label for="reply2">\name_question[2]:</label> \embed{r2,3}
</li><li><label for="reply3">\name_question[3]:</label> \embed{r3,3}
</li><li>\name_question[4]: \embed{r4,3}
</li></ul>
</div></div>
}

\answer{}{6}{type=raw}
\answer{}{12}{type=raw}
\answer{}{8}{type=raw}
#if defined TARGET_oefrecpersp1
\answer{}{1;\name_ouinon}{type=radio}
#endif
#if defined TARGET_oefrecpersp2
\answer{}{2;\name_ouinon}{type=radio}
#endif
