	AREA question_one, CODE, READONLY
	ENTRY
Start	ADR r0, UPC ;register r0 to point to the string
	MOV r1, #ARL ;initialize loop counter in r1 to 12
	MOV r2, #0 ;initialize and clear the sum in r2. this is the first sum
        MOV r3, #0 ;initialize and clear the sum in r3. this is the second sum
loop	LDRB r4, [r0, #0] ;copy the element pointed to by r0 into r4
        SUB r4, r4, #AS ;remove 30 to get digit to counter ascii value
        LDRB r5, [r0, #1] ;copy the next element pointed to by r0 into r5
        SUB r5, r5, #AS ;remove 30 to get digit to counter ascii value
        ADD r0, r0, #2 ;point to the element 2 after in the string
        ADD r2, r2, r4 ;adds to the running total of first sum
        ADD r3, r3, r5 ;adds to the running total of second sum
        SUBS r1, r1, #2 ;decrements the loop counter as it 
        BNE loop; repeat until all elements added
        SUB r3, r3, r5 ;remove this since it added the check digit
        MOV r1, #3 ;initiate r1 with 3 for multiplication
        MUL r2, r1, r2 ;multiply the first sum by 3
        ADD r2, r2, r3 ;adds the first sum to the second sum
        ADD r2, r2, r5 ;it adds the check digit which is in r5
Loop    CMP r2, #0 ;checks to see if the sum is 0 yet or at all
        BEQ VExit ;if it is equal to 0, it is a multiple of 10, so jump to VExit
        SUBS r2, r2, #10 ;subtract the value by 10 to see if it is a multiple of 10
        BMI InvExit ;if it is negative, the sum must have passed 0 and therefore it is not a multiple of 10
        B Loop ;repeat while true, either until it is negative or is zero
VExit	MOV r0, #1 ;move number 1 to r0 and exit
Endless B Endless ;this ends the program after a valid exit
InvExit MOV r0, #2 ;move number 2 in r0 and exit
Exit	B Exit ;this ends the program after an invalid exit
UPC	DCB "013800150738" ;correct UPC string
UPC2 	DCB "060383755577" ;correct UPC string
UPC3 	DCB "065633454712" ;correct UPC string 
UPC4 	DCB "065633454713" ;incorrect UPC string 
AS      EQU 0x30 ;this is the ascii shift that needs to be applied to values
ARL     EQU 12 ;code has 12 digits
ML      EQU 10 ;useful to check if variable is divisible by 10
	END