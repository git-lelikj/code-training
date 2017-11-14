// -----------------------------------------------------------------------------------------------------------
//  http://www.interqiew.com/tests?type=cpp: #1:4
//      Program output:   11010
//
//  disassembly command: g++ -std=c++11 -Wa,-adhln -g main.cpp > main.s
//
//  disassembly explained:
//
#if 0
1093:main.cpp      ****
1094:main.cpp      **** #include <iostream>
1095:main.cpp      ****
1096:main.cpp      **** using namespace std;
1097:main.cpp      ****
1098:main.cpp      **** class A
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// default constructor ?:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  18              		.loc 1 1098 0
  19              		.cfi_startproc
  20 0000 55       		pushq	%rbp
  21              		.cfi_def_cfa_offset 16
  22              		.cfi_offset 6, -16
  23 0001 4889E5   		movq	%rsp, %rbp
  24              		.cfi_def_cfa_register 6
  25 0004 48897DF8 		movq	%rdi, -8(%rbp)
  26              		.loc 1 1098 0
  27 0008 5D       		popq	%rbp
  28              		.cfi_def_cfa 7, 8
  29 0009 C3       		ret
  30              		.cfi_endproc
  31              	.LFE1197:
  33              		.weak	_ZN1AC1Ev
  34              		.set	_ZN1AC1Ev,_ZN1AC2Ev
  35              		.section	.text._ZN1BC2Ev,"axG",@progbits,_ZN1BC5Ev,comdat
  36              		.align 2
  37              		.weak	_ZN1BC2Ev
  39              	_ZN1BC2Ev:
  40              	.LFB1200:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1099:main.cpp      **** {
1100:main.cpp      **** //public:
1101:main.cpp      **** //    A() {}
1102:main.cpp      **** public:
1103:main.cpp      ****     int i_;
1104:main.cpp      **** };
1105:main.cpp      ****
1106:main.cpp      **** class B
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// default constructor ?:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  41              		.loc 1 1106 0
  42              		.cfi_startproc
  43 0000 55       		pushq	%rbp
  44              		.cfi_def_cfa_offset 16
  45              		.cfi_offset 6, -16
  46 0001 4889E5   		movq	%rsp, %rbp
  47              		.cfi_def_cfa_register 6
  48 0004 48897DF8 		movq	%rdi, -8(%rbp)
  49              		.loc 1 1106 0
  50 0008 5D       		popq	%rbp
  51              		.cfi_def_cfa 7, 8
  52 0009 C3       		ret
  53              		.cfi_endproc
  54              	.LFE1200:
  56              		.weak	_ZN1BC1Ev
  57              		.set	_ZN1BC1Ev,_ZN1BC2Ev
  58              		.section	.text._ZN1CC2Ev,"axG",@progbits,_ZN1CC5Ev,comdat
  59              		.align 2
  60              		.weak	_ZN1CC2Ev
  62              	_ZN1CC2Ev:
  63              	.LFB1202:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1107:main.cpp      **** {
1108:main.cpp      **** //public:
1109:main.cpp      **** //    B() {}
1110:main.cpp      **** public:
1111:main.cpp      ****     int ii_;
1112:main.cpp      **** };
1113:main.cpp      ****
1114:main.cpp      **** class C: public A,
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// default constructor ?:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  64              		.loc 1 1114 0
  65              		.cfi_startproc
  66 0000 55       		pushq	%rbp
  67              		.cfi_def_cfa_offset 16
  68              		.cfi_offset 6, -16
  69 0001 4889E5   		movq	%rsp, %rbp
  70              		.cfi_def_cfa_register 6
  71 0004 4883EC10 		subq	$16, %rsp
  72 0008 48897DF8 		movq	%rdi, -8(%rbp)
  73              	.LBB2:
  74              		.loc 1 1114 0
  75 000c 488B45F8 		movq	-8(%rbp), %rax
  76 0010 4889C7   		movq	%rax, %rdi
  77 0013 E8000000 		call	_ZN1AC2Ev
  77      00
  78 0018 488B45F8 		movq	-8(%rbp), %rax
  79 001c 4883C004 		addq	$4, %rax
  80 0020 4889C7   		movq	%rax, %rdi
  81 0023 E8000000 		call	_ZN1BC2Ev
  81      00
  82 0028 488B45F8 		movq	-8(%rbp), %rax
  83 002c C6400861 		movb	$97, 8(%rax)
  84              	.LBE2:
  85 0030 C9       		leave
  86              		.cfi_def_cfa 7, 8
  87 0031 C3       		ret
  88              		.cfi_endproc
  89              	.LFE1202:
  91              		.weak	_ZN1CC1Ev
  92              		.set	_ZN1CC1Ev,_ZN1CC2Ev
  93              		.text
  94              		.globl	main
  96              	main:
  97              	.LFB1194:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1115:main.cpp      ****          public B
