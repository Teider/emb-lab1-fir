;Rotina de filtro FIR

  EXPORT        fir_proc

  Section .text : CODE(2)

fir_proc
    PUSH        {R4-R11} ;store the values of R4-R11
    LDR         R4, [SP, #32] ;get the output address from the stack and store on R4
    SUB         R1, R1, R3 ;R1 = size_in - size_coef
    ADD         R1, R1, #1 ;R1 = size_in - (size_coef - 1)
    MOV         R10, R1 ;copy the value for later
    ADD         R0, R0, R3, LSL#2 ;skip the first N values from the input
    ADD         R0, R0, #-4 ;go back one input (skipping N-1 values total)
fir_loop    
    MOV         R5, #0 ;(re)start the iterator
    MOV         R6, #0 ;(re)start the reverse iterator
    MOV         R7, #0 ;(re)start the sum
coef_loop
    LDR         R8, [R0, R6, LSL#2] ;load x[n-k]
    LDR         R9, [R2, R5, LSL#2] ;load h[k]
    MLA         R7, R8, R9, R7 ;multiply and accumulate (y[n] += x[n-k] * h[k])
    ADD         R5, R5, #1 ;k = k + 1
    SUB         R6, R6, #1 ;-k = -k - 1
    CMP         R3, R5 ;test if all coeficients have been calculated
    BNE         coef_loop ;if R5 != R3, continue the loop
    STR         R7, [R4], #4 ;Store the result in the output address and advance the output address by one
    ADD         R0, R0, #4 ;Advance the input by one
    SUBS        R1, R1, #1 ;Decrease the number of items to be processed by one
    BNE         fir_loop ;Test if all items were processed
; function finish
    MOV         R0, R10 ;Store the number of items processed as the result value
    POP         {R4-R11} ;Restore the values of R4-R11
    BX          LR ;return from the procedure
   
    END