\text{name_answer=Number of ways}
#if defined TARGET_tablediner1 || defined TARGET_tablediner2 || defined TARGET_tablediner3 || defined TARGET_tablediner4
\text{name_enonce=couples take dinner together. How many ways there are for these,
  people to sit around the table such that}
# if defined TARGET_tablediner1 || defined TARGET_tablediner2 || defined TARGET_tablediner4
\text{name_question=each gentleman is between two ladies}
#   if defined TARGET_tablediner2
\text{name_question2= and each husband is at the side of his wife}
#   endif
#   if defined TARGET_tablediner4
\text{name_question2=and that no husband is at the side of his wife}
#   endif
# endif
# if defined TARGET_tablediner3
\text{name_question2=each husband is at the side of his wife}
# endif
#endif
#if defined TARGET_Regtriangle
\text{name_enonce=Let \(P\) be a regular polygon of,sides}
\text{name_question=How many distinct triangles are there, whose 3 vertices are
  vertices of \(P\)}
\text{name_answer=Number of triangles}
#endif
#if defined TARGET_boiteslettres
\text{name_question=How many different ways there are to put,
  letters into ,letterboxes}
#endif
#if defined TARGET_bonbon
\text{name_method=each girl gets at least one,
	each boy gets at least one,
	each child gets at least one,
	each girl gets at least 1 and each boy gets at least 2,
	each girl gets at least 2 and each boy gets at least 1,
	each child gets at least 2,
	each girl gets at least 2 and each boy gets at least 3,
	each girl gets at least 3 and each boy gets at least 2}
\text{name_question=How many ways there are to distribute,
  sweets to, girls and , boys so that}
#endif
#if defined TARGET_Doublelangue
\text{name_enonce=Among, pupils of a class, speak French,
  speak German. Each pupil speaks either French or German.}
\text{name_question=Now we have to choose two among these, such that one
  speaks French, the other speaks German.  How many possible
  choices are there}
\text{name_answer=Number of choices}
#endif
#if defined TARGET_Hotellampe
\text{name_enonce=A hotel has a long corridor lit by, aligned lamps.}
\text{name_enonce2=In order to save energy, the hotel turns off, of these lamps
  during the night.}
\text{name_question=To have a minimum of lighting, one cannot turn off adjacent lamps, nor
  lamps at the extremities of the corridor. In this case, how many different
  ways there are to turn off}
\text{name_lampe=lamps}
#endif
#if defined TARGET_triangline
\text{name_enonce=We have 2 parallel lines in the plane. On the first line we
have LLLL points, and on the second, MMMM points.}
\text{name_question=How many triangles can be formed by these TTTT points}
\text{name_answer=Number of triangles}
#endif
#if defined TARGET_triangle
\text{name_enonce=We haves LLLL lines in the plane, of which XXXX contains the
  origin of the plane. There is no other point contained in more than two lines,
  nor any line parallel to another.}
\text{name_question=How many triangles are formed by these,lines}
\text{name_answer=Number of triangles}
#endif
#if defined TARGET_subsets
\text{name_enonce=A finite set \(S\) has,subsets of,elements.
  What is the number of elements of \(S\)}
#endif
#if defined TARGET_rectangle
\text{name_enonce=We have XXXX lines in the plane, of which YYYY are horizontal,
  and ZZZZ are vertical.}
\text{name_question=How many rectangles are formed by these,lines}
#endif
#if defined TARGET_Ordinat1 || defined TARGET_Ordinat2
\text{name_enonce=A school has a computer room with XXXX PC's.
  A group of YYYY pupils take a lesson in this computer room.}
# if defined TARGET_Ordinat1
\text{name_question=How many different ways there are to attribute each pupil to
  a (distinct) PC}
# endif
# if defined TARGET_Ordinat2
\text{name_question=How many different ways there are to distribute the pupils over the PC's,
  such that each PC receives ZZZZ pupils}