1116:main.cpp      **** {
1117:main.cpp      **** //public:
1118:main.cpp      **** //    C() {}
1119:main.cpp      **** public:
1120:main.cpp      ****     char c_ = 'a';
1121:main.cpp      **** };
1122:main.cpp      ****
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	stack layout of pointers pc, pa and pb:
//
//	i_			-> -64(%rbp): 		address of c object	-> stored at -8(%rbp): pc		-> stored at -16(%rbp): pa
//	ii_			-> -64(%rbp) + 4:	stored at -24(%rbp): pb
//	c_
//
//	important:
//		when comparing pointers to classes, pointer to base and derived (pa and pc, pb and pc) are the same due to adjustments,
//		when comparing raw pointers, pa and pc are the same, pa and pb (pb and pc) are different (offset of 4 bytes)
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1123:main.cpp      **** int main()
1124:main.cpp      **** {
  98              		.loc 1 1124 0
  99              		.cfi_startproc
 100              		.cfi_personality 0x3,__gxx_personality_v0
 101              		.cfi_lsda 0x3,.LLSDA1194
 102 0000 55       		pushq	%rbp
 103              		.cfi_def_cfa_offset 16
 104              		.cfi_offset 6, -16
 105 0001 4889E5   		movq	%rsp, %rbp
 106              		.cfi_def_cfa_register 6
 107 0004 4883EC40 		subq	$64, %rsp
 108              	.LBB3:
1125:main.cpp      ****     C c;
 109              		.loc 1 1125 0
 110 0008 488D45C0 		leaq	-64(%rbp), %rax								// load address of c var to %rax: -64(%rbp) - address of c
 111 000c 4889C7   		movq	%rax, %rdi
 112 000f E8000000 		call	_ZN1CC1Ev
 112      00
1126:main.cpp      ****     C* pc = &c;
 113              		.loc 1 1126 0
 114 0014 488D45C0 		leaq	-64(%rbp), %rax								// load address of c var to %rax
 115 0018 488945F8 		movq	%rax, -8(%rbp)								// store address of c to -8(%rbp): pc var is offset -8 from (%rbp)
1127:main.cpp      ****     A* pa = &c;
 116              		.loc 1 1127 0
 117 001c 488D45C0 		leaq	-64(%rbp), %rax								// load address of c var to %rax
 118 0020 488945F0 		movq	%rax, -16(%rbp)								// store address of c + 0 to -16(%rbp): pa var is offset -16 from (%rbp) -> pa == pc
1128:main.cpp      ****     B* pb = &c;
 119              		.loc 1 1128 0
 120 0024 488D45C0 		leaq	-64(%rbp), %rax								// load address of c var to %rax
 121 0028 4883C004 		addq	$4, %rax
 122 002c 488945E8 		movq	%rax, -24(%rbp)								// store address of c + 4 to -24(%rbp): pb var is offset -24 from (%rbp) -> pb = pc + 4
1129:main.cpp      ****
1130:main.cpp      ****     pc->i_ = 5;
 123              		.loc 1 1130 0
 124 0030 488B45F8 		movq	-8(%rbp), %rax								// store pc to %rax (offset -8 from (%rbp))
 125 0034 C7000500 		movl	$5, (%rax)									// set value 5 to i_ at offset 0
 125      0000
1131:main.cpp      ****     pc->ii_ = 10;
 126              		.loc 1 1131 0
 127 003a 488B45F8 		movq	-8(%rbp), %rax								// store pc to %rax (offset -8 from (%rbp))
 128 003e C740040A 		movl	$10, 4(%rax)								// set value 10 to ii_ at offset 4
 128      000000
1132:main.cpp      ****     pc->c_ = 'b';
 129              		.loc 1 1132 0
 130 0045 488B45F8 		movq	-8(%rbp), %rax								// store pc to %rax (offset -8 from (%rbp))
 131 0049 C6400862 		movb	$98, 8(%rax)								// set value 98 to c_ at offset 8
1133:main.cpp      ****
1134:main.cpp      ****     pa->i_ = 25;
 132              		.loc 1 1134 0
 133 004d 488B45F0 		movq	-16(%rbp), %rax								// store pa to %rax (offset -16 from (%rbp)); note: points to same as pc
 134 0051 C7001900 		movl	$25, (%rax)									// set value 25 to i_ at offset 0; note: changes same as pc->i_
 134      0000
1135:main.cpp      ****
1136:main.cpp      ****     pb->ii_ = 20;
 135              		.loc 1 1136 0
 136 0057 488B45E8 		movq	-24(%rbp), %rax								// store pb to %rax (offset -24 from (%rbp))
 137 005b C7001400 		movl	$20, (%rax)									// set value 20 to ii_ at offset 0; note: changes same as pc->ii_
 137      0000
1137:main.cpp      ****
1138:main.cpp      ****     const int x = (pa == &c) ? 1 : 0;
 138              		.loc 1 1138 0
 139 0061 488D45C0 		leaq	-64(%rbp), %rax								// load address of c var to %rax: -64(%rbp) - address of c
 140 0065 483945F0 		cmpq	%rax, -16(%rbp)								// compares addres of c (==pc) with pa (-16(%rbp): pa var is offset -16 from (%rbp)) -> pa == &c
 141 0069 7507     		jne	.L5
 142              		.loc 1 1138 0 is_stmt 0 discriminator 1
 143 006b B8010000 		movl	$1, %eax
 143      00
 144 0070 EB05     		jmp	.L6
 145              	.L5:
 146              		.loc 1 1138 0 discriminator 2
 147 0072 B8000000 		movl	$0, %eax
 147      00
 148              	.L6:
 149              		.loc 1 1138 0 discriminator 3
 150 0077 8945E4   		movl	%eax, -28(%rbp)
1139:main.cpp      ****     const int y = (pb == &c) ? 1 : 0;
 151              		.loc 1 1139 0 is_stmt 1 discriminator 3
 152 007a 488D45C0 		leaq	-64(%rbp), %rax								// load address of c var to %rax: -64(%rbp) - address of c
 153 007e 4883C004 		addq	$4, %rax									// adjust offset of pb: add 4 to address of c
 154 0082 483945E8 		cmpq	%rax, -24(%rbp)								// compares addres of c (==pc) with pb (-24(%rbp): pb var is offset -24 from (%rbp)) -> pb == &c !!! after above adjustment
 155 0086 7507     		jne	.L7
 156              		.loc 1 1139 0 is_stmt 0 discriminator 1
 157 0088 B8010000 		movl	$1, %eax
 157      00
 158 008d EB05     		jmp	.L8
 159              	.L7:
 160              		.loc 1 1139 0 discriminator 2
 161 008f B8000000 		movl	$0, %eax
 161      00
 162              	.L8:
 163              		.loc 1 1139 0 discriminator 3
 164 0094 8945E0   		movl	%eax, -32(%rbp)
1140:main.cpp      ****     const int z = (reinterpret_cast<char*>(pa) == reinterpret_cast<char*>(pb)) ? 1 : 0;
 165              		.loc 1 1140 0 is_stmt 1 discriminator 3
 166 0097 488B45F0 		movq	-16(%rbp), %rax								// load address of pa var to %rax: -16(%rbp) - pa
 167 009b 483B45E8 		cmpq	-24(%rbp), %rax								// compare pa with address of pb: -24(%rbp): since no adjustment, raw pointers differ by 4
 168 009f 7507     		jne	.L9
 169              		.loc 1 1140 0 is_stmt 0 discriminator 1
 170 00a1 B8010000 		movl	$1, %eax
 170      00
 171 00a6 EB05     		jmp	.L10
 172              	.L9:
 173              		.loc 1 1140 0 discriminator 2
 174 00a8 B8000000 		movl	$0, %eax
 174      00
 175              	.L10:
 176              		.loc 1 1140 0 discriminator 3
 177 00ad 8945DC   		movl	%eax, -36(%rbp)
1141:main.cpp      ****     const int zz = (reinterpret_cast<char*>(pa) == reinterpret_cast<char*>(pc)) ? 1 : 0;
 178              		.loc 1 1141 0 is_stmt 1 discriminator 3
 179 00b0 488B45F0 		movq	-16(%rbp), %rax								// load address of pa var to %rax: -16(%rbp) - pa
 180 00b4 483B45F8 		cmpq	-8(%rbp), %rax								// compare pa with pc: -8(%rbp): raw pointers are the same
 181 00b8 7507     		jne	.L11
 182              		.loc 1 1141 0 is_stmt 0 discriminator 1
 183 00ba B8010000 		movl	$1, %eax
 183      00
 184 00bf EB05     		jmp	.L12
 185              	.L11:
 186              		.loc 1 1141 0 discriminator 2
 187 00c1 B8000000 		movl	$0, %eax
 187      00
 188              	.L12:
 189              		.loc 1 1141 0 discriminator 3
 190 00c6 8945D8   		movl	%eax, -40(%rbp)
1142:main.cpp      ****     const int zzz = (reinterpret_cast<char*>(pb) == reinterpret_cast<char*>(pc)) ? 1 : 0;
 191              		.loc 1 1142 0 is_stmt 1 discriminator 3
 192 00c9 488B45E8 		movq	-24(%rbp), %rax								// load address of pb var to %rax: -24(%rbp) - pb
 193 00cd 483B45F8 		cmpq	-8(%rbp), %rax								// compare pb with pc: -8(%rbp): raw pointers differ by 4, since no adjustment done
 194 00d1 7507     		jne	.L13
 195              		.loc 1 1142 0 is_stmt 0 discriminator 1
 196 00d3 B8010000 		movl	$1, %eax
 196      00
 197 00d8 EB05     		jmp	.L14
 198              	.L13:
 199              		.loc 1 1142 0 discriminator 2
 200 00da B8000000 		movl	$0, %eax
 200      00
 201              	.L14:
 202              		.loc 1 1142 0 discriminator 3
 203 00df 8945D4   		movl	%eax, -44(%rbp)
1143:main.cpp      ****
1144:main.cpp      ****     cout << x << y << z << zz << zzz << endl;
 204              		.loc 1 1144 0 is_stmt 1 discriminator 3
 205 00e2 8B45E4   		movl	-28(%rbp), %eax
 206 00e5 89C6     		movl	%eax, %esi
 207 00e7 BF000000 		movl	$_ZSt4cout, %edi
 207      00
 208              	.LEHB0:
 209 00ec E8000000 		call	_ZNSolsEi
 209      00
 210 00f1 8B55E0   		movl	-32(%rbp), %edx
 211 00f4 89D6     		movl	%edx, %esi
 212 00f6 4889C7   		movq	%rax, %rdi
 213 00f9 E8000000 		call	_ZNSolsEi
 213      00
 214              		.loc 1 1144 0 is_stmt 0 discriminator 1
 215 00fe 8B55DC   		movl	-36(%rbp), %edx
 216 0101 89D6     		movl	%edx, %esi
 217 0103 4889C7   		movq	%rax, %rdi
 218 0106 E8000000 		call	_ZNSolsEi
 218      00
 219 010b 8B55D8   		movl	-40(%rbp), %edx
 220 010e 89D6     		movl	%edx, %esi
 221 0110 4889C7   		movq	%rax, %rdi
 222 0113 E8000000 		call	_ZNSolsEi
 222      00
 223 0118 8B55D4   		movl	-44(%rbp), %edx
 224 011b 89D6     		movl	%edx, %esi
 225 011d 4889C7   		movq	%rax, %rdi
 226 0120 E8000000 		call	_ZNSolsEi
 226      00
 227 0125 BE000000 		movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
 227      00
 228 012a 4889C7   		movq	%rax, %rdi
 229 012d E8000000 		call	_ZNSolsEPFRSoS_E
 229      00
 230              	.LEHE0:
1145:main.cpp      **** //    cout << "C: " << std::hex << &c << "\nA: " << a << "\nB: " << b << endl;
1146:main.cpp      **** //    printf("C: %x\nA: %x\nB: %x\n", &c, a, b);
1147:main.cpp      **** //    const int x = (a == &c) ? 1 : 2;
1148:main.cpp      **** //    const int y = (b == &c) ? 3 : 4;
1149:main.cpp      **** //    const int z = (reinterpret_cast<char*>(a) == reinterpret_cast<char*>(b)) ? 5 : 6;
1150:main.cpp      ****
1151:main.cpp      **** //    std::cout << x << y << z << std::endl;
1152:main.cpp      ****
1153:main.cpp      ****     return 0;
 231              		.loc 1 1153 0 is_stmt 1
 232 0132 B8000000 		movl	$0, %eax
 232      00
 233 0137 EB08     		jmp	.L18
 234              	.L17:
 235 0139 4889C7   		movq	%rax, %rdi
 236              	.LEHB1:
 237 013c E8000000 		call	_Unwind_Resume
 237      00
 238              	.LEHE1:
 239              	.L18:
 240              	.LBE3:
1154:main.cpp      **** }
 241              		.loc 1 1154 0
 242 0141 C9       		leave
 243              		.cfi_def_cfa 7, 8
 244 0142 C3       		ret
 245              		.cfi_endproc
 246              	.LFE1194:
 247              		.globl	__gxx_personality_v0
 248              		.section	.gcc_except_table,"a",@progbits
 249              	.LLSDA1194:
 250 0000 FF       		.byte	0xff
 251 0001 FF       		.byte	0xff
 252 0002 01       		.byte	0x1
 253 0003 0B       		.uleb128 .LLSDACSE1194-.LLSDACSB1194
 254              	.LLSDACSB1194:
 255 0004 EC01     		.uleb128 .LEHB0-.LFB1194
 256 0006 46       		.uleb128 .LEHE0-.LEHB0
 257 0007 B902     		.uleb128 .L17-.LFB1194
 258 0009 00       		.uleb128 0
 259 000a BC02     		.uleb128 .LEHB1-.LFB1194
 260 000c 05       		.uleb128 .LEHE1-.LEHB1
 261 000d 00       		.uleb128 0
 262 000e 00       		.uleb128 0
 263              	.LLSDACSE1194:
 264              		.text
 267              	_Z41__static_initialization_and_destruction_0ii:
 268              	.LFB1355:
 269              		.loc 1 1154 0
 270              		.cfi_startproc
 271 0143 55       		pushq	%rbp
 272              		.cfi_def_cfa_offset 16
 273              		.cfi_offset 6, -16
 274 0144 4889E5   		movq	%rsp, %rbp
 275              		.cfi_def_cfa_register 6
 276 0147 4883EC10 		subq	$16, %rsp
 277 014b 897DFC   		movl	%edi, -4(%rbp)
 278 014e 8975F8   		movl	%esi, -8(%rbp)
 279              		.loc 1 1154 0
 280 0151 837DFC01 		cmpl	$1, -4(%rbp)
 281 0155 7527     		jne	.L19
 282              		.loc 1 1154 0 is_stmt 0 discriminator 1
 283 0157 817DF8FF 		cmpl	$65535, -8(%rbp)
 283      FF0000
 284 015e 751E     		jne	.L19
#endif
//
// -----------------------------------------------------------------------------------------------------------

#include <iostream>
using namespace std;

class A
{
public:
    int i_;
};

class B
{
public:
    int ii_;
};

class C: public A,
         public B
{
public:
    char c_ = 'a';
};

int main()
{
    C c;
    C* pc = &c;
    A* pa = &c;
    B* pb = &c;

    pc->i_ = 5;
    pc->ii_ = 10;
    pc->c_ = 'b';

    pa->i_ = 25;

    pb->ii_ = 20;

    const int x = (pa == &c) ? 1 : 0;
    const int y = (pb == &c) ? 1 : 0;
    const int z = (reinterpret_cast<char*>(pa) == reinterpret_cast<char*>(pb)) ? 1 : 0;
    const int zz = (reinterpret_cast<char*>(pa) == reinterpret_cast<char*>(pc)) ? 1 : 0;
    const int zzz = (reinterpret_cast<char*>(pb) == reinterpret_cast<char*>(pc)) ? 1 : 0;

    cout << x << y << z << zz << zzz << endl;

    return 0;
}
