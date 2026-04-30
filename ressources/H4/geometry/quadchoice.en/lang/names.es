!set lang_exists=yes
!!present
!distribute lines Dada la función \(f\) cuya gráfica es la siguiente.\
   Dada la función \(f\) definida por\
   ¿Cuál de las siguientes gráficas corresponde a la función\
   ¿Cuál de las siguientes expresiones corresponde a la función\
   \(g) tal que\
  Clicar encima.\
into name_present1,name_present2,name_present3,name_present4, name_present5,\
  name_present6

!!main
!set name_giveup=Abandonar la sesión

!set name_intro=Este ejercicio le ayuda a reconocer la gráfica de una función, o la función\
correspondiente a una gráfica. Las funciones en este ejercicio interactivo son funciones\
 cuadráticas, es decir, polinomios de grado 2.

!distribute lines Puede elegir sus opciones en la configuración del ejercicio\
   Tipo de ejercicio\
   Nivel de dificultad\
   Una sesión estará compuesta de\
   preguntas\
   con la puntuación asignada al final de cada sesión\
into name_choiceintro, name_style,name_level,name_seance,\
  name_questions,name_scoreremark

!set name_prompt=encontrar la función dada la gráfica,\
encontrar la gráfica dada la función,\
determinado al azar por el servidor

!!form
!distribute lines Clica aquí\
  si piensas que ninguna de las opciones corresponde a la respuesta correcta.\
 into name_click1, name_click2

!set name_questionnumber=!nosubst Pregunta número $[$replycnt+1] \
 de una sesión de $repeat.

!!answer
!distribute line Sí, su elección corresponde a la función correcta.\
    No, ha elegido una función incorrecta.\
    No, ha elegido una gráfica incorrecta.\
    No, la respuesta correcta está entre las opciones!\
    De hecho, la respuesta correcta no está en las opciones.\
    Respuesta correcta.\
    Respuesta incorrecta\
    Su elección se muestra en <span class="bold">negrita</span>, y la respuesta correcta en <span style="color:blue">azul</span>.\
   Continúe con la siguiente pregunta.\
   Puntuación\
into name_feed1,name_feed2,name_feed3,name_feed4,name_feed5,\
  name_feed6,name_feed7,name_feed8,name_feed9,name_feed10

!set name_answer1=!nosubst Pregunta número $replycnt de $repeat
!set name_answer2=!nosubst Usted debe terminar las $repeat preguntas para obtener una nota.
!set name_answer3=!nosubst Ha terminado la sesión de $repeat preguntas, con una puntuación de
!!! no accent in the following
!distribute items Opciones,Su elección,Respuesta correcta \
  into name_choice,name_yourchoice,name_goodanswer
