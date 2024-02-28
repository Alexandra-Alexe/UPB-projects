`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/12/2023 09:12:43 AM
// Design Name: 
// Module Name: automat_cafea
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module automat_cafea(
input B1,B2,B3,clk,reset,
output reg ESB,EB1,EB2
    );
    
reg [2:0]state;
reg [2:0]next_state;

always @(posedge clk)
    if(reset)
        begin
        state<=3'b000;
        ESB<=0;
        EB1<=0;
        EB2<=0;
        end
     else
        state<=next_state;


always @(state or B1 or B2 or B3)
    case({state,B1,B2,B3})
        6'b000100:
            begin
                next_state=3'b001;
                ESB=0;
                EB1=0;
                EB2=0;
            end
       6'b000010:
            begin
                next_state=3'b010;
                ESB=0;
                EB1=0;
                EB2=0;
            end
       6'b000001:
            begin
                next_state=3'b011;
                ESB=0; 
                EB1=0;
                EB2=0;
            end
       6'b001100:
            begin
                next_state=3'b101;
                ESB=0;
                EB1=0;
                EB2=0;
            end
       6'b101100:
            begin
                next_state=3'b100;
                ESB=0;
                EB1=0;
                EB2=0;
            end
       6'b100000:
            begin
                next_state=3'b000;
                ESB=1;
                EB1=0;
                EB2=0;
            end
       6'b101000:
            begin
                next_state=3'b001;
                ESB=0;
                EB1=1;
                EB2=0;
            end
       6'b001000:
            begin
                next_state=3'b000;
                ESB=0;
                EB1=1;
                EB2=0;
            end
        6'b010000:
            begin
                next_state=3'b101;
                ESB=1;
                EB1=0;
                EB2=0;
            end
        6'b011000:
            begin
                next_state=3'b111;
                ESB=1;
                EB1=0;
                EB2=0;
            end
        6'b111000:
            begin
                next_state=3'b101;
                ESB=0;
                EB1=0;
                EB2=1;
            end
       default:
            begin
            next_state=3'b000; 
            ESB=0;
            EB1=0;
            EB2=0;
            end
      endcase
endmodule
