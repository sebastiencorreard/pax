target=musique

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}

\text{range=xrange -1,1
  yrange -1,1
}
\text{size=50,50}
\text{ronde=ellipse 0,0,0.6,0.4,black}
\text{blanche=ellipse 0,0,0.6,0.4,black
  segment 0.3,0,0.3,1,black}
\text{noire=fellipse 0,0,0.6,0.4,black
  segment 0.3,0,0.3,1,black}
\text{croche=fellipse 0,0,0.6,0.4,black
  polylines black, 0.3,0,0.3,1,0.5,0.7}
\text{dcroche=\croche
  segment 0.3,0.8,0.5,0.5,black}
\text{tcroche=\dcroche
  segment 0.3,0.6,0.5,0.3,black}
\text{qcroche=\tcroche
  segment 0.3,0.4,0.5,0.1,black}
\text{point1=disk 0.5,0,3,black}
\text{point2=\point1
  disk 0.7,0,3,black}
\text{point3=\point2
  disk 0.9,0,3,black}
\text{ronde1=\ronde
  \point1}
\text{blanche1=\blanche
  \point1}
\text{noire1=\noire
  \point1}
\text{croche1=\croche
  \point1}
\text{dcroche1=\dcroche
  \point1}
\text{tcroche1=\tcroche
  \point1}
\text{ronde2=\ronde
  \point2}
\text{blanche2=\blanche
  \point2}
\text{noire2=\noire
  \point2}
\text{croche2=\croche
  \point2}
\text{dcroche2=\dcroche
  \point2}

\matrix{liste=(\ronde),(\blanche),(\noire),(\croche),(\dcroche),(\tcroche),(\qcroche)
  100,10,1,0.1,0.01,0.001,0.0001}

\matrix{liste1=(\ronde1),(\blanche1),(\noire1),(\croche1),(\dcroche1),(\tcroche1)
  110,11,1.1,0.11,0.011,0.0011}

\matrix{liste2=(\ronde2),(\blanche2),(\noire2),(\croche2),(\dcroche2)
  111,11.1,1.11,0.111,0.0111}

\matrix{Note = \liste[1;],\liste1[1;],\liste2[1;]
  \liste[2;],\liste1[2;],\liste2[2;]}

\integer{n=randint(3..5)}
\text{choix=randint(1..18)}
\for{j = 2 to \n}{
  \text{choix=\choix,randint(1..18)}
}

\text{theme=xrange -1,2*\n
    yrange -0.8,1.2}
\for{i= 1 to \n}{
  \text{theme= \theme
    translate 2*\i-2,0
    wims(rows2lines wims(declosing \Note[1;\choix[\i]]))
    killtranslate
  }
}
\text{sum=\Note[2;\choix]}
\text{sum=wims(replace internal , by + in \sum)}

\text{resultat= wims(exec float_calc
  obase=2; ibase=2; \sum)}
\integer{size1=\n*\size[1]}
\text{theme1=draw(\size1,\size[2]
  \theme)}
\text{theme= <img src="\theme1" alt="">}

#include "lang.inc"

\text{help_dessin=
    xrange -1,25
    yrange -0.8,2
    translate 0,0.4
    \noire
    text black,-0.9,-0.3,small,\name_list_notes[1]
    killtranslate
    translate 4,0.4
    \blanche
    text black,-0.9,-0.3,small,\name_list_notes[2]
    killtranslate
    translate 8,0.4
    \ronde
    text black,-0.9,-0.3,small,\name_list_notes[3]
    killtranslate
    translate 12,0.4
    \croche
    text black,-0.9,-0.3,small,\name_list_notes[4]
    killtranslate
    translate 16,0.4
    \dcroche
    text black,-0.9,-0.3,small,\name_list_notes[5]
    killtranslate
    translate 20,0.4
    \tcroche
    killtranslate
    translate 24,0.4
    \qcroche
    killtranslate
    }

\real{factor=26/2.8}

\text{newsize=\factor*\size[1]}
\text{helpd=draw(\newsize,\size[2]
  \help_dessin)}
\text{helpd= <img src="\helpd" alt="">}


\statement{\name_statement [\special{help notation,\name_explanation}] :
<div class="wimscenter">\theme</div>
}
\answer{\name_answer}{\res}{type=raw}{option=nospace}

\text{test= wims(exec float_calc
  obase=2; ibase=2; 1+(\resultat) - (\reply1))}
\condition{\name_condition \res }{\test=1}

\feedback{\test !=1}{\name_feedback \resultat}
\help{ \if{\help_subject issametext or \help_subject issametext notation}
{\name_help1
<div class="wimscenter">
\helpd
</div>
<div>
\name_help2
</div>
<div>
\name_help3
</div>
}
}
