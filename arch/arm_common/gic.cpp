#include "gic.h"
#include "../../util/print.h"



namespace ns_arm_common {

	void gic_init()
	{
		auto typer_val = mem_read<u32_t>(GIC_DIST_BASE+GICD_TYPER);
		const u16_t it_line_number = 32 * (extract_bits(typer_val, 0, 4)+1);
		const u8_t cpu_number 	  = extract_bits(typer_val, 5, 7) + 1;

		ns_util::console("- GIC").nl();
		ns_util::console(" \\- typer_reg=%").arg_num(typer_val, num_format_e::HEX).nl();
		ns_util::console(" |- lines=%").arg_num(it_line_number).nl();
		ns_util::console(" |- cpus=%").arg_num(cpu_number).nl();

		for(size_t iIl=0; iIl<it_line_number; iIl++) {

		}
	}

}
