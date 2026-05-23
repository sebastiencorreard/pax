target=clas

#include "author.inc"
#include "lang_titles.inc"
#include "header.inc"
#include "css.inc"

\title{TITRE}

\text{size=175x70x3}
\integer{nbfnct=3}
\integer{a=random(2..10)}
\integer{b=random(-1,1)*random(2..10)}
\integer{c=random(2..11)}
\integer{d=random(-1,1)*random(2..100)}
\real{e=randint(2..100)/10}
\text{evirg=slib(numeration/ecriturenombre \e,comma tex)}

\integer{f=random(-1,1)*random(3,5,9,15)}
\integer{g=random(-1,1)*random(2,7,4,8,14)}
\rational{fg=\f/\g}
\rational{invg=-1/\g}
\rational{ac=\a/\c}
\rational{ab=\a/\b}
\rational{ax=\a/x}
\text{tfg=texmath(\fg)}
\text{tinvg=texmath(\invg)}
\text{tac=texmath(\ac)}
\text{tab=texmath(\ab)}
\text{tax=texmath(\ax)}
\text{tfracax=texmath(\a/x)}
\text{flin=wims(randitem \b x,\evirg x,\tfg x,\tinvg x)}
\text{faff1=wims(randitem -x+\c,-x-\c,x+\c,x-\c)}
\text{faff2=wims(randitem \b x+\a,\b x-\a,\f x+\evirg,\f x-\evirg,\tfg x+\a,\tinvg x-\c,\tfg x+\tac)}
\text{fnaff=wims(randitem \b x^2+\a x+\c,-x^2+\evirg x+\c, \tfg x^2+\tab x+\c)}
\matrix{donnees=-x,x,\frac{\b x}{\a},\flin
\faff1,\faff2,\frac{\b x+\c}{\a},\a(\b x+\c)
\fnaff,\b x^2,(x+\c)(x+\a),(x+\evirg)^2,(x-\c)^2, \tax +\c
\b, \tfg,\tinvg
}

\matrix{sortie=}
\for{i=1 to 4}{
\text{tmp=row(\i,\donnees)}
\text{tmp=shuffle(\tmp)}
\text{line=}
\for{j=1 to \nbfnct}{
\text{tmp1=item(\j,\tmp)}
\text{tmp1=\(x \mapsto \tmp1)}
\text{line=wims(append item \tmp1 to \line)}
}
\matrix{sortie=wims(append line \line to \sortie)}
}

\text{goodlin=row(1,\sortie)}
\text{goodaff=row(2,\sortie)}
\text{goodaut=row(3,\sortie)}
\text{goodconst=row(4,\sortie)}

\text{list=\goodlin,\goodaff,\goodaut,\goodconst}     
#include "lang.inc"

\statement{
<div class="euler_quest_nobg spacer">\name_quest</div>
<ul class="spacer">
    <li><b>\name_enonafpart</b>
           <p>\name_enonfl</p>
           \embed{r1,\size}
            <p>\name_enonfc</p>
            \embed{r2,\size}</li>
    <li><b>\name_enonfa</b></li>
    <li class="wims_nopuce">\embed{r3,\size}</li>
    <li><b>\name_enonfna</b></li>
    <li class="wims_nopuce">\embed{r4,\size}</li>
</ul>
}

\answer{\name_listfl}{\replin;\list}{type=clickfill}{option=noorder}
\answer{\name_listfc}{\repconst;\list}{type=clickfill}{option=noorder}
\answer{\name_listfa}{\repaff;\list}{type=clickfill}{option=noorder}
\answer{\name_listnfa}{\repaut;\list}{type=clickfill}{option=noorder}

\text{tmpreplin=wims(listuniq \replin)}
\text{tmplin=\tmpreplin,\goodlin}
\text{tmplin=wims(listuniq \tmplin)}
\integer{lin1=items(\tmpreplin)}
\integer{lin2=items(\goodlin)}
\integer{lin3=items(\tmplin)}
\condition{\name_enonfl}{\lin1=\lin2 and \lin2=\lin3 and \lin1=\lin3}

\text{tmprepconst=wims(listuniq \repconst)}
\text{tmpconst=\repconst,\goodconst}
\text{tmpconst=wims(listuniq \tmpconst)}
\integer{const1=items(\tmprepconst)}
\integer{const2=items(\goodconst)}
\integer{const3=items(\tmpconst)}
\condition{\name_enonfc}{\const1=\const2 and \const2=\const3 and \const1=\const3}

\text{tmprepaff=wims(listuniq \repaff)}
\text{tmpaff=\repaff,\goodaff}
\text{tmpaff=wims(listuniq \tmpaff)}
\integer{aff1=items(\tmprepaff)}
\integer{aff2=items(\goodaff)}
\integer{aff3=items(\tmpaff)}
\condition{\name_enonfa}{\aff1=\aff2 and \aff2=\aff3 and \aff3=\aff1}

\text{tmprepaut=wims(listuniq \repaut)}
\text{tmpaut=\repaut,\goodaut}
\text{tmpaut=wims(listuniq \tmpaut)}
\integer{aut1=items(\tmprepaut)}
\integer{aut2=items(\goodaut)}
\integer{aut3=items(\tmprepaut)}
\condition{\name_enonfna}{\aut1=\aut2 and \aut2=\aut3 and \aut3=\aut1}

\solution{
<div class="container">  
    <div class="table-wrapper">        
      \name_enonfl&nbsp;:
      <ul class="spacer"><li>\goodlin[1]</li>
      <li>\goodlin[2]</li>
      <li>\goodlin[3]</li></ul>
    </div>
    <div class="table-wrapper">        
      \name_enonfc&nbsp;:
     <ul class="spacer"><li>\goodconst[1]</li>
      <li>\goodconst[2]</li>
      <li>\goodconst[3]</li></ul>
    </div>
    <div class="table-wrapper">  
      \name_enonfa&nbsp;:
     <ul class="spacer"><li>\goodaff[1]</li>
     <li>\goodaff[2]</li>
     <li>\goodaff[3]</li></ul>
    </div>
    <div class="table-wrapper">
     \name_enonfna&nbsp;:
     <ul class="spacer"><li>\goodaut[1]</li>
     <li>\goodaut[2]</li>
     <li>\goodaut[3]</li></ul>
    </div>
</div>
}

\hint{\name_hint}
