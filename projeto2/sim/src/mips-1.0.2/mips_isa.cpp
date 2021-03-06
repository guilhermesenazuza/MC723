/**
 * @file      mips_isa.cpp
 * @author    Sandro Rigo
 *            Marcus Bartholomeu
 *            Alexandro Baldassin (acasm information)
 *
 *            The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   1.0
 * @date      Mon, 19 Jun 2006 15:50:52 -0300
 * 
 * @brief     The ArchC i8051 functional model.
 * 
 * @attention Copyright (C) 2002-2006 --- The ArchC Team
 *
 */

#include  "mips_isa.H"
#include  "mips_isa_init.cpp"
#include  "mips_bhv_macros.H"


//If you want debug information for this model, uncomment next line
//#define DEBUG_MODEL
#include "ac_debug_model.H"


//!User defined macros to reference registers.
#define Ra 31
#define Sp 29

// 'using namespace' statement to allow access to all
// mips-specific datatypes
using namespace mips_parms;

static int processors_started = 0;
#define DEFAULT_STACK_SIZE (256*1024)

// y4k start
FILE *f_trace = fopen("/tmp/y4k_last.mips_trace", "w");
// FILE *f_trace = fopen("/tmp/y4k_susan_small_smooth_.mips_trace", "w");

int y4k_last_taken = 1;

int y4k_nottaken = 0;
int y4k_taken = 0;

int y4k_nt_after_nt = 0;
int y4k_nt_after_t = 0;
int y4k_t_after_nt = 0;
int y4k_t_after_t = 0;

int y4k_j = 0;
int y4k_jal = 0;
int y4k_jr = 0;
int y4k_jalr = 0;
int y4k_beq = 0;
int y4k_bne = 0;
int y4k_blez = 0;
int y4k_bgtz = 0;
int y4k_bltz = 0;
int y4k_bgez = 0;
int y4k_bltzal = 0;
int y4k_bgezal = 0;

int y4k_superscalar_idx = 1;
int y4k_prev_rdest = -1;
int y4k_prev_rsrc1 = -1;
int y4k_prev_rsrc2 = -1;

int y4k_war = 0;
int y4k_raw = 0;
int y4k_waw = 0;

int y4k_lb = 0;
int y4k_lbu = 0;
int y4k_lh = 0;
int y4k_lhu = 0;
int y4k_lw = 0;
int y4k_lwl = 0;
int y4k_lwr = 0;
int y4k_sb = 0;
int y4k_sh = 0;
int y4k_sw = 0;
int y4k_swl = 0;
int y4k_swr = 0;

void y4k_count_nosuperscalar_none() {
  y4k_prev_rdest = -1;
  y4k_prev_rsrc1 = -1;
  y4k_prev_rsrc2 = -1;
}

void y4k_count_nosuperscalar_rdest(int y4k_rdest) {
  if (y4k_superscalar_idx == 1) {
    if (y4k_prev_rdest != -1 && y4k_prev_rdest == y4k_rdest) {
      y4k_waw += 1;
      y4k_superscalar_idx = 0;
    } else if (y4k_rdest != -1) {
      if (y4k_rdest == y4k_prev_rsrc1 || y4k_rdest == y4k_prev_rsrc2) {
	y4k_war += 1;
	y4k_superscalar_idx = 0;
      }
    }
  }
  y4k_prev_rdest = y4k_rdest;
  y4k_prev_rsrc1 = -1;
  y4k_prev_rsrc2 = -1;
}

void y4k_count_nosuperscalar_rdest_rsrc1(int y4k_rdest, int y4k_rsrc1) {
  if (y4k_superscalar_idx == 1) {
    if (y4k_prev_rdest != -1) {
      if (y4k_prev_rdest == y4k_rdest) {
	y4k_waw += 1;
	y4k_superscalar_idx = 0;
      } else if (y4k_prev_rdest == y4k_rsrc1) {
	y4k_raw += 1;
	y4k_superscalar_idx = 0;
      }
    } else if (y4k_rdest != -1) {
      if (y4k_rdest == y4k_prev_rsrc1 || y4k_rdest == y4k_prev_rsrc2) {
	y4k_war += 1;
	y4k_superscalar_idx = 0;
      }
    }
  }
  y4k_prev_rdest = y4k_rdest;
  y4k_prev_rsrc1 = y4k_rsrc1;
  y4k_prev_rsrc2 = -1;
}

