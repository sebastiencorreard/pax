\text{name1=<span class="ecrit_1">slib(lang/fname fr,boy)</span>}
\text{name2=<span class="ecrit_2">slib(lang/fname fr,girl)</span>}
\text{name3=<span class="ecrit_3">slib(lang/fname fr,girl)</span>}
\text{name=shuffle(\name1,\name2,\name3)}
\text{name=wims(listuniq \name)}
\integer{nb=items(\name)}
\if{\nb<3}{\text{name=shuffle(Pierre,Diane,Albane)}
\text{name1=<span class="ecrit_1">\name[1]</span>}
\text{name2=<span class="ecrit_2">\name[2]</span>}
\text{name3=<span class="ecrit_3">\name[3]</span>}}
