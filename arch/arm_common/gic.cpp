#include "gic.h"
#include "../../util/print.h"

//TODO: #ifdef check for arch
#include "../aarch64/intrinsics.h"


namespace ns_arm_common {

	Gic::Gic()
	{
		//default: no irq is avail
		for(int i=0; i<IRQ_MAX; i++) {
			m_irq_available[i] = false;
		}

		//get some basic information about the irq controller
		auto typer_val = mem_read<u32_t>(GIC_DIST_BASE+GICD_TYPER);
		m_line_numbers = (extract_bits(typer_val, 0, 4)+1);
		const u8_t cpu_number 	  = extract_bits(typer_val, 5, 7) + 1;
		m_security_extension = extract_bits(typer_val, 10, 10);

		ns_util::console("- GIC").nl();
		ns_util::console(" \\- typer_reg=%").arg_num(typer_val, num_format_e::HEX).nl();
		ns_util::console("  |- lines=%").arg_num(32 * m_line_numbers).nl();
		ns_util::console("  |- cpus=%").arg_num(cpu_number).nl();

		//probe which irq avail
		global_disable();
		ns_util::console(" \\- irqs available").nl();
		for(int iln=0; iln<m_line_numbers; iln++) {
			mem_write<u32_t>(GIC_DIST_BASE+GICD_ISENABLER(iln), 0xFFFFFFFF);
			const u32_t line_en_val = mem_read<u32_t>(GIC_DIST_BASE+GICD_ISENABLER(iln));

			for(int iBit=0; iBit<IRQ_PER_LINE; iBit++) {
				if( 0x1 & (line_en_val>>iBit) ) {
					m_irq_available[iln*IRQ_PER_LINE+iBit] = true;
				}
			}

			mem_write<u32_t>(GIC_DIST_BASE+GICD_ICENABLER(iln), 0xFFFFFFFF);
			const u32_t line_dis_val = mem_read<u32_t>(GIC_DIST_BASE+GICD_ICENABLER(iln));
			for(int iBit=0; iBit<IRQ_PER_LINE; iBit++) {
				if( 0x1 & (line_dis_val>>iBit) ) {
					m_irq_always_on[iln*IRQ_PER_LINE+iBit] = true;
				}
			}

			ns_util::console("  |- avail=%; always_on=%")
				.arg_num(line_en_val, num_format_e::HEX)
				.arg_num(line_dis_val, num_format_e::HEX).nl();
		}
	}

	void Gic::global_enable()
	{
		intr_irq_enable(true);

		if( m_security_extension ) {
			ns_util::console("Gic: security extensions not supported");
		}
		else {
			mem_write<u32_t>(GIC_DIST_BASE+GICD_CTLR, GICD_CTLR_ENABLEGRP0);
		}
	}

	void Gic::global_disable()
	{
		intr_irq_enable(false);
		mem_write<u32_t>(GIC_DIST_BASE+GICD_CTLR, 0);
	}

	void Gic::set_handler(int aIrqNum, std::function<void()> aHndler)
	{
		if( !check_irq_available(aIrqNum) )
			return;

		m_handler[aIrqNum] = aHndler;
	}

	void Gic::set_enabled(int aIrqNum, bool aEnable)
	{
		if( !check_irq_available(aIrqNum) )
			return;

		const size_t reg_n = aIrqNum / IRQ_PER_LINE;
		const size_t irq_bit = aIrqNum % IRQ_PER_LINE;
		const u32_t val = 0x1<<irq_bit;

		switch(aEnable) {
			case true: 	mem_write<u32_t>(GIC_DIST_BASE+GICD_ISENABLER(reg_n), val); break;
			case false: mem_write<u32_t>(GIC_DIST_BASE+GICD_ICENABLER(reg_n), val); break;
		}

	}

	bool Gic::check_irq_available(int aIrqNum)
	{
		if( aIrqNum > IRQ_MAX || !m_irq_available[aIrqNum] ) {
			ns_util::console("Error: irq % not avail").arg_num(aIrqNum);
			return false;
		}

		return true;
	}

}