void y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(int y4k_rdest, int y4k_rsrc1, int y4k_rsrc2) {
  if (y4k_superscalar_idx == 1) {
    if (y4k_prev_rdest != -1) {
      if (y4k_prev_rdest == y4k_rdest) {
	y4k_waw += 1;
	y4k_superscalar_idx = 0;
      } else if (y4k_prev_rdest == y4k_rsrc1 || y4k_prev_rdest == y4k_rsrc2) {
	y4k_raw += 1;
	y4k_superscalar_idx = 0;
      }
    } else if (y4k_rdest != -1) {
      if (y4k_rdest == y4k_prev_rsrc1 || y4k_rdest == y4k_prev_rsrc2) {
	y4k_war += 1;
	y4k_superscalar_idx = 0;
      }
    }
  }
  y4k_prev_rdest = y4k_rdest;
  y4k_prev_rsrc1 = y4k_rsrc1;
  y4k_prev_rsrc2 = y4k_rsrc2;
}
// y4k end

//!Generic instruction behavior method.
void ac_behavior( instruction )
{ 
  y4k_superscalar_idx = 1 - y4k_superscalar_idx;
  // fprintf(stderr, "%20d y4k_superscalar_idx\n", y4k_superscalar_idx);
  dbg_printf("----- PC=%#x ----- %lld\n", (int) ac_pc, ac_instr_counter);
  //  dbg_printf("----- PC=%#x NPC=%#x ----- %lld\n", (int) ac_pc, (int)npc, ac_instr_counter);
#ifndef NO_NEED_PC_UPDATE
  ac_pc = npc;
  npc = ac_pc + 4;
#endif 

  // y4k start
  fprintf(f_trace, "2 %x\n", (int) ac_pc);
  // y4k end
};
 
//! Instruction Format behavior methods.
void ac_behavior( Type_R ){}
void ac_behavior( Type_I ){}
void ac_behavior( Type_J ){}
 
//!Behavior called before starting simulation
void ac_behavior(begin)
{
  dbg_printf("@@@ begin behavior @@@\n");
  RB[0] = 0;
  npc = ac_pc + 4;

  // Is is not required by the architecture, but makes debug really easier
  for (int regNum = 0; regNum < 32; regNum ++)
    RB[regNum] = 0;
  hi = 0;
  lo = 0;

  RB[29] =  AC_RAM_END - 1024 - processors_started++ * DEFAULT_STACK_SIZE;

  y4k_last_taken = 1;

  y4k_nottaken = 0;
  y4k_taken = 0;

  y4k_nt_after_nt = 0;
  y4k_nt_after_t = 0;
  y4k_t_after_nt = 0;
  y4k_t_after_t = 0;

  y4k_lb = 0;
  y4k_lbu = 0;
  y4k_lh = 0;
  y4k_lhu = 0;
  y4k_lw = 0;
  y4k_lwl = 0;
  y4k_lwr = 0;
  y4k_sb = 0;
  y4k_sh = 0;
  y4k_sw = 0;
  y4k_swl = 0;
  y4k_swr = 0;

  y4k_j = 0;
  y4k_jal = 0;
  y4k_jr = 0;
  y4k_jalr = 0;
  y4k_beq = 0;
  y4k_bne = 0;
  y4k_blez = 0;
  y4k_bgtz = 0;
  y4k_bltz = 0;
  y4k_bgez = 0;
  y4k_bltzal = 0;
  y4k_bgezal = 0;

  y4k_superscalar_idx = 1;
  y4k_prev_rdest = -1;
  y4k_prev_rsrc1 = -1;
  y4k_prev_rsrc2 = -1;

  y4k_war = 0;
  y4k_raw = 0;
  y4k_waw = 0;
}

