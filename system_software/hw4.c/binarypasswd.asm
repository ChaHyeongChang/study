0x0000000000401589 <+0>:     call   0x4031b5 <__fentry__>
   0x000000000040158e <+5>:     push   %rbp
   0x000000000040158f <+6>:     push   %rdi
   0x0000000000401590 <+7>:     sub    $0x228,%rsp
   0x0000000000401597 <+14>:    lea    0x80(%rsp),%rbp
   0x000000000040159f <+22>:    call   0x403870 <_monstartup>
   0x00000000004015a4 <+27>:    call   0x402480 <__main>
   0x00000000004015a9 <+32>:    movabs $0x2073746567,%rax
   0x00000000004015b3 <+42>:    mov    %rax,-0x60(%rbp)
   0x00000000004015b7 <+46>:    lea    -0x58(%rbp),%rdx
   0x00000000004015bb <+50>:    mov    $0x0,%eax
   0x00000000004015c0 <+55>:    mov    $0x1e,%ecx
   0x00000000004015c5 <+60>:    mov    %rdx,%rdi
   0x00000000004015c8 <+63>:    rep stos %rax,%es:(%rdi)
   0x00000000004015cb <+66>:    mov    %rdi,%rdx
   0x00000000004015ce <+69>:    mov    %eax,(%rdx)
   0x00000000004015d0 <+71>:    add    $0x4,%rdx
   0x00000000004015d4 <+75>:    mov    %ax,(%rdx)
   0x00000000004015d7 <+78>:    add    $0x2,%rdx
   0x00000000004015db <+82>:    mov    %al,(%rdx)
   0x00000000004015dd <+84>:    add    $0x1,%rdx
   0x00000000004015e1 <+88>:    lea    0x67bb(%rip),%rcx        # 0x407da3
--Type <RET> for more, q to quit, c to continue without paging--
   0x00000000004015e8 <+95>:    call   0x402d38 <printf>
   0x00000000004015ed <+100>:   lea    0xa0(%rbp),%rax
   0x00000000004015f4 <+107>:   mov    %rax,%rcx
   0x00000000004015f7 <+110>:   call   0x402d40 <gets>
   0x00000000004015fc <+115>:   lea    -0x60(%rbp),%rax
   0x0000000000401600 <+119>:   lea    0x4959(%rip),%rdx        # 0x405f60 <pw2>
   0x0000000000401607 <+126>:   mov    %rax,%rcx
   0x000000000040160a <+129>:   call   0x402d28 <strcat>
   0x000000000040160f <+134>:   lea    0xa0(%rbp),%rdx
   0x0000000000401616 <+141>:   lea    -0x60(%rbp),%rax
   0x000000000040161a <+145>:   mov    %rax,%rcx
   0x000000000040161d <+148>:   call   0x4014f0 <checkpw>
   0x0000000000401622 <+153>:   test   %eax,%eax
   0x0000000000401624 <+155>:   je     0x401647 <main+190>
   0x0000000000401626 <+157>:   lea    0x678b(%rip),%rcx        # 0x407db8
   0x000000000040162d <+164>:   call   0x402d48 <puts>
   0x0000000000401632 <+169>:   lea    -0x60(%rbp),%rax
   0x0000000000401636 <+173>:   mov    %rax,%rdx
   0x0000000000401639 <+176>:   lea    0x67b1(%rip),%rcx        # 0x407df1
   0x0000000000401640 <+183>:   call   0x402d38 <printf>
   0x0000000000401645 <+188>:   jmp    0x401669 <main+224>
   0x0000000000401647 <+190>:   lea    0x67a8(%rip),%rcx        # 0x407df6
   0x000000000040164e <+197>:   call   0x402d48 <puts>
--Type <RET> for more, q to quit, c to continue without paging--
   0x0000000000401653 <+202>:   lea    0xa0(%rbp),%rax
   0x000000000040165a <+209>:   mov    %rax,%rdx
   0x000000000040165d <+212>:   lea    0x678d(%rip),%rcx        # 0x407df1
   0x0000000000401664 <+219>:   call   0x402d38 <printf>
   0x0000000000401669 <+224>:   lea    0x678d(%rip),%rcx        # 0x407dfd
   0x0000000000401670 <+231>:   call   0x402d50 <system>
   0x0000000000401675 <+236>:   mov    $0x0,%eax
   0x000000000040167a <+241>:   add    $0x228,%rsp
   0x0000000000401681 <+248>:   pop    %rdi
   0x0000000000401682 <+249>:   pop    %rbp
   0x0000000000401683 <+250>:   ret
   0x0000000000401684 <+251>:   nop
