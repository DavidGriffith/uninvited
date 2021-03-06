! seeno.h for Inform 6 with library 6/10
!
! A library to change the standard Inform message "You can't see any such thing." to
! the more specific "You see no xxx yyy here."  Note that this can repeat
! typing errors back to the player.
!
! Written by C Knight.
! Comments and bug reports welcomed: please see www.metebelis3.free-online.co.uk to email.
!
! Based on dunno.h (I don't know the word "kludge")
! version 1.1 - 2 Apr 2001 by Neil Cerutti (cerutti@together.net)
!
! To use this file, put the command
!
!   Include "seeno.h";
!
! in your program's source code after including "parser".
!
! If you have defined your own ParserError() routine, you might instead call CantSeeError()
! routine in a LibraryMessages object (Inform Designer's Manual, 4th ed., section 25):
!
!   Object LibraryMessages with before [; 
!     Miscellany: if (lm_n == 30) return CantSeeError(); 
!   ];
!
! Version history 1.0 - 16 May 2003
! Version history 1.1 - 22 Sep 2003.  Fixed TAKE ALL FROM X problem.

! Can override these constants by defining them before including the file:

Default SEENO_MSG1 "You see no ";  ! or "You see nothing that can be described as ~"
Default SEENO_MSG2 " here.";

#ifdef ParserError;
#message "Warning: To use cantsee.h, call it from ParserError or LibraryMessages.";
#ifnot;
[ ParserError pe; 
   if (pe == CANTSEE_PE) return CantSeeError(); 
   rfalse;
 ];
#endif;

[ CantSeeError   wordnum word nwords stop pos end;
  wordnum=saved_oops;
#ifdef TARGET_GLULX;
  nwords=parse-->0;
#ifnot;
  nwords=parse->1; ! end of line
#endif;
  if (wordnum > 0)
  {
#ifdef TARGET_GLULX;
    word=parse-->(wordnum*3-2);
#ifnot;
    word=parse-->(wordnum*2-1);
#endif;
    ! this most likely the result of TAKE ALL FROM X, in which case use the default message
    if (word && (word->#dict_par1 & $80) ~= $80) rfalse;

    print (string) SEENO_MSG1;
    do {  ! print at least one word, more if the noun phrase needs it
       pos=WordAddress(wordnum); end = WordLength(wordnum) + pos; 
       for (: pos<end: pos++)  ! print each character of word.
           print (char) pos->0;
       wordnum++;
       if (wordnum > nwords) stop=1; ! end of line
       else {
#ifdef TARGET_GLULX;
          word=parse-->(wordnum*3-2);
#ifnot;
          word=parse-->(wordnum*2-1);
#endif;
          if (word) { ! recognised
             if (word->#dict_par1 & $88 ~= $80) stop=1;  ! not noun, or poss prep
             if (word == AND1__WD or ',//' or './/'
                  or BUT1__WD or BUT2__WD) ! conjunction
                stop=1;
             }
          } ! not end of line
       if (~~stop) print " ";
       } until (stop);
    print_ret (string) SEENO_MSG2; 
  } 
  else rfalse; 
];

! end seeno.h
