        .text
        .balign   4
        .global   CalculateTags_Simd

CalculateTags_Simd:
        ld1 {v12.4s}, [x2] // q12 = inverseDiameter
        mov w13, #0x100
        mov w14, #0x80000
        mov w15, #0x800

        dup v12.4s, w12
        dup v13.4s, w13
        dup v14.4s, w14
        dup v15.4s, w15

        scvtf v13.4s, v13.4s
        scvtf v14.4s, v14.4s
        scvtf v15.4s, v15.4s

.L_CalculateTags_MainLoop:
        ld2 {v0.4s, v1.4s}, [x0],#32 //32*8=2*128

        // Calculate tags four at a time.
        fmul v0.4s, v0.4s, v12.4s       // v0 = x = xPosition * inverseDiameter
        fmul v1.4s, v1.4s, v12.4s       // v1 = y = yPosition * inverseDiameter
        fmul v0.4s, v0.4s, v13.4s       // v0 = x * xScale
        fadd v1.4s, v1.4s, v15.4s       // v1 = y + yOffset
        fadd v0.4s, v0.4s, v14.4s       // v0 = x * xScale + xOffset
        fcvtzu v1.4s, v1.4s             // v1 = (uint32)(y + yOffset)
        fcvtzu v0.4s, v0.4s             // v0 = (uint32)(x * xScale + xOffset)
        sli v0.4s, v1.4s, #20

        sub w1, w1, #4

        // Write out, ignoring index.
        st1 {v0.4s}, [x3],#16   // write out tags// increment ptr //16*8=128

        bgt .L_CalculateTags_MainLoop

.L_CalculateTags_Return:
        ret



        .balign   4
