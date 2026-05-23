target=association

#include "author.inc"
#include "lang_titles.inc"

#include "lang.inc"

text{mix=shuffle(rows(\liste))}
  
\statement{\name_statement.<br>
<div class="wimscenter">\embed{reply1,40x125x300}</div>
}

\answer{}{\name_list[;1];\name_list[;2]}{type=correspond}{option=split}
