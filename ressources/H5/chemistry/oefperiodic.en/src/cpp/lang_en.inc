#if defined TARGET_click1
\text{namelist=atomic number, symbol,name,atomic mass in \(u\)}
\text{name_instruction=In the emptied periodic table of elements below,
  click in the box for the element whose}
\text{name_is=is}
\text{name_answer=The position}
\text{name_feed=You have clicked in the box of,instead of}
#endif
#if defined TARGET_blackbox|| defined TARGET_blackbox2
\text{namelist=atomic number, symbol, name, atomic mass in \(u\)}
\text{quel=What is the,What is the,What is the,What is the}
\text{name_instruction=In the periodic table of elements below,
  one box is blackened. }
\text{name_is=}
\text{name_instruction2=of the element in this box}
\text{name_answer=The atomic number,The symbol is,The element name is,The atomic mass in \(u\)}
#endif
#if defined TARGET_corr3|| defined TARGET_corr4 || defined TARGET_corr5 || defined TARGET_corr6 || defined TARGET_corr7
\text{namelist=atomic numbers,symbols,names,atomic masses in \(u\)}
\text{name_instruction=Establish the correct correspondance between the,
 and the,of the following atoms.}
\text{name_answer=The correspondance}
#endif
#if defined TARGET_fill3 || defined TARGET_fill4 || defined TARGET_fill5 || defined TARGET_fill6 || defined TARGET_fill8 || defined TARGET_fill10 || defined TARGET_fill14 || defined TARGET_fill20 || defined TARGET_fill33 || defined TARGET_fill54 || defined TARGET_fill62 || defined TARGET_fill103 || defined TARGET_fill108
\text{name_instruction=Put the given symbols into the following table.}
\text{name_case=Box}
#endif
#if defined TARGET_metals4 || defined TARGET_metals6 || defined TARGET_metals8 || defined TARGET_metals10
\text{name_instruction=Classify the elements below into metals and non-metals.}
\text{name_metal=Metals,Non-metals}
\text{name_ismetal=a metal,a non-metal,neither metal nor non-metal}
#endif
#if defined TARGET_one || defined TARGET_prec || defined TARGET_next
\text{name_connector=immediately preceeding the one,immediately following the one}
\text{namelist=atomic number,symbol,name,atomic mass in \(u\)}
\text{quel=What is,What is,What is,What is}
\text{name_is= is}
\text{name_instruction2=of the element, whose}
\text{name_answer=The atomic number is,The symbol is,The element name is,The atomic mass in \(u\) is}
#endif
#if defined TARGET_order3 || defined TARGET_order4 || defined TARGET_order5 || defined TARGET_order6
\text{namelist=atomic numbers,symbols,names,atomic masses in \(u\)}
\text{name_instruction=Arrange the following atoms in the increasing order, by dragging them
  in to the empty boxes.}
\text{name_answer=Element}
#endif
