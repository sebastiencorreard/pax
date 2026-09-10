target=placer
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\precision{100}
\text{a=randint(-7..7), randint(-7..7)}
\text{a=\a[1]=0 and \a[2]=0 ? randint(-7..7), randint(1..7)}
\text{script= var brd = JXG.JSXGraph.initBoard('jxgbox', {
 axis:true,boundingbox: [-10, 10, 10, -10], grid:true});
grid = brd.create('grid', []);
jxgbox_rep1 = brd.create('point',jxgbox_var1);
}
\statement{\instruction \((\a)\).
<div class="wimscenter">
 \embed{r1,400x400
jxgbox
\script
jxgbox_var1=[0,0]
}
</div>
}

\answer{}{\a}{type=jsxgraph}{option=precision=5}
