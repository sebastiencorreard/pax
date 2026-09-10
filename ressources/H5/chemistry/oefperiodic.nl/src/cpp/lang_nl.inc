#if defined TARGET_click1
\text{namelist=nummer, symbool,naam,atoomgewicht}
\text{name_instruction=In het leeg gemaakte "<em>periodiek systeem der elementen</em>" hieronder,
  moet je klikken op de plaats van het element waarvoor geldt}
\text{name_is=is}
\text{name_answer=De positie}
\text{name_feed=Je hebt geklikt op de plaats van,in plaats van}
#endif
#if defined TARGET_blackbox|| defined TARGET_blackbox2
\text{namelist=atoomnummer, symbool, naam, atoomgewicht}
\text{quel=Wat is de,Wat is de,Wat is de,Wat is de}
\text{name_instruction=In het periodiek systeem der elementen hieronder,
  is 1 element zwart gemaakt.}
\text{name_is=}
\text{name_instruction2=van dit element}
\text{name_answer=Het atoomnummer,Het symbool is,De naam van dit element is,Het atoomgewicht is}
#endif
#if defined TARGET_corr3|| defined TARGET_corr4 || defined TARGET_corr5 || defined TARGET_corr6 || defined TARGET_corr7
\text{namelist=nummers,symbolen,namen,gewichten}
\text{name_instruction=Bepaal de juiste overeenkomst tussen de,
  en de,van de volgende atomen.}
\text{name_answer=de overeenkomst}
#endif
#if defined TARGET_fill3 || defined TARGET_fill4 || defined TARGET_fill5 || defined TARGET_fill6 || defined TARGET_fill8 || defined TARGET_fill10 || defined TARGET_fill14 || defined TARGET_fill20 || defined TARGET_fill33 || defined TARGET_fill54 || defined TARGET_fill62 || defined TARGET_fill103 || defined TARGET_fill108
\text{name_instruction=Plaats de gegeven symbolen in de onderstaande tabel.}
\text{name_case=Box}
#endif
#if defined TARGET_metals4 || defined TARGET_metals6 || defined TARGET_metals8 || defined TARGET_metals10
\text{name_instruction=Verdeel de onderstaande elementen in <em>metalen</em> en <em>niet-metalen</em>.}
\text{name_metal=Metalen,Niet-metalen}
\text{name_ismetal=een metaal,een niet-metaal,geen metaal en ook geen niet-metaal}
#endif
#if defined TARGET_one || defined TARGET_prec || defined TARGET_next
\text{name_connector=voorafgaande,volgende}
\text{namelist=het nummer,het symbool,de naam,het atoomgewicht}
\text{quel=Wat is,Wat is,Wat is,Wat is}
\text{name_is=is}
\text{name_instruction2=van het, element en waarvan}
\text{name_answer=Het atoom nummer,Het symbool,De naam van het element,Het atoomgewicht}
#endif
#if defined TARGET_order3 || defined TARGET_order4 || defined TARGET_order5 || defined TARGET_order6
\text{namelist=nummers,symbolen,namen,massas}
\text{name_instruction=Rangschik de volgende atomen in oplopende volgorde,
  door de plaatjes met je muis te lepen naar de juiste open plekken.}
\text{name_answer=Element}
#endif