//!Behavior called after finishing simulation
void ac_behavior(end)
{
  dbg_printf("@@@ end behavior @@@\n");

  fprintf(stderr, "%20d y4k_superscalar_idx\n", y4k_superscalar_idx);

  fprintf(stderr, "\n");

  fprintf(stderr, "%20d y4k_nottaken\n", y4k_nottaken);
  fprintf(stderr, "%20d y4k_taken\n", y4k_taken);

  fprintf(stderr, "\n");

  fprintf(stderr, "%20d y4k_nt_after_nt\n", y4k_nt_after_nt);
  fprintf(stderr, "%20d y4k_nt_after_t\n", y4k_nt_after_t);
  fprintf(stderr, "%20d y4k_t_after_nt\n", y4k_t_after_nt);
  fprintf(stderr, "%20d y4k_t_after_t\n", y4k_t_after_t);

  fprintf(stderr, "\n");

  fprintf(stderr, "%20d y4k_lb\n", y4k_lb);
  fprintf(stderr, "%20d y4k_lbu\n", y4k_lbu);
  fprintf(stderr, "%20d y4k_lh\n", y4k_lh);
  fprintf(stderr, "%20d y4k_lhu\n", y4k_lhu);
  fprintf(stderr, "%20d y4k_lw\n", y4k_lw);
  fprintf(stderr, "%20d y4k_lwl\n", y4k_lwl);
  fprintf(stderr, "%20d y4k_lwr\n", y4k_lwr);
  fprintf(stderr, "%20d y4k_sb\n", y4k_sb);
  fprintf(stderr, "%20d y4k_sh\n", y4k_sh);
  fprintf(stderr, "%20d y4k_sw\n", y4k_sw);
  fprintf(stderr, "%20d y4k_swl\n", y4k_swl);
  fprintf(stderr, "%20d y4k_swr\n", y4k_swr);

  fprintf(stderr, "\n");

  fprintf(stderr, "%20d y4k_j\n", y4k_j);
  fprintf(stderr, "%20d y4k_jal\n", y4k_jal);
  fprintf(stderr, "%20d y4k_jr\n", y4k_jr);
  fprintf(stderr, "%20d y4k_jalr\n", y4k_jalr);
  fprintf(stderr, "%20d y4k_beq\n", y4k_beq);
  fprintf(stderr, "%20d y4k_bne\n", y4k_bne);
  fprintf(stderr, "%20d y4k_blez\n", y4k_blez);
  fprintf(stderr, "%20d y4k_bgtz\n", y4k_bgtz);
  fprintf(stderr, "%20d y4k_bltz\n", y4k_bltz);
  fprintf(stderr, "%20d y4k_bgez\n", y4k_bgez);
  fprintf(stderr, "%20d y4k_bltzal\n", y4k_bltzal);
  fprintf(stderr, "%20d y4k_bgezal\n", y4k_bgezal);

  fprintf(stderr, "\n");

  fprintf(stderr, "%20d y4k_war\n", y4k_war);
  fprintf(stderr, "%20d y4k_raw\n", y4k_raw);
  fprintf(stderr, "%20d y4k_waw\n", y4k_waw);
}


