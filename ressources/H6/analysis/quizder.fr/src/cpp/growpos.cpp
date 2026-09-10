target=growpos

#define NUM
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{data=randomrow(
 f,\inc,f',\pos,\spos,\inc,\sinc,\noth
 f,\dec,f',\neg,\sneg,\dec,\sdec,\noth
 f,\sinc,f',\pos,\spos,\inc,\sinc,\noth
 f,\sdec,f',\neg,\sneg,\dec,\sdec,\noth
 f,\spos,f',\noth,\sinc,\inc,\spos,\pos
 f',\pos,f,\inc,\sinc,\pos,\spos,\noth
 f',\neg,f,\dec,\sdec,\neg,\sneg,\noth
 f',\spos,f,\sinc,\inc,\pos,\spos,\noth
 f',\sneg,f,\sdec,\dec,\neg,\sneg,\noth
 f,random(\pos,\spos),f',\noth,\inc,\sinc,\pos,\spos
 f,random(\neg,\sneg),f',\noth,\dec,\sdec,\neg,\sneg
 f',random(\inc,\sinc),f,\noth,\pos,\spos,\inc,\sinc
 f',random(\dec,\sdec),f,\noth,\neg,\sneg,\dec,\sdec
)}

\text{f1=item(1,\data)}
\text{prop1=item(2,\data)}
\text{f2=item(3,\data)}
\text{good=item(4,\data)}
\text{bad=item(5..-1,\data)}

\statement{\name_statement:
<p>
\name_if \(\f1) \prop1, \(\f2) \embed{choice 1}.
</p>
\if{\status!=end}{
<div class="wims_instruction">
\name_instruction
</div>
}
}

\choice{\name_choice}{\good}{\bad}
