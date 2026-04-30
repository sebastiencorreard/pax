target=21 22
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#include "level.inc"
\text{poly=row(1,\poly)}
#if defined TARGET_21
\text{rep=\poly[1;4]}
#endif
#if defined TARGET_22
\text{rep=\poly[1;2]}
#endif
\text{patron=slib(geo2D/polynet \poly[1;1],size=200 html)}
\statement{
\name_instruction
\patron
<label for="reply1">\name_rep</label> \embed{r1,4}.
}
\answer{}{\rep}

#include "feedback.inc"