//!Instruction lb behavior method.
void ac_behavior( lb )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  y4k_lb += 1;
  char byte;
  dbg_printf("lb r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  byte = DM.read_byte(RB[rs]+ imm);
  RB[rt] = (ac_Sword)byte ;
  dbg_printf("Result = %#x\n", RB[rt]);

  // y4k start
  fprintf(f_trace, "0 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction lbu behavior method.
void ac_behavior( lbu )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  y4k_lbu += 1;
  unsigned char byte;
  dbg_printf("lbu r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  byte = DM.read_byte(RB[rs]+ imm);
  RB[rt] = byte ;
  dbg_printf("Result = %#x\n", RB[rt]);

  // y4k start
  fprintf(f_trace, "0 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction lh behavior method.
void ac_behavior( lh )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  y4k_lh += 1;
  short int half;
  dbg_printf("lh r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  half = DM.read_half(RB[rs]+ imm);
  RB[rt] = (ac_Sword)half ;
  dbg_printf("Result = %#x\n", RB[rt]);

  // y4k start
  fprintf(f_trace, "0 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction lhu behavior method.
void ac_behavior( lhu )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  y4k_lhu += 1;
  unsigned short int  half;
  half = DM.read_half(RB[rs]+ imm);
  RB[rt] = half ;
  dbg_printf("Result = %#x\n", RB[rt]);

  // y4k start
  fprintf(f_trace, "0 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction lw behavior method.
void ac_behavior( lw )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  y4k_lw += 1;
  dbg_printf("lw r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  RB[rt] = DM.read(RB[rs]+ imm);
  dbg_printf("Result = %#x\n", RB[rt]);

  // y4k start
  fprintf(f_trace, "0 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction lwl behavior method.
void ac_behavior( lwl )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  y4k_lwl += 1;
  dbg_printf("lwl r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  unsigned int addr, offset;
  ac_Uword data;

  addr = RB[rs] + imm;
  offset = (addr & 0x3) * 8;
  data = DM.read(addr & 0xFFFFFFFC);
  data <<= offset;
  data |= RB[rt] & ((1<<offset)-1);
  RB[rt] = data;
  dbg_printf("Result = %#x\n", RB[rt]);

  // y4k start
  fprintf(f_trace, "0 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction lwr behavior method.
void ac_behavior( lwr )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  y4k_lwr += 1;
  dbg_printf("lwr r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  unsigned int addr, offset;
  ac_Uword data;

  addr = RB[rs] + imm;
  offset = (3 - (addr & 0x3)) * 8;
  data = DM.read(addr & 0xFFFFFFFC);
  data >>= offset;
  data |= RB[rt] & (0xFFFFFFFF << (32-offset));
  RB[rt] = data;
  dbg_printf("Result = %#x\n", RB[rt]);

  // y4k start
  fprintf(f_trace, "0 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction sb behavior method.
void ac_behavior( sb )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(-1, rt, rs);
  y4k_sb += 1;
  unsigned char byte;
  dbg_printf("sb r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  byte = RB[rt] & 0xFF;
  DM.write_byte(RB[rs] + imm, byte);
  dbg_printf("Result = %#x\n", (int) byte);

  // y4k start
  fprintf(f_trace, "1 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction sh behavior method.
void ac_behavior( sh )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(-1, rt, rs);
  y4k_sh += 1;
  unsigned short int half;
  dbg_printf("sh r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  half = RB[rt] & 0xFFFF;
  DM.write_half(RB[rs] + imm, half);
  dbg_printf("Result = %#x\n", (int) half);

  // y4k start
  fprintf(f_trace, "1 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction sw behavior method.
void ac_behavior( sw )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(-1, rt, rs);
  y4k_sw += 1;
  dbg_printf("sw r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  DM.write(RB[rs] + imm, RB[rt]);
  dbg_printf("Result = %#x\n", RB[rt]);

  // y4k start
  fprintf(f_trace, "1 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction swl behavior method.
void ac_behavior( swl )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(-1, rt, rs);
  y4k_swl += 1;
  dbg_printf("swl r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  unsigned int addr, offset;
  ac_Uword data;

  addr = RB[rs] + imm;
  offset = (addr & 0x3) * 8;
  data = RB[rt];
  data >>= offset;
  data |= DM.read(addr & 0xFFFFFFFC) & (0xFFFFFFFF << (32-offset));
  DM.write(addr & 0xFFFFFFFC, data);
  dbg_printf("Result = %#x\n", data);

  // y4k start
  fprintf(f_trace, "1 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction swr behavior method.
void ac_behavior( swr )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(-1, rt, rs);
  y4k_swr += 1;
  dbg_printf("swr r%d, %d(r%d)\n", rt, imm & 0xFFFF, rs);
  unsigned int addr, offset;
  ac_Uword data;

  addr = RB[rs] + imm;
  offset = (3 - (addr & 0x3)) * 8;
  data = RB[rt];
  data <<= offset;
  data |= DM.read(addr & 0xFFFFFFFC) & ((1<<offset)-1);
  DM.write(addr & 0xFFFFFFFC, data);
  dbg_printf("Result = %#x\n", data);

  // y4k start
  fprintf(f_trace, "1 %x\n", RB[rs]+ imm);
  // y4k end
};

//!Instruction addi behavior method.
void ac_behavior( addi )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  dbg_printf("addi r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
  RB[rt] = RB[rs] + imm;
  dbg_printf("Result = %#x\n", RB[rt]);
  //Test overflow
  if ( ((RB[rs] & 0x80000000) == (imm & 0x80000000)) &&
       ((imm & 0x80000000) != (RB[rt] & 0x80000000)) ) {
    fprintf(stderr, "EXCEPTION(addi): integer overflow.\n"); exit(EXIT_FAILURE);
  }
};

//!Instruction addiu behavior method.
void ac_behavior( addiu )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  dbg_printf("addiu r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
  RB[rt] = RB[rs] + imm;
  dbg_printf("Result = %#x\n", RB[rt]);
};

//!Instruction slti behavior method.
void ac_behavior( slti )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  dbg_printf("slti r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
  // Set the RD if RS< IMM
  if( (ac_Sword) RB[rs] < (ac_Sword) imm )
    RB[rt] = 1;
  // Else reset RD
  else
    RB[rt] = 0;
  dbg_printf("Result = %#x\n", RB[rt]);
};

//!Instruction sltiu behavior method.
void ac_behavior( sltiu )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  dbg_printf("sltiu r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
  // Set the RD if RS< IMM
  if( (ac_Uword) RB[rs] < (ac_Uword) imm )
    RB[rt] = 1;
  // Else reset RD
  else
    RB[rt] = 0;
  dbg_printf("Result = %#x\n", RB[rt]);
};

//!Instruction andi behavior method.
void ac_behavior( andi )
{	
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  dbg_printf("andi r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
  RB[rt] = RB[rs] & (imm & 0xFFFF) ;
  dbg_printf("Result = %#x\n", RB[rt]);
};

//!Instruction ori behavior method.
void ac_behavior( ori )
{	
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  dbg_printf("ori r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
  RB[rt] = RB[rs] | (imm & 0xFFFF) ;
  dbg_printf("Result = %#x\n", RB[rt]);
};

//!Instruction xori behavior method.
void ac_behavior( xori )
{	
  y4k_count_nosuperscalar_rdest_rsrc1(rt, rs);
  dbg_printf("xori r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
  RB[rt] = RB[rs] ^ (imm & 0xFFFF) ;
  dbg_printf("Result = %#x\n", RB[rt]);
};

//!Instruction lui behavior method.
void ac_behavior( lui )
{	
  y4k_count_nosuperscalar_rdest(rt);
  dbg_printf("lui r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
  // Load a constant in the upper 16 bits of a register
  // To achieve the desired behaviour, the constant was shifted 16 bits left
  // and moved to the target register ( rt )
  RB[rt] = imm << 16;
  dbg_printf("Result = %#x\n", RB[rt]);
};

//!Instruction add behavior method.
void ac_behavior( add )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("add r%d, r%d, r%d\n", rd, rs, rt);
  RB[rd] = RB[rs] + RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
  //Test overflow
  if ( ((RB[rs] & 0x80000000) == (RB[rd] & 0x80000000)) &&
       ((RB[rd] & 0x80000000) != (RB[rt] & 0x80000000)) ) {
    fprintf(stderr, "EXCEPTION(add): integer overflow.\n"); exit(EXIT_FAILURE);
  }
};

//!Instruction addu behavior method.
void ac_behavior( addu )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("addu r%d, r%d, r%d\n", rd, rs, rt);
  RB[rd] = RB[rs] + RB[rt];
  //cout << "  RS: " << (unsigned int)RB[rs] << " RT: " << (unsigned int)RB[rt] << endl;
  //cout << "  Result =  " <<  (unsigned int)RB[rd] <<endl;
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction sub behavior method.
void ac_behavior( sub )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("sub r%d, r%d, r%d\n", rd, rs, rt);
  RB[rd] = RB[rs] - RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
  //TODO: test integer overflow exception for sub
};

//!Instruction subu behavior method.
void ac_behavior( subu )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("subu r%d, r%d, r%d\n", rd, rs, rt);
  RB[rd] = RB[rs] - RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction slt behavior method.
void ac_behavior( slt )
{	
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("slt r%d, r%d, r%d\n", rd, rs, rt);
  // Set the RD if RS< RT
  if( (ac_Sword) RB[rs] < (ac_Sword) RB[rt] )
    RB[rd] = 1;
  // Else reset RD
  else
    RB[rd] = 0;
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction sltu behavior method.
void ac_behavior( sltu )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("sltu r%d, r%d, r%d\n", rd, rs, rt);
  // Set the RD if RS < RT
  if( RB[rs] < RB[rt] )
    RB[rd] = 1;
  // Else reset RD
  else
    RB[rd] = 0;
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction instr_and behavior method.
void ac_behavior( instr_and )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("instr_and r%d, r%d, r%d\n", rd, rs, rt);
  RB[rd] = RB[rs] & RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction instr_or behavior method.
void ac_behavior( instr_or )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("instr_or r%d, r%d, r%d\n", rd, rs, rt);
  RB[rd] = RB[rs] | RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction instr_xor behavior method.
void ac_behavior( instr_xor )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("instr_xor r%d, r%d, r%d\n", rd, rs, rt);
  RB[rd] = RB[rs] ^ RB[rt];
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction instr_nor behavior method.
void ac_behavior( instr_nor )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("nor r%d, r%d, r%d\n", rd, rs, rt);
  RB[rd] = ~(RB[rs] | RB[rt]);
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction nop behavior method.
void ac_behavior( nop )
{  
  y4k_count_nosuperscalar_none()
  dbg_printf("nop\n");
};

//!Instruction sll behavior method.
void ac_behavior( sll )
{  
  y4k_count_nosuperscalar_rdest_rsrc1(rd, rt);
  dbg_printf("sll r%d, r%d, %d\n", rd, rs, shamt);
  RB[rd] = RB[rt] << shamt;
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction srl behavior method.
void ac_behavior( srl )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rd, rt);
  dbg_printf("srl r%d, r%d, %d\n", rd, rs, shamt);
  RB[rd] = RB[rt] >> shamt;
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction sra behavior method.
void ac_behavior( sra )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rd, rt);
  dbg_printf("sra r%d, r%d, %d\n", rd, rs, shamt);
  RB[rd] = (ac_Sword) RB[rt] >> shamt;
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction sllv behavior method.
void ac_behavior( sllv )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("sllv r%d, r%d, r%d\n", rd, rt, rs);
  RB[rd] = RB[rt] << (RB[rs] & 0x1F);
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction srlv behavior method.
void ac_behavior( srlv )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("srlv r%d, r%d, r%d\n", rd, rt, rs);
  RB[rd] = RB[rt] >> (RB[rs] & 0x1F);
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction srav behavior method.
void ac_behavior( srav )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(rd, rs, rt);
  dbg_printf("srav r%d, r%d, r%d\n", rd, rt, rs);
  RB[rd] = (ac_Sword) RB[rt] >> (RB[rs] & 0x1F);
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction mult behavior method.
void ac_behavior( mult )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rs, rt);
  dbg_printf("mult r%d, r%d\n", rs, rt);

  long long result;
  int half_result;

  result = (ac_Sword) RB[rs];
  result *= (ac_Sword) RB[rt];

  half_result = (result & 0xFFFFFFFF);
  // Register LO receives 32 less significant bits
  lo = half_result;

  half_result = ((result >> 32) & 0xFFFFFFFF);
  // Register HI receives 32 most significant bits
  hi = half_result ;

  dbg_printf("Result = %#llx\n", result);
};

//!Instruction multu behavior method.
void ac_behavior( multu )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rs, rt);
  dbg_printf("multu r%d, r%d\n", rs, rt);

  unsigned long long result;
  unsigned int half_result;

  result  = RB[rs];
  result *= RB[rt];

  half_result = (result & 0xFFFFFFFF);
  // Register LO receives 32 less significant bits
  lo = half_result;

  half_result = ((result>>32) & 0xFFFFFFFF);
  // Register HI receives 32 most significant bits
  hi = half_result ;

  dbg_printf("Result = %#llx\n", result);
};

//!Instruction div behavior method.
void ac_behavior( div )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rs, rt);
  dbg_printf("div r%d, r%d\n", rs, rt);
  // Register LO receives quotient
  lo = (ac_Sword) RB[rs] / (ac_Sword) RB[rt];
  // Register HI receives remainder
  hi = (ac_Sword) RB[rs] % (ac_Sword) RB[rt];
};

//!Instruction divu behavior method.
void ac_behavior( divu )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rs, rt);
  dbg_printf("divu r%d, r%d\n", rs, rt);
  // Register LO receives quotient
  lo = RB[rs] / RB[rt];
  // Register HI receives remainder
  hi = RB[rs] % RB[rt];
};

//!Instruction mfhi behavior method.
void ac_behavior( mfhi )
{
  y4k_count_nosuperscalar_rdest(rd);
  dbg_printf("mfhi r%d\n", rd);
  RB[rd] = hi;
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction mthi behavior method.
void ac_behavior( mthi )
{
  y4k_count_nosuperscalar_rdest_rsrc1(-1, rs);
  dbg_printf("mthi r%d\n", rs);
  hi = RB[rs];
  dbg_printf("Result = %#x\n", (unsigned int) hi);
};

//!Instruction mflo behavior method.
void ac_behavior( mflo )
{
  y4k_count_nosuperscalar_rdest(rd);
  dbg_printf("mflo r%d\n", rd);
  RB[rd] = lo;
  dbg_printf("Result = %#x\n", RB[rd]);
};

//!Instruction mtlo behavior method.
void ac_behavior( mtlo )
{
  y4k_count_nosuperscalar_rdest_rsrc1(-1, rs);
  dbg_printf("mtlo r%d\n", rs);
  lo = RB[rs];
  dbg_printf("Result = %#x\n", (unsigned int) lo);
};

//!Instruction j behavior method.
void ac_behavior( j )
{
  y4k_count_nosuperscalar_none();
  y4k_j += 1;
  dbg_printf("j %d\n", addr);
  addr = addr << 2;
#ifndef NO_NEED_PC_UPDATE
  npc =  (ac_pc & 0xF0000000) | addr;
#endif 
  dbg_printf("Target = %#x\n", (ac_pc & 0xF0000000) | addr );
};

//!Instruction jal behavior method.
void ac_behavior( jal )
{
  y4k_count_nosuperscalar_none();
  y4k_jal += 1;
  dbg_printf("jal %d\n", addr);
  // Save the value of PC + 8 (return address) in $ra ($31) and
  // jump to the address given by PC(31...28)||(addr<<2)
  // It must also flush the instructions that were loaded into the pipeline
  RB[Ra] = ac_pc+4; //ac_pc is pc+4, we need pc+8
	
  addr = addr << 2;
#ifndef NO_NEED_PC_UPDATE
  npc = (ac_pc & 0xF0000000) | addr;
#endif 
	
  dbg_printf("Target = %#x\n", (ac_pc & 0xF0000000) | addr );
  dbg_printf("Return = %#x\n", ac_pc+4);
};

//!Instruction jr behavior method.
void ac_behavior( jr )
{
  y4k_count_nosuperscalar_rdest_rsrc1(-1, rs);
  y4k_jr += 1;
  dbg_printf("jr r%d\n", rs);
  // Jump to the address stored on the register reg[RS]
  // It must also flush the instructions that were loaded into the pipeline
#ifndef NO_NEED_PC_UPDATE
  npc = RB[rs], 1;
#endif 
  dbg_printf("Target = %#x\n", RB[rs]);
};

//!Instruction jalr behavior method.
void ac_behavior( jalr )
{
  y4k_count_nosuperscalar_rdest_rsrc1(rd, rs);
  y4k_jalr += 1;
  dbg_printf("jalr r%d, r%d\n", rd, rs);
  // Save the value of PC + 8(return address) in rd and
  // jump to the address given by [rs]

#ifndef NO_NEED_PC_UPDATE
  npc = RB[rs], 1;
#endif 
  dbg_printf("Target = %#x\n", RB[rs]);

  if( rd == 0 )  //If rd is not defined use default
    rd = Ra;
  RB[rd] = ac_pc+4;
  dbg_printf("Return = %#x\n", ac_pc+4);
};

//!Instruction beq behavior method.
void ac_behavior( beq )
{
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(-1, rs, rt);
  y4k_beq += 1;
  dbg_printf("beq r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
  if( RB[rs] == RB[rt] ){
#ifndef NO_NEED_PC_UPDATE
    npc = ac_pc + (imm<<2);
#endif 
    dbg_printf("Taken to %#x\n", ac_pc + (imm<<2));
    y4k_taken += 1;
    if (y4k_last_taken == 1) {
      y4k_t_after_t += 1;
    } else {
      y4k_t_after_nt += 1;
    }
    y4k_last_taken = 1;
  } else {
    y4k_nottaken += 1;
    if (y4k_last_taken == 1) {
      y4k_nt_after_t += 1;
    } else {
      y4k_nt_after_nt += 1;
    }
    y4k_last_taken = 0;
  }
};

//!Instruction bne behavior method.
void ac_behavior( bne )
{	
  y4k_count_nosuperscalar_rdest_rsrc1_rsrc2(-1, rs, rt);
  y4k_bne += 1;
  dbg_printf("bne r%d, r%d, %d\n", rt, rs, imm & 0xFFFF);
  if( RB[rs] != RB[rt] ){
#ifndef NO_NEED_PC_UPDATE
    npc = ac_pc + (imm<<2);
#endif 
    dbg_printf("Taken to %#x\n", ac_pc + (imm<<2));
    y4k_taken += 1;
    if (y4k_last_taken == 1) {
      y4k_t_after_t += 1;
    } else {
      y4k_t_after_nt += 1;
    }
    y4k_last_taken = 1;
  } else {
    y4k_nottaken += 1;
    if (y4k_last_taken == 1) {
      y4k_nt_after_t += 1;
    } else {
      y4k_nt_after_nt += 1;
    }
    y4k_last_taken = 0;
  }
};

//!Instruction blez behavior method.
void ac_behavior( blez )
{
  y4k_count_nosuperscalar_rdest_rsrc1(-1, rs);
  y4k_blez += 1;
  dbg_printf("blez r%d, %d\n", rs, imm & 0xFFFF);
  if( (RB[rs] == 0 ) || (RB[rs]&0x80000000 ) ){
#ifndef NO_NEED_PC_UPDATE
    npc = ac_pc + (imm<<2), 1;
#endif 
    dbg_printf("Taken to %#x\n", ac_pc + (imm<<2));
    y4k_taken += 1;
    if (y4k_last_taken == 1) {
      y4k_t_after_t += 1;
    } else {
      y4k_t_after_nt += 1;
    }
    y4k_last_taken = 1;
  } else {
    y4k_nottaken += 1;
    if (y4k_last_taken == 1) {
      y4k_nt_after_t += 1;
    } else {
      y4k_nt_after_nt += 1;
    }
    y4k_last_taken = 0;
  }	
};

//!Instruction bgtz behavior method.
void ac_behavior( bgtz )
{
  y4k_count_nosuperscalar_rdest_rsrc1(-1, rs);
  y4k_bgtz += 1;
  dbg_printf("bgtz r%d, %d\n", rs, imm & 0xFFFF);
  if( !(RB[rs] & 0x80000000) && (RB[rs]!=0) ){
#ifndef NO_NEED_PC_UPDATE
    npc = ac_pc + (imm<<2);
#endif 
    dbg_printf("Taken to %#x\n", ac_pc + (imm<<2));
    y4k_taken += 1;
    if (y4k_last_taken == 1) {
      y4k_t_after_t += 1;
    } else {
      y4k_t_after_nt += 1;
    }
    y4k_last_taken = 1;
  } else {
    y4k_nottaken += 1;
    if (y4k_last_taken == 1) {
      y4k_nt_after_t += 1;
    } else {
      y4k_nt_after_nt += 1;
    }
    y4k_last_taken = 0;
  }	
};

//!Instruction bltz behavior method.
void ac_behavior( bltz )
{
  y4k_count_nosuperscalar_rdest_rsrc1(-1, rs);
  y4k_bltz += 1;
  dbg_printf("bltz r%d, %d\n", rs, imm & 0xFFFF);
  if( RB[rs] & 0x80000000 ){
#ifndef NO_NEED_PC_UPDATE
    npc = ac_pc + (imm<<2);
#endif 
    dbg_printf("Taken to %#x\n", ac_pc + (imm<<2));
    y4k_taken += 1;
    if (y4k_last_taken == 1) {
      y4k_t_after_t += 1;
    } else {
      y4k_t_after_nt += 1;
    }
    y4k_last_taken = 1;
  } else {
    y4k_nottaken += 1;
    if (y4k_last_taken == 1) {
      y4k_nt_after_t += 1;
    } else {
      y4k_nt_after_nt += 1;
    }
    y4k_last_taken = 0;
  }	
};

//!Instruction bgez behavior method.
void ac_behavior( bgez )
{
  y4k_count_nosuperscalar_rdest_rsrc1(-1, rs);
  y4k_bgez += 1;
  dbg_printf("bgez r%d, %d\n", rs, imm & 0xFFFF);
  if( !(RB[rs] & 0x80000000) ){
#ifndef NO_NEED_PC_UPDATE
    npc = ac_pc + (imm<<2);
#endif 
    dbg_printf("Taken to %#x\n", ac_pc + (imm<<2));
    y4k_taken += 1;
    if (y4k_last_taken == 1) {
      y4k_t_after_t += 1;
    } else {
      y4k_t_after_nt += 1;
    }
    y4k_last_taken = 1;
  } else {
    y4k_nottaken += 1;
    if (y4k_last_taken == 1) {
      y4k_nt_after_t += 1;
    } else {
      y4k_nt_after_nt += 1;
    }
    y4k_last_taken = 0;
  }	
};

//!Instruction bltzal behavior method.
void ac_behavior( bltzal )
{
  y4k_count_nosuperscalar_rdest_rsrc1(-1, rs);
  y4k_bltzal += 1;
  dbg_printf("bltzal r%d, %d\n", rs, imm & 0xFFFF);
  RB[Ra] = ac_pc+4; //ac_pc is pc+4, we need pc+8
  if( RB[rs] & 0x80000000 ){
#ifndef NO_NEED_PC_UPDATE
    npc = ac_pc + (imm<<2);
#endif 
    dbg_printf("Taken to %#x\n", ac_pc + (imm<<2));
    y4k_taken += 1;
    if (y4k_last_taken == 1) {
      y4k_t_after_t += 1;
    } else {
      y4k_t_after_nt += 1;
    }
    y4k_last_taken = 1;
  } else {
    y4k_nottaken += 1;
    if (y4k_last_taken == 1) {
      y4k_nt_after_t += 1;
    } else {
      y4k_nt_after_nt += 1;
    }
    y4k_last_taken = 0;
  }
  dbg_printf("Return = %#x\n", ac_pc+4);
};

//!Instruction bgezal behavior method.
void ac_behavior( bgezal )
{
  y4k_count_nosuperscalar_rdest_rsrc1(-1, rs);
  dbg_printf("bgezal r%d, %d\n", rs, imm & 0xFFFF);
  RB[Ra] = ac_pc+4; //ac_pc is pc+4, we need pc+8
  if( !(RB[rs] & 0x80000000) ){
#ifndef NO_NEED_PC_UPDATE
    npc = ac_pc + (imm<<2);
#endif 
    dbg_printf("Taken to %#x\n", ac_pc + (imm<<2));
    y4k_taken += 1;
    if (y4k_last_taken == 1) {
      y4k_t_after_t += 1;
    } else {
      y4k_t_after_nt += 1;
    }
    y4k_last_taken = 1;
  } else {
    y4k_nottaken += 1;
    if (y4k_last_taken == 1) {
      y4k_nt_after_t += 1;
    } else {
      y4k_nt_after_nt += 1;
    }
    y4k_last_taken = 0;
  }	
  dbg_printf("Return = %#x\n", ac_pc+4);
};

//!Instruction sys_call behavior method.
void ac_behavior( sys_call )
{
  dbg_printf("syscall\n");
  stop();
}

//!Instruction instr_break behavior method.
void ac_behavior( instr_break )
{
  fprintf(stderr, "instr_break behavior not implemented.\n"); 
  exit(EXIT_FAILURE);
}