FindContacts_PostProcess:
        ldrh              w9, [x4]
        ldrh              w10, [x4, #2]
        ldrh              w11, [x4, #16]
        ldrh              w12, [x4, #18]

        ld4 {v0.4s, v1.4s, v2.4s, v3.4s},[x4],#64

        // Use distSq to estimate 1 / dist.
        frsqrte   v8.4s, v1.4s      // v8 = 1 / dist -- (rough estimate)
        fmul      v9.4s, v8.4s, v1.4s  // v9 = 1 / dist * distSq -- (appr 'dist')
        frsqrts   v9.4s, v9.4s, v8.4s  // v9 = (3 - 1/dist * dist) / 2 -- (error)
        fmul      v8.4s, v8.4s, v9.4s  // v8 = (error) / dist -- (estimate)
        fcmgt     v9.4s, v8.4s, #0  // v8 = 1 / dist > 0 (true if not NaN)
        and       v8.16b, v8.16b, v9.16b  // v8 = 1 / dist if valid, or 0 if NaN
        
        add               x8, x4, #64
        ld1               {v9.4s, v10.4s, v11.4s}, [x8]

        // Load first four flags, 'or' them in pairs, then write to destination.
        ldr               w9 , [x7, w9 , uxtw #2]
        ldr               w10, [x7, w10, uxtw #2]
        ldr               w11, [x7, w11, uxtw #2]
        ldr               w12, [x7, w12, uxtw #2]
        orr               w9, w9, w10
        orr               w11, w11, w12
        str               w9, [x4, #16]
        str               w11, [x4, #36]

        // Preload the next four flags into cache.
        ldrh              w9, [x4, #32]
        ldrh              w10, [x4, #34]
        ldrh              w11, [x4, #48]
        ldrh              w12, [x4, #50]

        // Calculate normal and weight.
        fmul v1.4s, v1.4s, v8.4s     // v1 = distSq / dist = dist
        fmul v2.4s, v2.4s, v8.4s     // v2 = normX = diffX / dist
        fmul v1.4s, v1.4s, v14.4s    // v1 = dist / diameter
        fmul v3.4s, v3.4s, v8.4s     // v3 = normY = diffY / dist
        fsub v1.4s, v12.4s, v1.4s    // v1 = weight = 1 - dist / diameter

        mov               x8, #20        // x8 = 20 = sizeof(b2ParticleContact)
        // 第一步：交换v0和v1的元素
        trn1 v4.4s, v0.4s, v1.4s  // v4: a0, b0, a2, b2
        trn2 v5.4s, v0.4s, v1.4s  // v5: a1, b1, a3, b3
        // 第二步：交换v2和v3的元素
        trn1 v6.4s, v2.4s, v3.4s  // v6: c0, d0, c2, d2
        trn2 v7.4s, v2.4s, v3.4s  // v7: c1, d1, c3, d3
        // 第三步：交换v4和v6的元素
        trn1 v0.2d, v4.2d, v6.2d  // v0: a0, b0, c0, d0
        trn2 v2.2d, v4.2d, v6.2d  // v2: a2, b2, c2, d2
        // 第四步：交换v5和v7的元素
        trn1 v1.2d, v5.2d, v7.2d  // v1: a1, b1, c1, d1
        trn2 v3.2d, v5.2d, v7.2d  // v3: a3, b3, c3, d3

        st1 {v0.4s}, [x4], x8
        st1 {v1.4s}, [x4], x8
        st1 {v2.4s}, [x4], x8
        st1 {v3.4s}, [x4], x8

        mov               x8, #12        // x8 = 12 = sizeof(FindContactInput)

        // Load next four flags, 'or' them in pairs, then write to destination.
        ldr               w9 , [x7, w9 , uxtw #2]
        ldr               w10, [x7, w10, uxtw #2]
        ldr               w11, [x7, w11, uxtw #2]
        ldr               w12, [x7, w12, uxtw #2]
        orr               w9, w9, w10
        orr               w11, w11, w12
        str               w9, [x4, #-24]
        str               w11, [x4, #-4]

        add               x3, x3, #16
        add               w5, w5, #4          // numContacts += 4

        st1 {v9.4s, v10.4s, v11.4s}, [x4]

        ret


CONST_IS_CLOSE_TABLE_INDICES:
        .byte           0
        .byte           4
        .byte           8
        .byte           12
        .byte           0xFF
        .byte           0xFF
        .byte           0xFF
        .byte           0xFF


        .align   4
        .global   FindContactsFromChecks_Simd
FindContactsFromChecks_Simd:
        stp x4, x5, [sp, #-16]!
        stp x6, x7, [sp, #-16]!
        stp x8, x9, [sp, #-16]!
        stp x10, x11, [sp, #-16]!
        stp x30, xzr, [sp, #-16]!

        // Load constants from registers and stack.
        ld1r               {v15.4s}, [x3]  // v15 = particleDiameterSq
        ldr               x12, [x4]       // r12 = particleDiameterInv
        ld1r               {v14.4s}, [x12] // v14 = particleDiameterInv
        ldr               x9, [x6]    // x9 = contacts//x6
        ldr               x7, [x5]    // x7 = flags//x5
        ldr               x3, [x9, #0]     // x3 = out = contacts.data
        ldr               w6, [x9, #12]     // w6 = contacts.capacity
        mov               x4, x3           // x4 = postProcess = outContacts
        mov               w5, #0           // w5 = numContacts
        sub               w6, w6, #8       // w6 = maxSafeContacts = capacity - 8
        mov               w8, #12          // w8 = 12 = sizeof(FindContactInput)

        // Perform zero iterations if 'numChecks' is empty.
        // Must happen after initializing w5 = numContacts = 0.
        cmp               w2, #0
        ble               .L_FindContacts_Return

        // Load and calculate remaining constants.
        fmov              v12.4s, #1.0        // v12 = 1.0f splatted
        adr               x12, CONST_IS_CLOSE_TABLE_INDICES
        ld1               {v13.8b}, [x12]     // v13 = *CONST_IS_CLOSE_TABLE_INDICES



.L_FindContacts_MainLoop:
        prfm              pldl1keep, [x1, #8] // prefetch two loops ahead

        // x10 <== Address of 'position', the current particle position
        // x11 <== Address of '&comparator[0]', the first particle position we
        //         compare against.
        //uxtw x10, w10         // Zero extend w10 to x10, making it 32 bits

        ldrh w10, [x0]    // Load the first 16-bit number from position, increment x0 by 2
        uxtw x10, w10
        madd x11, x10, x8, x0 // x11 = address of first comparator
        ldrh w10, [x0,#2]    // Load the second 16-bit number from position, increment x0 by 2
        uxtw x10, w10
        madd x10, x10, x8, x0 // x10 = address of current input
        add x12, x11, #24     // x12 = address of third comparator

        // Exit if not enough space in output array (part 1)
        cmp               w5, w6

        // {v0, v1, v2} == index, positionX, positionY, splatted across vector
        // one to all
        ld3r              {v0.4s,v1.4s,v2.4s}, [x10]

        // {v8, v9, v10} == comparatorIndices, comparatorPosX and comparatorPosY
        //                 positions we compare against (positionX, positionY)
        // one by one
        ld3              {v8.4s, v9.4s, v10.4s}, [x11]

        // v0 = packedIndices -- indices output to b2ParticleContact
        // v1 = distBtParticlesSq -- will be used to calculate weight
        // v2 = diffX -- will be used to calculate normal
        // v3 = diffY -- will be used to calculate normal
        fsub              v3.4s, v10.4s, v2.4s  // v3 = diffY = comparatorPosY - positionY
        fsub              v2.4s, v9.4s, v1.4s   // v2 = diffX = comparatorPosX - positionX
        sli v0.4s, v8.4s, #16     // v0 = comparatorIndex[i] << 16 | index
        fmul              v1.4s, v3.4s, v3.4s   // v1 = diffX * diffX
        fmla              v1.4s, v2.4s, v2.4s   // v1 = diffX * diffX + diffY * diffY

        // Determine if each particle is close enough to output.
        // Pack the isClose bitmap (four T or F) into a 32-bit bitmap.
        // Move 32-bit bitmap to CPU register, for conditional operations.
        // Note: NEON to CPU register moves are slow (20 cyclds) on some
        // implementations of NEON.
        //   isClose = distBtParticlesSq < particleDiameterSq
        fcmlt v8.4s, v1.4s, v15.4s    // v8 = isClose
        tbl v8.8b, {v8.16b}, v13.8b  // v16 = isClose(packed)
        mov w12, v8.s[0]            // v16[0] ==> w12

        // If not enough space in output array, grow it.
        // This is a heavy operation, but should happen rarely.
        b.le              .L_FindContacts_Output
        ldr               x9, [x6]        // x9 = contacts
        str               w5, [x9, #8]         // contacts.count = numContacts
        ldr               x10, [x9, #0]        // x10 = contacts.data
        stp               x0, x1, [sp, #-16]!
        stp               x2, x3, [sp, #-16]!
        stp               x9, x10, [sp, #-16]!
        stp               x12, xzr, [sp, #-16]!
        sub               sp, sp, #16
        st1               {v0.4s, v1.4s, v2.4s, v3.4s}, [sp], #64
        st1               {v12.4s, v13.4s, v14.4s, v15.4s}, [sp], #64
        mov               x0, x9               // x0 = contacts
        bl                GrowParticleContactBuffer
        ld1               {v12.4s, v13.4s, v14.4s, v15.4s}, [sp], #64
        ld1               {v0.4s, v1.4s, v2.4s, v3.4s}, [sp], #64
        add               sp, sp, #16
        ldp               x12, xzr, [sp], #16
        ldp               x9, x10, [sp], #16
        ldp               x2, x3, [sp], #16
        ldp               x0, x1, [sp], #16

        // The output array was reallocated, so update 'out', 'postProcess' and
        // 'maxSafeContacts' pointers.
        ldr               w6, [x9, #12]         // w6 = contacts.capacity
        ldr               x9, [x9, #0]         // x9 = contacts.data
        sub               x9, x9, x10          // x9 = data buffer offset
        sub               w6, w6, #8           // w6 = maxSafeContacts
        add               x3, x3, x9           // x3 += data buffer offset
        add               x4, x4, x9           // x4 += data buffer offset



.L_FindContacts_Output:
        // 第一步：交换v0和v1的元素
        trn1 v4.4s, v0.4s, v1.4s  // v4: a0, b0, a2, b2
        trn2 v5.4s, v0.4s, v1.4s  // v5: a1, b1, a3, b3
        // 第二步：交换v2和v3的元素
        trn1 v6.4s, v2.4s, v3.4s  // v6: c0, d0, c2, d2
        trn2 v7.4s, v2.4s, v3.4s  // v7: c1, d1, c3, d3
        // 第三步：交换v4和v6的元素
        trn1 v0.2d, v4.2d, v6.2d  // v0: a0, b0, c0, d0
        trn2 v2.2d, v4.2d, v6.2d  // v2: a2, b2, c2, d2
        // 第四步：交换v5和v7的元素
        trn1 v1.2d, v5.2d, v7.2d  // v1: a1, b1, c1, d1
        trn2 v3.2d, v5.2d, v7.2d  // v3: a3, b3, c3, d3

        // Store results to memory, but only results that are close
        tst   w12, #0xFF
        b.ne  .L_Skip_1st_Contact
        st1 {v0.4s}, [x3],#16

.L_Skip_1st_Contact:
        tst   w12, #0xFF00
        b.ne  .L_Skip_2nd_Contact
        st1 {v1.4s}, [x3],#16

.L_Skip_2nd_Contact:
        tst   w12, #0xFF0000
        b.ne  .L_Skip_3rd_Contact
        st1 {v2.4s}, [x3],#16

.L_Skip_3rd_Contact:
        tst   w12, #0xFF000000
        b.ne  .L_Skip_4th_Contact
        st1 {v3.4s}, [x3],#16

.L_Skip_4th_Contact:
        // post-process the last four elements that have been output
        // w12 = 5th element to not be post-processed yet
        add   x12, x4, #64         // w12 = nextPostProcess
        cmp   x3, x12
        b.ge  FindContacts_PostProcess  
        // decrement loop counter // sets the 'gt' flag used in 'bgt' below
        subs  w2, w2, #1
        bgt   .L_FindContacts_MainLoop

.L_FindContacts_PostProcessRemainingItems:
        // If at least one output item needs post-processing, do it.
        subs              x12, x3, x4
        ble               .L_FindContacts_Return

        // w12/16 = num extra contacts to process
        add               w5, w5, w12, lsr #4  // numContacts += num extra
        stp               x5, x30, [sp, #-16]! // Save numContacts and lr

        // Ensure indices past end of array are zeroed out.
        // We process 4 contacts in FindContacts_PostProcess, even if we only
        // have one left to process.
        mov               w12, #0
        str               w12, [x3]
        str               w12, [x3, #16]
        str               w12, [x3, #32]

        bl                FindContacts_PostProcess
        ldp               x5, x30, [sp], #16   // Restore numContacts and lr

.L_FindContacts_Return:
        // Set the final number of contacts in the output buffer.
        ldr               x9, [x6]        // x9 = contacts
        str               w5, [x9, #8]         // contacts.count = numContacts

        // Return by popping the original lr into pc.
        ldp x30, xzr, [sp], #16
        ldp x10, x11, [sp], #16
        ldp x8, x9, [sp], #16
        ldp x6, x7, [sp], #16
        ldp x4, x5, [sp], #16
        ret
