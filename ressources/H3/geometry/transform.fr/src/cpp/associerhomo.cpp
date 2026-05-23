target=associerapportsitu

#include "author.inc"
#include "lang_titles.inc"

#include "lang.inc"
  
\text{situ=\name_situation 1,\name_situation 2,\name_situation 3,\name_situation 4}
\text{list1=shuffle(wims(makelist x for x=1.1 to 5 step 0.1))}
\text{list2=pari(-1*\list1[2]),pari(-1*\list1[3]),pari(-1*\list1[4])}
\text{list3bis=shuffle(2,3,4,5)}
\text{list3ter=shuffle(-2,-3,-4,-5)}
\text{list3=shuffle(\list3bis,\list3ter)}
\text{list4=shuffle(3/2,5/2,7/2,9/2,4/3,5/3,7/3,8/3,10/3,5/4,7/4,9/4,6/5,7/5,8/5,9/5,7/6,8/7,9/7,9/8)}
\text{list5=pari(-1*\list4[2]),pari(-1*\list4[3]),pari(-1*\list4[4])}
\text{list6=shuffle(wims(makelist x for x=0.1 to 0.9 step 0.1))}
\text{list7=pari(-1*\list6[2]),pari(-1*\list6[3]),pari(-1*\list6[4])}
\text{list8=shuffle(1/2,1/3,1/4,1/5,1/6,1/7,1/8,1/9,1/10,2/3,2/5,2/7,2/9,3/4,3/5,3/7,3/8,3/10,4/5,4/7,4/9,5/6,5/7,5/8,5/9,6/7,7/8,7/9,8/9)}
\text{list9=pari(-1*\list8[2]),pari(-1*\list8[3]),pari(-1*\list8[4])}
\text{choix=1,2,3,4,5,6,7,8,9}
\text{choix=shuffle(\choix)}
\text{listsitu1=\list1[1],\list3bis[1],\list4[1]}
\text{listsitu4=\list2[1],\list3ter[1],\list5[1]}
\text{listsitu2=\list6[1],\list8[1]}
\text{listsitu3=\list7[1],\list9[1]}
\text{rap1=randitem(\listsitu1)}
\text{rap2=randitem(\listsitu2)}
\text{rap3=randitem(\listsitu3)}
\text{rap4=randitem(\listsitu4)}
\text{listrap=shuffle(\rap1,\rap2,\rap3,\rap4)}
\text{rap1=\listrap[1]}
\text{rap2=\listrap[2]}
\text{rap3=\listrap[3]}
\text{rap4=\listrap[4]}
\if{\rap1 isitemof \list1 or \rap1 isitemof \list3bis or \rap1 isitemof \list4}
    {\text{good1=1}
     \text{solu1=\(\rap1 > 1\) \name_sol1 }
    }
\if{\rap1 isitemof \list2 or \rap1 isitemof \list3ter or \rap1 isitemof \list5}
    {\text{good1=4}
     \text{solu1=\(\rap1 < -1\) \name_sol4}
    }
\if{\rap1 isitemof \list6 or \rap1 isitemof \list8}
    {\text{good1=2}
     \text{solu1=\(0 < \rap1 < 1\) \name_sol2}
    }
\if{\rap1 isitemof \list7 or \rap1 isitemof \list9}
    {\text{good1=3}
     \text{solu1=\(-1 < \rap1 < 0\) \name_sol3}
    }
\if{\rap2 isitemof \list1 or \rap2 isitemof \list3bis or \rap2 isitemof \list4}
    {\text{good2=1}
    \text{solu2=\(\rap2 > 1\) \name_sol1}
    }
\if{\rap2 isitemof \list2 or \rap2 isitemof \list3ter or \rap2 isitemof \list5}
    {\text{good2=4}
    \text{solu2=\(\rap2 < -1\) \name_sol4}
    }
\if{\rap2 isitemof \list6 or \rap2 isitemof \list8}
    {\text{good2=2}
    \text{solu2=\(0 < \rap2 < 1\) \name_sol2}
    }
\if{\rap2 isitemof \list7 or \rap2 isitemof \list9}
    {\text{good2=3}
    \text{solu2=\(-1 < \rap2 < 0\) \name_sol3}
    }
\if{\rap3 isitemof \list1 or \rap3 isitemof \list3bis or \rap3 isitemof \list4}
    {\text{good3=1}
    \text{solu3=\(\rap3 > 1\) \name_sol1}
    }
\if{\rap3 isitemof \list2 or \rap3 isitemof \list3ter or \rap3 isitemof \list5}
    {\text{good3=4}
    \text{solu3=\(\rap3 < -1\) \name_sol4}
    }
\if{\rap3 isitemof \list6 or \rap3 isitemof \list8}
    {\text{good3=2}
    \text{solu3=\(0 < \rap3 < 1\) \name_sol2}
    }
\if{\rap3 isitemof \list7 or \rap3 isitemof \list9}
    {\text{good3=3}
    \text{solu3=\(-1 < \rap3 < 0\) \name_sol3}
    }
\if{\rap4 isitemof \list1 or \rap4 isitemof \list3bis or \rap4 isitemof \list4}
    {\text{good4=1}
    \text{solu4=\(\rap4 > 1\) \name_sol1}
    }
\if{\rap4 isitemof \list2 or \rap4 isitemof \list3ter or \rap4 isitemof \list5}
    {\text{good4=4}
    \text{solu4=\( \rap4 < -1\) \name_sol4}
    }
\if{\rap4 isitemof \list6 or \rap4 isitemof \list8}
    {\text{good4=2}
    \text{solu4=\(0 < \rap4 < 1\) \name_sol2}
    }
\if{\rap4 isitemof \list7 or \rap4 isitemof \list9}
    {\text{good4=3}
    \text{solu4=\(-1 < \rap4 < 0\) \name_sol3}
    }

#include "lang2.inc"

\statement{\name_statement1.
<p>\name_statement2</p>
<table class="wimscenter wimsborder">
<tr><td><img src="\imagedir/s1.png" alt="\name_alt"></td><td><img src="\imagedir/s2.png" alt="\name_alt"></td><td><img src="\imagedir/s3.png" alt="\name_alt"></td><td><img src="\imagedir/s4.png" alt="\name_alt"></td></tr>
<tr><td>\name_ssituation 1</td><td>\name_ssituation 2</td><td>\name_ssituation 3</td><td>\name_ssituation 4</td></tr></table>
\name_statement3.
<ul><li>\name_question[1] \(\rap1\) \name_question[2] \embed{reply1}. \name_question[3] \embed{reply2}.</li>
<li>\name_question[1] \(\rap2\) \name_question[2] \embed{reply3}. \name_question[3] \embed{reply4}.</li>
<li>\name_question[1] \(\rap3\) \name_question[2] \embed{reply5}. \name_question[3] \embed{reply6}.</li>
<li>\name_question[1] \(\rap4\) \name_question[2] \embed{reply7}. \name_question[3] \embed{reply8}.</li>
</ul>}

\answer{}{\good1;\name_liste}{type=menu}
\answer{}{\good1;\situ}{type=menu}
\answer{}{\good2;\name_liste}{type=menu}
\answer{}{\good2;\situ}{type=menu}
\answer{}{\good3;\name_liste}{type=menu}
\answer{}{\good3;\situ}{type=menu}
\answer{}{\good4;\name_liste}{type=menu}
\answer{}{\good4;\situ}{type=menu}

\hint{\name_hint}

\solution{<ul><li>\solu1.</li>
<li>\solu2.</li>
<li>\solu3.</li>
<li>\solu4.</li>
</ul>}