///////////////////////

   -Type <RET> for more, q to quit, c to continue without paging--q
Quit
(gdb) delete
(gdb) breeak        Quit
(gdb) Quit
(gdb) elete
Undefined command: "elete".  Try "help".
(gdb) delete
(gdb) break checkpw
Breakpoint 1 at 0x401506
(gdb) run
Starting program: C:\Users\56flo\Desktop\study\study\system_software\hw4.c\binarypasswd.exe
[New Thread 18468.0x2cc4]
[New Thread 18468.0x3bd8]
Input password : abcd

Thread 1 hit Breakpoint 1, 0x0000000000401506 in checkpw ()
(gdb) disassemble
Dump of assembler code for function checkpw:
   0x00000000004014f0 <+0>:     call   0x4031b5 <__fentry__>
   0x00000000004014f5 <+5>:     push   %rbp
   0x00000000004014f6 <+6>:     push   %rdi
   0x00000000004014f7 <+7>:     sub    $0x128,%rsp
   0x00000000004014fe <+14>:    lea    0x80(%rsp),%rbp
=> 0x0000000000401506 <+22>:    mov    %rcx,0xc0(%rbp)
   0x000000000040150d <+29>:    mov    %rdx,0xc8(%rbp)
   0x0000000000401514 <+36>:    movq   $0x72616863,-0x60(%rbp)
   0x000000000040151c <+44>:    lea    -0x58(%rbp),%rdx
   0x0000000000401520 <+48>:    mov    $0x0,%eax
   0x0000000000401525 <+53>:    mov    $0x1e,%ecx
   0x000000000040152a <+58>:    mov    %rdx,%rdi
   0x000000000040152d <+61>:    rep stos %rax,%es:(%rdi)
   0x0000000000401530 <+64>:    mov    %rdi,%rdx
   0x0000000000401533 <+67>:    mov    %eax,(%rdx)
   0x0000000000401535 <+69>:    add    $0x4,%rdx
   0x0000000000401539 <+73>:    mov    %ax,(%rdx)
   0x000000000040153c <+76>:    add    $0x2,%rdx
   0x0000000000401540 <+80>:    mov    %al,(%rdx)
   0x0000000000401542 <+82>:    add    $0x1,%rdx
   0x0000000000401546 <+86>:    lea    -0x60(%rbp),%rax
   0x000000000040154a <+90>:    mov    %rax,%rdx
--Type <RET> for more, q to quit, c to continue without paging--
   0x000000000040154d <+93>:    mov    0xc0(%rbp),%rcx
   0x0000000000401554 <+100>:   call   0x402d28 <strcat>
   0x0000000000401559 <+105>:   mov    0xc8(%rbp),%rax
   0x0000000000401560 <+112>:   mov    %rax,%rdx
   0x0000000000401563 <+115>:   mov    0xc0(%rbp),%rcx
   0x000000000040156a <+122>:   call   0x402d30 <strcmp>
   0x000000000040156f <+127>:   test   %eax,%eax
   0x0000000000401571 <+129>:   jne    0x40157a <checkpw+138>
   0x0000000000401573 <+131>:   mov    $0x1,%eax
   0x0000000000401578 <+136>:   jmp    0x40157f <checkpw+143>
   0x000000000040157a <+138>:   mov    $0x0,%eax
   0x000000000040157f <+143>:   add    $0x128,%rsp
   0x0000000000401586 <+150>:   pop    %rdi
   0x0000000000401587 <+151>:   pop    %rbp
   0x0000000000401588 <+152>:   ret
End of assembler dump.
(gdb) break *0x40156a
Breakpoint 2 at 0x40156a
(gdb) x/s $rcx
0x62fc40:       Converting character sets: Invalid argument.
(gdb) x/s $rdx
0x62fd40:       Converting character sets: Invalid argument.
(gdb) c
Continuing.

Thread 1 hit Breakpoint 2, 0x000000000040156a in checkpw ()
(gdb) set charset ASCII
(gdb) ]
(gdb) x/s $rcx
0x62fc40:       "gets  char"
(gdb) x/s $rdx
0x62fd40:       "abcd"
(gdb)