# endif
#endif
#if defined TARGET_quadriline
\text{name_enonce=We have 2 parallel lines in the plane. On the first line we
have XXXX points, and on the second, YYYY points.}
\text{name_question=How many quadrilaterals can be formed by these, points}
\text{name_answer=Number of quadrilaterals}
#endif
#if defined TARGET_partfix
\matrix{name_question=In how many ways can we write
  where the \(n_i\) are integers greater than or equal to,arranged in the order}
\text{name_order=increasing,decreasing}
#endif
#if defined TARGET_n || defined TARGET_nn
\text{name_question=Let \(n\) be a positive integer such that}
\text{name_question=What is the value of }
\text{name_answer=Your answer}
#endif
#if defined TARGET_busetconducteu
\text{name_enonce=There are, bus,drivers and,controllers}
\text{name_question=How many ways there are to attribute the drivers and controllers
  to the bus, such that each bus has one driver and one controller}
#endif
#if defined TARGET_committee
\text{name_question=We have a class of XXXX boys and YYYY girls.
  How many possibilities are there to compose a committee of class with
  CCCC pupils, knowing that there must be at least BBBB and
  GGGG in the committee}
\text{name_answer=Nombre de possibilités}
\text{name_gb=boy,girl}
\text{name_gbs=boys,girls}
#endif
#if defined TARGET_intersection || defined TARGET_intersection2 || defined TARGET_intersection3
\text{name_enonce=In the plane, two lines has at most one intersection point.}
\text{name_question=How many intersection points there are at most among,lines}
\text{name_answer=Number of points}
# if defined TARGET_intersection2
\text{name_question1=of which,are ,(therefore parallel)}
\text{name_dir=horizontal,vertical}
# endif
# if defined TARGET_intersection3
\text{name_question1=of which, contains the origin of the plane}
# endif
#endif
#if defined TARGET_posneg
\text{name_enonce=Let \(S\) be a set containing, positive integers and,
  negative integers. The absolute values of these, integers are
  distinct prime numbers.}
\text{name_question=What is the number of, of two different numbers in \(S\)&nbsp;}
\text{qlist=negative numbers which are products,
positive numbers which are products,
negative rational numbers which are quotients,
positive rational numbers which are quotients}
\text{name_answer=The number}
#endif
#if defined TARGET_party
\text{name_enonce=XXXX couples and YYYY non-maried people meet during a party.
  At the start of the party, each participant shake hands with each other
  participant once, except that there is no handshake between husband and
  wife.}
\text{name_question=How many handshakes have occurred in total}
\text{name_answer=Handshakes}
#endif
#if defined TARGET_couples
\text{name_question=How many possibilities are there to form,
  couples from , men and, women}
\text{name_answer=Number of possibilities}
#endif
#if defined TARGET_groupement
\text{name_question=In how many ways can one divide a class of,
  pupils into, groups of , pupils each}
#endif
#if defined TARGET_helico
\text{name_enonce=We have,tourism helicopters, pilots and, hostesses.}
\text{name_question=How many different ways there are to attribute the pilots
  and hostesses to the helicopters, such that each helicopter has one pilot
  and two hostesses}
#endif
#if defined TARGET_mots
\text{name_question=How many distinct words can be formed from the TTTT first
  letters of the alphabet, knowing that each letter is used exactly once
in each word, and that the AAAA first letters {BBBB} must appear grouped
in each word}
\text{name_hint=First consider the, first letters as one element.}
\text{name_answer=Number of words}
#endif
#if defined TARGET_monom3 || defined TARGET_monom4
\text{name_question=How many integers are there of the form,
  where the exponents,
  are non-negative integers with}
\text{name_answer=Number of integers}
\text{name_hint=The bases XXXX being coprime,
  these integers are different for any different choices of XXXX.
  Hence it suffices to evaluate the number of possibilities of writing}
#endif
