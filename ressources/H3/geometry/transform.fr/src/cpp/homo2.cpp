target=homo2

#include "author.inc"
#include "lang_titles.inc"

#include "lang.inc"

\matrix{liste=<img src="\imagedir/homo2_1.png" alt="\name_alt">,-2,-0.5
<img src="\imagedir/homo2_2.png" alt="\name_alt">,2,0.5
<img src="\imagedir/homo2_3.png" alt="\name_alt">,0.5,2}
\integer{choix1=randint(3)}
\integer{choix2=randint(2)}
\if{\choix2=1}{\text{dep=\name_color_list[1]}
               \text{image=\name_color_list[2]}
               \text{rapport=\liste[\choix1;2]}
                \if{\choix1=1}{\text{sol=<p>\name_sol_list[1] \rapport \name_sol_list[2] -1, \name_types_list[1].</p>
                              \name_sol_list[6] \liste[1;1].}
                              }
                \if{\choix1=2}{\text{sol=<p>\name_sol_list[1] \rapport \name_sol_list[3] 1, \name_types_list[2].</p>
                              \name_sol_list[6] \liste[2;1].}
                              }
                \if{\choix1=3}{\text{sol=<p>\name_sol_list[1] \rapport \name_sol_list[4] 1, \name_types_list[3].</p>
                              \name_sol_list[6] \liste[3;1].}
                              }
               }
              {\text{dep=\name_color_list[2]}
               \text{image=\name_color_list[1]}
               \text{rapport=\liste[\choix1;3]}
               \if{\choix1=1}{\text{sol=<p>\name_sol_list[1] \rapport \name_sol_list[5] -1, \name_types_list[4].</p>
                              \name_sol_list[6] \liste[1;1].}
                              }
                \if{\choix1=2}{\text{sol=<p>\name_sol_list[1] \rapport \name_sol_list[4] 1, \name_types_list[3].</p>
                              \name_sol_list[6] \liste[2;1].}
                              }
                \if{\choix1=3}{\text{sol=<p>\name_sol_list[1] \rapport \name_sol_list[3] 1, \name_types_list[2].</p>
                              \name_sol_list[6] \liste[3;1].}
                              }
               }



\statement{\name_statement1:
  "\name_statement2[1] \image \name_statement2[2] \dep \name_statement2[3] P \name_statement2[4] \rapport".
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
</ul>
}
\answer{}{\choix1;\liste[;1]}{type=click}{option=shuffle}
\solution{\name_statement2[1] \image \name_statement2[2] \dep \name_statement2[3] P \name_statement2[4] \rapport.
\sol}
