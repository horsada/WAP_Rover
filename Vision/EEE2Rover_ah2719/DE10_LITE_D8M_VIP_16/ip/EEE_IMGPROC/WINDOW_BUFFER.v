module WINDOW_BUFFER(
    clk,
    in_p0, in_p3, in_p6,
    out_p0, out_p1, out_p2, out_p3, out_p4, out_p5, out_p6, out_p7, out_p8
);

input clk;
input [23:0] in_p0, in_p3, in_p6;
output [23:0] out_p0, out_p1, out_p2, out_p3, out_p4, out_p5, out_p6, out_p7, out_p8;
/* TODO: FIX
always @(posedge clk) begin
	for(int i = 0; i < 3; i = i + 1) begin
		 for(int j = 0; j < 2; j = j + 1) begin
			  p[i][j+1] <= p[i][j];
		 end
		 p[i][0] <= wire_in_p[i];
	end
end
*/
endmodule

