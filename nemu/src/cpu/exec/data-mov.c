#include "cpu/exec.h"

make_EHelper(mov) {
  operand_write(id_dest, &id_src->val);
  print_asm_template2(mov);
}

make_EHelper(push) {
	// TODO();
	if(id_dest->width == 1){
	  	uint8_t utmp = id_dest->val;
		int8_t temp = utmp;
		id_dest->val = temp;
	}
   	rtl_push(&id_dest->val);  

	print_asm_template1(push);
}

make_EHelper(pop) {
	// TODO();
	rtl_pop(&t0);
	if(id_dest->width == 1){
		uint8_t utemp = t0;
		int8_t temp = utemp; 
		id_dest->val = temp;
	}
	else 
	  	id_dest->val = at;
	
	print_asm_template1(pop);
}

make_EHelper(pusha) {
	// TODO();
	t0 = cpu.esp;
	rtl_push(&cpu.eax);
	rtl_push(&cpu.ecx);
	rtl_push(&cpu.edx);
	rtl_push(&cpu.ebx);
	rtl_push(&t0);
	rtl_push(&cpu.ebp);
	rtl_push(&cpu.esi);
	rtl_push(&cpu.edi);

	print_asm("pusha");
}

make_EHelper(popa) {
	// TODO();
	rtl_pop(&cpu.edi);
	rtl_pop(&cpu.esi);
	rtl_pop(&cpu.ebp);
	rtl_pop(&t0);
	rtl_pop(&cpu.ebx);
	rtl_pop(&cpu.edx);
	rtl_pop(&cpu.ecx);
	rtl_pop(&cpu.eax);
	
	print_asm("popa");
}

make_EHelper(leave) {
	// TODO();
	reg_l(4) = reg_l(5);
	rtl_pop(&t0);
	reg_w(5) = t0;
	
	print_asm("leave");
}

make_EHelper(cltd) {
	if (decoding.is_operand_size_16) {
    rtl_lr(&t0, R_AX, 2);
    rtl_sext(&t0, &t0, 2);
    rtl_sari(&t0, &t0, 16);
    rtl_sr(R_DX, &t0, 2);
  } else {
    rtl_lr(&t0, R_EAX, 4);
    rtl_sari(&t0, &t0, 31);
    rtl_sari(&t0, &t0, 1);
    rtl_sr(R_EDX, &t0, 4);
  }

	print_asm(decoding.is_operand_size_16 ? "cwtl" : "cltd");
}

make_EHelper(cwtl) {
	if (decoding.is_operand_size_16) {
    rtl_lr(&t0, R_AX, 1);
    rtl_sext(&t0, &t0, 1);
    rtl_sr(R_AX, &t0, 2);
  }
  else {
    rtl_lr(&t0, R_AX, 2);
    rtl_sext(&t0, &t0, 2);
    rtl_sr(R_EAX, &t0, 4);
  }

	print_asm(decoding.is_operand_size_16 ? "cbtw" : "cwtl");
}

make_EHelper(movsx) {
	id_dest->width = decoding.is_operand_size_16 ? 2 : 4;
	rtl_sext(&t0, &id_src->val, id_src->width);
	operand_write(id_dest, &t0);
	print_asm_template2(movsx);
}

make_EHelper(movzx) {
	id_dest->width = decoding.is_operand_size_16 ? 2 : 4;
	operand_write(id_dest, &id_src->val);
	print_asm_template2(movzx);
}

make_EHelper(lea) {
	operand_write(id_dest, &id_src->addr);
	print_asm_template2(lea);
}
