          AREA question, CODE, READONLY
          ENTRY
          ADR       r0, STRING1    ; we allocate r0 to point to the start of the first string 
          ADR       r5, STRING2    ; we allocate r5 to point to the start of the second string
          LDRB      r9, EoS        ;this loads the value of end of string, 0x00, to the 9th register     
repeat    LDRB      r1, [r0], #1   ;pick up a character from r0 and store in r1, updating and incrementing the pointer
          LDRB      r8, [r0, #-2]  ;this picks up the previous character in the string in order to track the previous number 
          LDRB      r6, [r5], #1   ;this picks up the adjactent character in the second string in order to be able to put values in the new string
          CMP       r1, r9         ;must check if we have reached the end of the string by coming across EoS
          BEQ       exitloop       ;if we are at the end of the string, we exit the loop
          MOV       r2, #0         ;the following set these registers in order to have something to compare to in the following
          MOV       r3, #0
          MOV       r3, #0
          MOV       r4, #0
          CMP       r8, #0x23      ; we start from # on ASCII table since we want to find anything besides digits and characters, excluding spaces and double quotes
          RSBGES    r10, r8, #z    ;this updates the flags to check within the range of 0x23 and 0x7A
          BGE       remain         ;we can jump to keeping the number because we know that we cant remove it if theres a solid character in the place before
          CMP       r1, #t         ;we check to see if the value we are pointing to is equal to t, if it is not, r2 is never changed and the next few lines are disregarded
          LDRBEQ    r2, [r0]       ;if it is equal to t, it points to next charater in order to check if the next one matches
          CMP       r2, #h         ;we do the same thing here as above, check to see if h is the next char
          LDRBEQ    r3, [r0, #1]   ;if it is the same character, the pointer is updated to the next value
          CMP       r3, #e         ;same as above
          LDRBEQ    r4, [r0, #2]   ;same as above
          CMP       r4, #0x23      ;starting from # on ASCII table, as stated in line 15
          RSBGES    r2, r4, #z     ;we want to create the valid character range similar to line 16
remain    STRBGE    r1, [r6]       ;if it is between # and z inlcusive, we do not remove them, and we store in string2 
          MOVLT     r10, #0x20     ;if it is not in the range, we take #0x20, the value for space, and put it in r10 for now
          STRBLT    r10, [r6]      ;if it is just the word 'the', we replace t,h,e with a space, 0x20. In this case we store 0 where t is
          STRBLT    r10, [r6, #1]  ; now we store where h is
          STRBLT    r10, [r6, #2]  ; now we store where e is
          B         repeat         ;we repeat until the EoS is found
exitloop  B         exitloop       ;once the loop is exited, we create an infinte loop to terminate the project
          AREA question, DATA, READWRITE
STRING1   DCB       "and the man said they must go";String1
EoS       DCB       0x00           ;end of string1
STRING2   space     0x7F           ;just allocating 127 bytes
t         EQU       0x74
h         EQU       0x68
e         EQU       0x65
z         EQU       0x7A
          END