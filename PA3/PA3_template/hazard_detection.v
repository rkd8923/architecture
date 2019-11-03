/*-----------------------------------------------------------------------------

4190.308-002 Computer Architecture

Instructor: Prof. Jae W. Lee (jaewlee@snu.ac.kr)

Homework #3: RISC-V Pipeline in Verilog

Description:
	Pipeline control signal generator

-----------------------------------------------------------------------------*/

module hazard_detection (
  // input MEM_WB_RW,
  // input MEM_WB_RD,
  // input EX_MEM_RW,
  input EX_MEM_RD,
  input ID_EX_RS1,
  // input ID_EX_RS2,
  output reg MEM_Hazard,
);

always @(MEM_WB_RW, MEM_WB_RD, EX_MEM_RW, EX_MEM_RD, ID_EX_RS1, ID_EX_RS2)begin
  if (EX_MEM_RD == ID_EX_RS1) begin
    MEM_Hazard <= 1'b0;
  end


end	
endmodule