        .text
        .balign   4
        .global   CalculateTags_Simd

CalculateTags_Simd:
        vld1.f32          {d24[],d25[]}, [r2] 
        vmov.i32          q13, #0x100   
        vmov.i32          q14, #0x80000 
        vmov.i32          q15, #0x800   
        vcvt.f32.u32      q13, q13      
        vcvt.f32.u32      q14, q14
        vcvt.f32.u32      q15, q15

.L_CalculateTags_MainLoop:
        pld               [r0, #128]    
        vld2.f32          {q0, q1}, [r0]! 
        vmul.f32          q0, q0, q12   
        vmul.f32          q1, q1, q12   
        vmul.f32          q0, q0, q13   
        vadd.f32          q1, q1, q15   
        vadd.f32          q0, q0, q14   
        vcvt.u32.f32      q1, q1        
        vcvt.u32.f32      q0, q0        
        vsli.u32          q0, q1, #20   
        subs              r1, r1, #4

        pld               [r3, #64]     
        vst1.f32          {q0}, [r3]!   

        bgt               .L_CalculateTags_MainLoop

.L_CalculateTags_Return:
        bx                ldr



        .balign   4
FindContacts_PostProcess:
        
        ldrh              r9, [r4]
        ldrh              r10, [r4, #2]
        ldrh              r11, [r4, #16]
        ldrh              r12, [r4, #18]
        pld               [r7, r9, lsl #2]
        pld               [r7, r10, lsl #2]
        pld               [r7, r11, lsl #2]
        pld               [r7, r12, lsl #2]

        add               r8, r4, #32
        vld4.f32          {d0, d2, d4, d6}, [r4]
        vld4.f32          {d1, d3, d5, d7}, [r8]
        
        vrsqrte.f32       q8, q1      
        vmul.f32          q9, q8, q1  
        vrsqrts.f32       q9, q9, q8  
        vmul.f32          q8, q8, q9  
        vcgt.f32          q9, q8, #0  
        vand              q8, q8, q9  
        
        add               r8, r4, #64
        vldmia            r8, {q9, q10, q11}

        ldr               r9, [r7, r9, lsl #2]
        ldr               r10, [r7, r10, lsl #2]
        ldr               r11, [r7, r11, lsl #2]
        ldr               r12, [r7, r12, lsl #2]
        orr               r9, r9, r10
        orr               r11, r11, r12
        str               r9, [r4, #16]
        str               r11, [r4, #36]

        ldrh              r9, [r4, #32]
        ldrh              r10, [r4, #34]
        ldrh              r11, [r4, #48]
        ldrh              r12, [r4, #50]
        pld               [r7, r9, lsl #2]
        pld               [r7, r10, lsl #2]
        pld               [r7, r11, lsl #2]
        pld               [r7, r12, lsl #2]

        vmul.f32          q1, q1, q8     
        vmul.f32          q2, q2, q8     
        vmul.f32          q1, q1, q14    
        vmul.f32          q3, q3, q8     
        vsub.f32          q1, q12, q1    
        
        mov               r8, #20        
        vst4.f32          {d0[0], d2[0], d4[0], d6[0]}, [r4], r8
        vst4.f32          {d0[1], d2[1], d4[1], d6[1]}, [r4], r8
        vst4.f32          {d1[0], d3[0], d5[0], d7[0]}, [r4], r8
        vst4.f32          {d1[1], d3[1], d5[1], d7[1]}, [r4], r8
        mov               r8, #12        

        ldr               r9, [r7, r9, lsl #2]
        ldr               r10, [r7, r10, lsl #2]
        ldr               r11, [r7, r11, lsl #2]
        ldr               r12, [r7, r12, lsl #2]
        orr               r9, r9, r10
        orr               r11, r11, r12
        str               r9, [r4, #-24]
        str               r11, [r4, #-4]
        
        add               r3, r3, #16
        add               r5, r5, #4
        
        vstmia            r4, {q9, q10, q11}
        
        bx                lr
        


CONST_IS_CLOSE_TABLE_INDICES:
        .byte           0
        .byte           4
        .byte           8
        .byte           12
        .byte           0xFF
        .byte           0xFF
        .byte           0xFF
        .byte           0xFF
        
        .balign   4
        .global   FindContactsFromChecks_Simd
FindContactsFromChecks_Simd:
        push              {r4-r11, lr}

        vld1.f32          {d30[],d31[]}, [r3]  
        ldr               r12, [sp, #36]       
        vld1.f32          {d28[],d29[]}, [r12] 
        ldr               r9, [sp, #44]    
        ldr               r7, [sp, #40]    
        ldr               r3, [r9, #0]     
        ldr               r6, [r9, #8]     
        mov               r4, r3           
        mov               r5, #0           
        sub               r6, r6, #8       
        mov               r8, #12   
        
        cmp               r2, #0
        ble               .L_FindContacts_Return

        vmov.f32          q12, #1.0        
        adr               r12, CONST_IS_CLOSE_TABLE_INDICES
        vld1.8            {d26}, [r12]     

.L_FindContacts_MainLoop:
        pld               [r1, #8]      
        
        ldr               r10, [r1], #4    
        smlatb            r11, r10, r8, r0 
        smlabb            r10, r10, r8, r0 
        add               r12, r11, #24    

        cmp               r5, r6

        vld3.f32          {d0[], d2[], d4[]}, [r10]
        vld3.f32          {d1[], d3[], d5[]}, [r10]

        
        vld3.f32          {d16, d18, d20}, [r11]
        vld3.f32          {d17, d19, d21}, [r12]

        
        
        vsub.f32          q3, q10, q2  
        vsub.f32          q2, q9, q1   
        vsli.32           q0, q8, #16  
        vmul.f32          q1, q3, q3   
        vmla.f32          q1, q2, q2   
        
        vclt.f32          q8, q1, q15          
        vtbl.8            d16, {d16,d17}, d26  
        vmov.32           r12, d16[0]
        
        ble               .L_FindContacts_Output
        ldr               r9, [sp, #44]        
        str               r5, [r9, #4]         
        ldr               r10, [r9, #0]        
        push              {r0-r3, r9, r10, r12}
        vpush             {q0, q1, q2, q3}
        vpush             {q12, q13, q14, q15}
        mov               r0, r9               
        bl                GrowParticleContactBuffer
        vpop              {q12, q13, q14, q15}
        vpop              {q0, q1, q2, q3}
        pop               {r0-r3, r9, r10, r12}
        
        ldr               r6, [r9, #8]         
        ldr               r9, [r9, #0]         
        sub               r9, r9, r10          
        sub               r6, r6, #8           
        add               r3, r3, r9           
        add               r4, r4, r9           

.L_FindContacts_Output:
        tst               r12, 0xFF
        it                ne
        vst4ne.32         {d0[0],d2[0],d4[0],d6[0]}, [r3]! 

        tst               r12, 0xFF00
        it                ne
        vst4ne.32         {d0[1],d2[1],d4[1],d6[1]}, [r3]! 

        tst               r12, 0xFF0000
        it                ne
        vst4ne.32         {d1[0],d3[0],d5[0],d7[0]}, [r3]! 

        tst               r12, 0xFF000000
        it                ne
        vst4ne.32         {d1[1],d3[1],d5[1],d7[1]}, [r3]! 
        
        add               r12, r4, #64         
        cmp               r3, r12
        it                ge
        blge              FindContacts_PostProcess

        subs              r2, r2, #1
        bgt               .L_FindContacts_MainLoop

.L_FindContacts_PostProcessRemainingItems:
        subs              r12, r3, r4
        ble               .L_FindContacts_Return

        add               r5, r5, r12, lsr #4  
        push              {r5}                 

        
        mov               r12, #0
        str               r12, [r3]
        str               r12, [r3, #16]
        str               r12, [r3, #32]

        bl                FindContacts_PostProcess
        pop               {r5}                 

.L_FindContacts_Return:
        ldr               r9, [sp, #44]        
        str               r5, [r9, #4]         

        pop               {r4-r11, pc}